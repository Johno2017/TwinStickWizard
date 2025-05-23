// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMagicCharacter.h"
#include "BaseWeapon.h"
#include "BaseBullet.h"

// Sets default values
ABaseMagicCharacter::ABaseMagicCharacter()
{
	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet Spawn Point"));
	SpawnLocation->SetupAttachment(GetMesh());

}

// Called when the game starts or when spawned
void ABaseMagicCharacter::BeginPlay()
{
	Super::BeginPlay();

	ABaseWeapon* WeaponPtr = Cast<ABaseWeapon>(Weapon->GetChildActor());
	if (WeaponPtr) {
		WeaponPtr->SetPlayerPointer(this);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Weapon not found."));
	}
}

float ABaseMagicCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HP -= DamageAmount;
	if (HP <= 0) {
		Destroy();
	}
	return DamageAmount;
}

void ABaseMagicCharacter::SetCanFire(bool Value)
{
	uCanFire = Value;
}

void ABaseMagicCharacter::ToggleShooting()
{
	uIsShooting = !uIsShooting;
}

void ABaseMagicCharacter::SetMovementRotation(FVector RotValue)
{
	MovementRot = RotValue.Rotation();
}

FVector ABaseMagicCharacter::CalculateMovementBlending()
{
	FVector movement = MovementRot.Vector();
	FVector shooting = ShootRot.Vector();

	float DotProd = FVector::DotProduct(movement, shooting);

	FVector BlendVector = movement - shooting * DotProd;

	FVector OutputVector = FVector(DotProd, BlendVector.Length(), 0);

	return OutputVector * 100;
}

AActor* ABaseMagicCharacter::ShootBullet(FVector Direction)
{

	ShootRot = Direction.Rotation();
	AActor* Bullet = nullptr;

	if (uCanFire) {
		uCanFire = false;

		FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ABaseMagicCharacter::SetCanFire, true);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, TimeBetweenFires, false);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;
		AActor* SpawnedActor = GetWorld()->SpawnActor<ABaseBullet>(
			BulletToSpawn,
			SpawnLocation->GetComponentLocation(),
			GetActorRotation(),
			SpawnParams);
		Bullet = SpawnedActor;
	}

	SetActorRotation(Direction.Rotation());

	return Bullet;
}

// Called every frame
void ABaseMagicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator currentOrientation;
	if (uIsShooting)
	{
		currentOrientation = ShootRot;
	}
	else
	{
		currentOrientation = MovementRot;
	}
	
	SetActorRotation(currentOrientation);

}

// Called to bind functionality to input
void ABaseMagicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

