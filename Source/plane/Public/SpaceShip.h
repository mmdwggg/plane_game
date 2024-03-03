// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShip.generated.h"

class USphereComponent;
class UCameraComponent;
class USpringArmComponent;
class ABullet;
class USoundCue;
UCLASS()
class PLANE_API ASpaceShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShip();

protected:
	//在蓝图中看到
	UPROPERTY(VisibleAnywhere, Category = "Component");
	//显示组件
	UStaticMeshComponent* ShipSM;
	//碰撞检测组件
	UPROPERTY(VisibleAnywhere, Category = "Component");
	USphereComponent* CollisionComp;
	//摄像头
	UPROPERTY(VisibleAnywhere, Category = "Component");
	UCameraComponent* CameraComp;
	//显示鼠标
	APlayerController* PC;

	//声明子弹限定子弹类型为ABullet和其子类
	UPROPERTY(EditAnywhere, Category = "Fire");
	TSubclassOf<ABullet> Bullet;
	//声明子弹发射位置
	UPROPERTY(VisibleAnywhere, Category = "Component");
	USceneComponent* SpawnPoint;
	//声明一个弹簧臂使摄像头不旋转
	UPROPERTY(VisibleAnywhere, Category = "Component");
	USpringArmComponent* SpringArmComp;

	FTimerHandle TimerHandle_BetweenShot;
	FTimerHandle TimerHandle_Restart;
	//速度
	UPROPERTY(EditAnywhere, Category = "Move");
	float Speed;
	//发射间隔
	UPROPERTY(EditAnywhere, Category = "Fire");
	float TimeBetweenShow;
	bool bDead;
	//主角爆炸声音
	UPROPERTY(EditAnywhere, Category = "Sound");
	USoundCue* GameOverCue;
	//射击音效
	UPROPERTY(EditAnywhere, Category = "Sound");
	USoundCue* ShootCue;

	//尾气粒子系统
	UPROPERTY(VisibleAnywhere, Category = "Component");
	UParticleSystemComponent* ThrusterParticle;
	//爆炸粒子系统
	UPROPERTY(EditAnywhere, Category = "Particle");
	UParticleSystem* ExplosionParticle;
	//判断飞船是否移动
	bool bUpMove;
	bool bRightMove;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//鼠标指向为飞机朝向
	void LookAtCursor();
	void MoveUP(float Value);
	void MoveRight(float Value);
	void  Move(float DeltaTime);
	void  Fire();
	void StartFire();
	void EndFire();
	//重现开始关卡
	void RestartLevel();
	void OnDeath();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//被敌人撞到
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	bool GetBDead();
};
