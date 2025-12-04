#include "MenuBaseWidget.h"

UMenuBaseWidget::UMenuBaseWidget(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    // 默认设置
}

// 默认 C++ 实现：调用蓝图事件或直接广播（这里保持空实现，以便蓝图覆盖）
void UMenuBaseWidget::OnMenuOpen_Implementation()
{
    // 默认行为：蓝图通常会实现动画并在动画完成时触发 OnMenuOpened.Broadcast()
}

void UMenuBaseWidget::OnMenuClose_Implementation()
{
    // 默认行为：蓝图通常会实现动画并在动画完成时触发 OnMenuClosed.Broadcast()
}

bool UMenuBaseWidget::OnMenuBack_Implementation()
{
    // 默认不消费返回，由系统处理（返回 false）
    return false;
}
