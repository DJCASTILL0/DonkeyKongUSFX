#include "Projectiles/BalaDeCanion.h" // Corregido
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DKCPlayerCharacter.h"
#include "Components/HealthComponent.h"


ABalaDeCanion::ABalaDeCanion() // Corregido
{
	PrimaryActorTick.bCanEverTick = false;

	MallaProyectil = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaProyectil"));
	RootComponent = MallaProyectil;
	MallaProyectil->OnComponentHit.AddDynamic(this, &ABalaDeCanion::AlGolpear);

	MovimientoProyectil = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovimientoProyectil"));
	MovimientoProyectil->InitialSpeed = 1000.f;
	MovimientoProyectil->MaxSpeed = 1000.f;
	MovimientoProyectil->ProjectileGravityScale = 0.5f;
	InitialLifeSpan = 5.0f;
}

// Called when the game starts or when spawned
void ABalaDeCanion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABalaDeCanion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABalaDeCanion::AlGolpear(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) // Corregido
{
	ADKCPlayerCharacter* Jugador = Cast<ADKCPlayerCharacter>(OtherActor);
	if (Jugador)
	{
		if (Jugador->GetHealthComponent())
		{
			Jugador->GetHealthComponent()->TakeDamage(1.0f);
		}
	}
	Destroy();
}