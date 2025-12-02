// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingPageItemBase.generated.h"

/**
 * 
 */
UCLASS(Abstract,Blueprintable)
class UICORE_API USettingPageItemBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 提供一个虚函数，让子类根据需要覆盖它
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void ApplySetting();// 点击“应用”按钮时触发

	virtual void ApplySetting_Implementation();


};
