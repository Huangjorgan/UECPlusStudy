// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeoutPageWidget.generated.h"

/**
 * 暂停页面界面
 */

class UButton;

UCLASS(Blueprintable,BlueprintType)
class UICORE_API UTimeoutPageWidget : public UUserWidget
{
	GENERATED_BODY()
	
//protected:
//	virtual bool Initialize() override;


//public:
//	// 在蓝图中绑定的按钮
//	UPROPERTY(meta = (BindWidget))
//	UButton* ResumeButton;
//	UPROPERTY(meta = (BindWidget))
//	UButton* SettingsButton;
//	UPROPERTY(meta = (BindWidget))
//	UButton* MainMenuButton;
};
