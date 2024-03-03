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
	//显示组件
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Component");
	UStaticMeshComponent* ShipSM;
	//碰撞检测组件
	UPROPERTY(VisibleAnywhere, Category = "Component");
	USphereComponent* CollisionComp;
	//爆炸粒子系统
	UPROPERTY(EditAnywhere, Category = "Particle");
	UParticleSystem* ExplosionParticle;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveTowardsPlayer(float DeltaTime);
	//在蓝图中实现代码
	UFUNCTION(BlueprintImplementableEvent)
	void SetColor();
	//爆炸特效
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnExplosion();
	float Speed = 300.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//分数计算函数
	void OnDeath();
};
