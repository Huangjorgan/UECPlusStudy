// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Weapon.generated.h"

//武器实现类
UCLASS()
class GAMEPLAYCORE_API AWeapon : public AWeaponBase
{
	GENERATED_BODY()
	
public:	
	// 设置武器默认属性
	AWeapon();
};
