
#include "Characters/MyCharacter.h"


AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建第一人称摄像机组件
	MyCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(MyCameraComponent != nullptr);
	//将摄像机组件附加到胶囊体组件
	MyCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	// 将摄像机置于略高于眼睛上方的位置
	MyCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// 启用Pawn控制摄像机旋转。
	MyCameraComponent->bUsePawnControlRotation = true;

	// 创建武器组件。
	MyWeaponComp = CreateDefaultSubobject<UWeaponComp>(TEXT("WeaponComp"));
	check(MyWeaponComp != nullptr);
	// 设置武器组件的拥有者为此角色。
	MyWeaponComp->SetOwnerActor(this);

	//// 为所属玩家创建第一人称网格体组件。
	//FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	//// 只有所属玩家可以看见此网格体。
	//FPSMesh->SetOnlyOwnerSee(true);
	//// 将FPS网格体附加到FPS摄像机。
	//FPSMesh->SetupAttachment(FPSCameraComponent);
	//// 禁用某些环境阴影以便实现只有一个网格体的感觉。
	//FPSMesh->bCastDynamicShadow = false;
	//FPSMesh->CastShadow = false;

	// 所属玩家看不到常规（第三人称）全身网格体。
	//GetMesh()->SetOwnerNoSee(true);
}


void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 确保 PlayerController 存在
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	// 获取并缓存 PlayerState
	AMyPlayerState* PS = GetPlayerState<AMyPlayerState>();
	if(PS)
	{
		CachedPlayerState = PS;

		//绑定死亡事件
		PS->OnDeath.AddDynamic(this, &AMyCharacter::HandleDeath);

		//绑定受击事件
		PS->OnDamageReceived.AddDynamic(this, &AMyCharacter::HandleDamageReceived);
	}
}

// 绑定输入映射C
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 设置"移动"绑定。
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	//设置"观看"绑定
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);

	//设置"操作"绑定
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJump);

	//设置"开火"绑定
	PlayerInputComponent->BindAction("Fire", IE_Pressed, MyWeaponComp, &UWeaponComp::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, MyWeaponComp, &UWeaponComp::StopFire);
}

void AMyCharacter::MoveForward(float value)
{
	// 找出"前进"方向，并记录玩家想向该方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}
void AMyCharacter::MoveRight(float value)
{
	// 找出"右侧"方向，并记录玩家想向该方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}
void AMyCharacter::StartJump()
{
	bPressedJump = true;
}
void AMyCharacter::StopJump()
{
	bPressedJump = false;
}
void AMyCharacter::StartFire()
{
	if(MyWeaponComp)
	{
		MyWeaponComp->StartFire();
	}
}
void AMyCharacter::StopFire()
{
	if(MyWeaponComp)
	{
		MyWeaponComp->StopFire();
	}
}

// 死亡处理函数
void AMyCharacter::HandleDeath()
{
	// 此函数会在绑定的 OnDeath 广播时被调用（OnDeath 在服务器上触发）
	UE_LOG(LogTemp, Warning, TEXT("Character %s has died."), *GetName());
}

// 受击处理函数
void AMyCharacter::HandleDamageReceived(float DamageValue, AActor* DamageCauser)
{
	// 这里是表现层：播放受击动画/粒子/音效等（客户端可根据需要播放）
	UE_LOG(LogTemp, Warning, TEXT("Character %s received %.2f damage from %s."), *GetName(), DamageValue, *GetNameSafe(DamageCauser));
}
void AMyCharacter::FinishDeath()
{
	// 延迟销毁角色
	/*Destroy();*/
}
