// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"
class UProjectileMovementComponent;
class AEnemySpawner;
UCLASS()
class PLANE_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

protected:
	//显示子弹组件
	UPROPERTY(VisibleAnywhere, Category = "Component");
	UStaticMeshComponent* BulletSM;
	//根组件
	UPROPERTY(VisibleAnywhere, Category = "Component");
	USceneComponent* RootComp;
	//抛射运动组件
	UPROPERTY(VisibleAnywhere, Category = "Component");
	UProjectileMovementComponent* ProjectileMovementComp;
	//获取敌人生成器用于计算死亡敌人数
	AEnemySpawner* EnemySpawner;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//射击敌人
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
