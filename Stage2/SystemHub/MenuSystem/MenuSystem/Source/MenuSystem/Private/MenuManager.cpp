#include "MenuManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

UMenuManager::UMenuManager()
{
    // 构造时可以初始化必要内容
}

UMenuBaseWidget* UMenuManager::OpenMenu(const FMenuDescriptor& Descriptor, UWorld* World)
{
    if (!Descriptor.WidgetClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("MenuManager: WidgetClass is null for MenuId %s"), *Descriptor.MenuId.ToString());
        return nullptr;
    }

    if (!World)
    {
        UE_LOG(LogTemp, Warning, TEXT("MenuManager: World is null when opening menu %s"), *Descriptor.MenuId.ToString());
        return nullptr;
    }

    // 获取 PlayerController 作为 Owning Player
    APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
    if (!PC)
    {
        UE_LOG(LogTemp, Warning, TEXT("MenuManager: PlayerController not found for opening menu %s"), *Descriptor.MenuId.ToString());
        return nullptr;
    }

    // 创建 Widget（注意模板类必须继承自 UMenuBaseWidget）
    UMenuBaseWidget* Widget = CreateWidget<UMenuBaseWidget>(PC, Descriptor.WidgetClass);
    if (!Widget)
    {
        UE_LOG(LogTemp, Warning, TEXT("MenuManager: Failed to create widget for %s"), *Descriptor.MenuId.ToString());
        return nullptr;
    }

    // 设置基本属性（菜单 ID / 类型）
    Widget->MenuId = Descriptor.MenuId;
    Widget->MenuType = Descriptor.MenuType;

    // 将 Widget 添加到视口（使用较高 ZOrder 以保证在最上层）
    Widget->AddToViewport(100);

    // 禁用下面已存在的顶部菜单交互（若有）
    if (UMenuBaseWidget* Top = GetTopMenu())
    {
        if (Top != Widget)
        {
            Top->SetIsEnabled(false);
        }
    }

    // 绑定关闭事件（在蓝图动画完成后广播）
    Widget->OnMenuClosed.AddDynamic(this, &UMenuManager::HandleWidgetClosed);

    // 将其加入栈中
    MenuStack.Add(Widget);

    // 切换到 UI 输入模式
    EnterUIMode();

    // 调用 Widget 的打开逻辑（蓝图实现动画）
    Widget->OnMenuOpen();

    return Widget;
}

void UMenuManager::CloseTopMenu()
{
    if (MenuStack.Num() == 0) return;

    UMenuBaseWidget* Top = MenuStack.Last();
    if (!Top) 
    {
        MenuStack.Pop();
        return;
    }

    // 请求 Widget 执行关闭逻辑（蓝图应播放关闭动画并在完成时广播 OnMenuClosed）
    Top->OnMenuClose();
}

void UMenuManager::CloseAllMenus()
{
    // 从栈顶依次触发 Close，实际移除发生在 HandleWidgetClosed 回调中
    for (int32 i = MenuStack.Num() - 1; i >= 0; --i)
    {
        if (UMenuBaseWidget* W = MenuStack[i])
        {
            W->OnMenuClose();
        }
    }
}

UMenuBaseWidget* UMenuManager::GetTopMenu() const
{
    if (MenuStack.Num() == 0) return nullptr;
    return MenuStack.Last();
}

void UMenuManager::HandleWidgetClosed()
{
    // 当某个 Widget 的 OnMenuClosed 广播时，会触发此处。
    // 由于我们不知道是哪个 Widget 调用了，需要在栈中查找并移除最后一个已关闭的 Widget。

    // 这里做个简单策略：遍历栈并移除那些已经不在父级（已被 RemoveFromParent 的）或处于隐藏状态的。
    for (int32 i = MenuStack.Num() - 1; i >= 0; --i)
    {
        UMenuBaseWidget* W = MenuStack[i];
        if (!W)
        {
            MenuStack.RemoveAt(i);
            continue;
        }

        // 如果 Widget 已经没有父节点（通常意味着被 RemoveFromParent），则移除
        if (!W->IsInViewport())
        {
            MenuStack.RemoveAt(i);
        }
    }

    // 恢复新的栈顶交互（若存在）
    if (UMenuBaseWidget* NewTop = GetTopMenu())
    {
        NewTop->SetIsEnabled(true);
    }
    else
    {
        // 栈为空则退出 UI 模式
        ExitUIModeIfStackEmpty();
    }
}

void UMenuManager::EnterUIMode()
{
    if (!MenuStack.Num()) return;

    UWorld* World = nullptr;
    if (MenuStack.Num() > 0 && MenuStack.Last())
    {
        World = MenuStack.Last()->GetWorld();
    }
    if (!World) return;

    APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
    if (!PC) return;

    FInputModeUIOnly InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    PC->SetInputMode(InputMode);
    PC->bShowMouseCursor = true;
}

void UMenuManager::ExitUIModeIfStackEmpty()
{
    if (MenuStack.Num() != 0) return;

    // 恢复到 GameOnly
    // 通过获取世界与 PlayerController 执行恢复
    UWorld* World = nullptr;
    // 尝试通过 GEngine 获取第一个本地玩家控制器
    if (GEngine && GEngine->GetWorldContexts().Num() > 0)
    {
        World = GEngine->GetWorldContexts()[0].World();
    }
    if (!World) return;

    APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
    if (!PC) return;

    FInputModeGameOnly GameInput;
    PC->SetInputMode(GameInput);
    PC->bShowMouseCursor = false;
}
