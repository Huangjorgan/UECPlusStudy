#include "MenuTestWidget.h"
#include "Engine/Engine.h"

UMenuTestWidget::UMenuTestWidget(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    // Test widget 默认 ID（可被 Actor 覆盖）
    MenuId = FName("TestMenu_Cpp");
    MenuType = EMenuType::Custom;
}

void UMenuTestWidget::OnMenuOpen_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("UMenuTestWidget::OnMenuOpen_Implementation - %s"), *MenuId.ToString());

    // 立即广播已打开（模拟动画完成）
    OnMenuOpened.Broadcast();
}

void UMenuTestWidget::OnMenuClose_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("UMenuTestWidget::OnMenuClose_Implementation - %s"), *MenuId.ToString());

    // 从视口移除（确保 IsInViewport 返回 false）
    RemoveFromParent();

    // 立即广播已关闭（模拟动画完成）
    OnMenuClosed.Broadcast();
}

bool UMenuTestWidget::OnMenuBack_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("UMenuTestWidget::OnMenuBack_Implementation - %s (not consumed)"), *MenuId.ToString());
    // 返回 false 表示不消费 Back，交由 MenuManager 关闭栈顶菜单
    return false;
}