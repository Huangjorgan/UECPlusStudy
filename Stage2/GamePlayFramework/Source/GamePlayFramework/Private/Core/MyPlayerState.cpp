
#include "Core/MyPlayerState.h"

AMyPlayerState::AMyPlayerState()
{
	// 初始化属性值
	MaxHealth = 100.0f;
	Health = MaxHealth;
	MaxStamina = 100.0f;
	Stamina = MaxStamina;
}

void AMyPlayerState::BeginPlay()
{
	Super::BeginPlay();

	//确保属性被正确初始化
	if(HasAuthority())
	{
		Health = MaxHealth;
		Stamina = MaxStamina;
	}
}

//ApplyDamage 的实现
void AMyPlayerState::ApplyDamage(float DamageValue, AActor* DamageCauser)
{
	
	//合法性检查
	if(DamageValue <= 0.0f )
	{
		//非正数伤害无效
		return;
	}

	//扣血
	const float OldHealth = Health;
	Health -= DamageValue;

	Health = FMath::Clamp(Health, 0.0f, MaxHealth);//确保血量在合理范围内

	//广播伤害事件
	OnDamageReceived.Broadcast(DamageValue, DamageCauser);

	//死亡判定
	if(Health <= 0.0f && OldHealth > 0.0f)
	{
		//// Health 从正变为 0 或以下 → 触发死亡事件
		OnDeath.Broadcast();
	}
}

