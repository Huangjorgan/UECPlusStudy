#include "MenuSystemSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UMenuSystemSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // 创建并持有 MenuManager 实例（由 Subsystem 管理生命周期）
    MenuManager = NewObject<UMenuManager>(this, UMenuManager::StaticClass());
    if (!MenuManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("MenuSystemSubsystem: Failed to create MenuManager instance.")); 
    }

    // 可在此处预注册某些默认菜单（若插件自带默认 Widget），示例留空
    // 例如：
    // FMenuDescriptor Desc;
    // Desc.MenuId = FName("Main");
    // Desc.WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Plugins/MenuSystem/DefaultWidgets/WBP_MainMenu.WBP_MainMenu_C"));
    // RegisterMenu(Desc);
}

void UMenuSystemSubsystem::Deinitialize()
{
    // 清理管理器（UObject 会由 GC 回收）
    if (MenuManager)
    {
        MenuManager->CloseAllMenus();
        MenuManager = nullptr;
    }

    Super::Deinitialize();
}

void UMenuSystemSubsystem::RegisterMenu(const FMenuDescriptor& Descriptor)
{
    if (Descriptor.MenuId == NAME_None)
    {
        UE_LOG(LogTemp, Warning, TEXT("MenuSystemSubsystem: Attempt to register menu with empty MenuId.")); 
        return;
    }

    RegisteredMenus.Add(Descriptor.MenuId, Descriptor);
}

void UMenuSystemSubsystem::OpenMenuById(FName MenuId)
{
    if (!MenuManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("MenuSystemSubsystem: MenuManager is null.")); 
        return;
    }

    if (!RegisteredMenus.Contains(MenuId))
    {
        UE_LOG(LogTemp, Warning, TEXT("MenuSystemSubsystem: MenuId %s not registered."), *MenuId.ToString());
        return;
    }

    FMenuDescriptor Desc = RegisteredMenus[MenuId];
    UWorld* World = GetWorld();
    MenuManager->OpenMenu(Desc, World);
}

void UMenuSystemSubsystem::CloseTopMenu()
{
    if (MenuManager)
    {
        MenuManager->CloseTopMenu();
    }
}

void UMenuSystemSubsystem::CloseAllMenus()
{
    if (MenuManager)
    {
        MenuManager->CloseAllMenus();
    }
}

void UMenuSystemSubsystem::HandleBackPressed()
{
    if (!MenuManager) return;

    UMenuBaseWidget* Top = MenuManager->GetTopMenu();
    if (!Top) return;

    bool bConsumed = Top->OnMenuBack();
    if (!bConsumed)
    {
        MenuManager->CloseTopMenu();
    }
}

UMenuBaseWidget* UMenuSystemSubsystem::GetTopMenu() const
{
    if (!MenuManager) return nullptr;
    return MenuManager->GetTopMenu();
}
