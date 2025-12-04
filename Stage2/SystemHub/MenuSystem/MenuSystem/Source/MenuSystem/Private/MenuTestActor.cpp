#include "MenuTestActor.h"
#include "MenuSystemSubsystem.h"
#include "MenuTestWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AMenuTestActor::AMenuTestActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMenuTestActor::BeginPlay()
{
    Super::BeginPlay();

    if (!bAutoOpenMenu) return;

    UGameInstance* GI = GetGameInstance();
    if (!GI)
    {
        UE_LOG(LogTemp, Warning, TEXT("AMenuTestActor: GameInstance is null"));
        return;
    }

    UMenuSystemSubsystem* Subsys = GI->GetSubsystem<UMenuSystemSubsystem>();
    if (!Subsys)
    {
        UE_LOG(LogTemp, Warning, TEXT("AMenuTestActor: MenuSystemSubsystem not found"));
        return;
    }

    // 注册测试菜单描述
    FMenuDescriptor Desc;
    Desc.MenuId = FName("TestMenu");
    Desc.MenuType = EMenuType::Custom;
    Desc.WidgetClass = UMenuTestWidget::StaticClass();

    Subsys->RegisterMenu(Desc);

    // 打开菜单（通过子系统）
    UE_LOG(LogTemp, Log, TEXT("AMenuTestActor: Opening TestMenu via subsystem"));
    Subsys->OpenMenuById(FName("TestMenu"));

    // 可在此处设置延迟关闭测试或按键触发 CloseTopMenu 来验证 Close 路径
}