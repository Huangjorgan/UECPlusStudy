
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponBase.h"
#include "WeaponComp.generated.h"

/*
* 武器组件类
* 用于管理角色的武器和操作
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYCORE_API UWeaponComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// 构造函数
	UWeaponComp();

protected:
	// 当前武器
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AWeaponBase* CurrentWeapon;

	// 武器的附着点socket名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName WeaponSocketName;

	// 武器的类型(默认武器)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<AWeaponBase> DefaultWeaponClass;

	// 拥有该组件的Actor
	UPROPERTY()
	AActor* OwnerActor;

public:	

	// 生成并装备默认武器
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SpawnAndEquipDefaultWeapon();

	// 武器开火(调用该武器的StartFire)
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StartFire();

	// 武器停止开火(调用该武器的StopFire)
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StopFire();

	// 设置拥有该武器的角色
	void SetOwnerActor(AActor* NewOwner);
};
