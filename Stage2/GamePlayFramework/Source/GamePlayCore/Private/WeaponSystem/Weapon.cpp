
#include "WeaponSystem/Weapon.h"

// 设置默认属性
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	// 设置默认值
	WeaponName = "Weapon";
	Damage = 25.0f;
	Range = 1000.0f;
	FireRate = 300.0f; // 每分钟600发
	MagazineSize = 40;
	CurrentAmmo = MagazineSize;
	bIsFiring = false;
}

