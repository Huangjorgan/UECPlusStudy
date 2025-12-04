# 菜单系统

## 目标
构建一个标准化，可拓展，可复用的菜单系统。
包括主菜单，暂停菜单，*设置菜单*等等。


## 概览（架构与职责）
UMenuSystemSubsystem（GameInstanceSubsystem）
•	外部门面（facade），负责注册菜单描述（RegisteredMenus）并持有 UMenuManager 实例。生命周期与 GameInstance 同步，适合跨地图持久管理。
•	公开蓝图/代码接口：RegisterMenu、OpenMenuById、CloseTopMenu、CloseAllMenus、HandleBackPressed、GetTopMenu。

UMenuManager（UObject）
•	真正管理菜单栈的实现者：维护 MenuStack（TArray<UMenuBaseWidget*>），实现 OpenMenu / CloseTopMenu / CloseAllMenus / GetTopMenu。由 Subsystem 使用 NewObject 创建并作为其子对象托管生命周期。

UMenuBaseWidget（UUserWidget 基类）
•	菜单 Widget 的 C++ 基类。定义菜单 ID、类型、并提供 BlueprintNativeEvent：OnMenuOpen、OnMenuClose、OnMenuBack。并暴露两个动态 multicast 委托 OnMenuOpened、OnMenuClosed 供蓝图在动画完成时广播。

测试用例（UMenuTestWidget / AMenuTestActor）
•	UMenuTestWidget 直接在 Open/Close 时立即广播事件，可在不依赖 UMG 动画下测试流程。AMenuTestActor 在 BeginPlay 注册并打开菜单，便于快速验证。

## 典型交互流程（打开/关闭/回退）
1.	注册：Subsystem::RegisterMenu 存储 FMenuDescriptor（MenuId, WidgetClass, MenuType）。
2.	打开：SubsystemOpenMenuById 查表获取 FMenuDescriptor -> MenuManagerOpenMenu(Descriptor, World)
•	校验 Descriptor.WidgetClass 和 World。
•	使用 CreateWidget< UMenuBaseWidget >(PC, Descriptor.WidgetClass) 创建 Widget（OwningPlayer 为 PlayerController）。
•	设置 Widget->MenuId/ MenuType。
•	Widget->AddToViewport(100)（所有菜单默认 ZOrder=100，保证可见但可能互相覆盖）。
•	若已有栈顶菜单，调用 Top->SetIsEnabled(false) 禁用其交互。
•	绑定关闭委托：Widget->OnMenuClosed.AddDynamic(this, &UMenuManager::HandleWidgetClosed)。
•	MenuStack.Add(Widget)；调用 EnterUIMode()；调用 Widget->OnMenuOpen()（蓝图可播放动画并在动画结束时广播 OnMenuOpened）。
3.	关闭栈顶：MenuManager::CloseTopMenu 调用 Top->OnMenuClose()（蓝图应播放关闭动画并在结束时广播 OnMenuClosed）。
4.	关闭完成回调：当 Widget 广播 OnMenuClosed，绑定的 UMenuManager::HandleWidgetClosed 被调用。当前实现策略：
•	遍历 MenuStack（从后向前），移除所有 !IsInViewport() 的项（或 nullptr）。
•	重新启用新的栈顶项 SetIsEnabled(true)（若存在）；若栈为空则调用 ExitUIModeIfStackEmpty 恢复游戏输入模式。

## 输入模式与鼠标
•	EnterUIMode(): 取得 PlayerController -> 设置 FInputModeUIOnly（DoNotLock），PC->bShowMouseCursor = true。
•	ExitUIModeIfStackEmpty(): 若 MenuStack 为空，尝试通过 GEngine->GetWorldContexts()[0].World() 获取 World -> 获取 PlayerController -> 设置 FInputModeGameOnly 并隐藏鼠标。
•	要点：输入切换发生在游戏线程、对第 0 个本地玩家生效。多玩家或分屏需扩展。

## 内存 / 生命周期 / GC
•	Subsystem 用 NewObject<UMenuManager>(this, …) 创建 Manager，Outer 为 Subsystem，生命周期由 Subsystem 管控（Subsystem 成员用 UPROPERTY 保持引用）。
•	MenuStack 使用 UPROPERTY() TArray<UMenuBaseWidget*>，保证 GC 不回收已打开的 Widget。
•	CreateWidget 的返回值若只有 AddToViewport 但没有保存引用，会被 GC 收回；因此 MenuStack 保存引用是必要的。
•	RemoveFromParent() + OnMenuClosed.Broadcast() 是关闭流程里移除视图并使 IsInViewport 返回 false，从而在 HandleWidgetClosed 中被移除栈。

## 事件、委托与绑定策略
•	UMenuBaseWidget 使用 DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMenuEvent)（无参数）。因此 UMenuManager::HandleWidgetClosed 必须是 UFUNCTION() 且签名无参（当前实现满足）。
•	现有实现为“全局回扫”策略：任意一个 Widget 广播 OnMenuClosed 时，Manager 遍历栈检测所有不在视口的 Widget 并移除。优点：简单；缺点：不能精确识别是哪个 Widget 触发事件，若需要可改为在委托中传递发送者（DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam）并绑定成员接收参数以直接移除目标项。
•	建议改进：使用 AddUniqueDynamic、在移除时 Unbind 委托、或使用 TWeakObjectPtr 以避免悬挂引用。

## 并发/时序/边界情况
•	多个菜单同时触发关闭（例如多个动画同时广播）：当前实现会遍历并移除所有不在视口项，通常可处理，但若逻辑依赖于顺序（例如链式关闭触发新菜单打开），需谨慎。
•	ZOrder 固定为 100：若希望层级按打开顺序递增，建议使用递增 ZOrder（或 Slate 层级管理）。
•	当 PlayerController 丢失或 World 为 null 时 OpenMenu/EnterUIMode 会失败并打印警告——在关卡切换或非本地环境下需健壮性检测。
•	多玩家场景：当前实现总使用 GetPlayerController(World, 0)；若需要支撑本地分屏或网络玩家，需要按 PlayerState/LocalPlayer 指定 OwningPlayer。

## 资源改进建议（可选）
•	将 OnMenuClosed 委托改为带参数（发送者），消除全局回扫：
•	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMenuEventWithSender, UMenuBaseWidget*, Sender);
•	在 MenuManager 中维护 TArray<TWeakObjectPtr<UMenuBaseWidget>> 或同时使用 RemoveAt 并 Unbind 委托。
•	在 OpenMenu 时设置不同 ZOrder（如 BaseZ + MenuStack.Num()）以保证打开顺序。
•	支持模式窗口（modal）或阻塞输入层（遮罩）时添加遮罩 Widget、控制点击穿透与 input priority。
•	提供事件/接口通知注册者某菜单打开/关闭（便于外部逻辑）。

## 调试与验证步骤（快速）
•	在以下函数处设断点并运行 Play：MenuManagerOpenMenu、MenuManagerHandleWidgetClosed、MenuManagerEnterUIMode、MenuManagerExitUIModeIfStackEmpty、MenuSystemSubsystem::OpenMenuById。
•	使用 UMenuTestWidget（已在工程中）验证：它在 Open/Close 时立即广播，便于观察栈变化与输入模式切换。
•	在编辑器执行 Build Solution，把 AMenuTestActor 放入关卡并 Play。观察 Output 面板日志（或 UE_LOG）。
•	要模拟 Back 键：在合适处调用 UMenuSystemSubsystem::HandleBackPressed（或把该调用绑定到 PlayerController 的输入事件），观察是否调用 Top->OnMenuBack 返回值及后续 CloseTopMenu。

## 结论（核心要点）
•	Subsystem = 外观（持久化），MenuManager = 栈与视图管理，MenuBaseWidget = 可在蓝图中实现动画和广播的生命周期钩子。
•	当前实现以 UObject + UPROPERTY 保证生命周期，以动态多播委托解耦动画完成信号，以输入模式切换保证 UI 交互。
•	若要更精确、更健壮，优先改进委托签名（传 sender）、ZOrder 管理、对多玩家/分屏的 OwningPlayer 支持，以及在绑定/解绑上更小心以避免内存泄露或重复绑定。