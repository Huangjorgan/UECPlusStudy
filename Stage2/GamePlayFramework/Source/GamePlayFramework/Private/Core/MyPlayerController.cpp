// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Core/MyStartGameMode.h"


void AMyPlayerController::Init()
{
	// 初始化相关逻辑
	// 创建暂停菜单UI实例
	if (!TimeoutMenuWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("TimeoutMenuWidgetClass is not set in MyPlayerController."));
		return;
	}
	if(!TimeoutMenuWidget && TimeoutMenuWidgetClass)
	{
		TimeoutMenuWidget = CreateWidget<UUserWidget>(this, TimeoutMenuWidgetClass);
		UE_LOG(LogTemp, Log, TEXT("TimeoutMenuWidget created."));
	}
	
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//获取当前游戏模式
	if(AGameModeBase* GM = UGameplayStatics::GetGameMode(this))
	{
		// 如果是 StartMenu 的 Gamemode，就直接返回
		if (GM->IsA(AMyStartGameMode::StaticClass()))
		{
			UE_LOG(LogTemp, Log, TEXT("Current GameMode is MyStartGameMode, skipping input bindings."));
			return;
		}
	}
	if (InputComponent)
	{
		InputComponent->BindAction("Timeout", IE_Pressed, this, &AMyPlayerController::ToggleTimeoutMenu);
		UE_LOG(LogTemp, Log, TEXT("Input binding for 'Timeout' action set up."));
	}
}

void AMyPlayerController::StartGame()
{
	//切换关卡到主游戏关卡
	UGameplayStatics::OpenLevel(this, FName("MyMap"));
	UE_LOG(LogTemp, Log, TEXT("Loading MyMap level."));
	// 恢复游戏模式输入
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	// 隐藏鼠标
	bShowMouseCursor = false;
}

void AMyPlayerController::Back2StartMenu()
{
	//切换关卡到主菜单关卡
	UGameplayStatics::OpenLevel(this, FName("MyStartMap"));
	UE_LOG(LogTemp, Log, TEXT("Loading MyStartMap level."));
	// 设置输入模式为 UI，鼠标可见
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(TimeoutMenuWidget->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	SetInputMode(InputMode);
	// 显示鼠标
	bShowMouseCursor = true;

	//UE_LOG(LogTemp, Log, TEXT("Back2StartMenu called, loading MyStartMap level."));
}

void AMyPlayerController::ToggleTimeoutMenu()
{
	UWorld* World = GetWorld();
	if (!World) return;

	UE_LOG(LogTemp, Log, TEXT("Toggling Timeout Menu. Current Pause State: %s"), World->IsPaused() ? TEXT("Unpaused") : TEXT("Paused"));
	// 使用世界的暂停状态来判断并切换
	if (World->IsPaused())
	{
		// 取消暂停
		SetPause(false);
		// 隐藏暂停菜单UI
		if (TimeoutMenuWidget)
		{
			// 恢复游戏模式输入
			FInputModeGameOnly InputMode;
			SetInputMode(InputMode);
			bShowMouseCursor = false;

			TimeoutMenuWidget->RemoveFromViewport();
		}
	}
	else
	{
		// 设置为暂停
		SetPause(true);

		// 显示暂停菜单UI
		if (TimeoutMenuWidget)
		{
			// 设置输入模式为 UI，鼠标可见
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(TimeoutMenuWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

			SetInputMode(InputMode);
			bShowMouseCursor = true;

			TimeoutMenuWidget->AddToViewport();
		}
	}
}
