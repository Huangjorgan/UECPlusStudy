
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Core/MyPlayerState.h"
#include "WeaponSystem/WeaponComp.h"
#include "WeaponSystem/Weapon.h"
#include "MyCharacter.generated.h"

UCLASS()
class GAMEPLAYFRAMEWORK_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// 构造函数
	AMyCharacter();

protected:
	virtual void BeginPlay() override;

	// 死亡处理函数（绑定到 PlayerState 的 OnDeath）
	UFUNCTION()
	void HandleDeath();

	// 供内部使用的延迟销毁回调（在玩家死亡后调用以给动画时间）
	void FinishDeath();

	// 受击处理（绑定到 PlayerState 的 OnDamageReceived）
	UFUNCTION()
	void HandleDamageReceived(float DamageValue, AActor* DamageCauser);

	// 保存绑定用的 PlayerState 指针（方便解绑/访问）
	UPROPERTY()
	AMyPlayerState* CachedPlayerState;

public:	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 处理用于前后移动的输入。
	UFUNCTION()
	void MoveForward(float value);

	// 处理用于左右移动的输入。
	UFUNCTION()
	void MoveRight(float value);

	// 按下键时，设置跳跃标记。
	UFUNCTION()
	void StartJump();

	// 释放键时，清除跳跃标记。
	UFUNCTION()
	void StopJump();

	//按下键时，开火
	UFUNCTION()
	void StartFire();

	//释放键时，停止开火
	UFUNCTION()
	void StopFire();

	//摄像机
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* MyCameraComponent;

	//一人称网格体
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* FPSMesh;
	
	//武器组件
	UPROPERTY(VisibleAnywhere)
	UWeaponComp* MyWeaponComp;

};
