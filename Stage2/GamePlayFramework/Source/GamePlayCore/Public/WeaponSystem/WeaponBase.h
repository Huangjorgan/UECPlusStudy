#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

/**
 * 武器基类
 */
UCLASS()
class GAMEPLAYCORE_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:
	// 设置默认值
	AWeaponBase();

protected:

	// 武器名称
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	FString WeaponName;

	//武器伤害
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float Damage;

	// 武器射程
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float Range;

	// 武器射速
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float FireRate;

	// 武器弹夹容量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 MagazineSize;

	// 当前弹药数量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 CurrentAmmo;

	// 是否开火中
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Weapon")
	bool bIsFiring;

public:
	// 开火函数
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StartFire();

	// 停止开火函数
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StopFire();

	// 装弹函数
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Reload();

	// 执行一次开火逻辑
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void FireOnce();
};
