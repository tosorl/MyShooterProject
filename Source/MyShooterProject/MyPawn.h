// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawnMovementComponent.h"
#include "MyPawn.generated.h"

UCLASS()
class MYSHOOTERPROJECT_API AMyPawn : public APawn
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	/*UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;*/
	UPROPERTY(Category = Gameplay, EditAnywhere)
	class UMyPawnMovementComponent* MyMovementComponent;

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	FVector GunOffset;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	bool Alive;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	bool Invincible;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	bool EnterFiringYet;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	bool LockFiring;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRateMulti;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float Damage;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		bool Ghosting;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float GhostingDur;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

private:
	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Fire();

	void MoveForward(float value);
	void MoveRight(float value);
};
