// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include"Components/SphereComponent.h"
#include"Components/StaticMeshComponent.h"
#include"Kismet/GameplayStatics.h"
#include"SpaceShip.h"
#include"Kismet/KismetMathLibrary.h"
#include"ShipGameMode.h"
#include"Particles/ParticleSystemComponent.h"
#include"Particles/ParticleSystem.h"
// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//����ײ�����������
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;
	//ʵ�����ɻ����
	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipSM"));
	ShipSM->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	//������Ƿɻ�
	Super::BeginPlay();
	SpaceShip = Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(this, 0));
	//���˷ɻ���ɫ
	SetColor();
	MySpaceShip = Cast<AShipGameMode>(UGameplayStatics::GetGameMode(this));
}
//�������Ƿɻ��ƶ�
void AEnemy::MoveTowardsPlayer(float DeltaTime)
{
	FVector Direction = (SpaceShip->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	AddActorWorldOffset(Direction*Speed* DeltaTime, true);
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), SpaceShip->GetActorLocation()));
}

void AEnemy::OnDeath()
{
	MySpaceShip->IncreaseScore();
	SpawnExplosion();
	Destroy();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!SpaceShip->GetBDead())
	MoveTowardsPlayer(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

