#include "Projectiles/ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "DKCPlayerCharacter.h" 
#include "Components/HealthComponent.h" 

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Creamos el mesh. Usaremos una esfera como coco temporal.
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	// Asignamos una forma visual del Starter Content.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereMesh.Succeeded())
	{
		ProjectileMesh->SetStaticMesh(SphereMesh.Object);
	}
	// Suscribimos nuestra función OnHit al evento de colisión del mesh.
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

	// Creamos el componente de movimiento de proyectiles.
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	// Configuramos el movimiento.
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 1000.f;
	ProjectileMovement->bRotationFollowsVelocity = true; // El mesh rota en la dirección del movimiento.
	ProjectileMovement->bShouldBounce = false; // No queremos que rebote.
	ProjectileMovement->ProjectileGravityScale = 3.0f; //gravedad del coco
	// Hacemos que el proyectil se destruya automáticamente después de 3 segundos si no choca con nada.
	InitialLifeSpan = 3.f;
}


void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Intentamos convertir el actor con el que chocamos a un jugador.
	ADKCPlayerCharacter* Player = Cast<ADKCPlayerCharacter>(OtherActor);
	if (Player)
	{
		// Si es el jugador, le aplicamos daño.
		UHealthComponent* PlayerHealth = Player->GetHealthComponent();
		if (PlayerHealth)
		{
			PlayerHealth->TakeDamage(1.f);
		}
	}
	Destroy();
}