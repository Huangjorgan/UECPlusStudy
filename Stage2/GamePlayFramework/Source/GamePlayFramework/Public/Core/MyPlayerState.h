
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

 /**
  * 事件委托：
  * - FOnDamageReceived: 当收到伤害时广播（伤害数值，伤害来源Actor）
  * - FOnDeath: 当触发死亡时广播（没有参数）
  *
  * 使用 DYNAMIC 委托以便蓝图也可以绑定这些事件。
  */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageReceived, float, DamageAmount, AActor*, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);


/**
 * AMyPlayerState
 * 
 * 负责保存玩家的核心属性（Health, Stamina）并提供伤害入口 ApplyDamage。
 * 
 * 设计原则：
 * - 属性存放在 PlayerState（因为 PlayerState 在 Character 被销毁时会保留）
 */

UCLASS()
class GAMEPLAYFRAMEWORK_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AMyPlayerState();

protected:

	// 属性（状态值）
	
	// 当前生命值
	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	float Health;

	// 最大生命值
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float MaxHealth;

	// 当前耐力值
	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	float Stamina;

	// 最大耐力值
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float MaxStamina;

public:

	// 事件委托
	
	// 当收到伤害时广播
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDamageReceived OnDamageReceived;
	// 当触发死亡时广播
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeath OnDeath;
	
	virtual void BeginPlay() override;
	 
	// 伤害接口外部（武器/其他系统）调用此函数来对该 PlayerState 所属玩家造成伤害
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ApplyDamage(float DamageValue, AActor* DamageCauser);

	// Getter（BlueprintCallable 方便 UI 直接读取）
	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetHealth() const { return Health; }
	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetMaxHealth() const { return MaxHealth; }
	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetStamina() const { return Stamina; }
	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetMaxStamina() const { return MaxStamina; }
};
