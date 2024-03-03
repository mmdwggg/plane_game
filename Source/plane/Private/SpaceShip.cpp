// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include "Bullet.h"
#include"Components/StaticMeshComponent.h"
#include"Components/SphereComponent.h"
#include"Camera/CameraComponent.h"
#include"GameFramework/PlayerController.h"
#include"Kismet/KismetMathLibrary.h"
#include"GameFramework/SpringArmComponent.h"
#include"Engine/World.h"
#include"TimerManager.h"
#include"Enemy.h"
#include"Kismet/GameplayStatics.h"
#include"Sound/SoundCue.h"
#include"Particles/ParticleSystemComponent.h"
#include"Particles/ParticleSystem.h"
// Sets default values
ASpaceShip::ASpaceShip()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//将碰撞检测绑定在组件上
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;
	//实例化飞机组件
	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipSM"));
	ShipSM->SetupAttachment(RootComponent);
	//弹簧臂绑定在根组件上
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	//摄像机实例化，绑定在弹簧臂上
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	//发射位置绑定在飞船上
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(ShipSM);
	//粒子系统绑定到根组件上
	ThrusterParticle= CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ThrusterParticle"));
	ThrusterParticle->SetupAttachment(RootComponent);

	Speed = 1000;
	TimeBetweenShow = 0.2f;
	bDead = false;
}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<APlayerController>(GetController());
	PC->bShowMouseCursor = true;
}

void ASpaceShip::LookAtCursor()
{
	//获取飞机位置等信息
	FVector MouseLocation, MouseDirection;
	PC->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	//获取飞机需要转向的角度，并且进行转向
	FVector TargetLocation = FVector(MouseLocation.X, MouseLocation.Y, GetActorLocation().Z);
	FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
	SetActorRotation(Rotator);
}

void ASpaceShip::MoveUP(float Value)
{
	if (Value != 0)
		bUpMove = true;
	else
		bUpMove = false;
	//AddMovementInput(FVector(1,0,0));
	AddMovementInput(FVector::ForwardVector, Value);
}

void ASpaceShip::MoveRight(float Value)
{
	if (Value != 0)
		bRightMove = true;
	else
		bRightMove = false;
	//AddMovementInput(FVector(0,1,0));
	AddMovementInput(FVector::RightVector, Value);
}

void ASpaceShip::Move(float DeltaTime)
{
	AddActorWorldOffset(ConsumeMovementInputVector() * Speed * DeltaTime, true);
}

void ASpaceShip::Fire()
{
	if (Bullet&&!bDead) {
		FActorSpawnParameters SpawnParams;
		//子弹在发射位置生成
		//动态加载Actor
		GetWorld()->SpawnActor<ABullet>(Bullet, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation(), SpawnParams);
		UGameplayStatics::PlaySoundAtLocation(this,ShootCue, GetActorLocation());
	}
}

void ASpaceShip::StartFire()
{
	GetWorldTimerManager().SetTimer(TimerHandle_BetweenShot, this, &ASpaceShip::Fire, TimeBetweenShow, true, 0);
}

void ASpaceShip::EndFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BetweenShot);
}

void ASpaceShip::RestartLevel()
{

	UGameplayStatics::OpenLevel(this,"MainMap");
}

void ASpaceShip::OnDeath()
{
	bDead = true;
	CollisionComp->SetVisibility(false,true);
	UGameplayStatics::PlaySoundAtLocation(this, GameOverCue, GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation(), FRotator::ZeroRotator, true);
	GetWorldTimerManager().SetTimer(TimerHandle_Restart, this, &ASpaceShip::RestartLevel, 2.0f,false);
}


// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bDead) {
		if (bUpMove || bRightMove)
			ThrusterParticle->Activate();
		else
			ThrusterParticle->Deactivate();
		LookAtCursor();
		Move(DeltaTime);
	}
	else {
		ThrusterParticle->Deactivate();
	}

}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveUp", this, &ASpaceShip::MoveUP);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpaceShip::MoveRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceShip::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASpaceShip::EndFire);
}

void ASpaceShip::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy) {
		Enemy->Destroy();
		OnDeath();
	}
}

bool ASpaceShip::GetBDead()
{
	return bDead ;
}

