// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MyStartGameMode.h"
#include "Core/MyPlayerController.h"

AMyStartGameMode::AMyStartGameMode()
{
	// 设置默认PlayerController类为我们的自定义PlayerController
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
