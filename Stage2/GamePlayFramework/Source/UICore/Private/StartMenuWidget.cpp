// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuWidget.h"
#include "Components/Button.h"
#include "Core/MyPlayerController.h"

bool UStartMenuWidget::Initialize()
{
	if (!Super::Initialize()) return false;
	
	// 绑定按钮点击事件
	if (StartButton)
		StartButton->OnClicked.AddDynamic(this, &UStartMenuWidget::OnStartButtonClicked);
	if (SettingsButton)
		SettingsButton->OnClicked.AddDynamic(this, &UStartMenuWidget::OnSettingsButtonClicked);
	if (QuitButton)
		QuitButton->OnClicked.AddDynamic(this, &UStartMenuWidget::OnQuitButtonClicked);

	return true;
}

void UStartMenuWidget::OnStartButtonClicked()
{
	// 移除自己
	RemoveFromParent();
	//// 可选：切换输入模式回游戏模式
	//if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	//{
	//	PC->SetInputMode(FInputModeGameOnly());
	//	PC->bShowMouseCursor = false;
	//}
	// 
	// 处理 Start Button 被点击的逻辑
	// 切换关卡
	if(APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		AMyPlayerController* MyPC = Cast<AMyPlayerController>(PC);
		if (MyPC)
		{
			MyPC->StartGame();
		}
	}
}

void UStartMenuWidget::OnSettingsButtonClicked()
{
	// 处理 Settings Button 被点击的逻辑
	// 打开设置菜单
	UE_LOG(LogTemp, Log, TEXT("Settings Button Clicked"));
}

void UStartMenuWidget::OnQuitButtonClicked()
{
	// 处理 Quit Button 被点击的逻辑
	// 退出游戏
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->ConsoleCommand("quit");
	}
}