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
	//����ͼ�п���
	UPROPERTY(VisibleAnywhere, Category = "Component");
	//��ʾ���
	UStaticMeshComponent* ShipSM;
	//��ײ������
	UPROPERTY(VisibleAnywhere, Category = "Component");
	USphereComponent* CollisionComp;
	//����ͷ
	UPROPERTY(VisibleAnywhere, Category = "Component");
	UCameraComponent* CameraComp;
	//��ʾ���
	APlayerController* PC;

	//�����ӵ��޶��ӵ�����ΪABullet��������
	UPROPERTY(EditAnywhere, Category = "Fire");
	TSubclassOf<ABullet> Bullet;
	//�����ӵ�����λ��
	UPROPERTY(VisibleAnywhere, Category = "Component");
	USceneComponent* SpawnPoint;
	//����һ�����ɱ�ʹ����ͷ����ת
	UPROPERTY(VisibleAnywhere, Category = "Component");
	USpringArmComponent* SpringArmComp;

	FTimerHandle TimerHandle_BetweenShot;
	FTimerHandle TimerHandle_Restart;
	//�ٶ�
	UPROPERTY(EditAnywhere, Category = "Move");
	float Speed;
	//������
	UPROPERTY(EditAnywhere, Category = "Fire");
	float TimeBetweenShow;
	bool bDead;
	//���Ǳ�ը����
	UPROPERTY(EditAnywhere, Category = "Sound");
	USoundCue* GameOverCue;
	//�����Ч
	UPROPERTY(EditAnywhere, Category = "Sound");
	USoundCue* ShootCue;

	//β������ϵͳ
	UPROPERTY(VisibleAnywhere, Category = "Component");
	UParticleSystemComponent* ThrusterParticle;
	//��ը����ϵͳ
	UPROPERTY(EditAnywhere, Category = "Particle");
	UParticleSystem* ExplosionParticle;
	//�жϷɴ��Ƿ��ƶ�
	bool bUpMove;
	bool bRightMove;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//���ָ��Ϊ�ɻ�����
	void LookAtCursor();
	void MoveUP(float Value);
	void MoveRight(float Value);
	void  Move(float DeltaTime);
	void  Fire();
	void StartFire();
	void EndFire();
	//���ֿ�ʼ�ؿ�
	void RestartLevel();
	void OnDeath();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//������ײ��
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	bool GetBDead();
};
