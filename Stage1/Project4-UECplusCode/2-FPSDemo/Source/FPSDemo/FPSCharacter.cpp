// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建第一人称摄像机组件
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	//将摄像机组件附加到胶囊体组件
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// 将摄像机置于略高于眼睛上方的位置
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// 启用Pawn控制摄像机旋转。
	FPSCameraComponent->bUsePawnControlRotation = true;

	// 为所属玩家创建第一人称网格体组件。
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));

	// 只有所属玩家可以看见此网格体。
	FPSMesh->SetOnlyOwnerSee(true);

	// 将FPS网格体附加到FPS摄像机。
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// 禁用某些环境阴影以便实现只有一个网格体的感觉。
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// 所属玩家看不到常规（第三人称）全身网格体。
	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);

	// 显示调试消息五秒。 
	// -1"键"值参数可以防止更新或刷新消息。
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("[FPSCharacter]"));

}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 设置"移动"绑定。
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	//设置"观看"绑定
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	//设置"操作"绑定
	PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released,this, &AFPSCharacter::StopJump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
}


void AFPSCharacter::MoveForward(float value)
{
	// 找出"前进"方向，并记录玩家想向该方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

void AFPSCharacter::MoveRight(float value)
{
	// 找出"右侧"方向，并记录玩家想向该方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}
void AFPSCharacter::Fire()
{
	//ProjectileClass 必须非空才能生成发射物
	if (!ProjectileClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("ProjectileClass is NULL!"));
		return;
	}

	// 获取摄像机变换
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	MuzzleOffset.Set(100.0f, 0.0f, 0.0f);
	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

	FRotator MuzzleRotation = CameraRotation;
	MuzzleRotation.Pitch += 10.0f;

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		AFPSProjectile* Projectile =
			World->SpawnActor<AFPSProjectile>(
				ProjectileClass,
				MuzzleLocation,
				MuzzleRotation,
				SpawnParams);

		if (Projectile)
		{
			Projectile->FireInDirection(MuzzleRotation.Vector());
		}
	}
}
