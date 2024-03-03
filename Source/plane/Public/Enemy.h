// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

class USphereComponent;
class ASpaceShip;
class AShipGameMode;
UCLASS()
class PLANE_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:
	AShipGameMode* MySpaceShip;
	ASpaceShip* SpaceShip;
	//��ʾ���
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Component");
	UStaticMeshComponent* ShipSM;
	//��ײ������
	UPROPERTY(VisibleAnywhere, Category = "Component");
	USphereComponent* CollisionComp;
	//��ը����ϵͳ
	UPROPERTY(EditAnywhere, Category = "Particle");
	UParticleSystem* ExplosionParticle;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveTowardsPlayer(float DeltaTime);
	//����ͼ��ʵ�ִ���
	UFUNCTION(BlueprintImplementableEvent)
	void SetColor();
	//��ը��Ч
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnExplosion();
	float Speed = 300.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//�������㺯��
	void OnDeath();
};
