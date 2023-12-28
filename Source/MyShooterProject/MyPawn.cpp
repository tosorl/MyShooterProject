// Fill out your copyright notice in the Description page of Project Settings.

#include "UObject/ConstructorHelpers.h"
#include "MyShooterProjectProjectile.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);

	// Create a camera boom...
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	//CameraBoom->TargetArmLength = 1200.f;
	//CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	//CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	//CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	//CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MyMovementComponent = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("CustomMovementComponent"));
	MyMovementComponent->UpdatedComponent = RootComponent;

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
		
	}*/

}

UPawnMovementComponent* AMyPawn::GetMovementComponent() const 
{ 
	return MyMovementComponent; 
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPawn::MoveRight);
	/*PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);*/
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyPawn::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMyPawn::StopFire);

}
void AMyPawn::StartFire() {
	LockFiring = true;
	Fire();
}
void AMyPawn::StopFire() {
	LockFiring = false;
}
//사용하는 무기의 종류 변화 고려
// 상태 패턴으로 무기 다양화 고려
//타이머 갱신으로 연사 방식 구현, 타이머에 해당되는 코드는 별도의 함수로 분리
void AMyPawn::Fire() {	
	const FRotator FireRotation = GetActorForwardVector().Rotation();
	// Spawn projectile at an offset from this pawn
	const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
	//연사 확인
	//발사 버튼 홀드 -> 연사, 버튼 오프 -> 연사 해제
	// 타이머 사용 필요
	if (LockFiring) {
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMyPawn::Fire, FireRate, false);
	}
	else {
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ShotTimerExpired);
	}
	// spawn the projectile
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		
		World->SpawnActor<AMyShooterProjectProjectile>(SpawnLocation, FireRotation);
	}
	
}

void AMyPawn::MoveForward(float value) {
	if (MyMovementComponent && (MyMovementComponent->UpdatedComponent == RootComponent))
	{
		MyMovementComponent->AddInputVector(GetActorForwardVector() * value);
	}
}

void AMyPawn::MoveRight(float value) {
	if (MyMovementComponent && (MyMovementComponent->UpdatedComponent == RootComponent))
	{
		MyMovementComponent->AddInputVector(GetActorRightVector() * value);
	}
}