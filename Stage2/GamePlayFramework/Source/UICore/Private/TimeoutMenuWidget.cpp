// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeoutMenuWidget.h"
#include "Components/Button.h"
#include "Core/MyPlayerController.h"

bool UTimeoutMenuWidget::Initialize()
{
	if (!Super::Initialize()) return false;
	
	// 绑定按钮点击事件
	if (ResumeButton)
		ResumeButton->OnClicked.AddDynamic(this, &UTimeoutMenuWidget::OnResumeButtonClicked);
	if (SettingsButton)
		SettingsButton->OnClicked.AddDynamic(this, &UTimeoutMenuWidget::OnSettingsButtonClicked);
	if (MainMenuButton)
		MainMenuButton->OnClicked.AddDynamic(this, &UTimeoutMenuWidget::OnMainMenuButtonClicked);
	
	return true;
}

void UTimeoutMenuWidget::OnResumeButtonClicked()
{
	// 返回游戏
	// 处理 Resume Button 被点击的逻辑
	

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (IWidgetPCInterface* MyPCInterface = Cast<IWidgetPCInterface>(PC))
		{
			MyPCInterface->ToggleTimeoutMenu();
		}
	}

	////设置游戏模式为游戏中
	//UGameplayStatics::SetGamePaused(this, false);
}

void UTimeoutMenuWidget::OnSettingsButtonClicked()
{
	// 处理 Setting Button 被点击的逻辑
	// 打开设置菜单
	UE_LOG(LogTemp, Log, TEXT("Setting Button Clicked"));
}

void UTimeoutMenuWidget::OnMainMenuButtonClicked()
{
	// 处理 Main Menu Button 被点击的逻辑
	// 返回主菜单	
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (IWidgetPCInterface* MyPCInterface = Cast<IWidgetPCInterface>(PC))
		{
			MyPCInterface->Back2StartMenu();
		}
	}
}