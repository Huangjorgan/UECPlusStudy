// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeoutMenuWidget.generated.h"

/**
 * 暂停菜单界面
 */
class UButton;

UCLASS(Blueprintable,BlueprintType)
class UICORE_API UTimeoutMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;

	// 绑定到 Resume Button 的回调
	UFUNCTION()
	void OnResumeButtonClicked();
	// 绑定到 Setting Button 的回调
	UFUNCTION()
	void OnSettingsButtonClicked();
	// 绑定到 Main Menu Button 的回调
	UFUNCTION()
	void OnMainMenuButtonClicked();

public:
	// 在蓝图中绑定的按钮
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;
};
