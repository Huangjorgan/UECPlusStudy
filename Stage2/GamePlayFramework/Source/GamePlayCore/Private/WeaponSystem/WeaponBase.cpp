
#include "WeaponSystem/WeaponBase.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// 设置默认值
	WeaponName = "DefaultWeapon";
	Damage = 24.0f;
	Range = 1000.0f;
	FireRate = 600.0f; // 每分钟600发
	MagazineSize = 30;
	CurrentAmmo = MagazineSize;
	bIsFiring = false;
}

void AWeaponBase::StartFire()
{
	//如果要做全自动或者连发，则在此处多次调用FireOnce()，并使用定时器控制射速
	if (CurrentAmmo > 0 && !bIsFiring)
	{
		bIsFiring = true;
		// 实现开火逻辑，例如生成子弹、播放音效等
		// 这里可以添加定时器来控制射速
		FireOnce();
	}
	else if(CurrentAmmo <= 0)
	{
		StopFire();
		// 弹药耗尽，不能开火
	}
}

void AWeaponBase::StopFire()
{
	bIsFiring = false;
	UE_LOG(LogTemp, Warning, TEXT("[%s] stopped firing."), *WeaponName);
	// 停止开火逻辑，例如停止音效等
}

void AWeaponBase::Reload()
{
	CurrentAmmo = MagazineSize;//装满弹夹
	UE_LOG(LogTemp, Warning, TEXT("[%s] reloaded. Current Ammo: [%d]"), *WeaponName, CurrentAmmo);
	// 实现装弹逻辑，例如播放装弹动画等
}
  
void AWeaponBase::FireOnce()
{
	//单次开火逻辑
	CurrentAmmo--;
	// 这里可以添加射线检测、生成子弹等逻辑
}