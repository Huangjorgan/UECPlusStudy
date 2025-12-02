// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MyGameMode.h"
#include "Characters/MyCharacter.h"
#include "Core/MyPlayerController.h"
#include "Core/MyGameStateBase.h"
#include "Core/MyHUD.h"


AMyGameMode::AMyGameMode()
{
	// 设置子蓝图类为默认Pawn类
	DefaultPawnClass = AMyCharacter::StaticClass();

	// 设置默认PlayerController类为我们的自定义PlayerController
	PlayerControllerClass = AMyPlayerController::StaticClass();

	// 设置默认HUD类为我们的自定义HUD
	HUDClass = AMyHUD::StaticClass();

	// 设置默认GameState类为我们的自定义GameState
	GameStateClass = AMyGameStateBase::StaticClass();

}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();
	// 在游戏开始时执行的自定义逻辑

	AMyPlayerController* MyPC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (MyPC)
	{
		//玩家控制器初始化
		MyPC->Init();
	}
}