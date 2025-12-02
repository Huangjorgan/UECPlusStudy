#include "FPSProjectile.h"

// 设置默认值
AFPSProjectile::AFPSProjectile()
{
    // 将此actor设置为每帧调用Tick()。  如果不需要此特性，可以关闭以提升性能。
    PrimaryActorTick.bCanEverTick = true;

    // 3 秒后删除发射物。
    InitialLifeSpan = 3.0f;

    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Fire"));

    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
    }

    if (!CollisionComponent)
    {
        // 用球体进行简单的碰撞展示。
        CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
        //// 将球体的碰撞配置文件名称设置为"Projectile"。
        //CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
        //// 组件击中某物时调用的事件。
        //CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
        // 设置球体的碰撞半径。
        CollisionComponent->InitSphereRadius(15.0f);
        // 将根组件设置为碰撞组件。
        RootComponent = CollisionComponent;
    }

    if (!ProjectileMovementComponent)
    {
        // 使用此组件驱动发射物的移动。
        ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
        ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
        ProjectileMovementComponent->InitialSpeed = 3000.0f;
        ProjectileMovementComponent->MaxSpeed = 3000.0f;
        ProjectileMovementComponent->bRotationFollowsVelocity = true;
        ProjectileMovementComponent->bShouldBounce = true;
        ProjectileMovementComponent->Bounciness = 0.3f;
        ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
    }

    if (!ProjectileMeshComponent)
    {
        ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
        static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Soccer_ball/soccer_ball.soccer_ball'"));
        if (Mesh.Succeeded())
        {
            ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
        }

        //static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/SphereMaterial.SphereMaterial'"));
        //if (Material.Succeeded())
        //{
        //    ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
        //}
        //ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
        ProjectileMeshComponent->SetupAttachment(RootComponent);
    }

}

// 当游戏开始或重生（Spawn）时被调用
void AFPSProjectile::BeginPlay()
{
    Super::BeginPlay();

}

// 每一帧都被调用
void AFPSProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// 初始化射击方向上发射物速度的函数。
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

//void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
//{
//    if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
//    {
//        OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
//    }
//
//    Destroy();
//}