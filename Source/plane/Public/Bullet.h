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
	//��ʾ�ӵ����
	UPROPERTY(VisibleAnywhere, Category = "Component");
	UStaticMeshComponent* BulletSM;
	//�����
	UPROPERTY(VisibleAnywhere, Category = "Component");
	USceneComponent* RootComp;
	//�����˶����
	UPROPERTY(VisibleAnywhere, Category = "Component");
	UProjectileMovementComponent* ProjectileMovementComp;
	//��ȡ�������������ڼ�������������
	AEnemySpawner* EnemySpawner;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//�������
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
