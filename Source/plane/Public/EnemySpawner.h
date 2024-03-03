// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AEnemy;
class UBoxComponent;
class ASpaceShip;
UCLASS()
class PLANE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:

	ASpaceShip* SpaceShip;
	//���е���
	UPROPERTY(EditAnywhere, Category = "Enemy");
	TSubclassOf<AEnemy> Enemy;
	//�������ɵĺ���
	UPROPERTY(VisibleAnywhere, Category = "Component");
	UBoxComponent* SpawnArea;
	FTimerHandle TimerHandle_Spawn;
	float MinimunDistanceToPlayer = 1200.0f;
	//���ɵ��˼��
	float SpawnInterval;
	//��ǰ��������������������
	UPROPERTY(EditAnywhere, Category = "Spawn");
	int MaxEnemyNum;
	int CurrentEnemyCount;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector GetGenerateLocation();
	void SpawnEnemy();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void DecreaseEnemyCount();
};
