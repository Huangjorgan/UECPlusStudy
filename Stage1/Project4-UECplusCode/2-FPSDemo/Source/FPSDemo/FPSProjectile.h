#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FPSProjectile.generated.h"

UCLASS()
class FPSDEMO_API AFPSProjectile : public AActor
{
    GENERATED_BODY()

public:
    // 为此Actor的属性设置默认值
    AFPSProjectile();

protected:
    // 当游戏开始或重生（Spawn）时被调用
    virtual void BeginPlay() override;

public:
    // 每一帧都被调用
    virtual void Tick(float DeltaTime) override;

    // 初始化射击方向上发射物速度的函数。
    void FireInDirection(const FVector& ShootDirection);

    // 当发射物击中物体时会调用的函数。
 /*   UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComponent,FVector NormalImpulse,const FHitResult& Hit);*/

    // 球体碰撞组件
    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    USphereComponent* CollisionComponent;

    // 发射物移动组件
    UPROPERTY(VisibleAnywhere, Category = Movement)
    UProjectileMovementComponent* ProjectileMovementComponent;

    // 发射物网格体
    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    UStaticMeshComponent* ProjectileMeshComponent;

    //// 发射物材质
    //UPROPERTY(VisibleDefaultsOnly, Category = Movement)
    //UMaterialInstanceDynamic* ProjectileMaterialInstance;
    

};