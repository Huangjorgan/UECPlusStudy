
#include "WeaponSystem/WeaponComp.h"

// 设置默认值
UWeaponComp::UWeaponComp()
{
	PrimaryComponentTick.bCanEverTick = false;

	//武器的附着点socket名称(武器插槽)
	WeaponSocketName = TEXT("WeaponSocket");
	//默认武器为AWeapon
	DefaultWeaponClass = nullptr;
	CurrentWeapon = nullptr;
}
/*
Pseudocode (详细构建计划):
1. 检查 DefaultWeaponClass 是否有效（避免尝试生成一个空的类）。
2. 获取当前组件的拥有者（Owner），如果没有拥有者则直接返回。
3. 构造 FActorSpawnParameters，并把 Owner 赋给 SpawnParams.Owner（保证新生成的武器知道它的拥有者，这对权限/网络/生命周期管理很重要）。
4. 调用 World->SpawnActor< AWeaponBase >(DefaultWeaponClass, SpawnParams) 来实际生成武器实例。
5. 如果生成成功（CurrentWeapon 非空），则将武器附加到拥有者的指定 Socket（WeaponSocketName）上：
   - 使用 FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true)：
     * SnapToTarget 会使武器的位置/旋转/缩放与目标 Socket 完全一致（快速对齐）。
     * 第二个参数 true 表示尝试将物理模拟的刚体焊接到一起（WeldSimulatedBodies），用于物理效果一致性（在需要物理合并时有用，但在某些情况下可能不需要或不可取）。
   - 使用 AttachToComponent 将武器附加到 Owner 的根组件（RootComponent）上并指定 Socket 名称。
6. 结束（不返回值）。
*/

// 设置默认武器并装备到角色指定的 socket 上
void UWeaponComp::SpawnAndEquipDefaultWeapon()
{
	//// 1. 确保有默认武器类：如果没有配置 DefaultWeaponClass，则不执行生成逻辑
	//if (DefaultWeaponClass)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("WeaponComp is spawning default weapon of class: %s"), *DefaultWeaponClass->GetName());
	//	// 2. 获取拥有该组件的 Actor
	//	if (OwnerActor)
	//	{
	//		//Spawn武器
	//		AWeaponBase* NewWeapon = GetWorld()->SpawnActor<AWeaponBase>(DefaultWeaponClass);

	//		// 5. 如果生成成功，则进行附加操作以完成“装备”流程	
	//		if (NewWeapon)
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("WeaponComp successfully spawned weapon: %s"), *CurrentWeapon->GetName());

	//			// 关键：把 OwnerCharacter 传给武器
	//			NewWeapon->SetOwnerActor(OwnerActor);

	//			CurrentWeapon = NewWeapon;
	//		}

	//			
	//	}
	//	// 若 Owner 为空，则说明组件未正确附着到 Actor 上，无法生成属于该 Actor 的武器
	//	UE_LOG(LogTemp, Warning, TEXT("WeaponComp has no valid Owner to spawn weapon for."));
	//}
	//// 若 DefaultWeaponClass 为空，则直接跳过生成（可能意味着该角色无默认武器）
}

void UWeaponComp::StartFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StartFire();
	}
}

void UWeaponComp::StopFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
	}
}

void UWeaponComp::SetOwnerActor(AActor* NewOwner)
{
	OwnerActor = NewOwner;
}