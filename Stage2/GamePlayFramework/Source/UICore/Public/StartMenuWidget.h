// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuWidget.generated.h"

/**
 * 开始界面 Widget
 */

class UButton;

UCLASS(Blueprintable,BlueprintType)
class UICORE_API UStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	virtual bool Initialize() override;

	// 绑定到 Start Button 的回调
	UFUNCTION()
	void OnStartButtonClicked();
	// 绑定到 Settings Button 的回调
	UFUNCTION()
	void OnSettingsButtonClicked();
	// 绑定到 Quit Button 的回调
	UFUNCTION()
	void OnQuitButtonClicked();

public:
	// 在蓝图中绑定的按钮
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
};
