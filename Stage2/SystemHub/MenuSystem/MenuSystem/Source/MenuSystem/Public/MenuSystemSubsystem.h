#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MenuTypes.h"
#include "MenuManager.h"
#include "MenuSystemSubsystem.generated.h"

/**
 * UMenuSystemSubsystem
 *
 * 插件对外暴露的子系统接口。作为 GameInstanceSubsystem，它会在 GameInstance 初始化时创建，
 * 并在整个运行时跨地图持久存在，适合管理全局菜单系统。
 *
 * 提供 Register / Open / Close 等蓝图/代码可调用接口。
 */
UCLASS()
class MENUSYSTEM_API UMenuSystemSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /** 在运行时注册一个菜单描述（通常在初始化时通过蓝图或代码注册） */
    UFUNCTION(BlueprintCallable, Category="Menu")
    void RegisterMenu(const FMenuDescriptor& Descriptor);

    /** 通过 MenuId 打开菜单（如果注册过则创建） */
    UFUNCTION(BlueprintCallable, Category="Menu")
    void OpenMenuById(FName MenuId);

    /** 关闭当前栈顶菜单 */
    UFUNCTION(BlueprintCallable, Category="Menu")
    void CloseTopMenu();

    /** 关闭所有菜单 */
    UFUNCTION(BlueprintCallable, Category="Menu")
    void CloseAllMenus();

    /** 处理返回键（Back）事件：调用栈顶 Widget 的 OnMenuBack，若未消费则 CloseTopMenu */
    UFUNCTION(BlueprintCallable, Category="Menu")
    void HandleBackPressed();

    /** 获取当前顶部菜单，供外部查询 */
    UFUNCTION(BlueprintCallable, Category="Menu")
    UMenuBaseWidget* GetTopMenu() const;

protected:
    /** 菜单描述 Map：MenuId -> Descriptor */
    UPROPERTY()
    TMap<FName, FMenuDescriptor> RegisteredMenus;

    /** 菜单管理器实例（托管生命周期） */
    UPROPERTY()
    UMenuManager* MenuManager;
};
