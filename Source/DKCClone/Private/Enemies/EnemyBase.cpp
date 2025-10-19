#include "Enemies/EnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "DKCCloneGameMode.h"
#include "Components/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Hacemos la cápsula de colisión del enemigo un poco más pequeña que la del jugador
	GetCapsuleComponent()->SetCapsuleHalfHeight(60.f);
	GetCapsuleComponent()->SetCapsuleRadius(40.f);

	// Ajustamos la posición del Mesh para que encaje bien dentro de la cápsula
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -60.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	// Suscribimos nuestra función OnHit al evento de colisión de la cápsula.
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemyBase::OnHit);

	// Dirección inicial del movimiento (hacia la derecha en el eje Y).
	MovementDirection = FVector(0.f, 1.f, 0.f);

	// Hacemos que la rotación del personaje se oriente automáticamente a la dirección de movimiento.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	// Establecemos una velocidad de movimiento por defecto.
	GetCharacterMovement()->MaxWalkSpeed = 150.f;

}


// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	ADKCCloneGameMode* GameMode = Cast<ADKCCloneGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->AddEnemyToArray(this);
	}
	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddDynamic(this, &AEnemyBase::OnDeath);
	}
}


void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddMovementInput(MovementDirection);
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Lógica para des-registrarse:
	ADKCCloneGameMode* GameMode = Cast<ADKCCloneGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->RemoveEnemyFromArray(this);
	}
}

void AEnemyBase::OnDeath()
{
	// Cuando morimos, simplemente nos destruimos.
	Destroy();
}

void AEnemyBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Si chocamos con algo y no es el jugador, invertimos la dirección.
	if (OtherActor && OtherActor != this && OtherActor != GetOwner())
	{
		MovementDirection *= -1.f; // Invertimos el vector (ej: de (0,1,0) a (0,-1,0))
	}
}