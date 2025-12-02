#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Interface/IWidgetPCInterface.h"
#include "MyPlayerController.generated.h"

/**
 * 此PlayerController类管理玩家输入和UI交互
 * 全局使用该PlayerController
 */

class UUserWidget;

UCLASS()
class GAMEPLAYFRAMEWORK_API AMyPlayerController : public APlayerController, public IWidgetPCInterface
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;
	// 切换暂停菜单的显示与隐藏
	virtual void ToggleTimeoutMenu() override;
	// 返回主菜单，加载主菜单关卡
	virtual void Back2StartMenu() override;


	// 相关逻辑的初始化
	UFUNCTION()
	void Init();

	// 开始游戏，加载主关卡
	UFUNCTION(BlueprintCallable)
	void StartGame();
	

	// 暂停菜单的UI类
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> TimeoutMenuWidgetClass;

private:
	// 暂停菜单的UI实例
	UPROPERTY()
	UUserWidget* TimeoutMenuWidget;

	bool bIsTimeoutMenuInitialized = false;
};
