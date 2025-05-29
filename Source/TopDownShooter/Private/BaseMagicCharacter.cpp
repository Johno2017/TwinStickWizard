// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMagicCharacter.h"
#include "BaseWeapon.h"
#include "BaseBullet.h"

// Sets default values
ABaseMagicCharacter::ABaseMagicCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!Weapon) {
		Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
		Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
	}

	if (!BulletSpawnLocation) {
		BulletSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet Spawn Point"));
		BulletSpawnLocation->SetupAttachment(GetMesh());
	}
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

void ABaseMagicCharacter::Fire(FVector Direction)
{
	ShootRot = Direction.Rotation();
	SetActorRotation(ShootRot);

	if (uCanFire) {

		uCanFire = false;

		UWorld* World = GetWorld();
		
		if (World)
		{
			FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ABaseMagicCharacter::SetCanFire, true);
			FTimerHandle TimerHandle;
			World->GetTimerManager().SetTimer(TimerHandle, Delegate, TimeBetweenFires, false);

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle.
			ABaseBullet* Projectile = World->SpawnActor<ABaseBullet>(ProjectileClass, BulletSpawnLocation->GetComponentLocation(), GetActorRotation(), SpawnParams);
			if (Projectile)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = Direction;
				Projectile->FireInDirection(LaunchDirection);
			}
		}	
	}
}

// Called every frame
void ABaseMagicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator currentOrientation = FRotator::ZeroRotator;

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

