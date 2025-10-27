#include "Projectiles/CrownProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACrownProjectile::ACrownProjectile()
{
	// Activamos el Tick para poder controlar el movimiento de retorno
	PrimaryActorTick.bCanEverTick = true;

	MaxTravelDistance = 1000.f; // 10 metros de alcance
	bIsReturning = false;

	// La corona no debe ser afectada por la gravedad
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void ACrownProjectile::BeginPlay()
{
	Super::BeginPlay();
	// Guardamos la ubicación inicial al ser disparada
	StartLocation = GetActorLocation();
}

void ACrownProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Si la corona no está volviendo...
	if (!bIsReturning)
	{
		// ...calculamos la distancia que ha recorrido.
		float DistanceTraveled = FVector::Dist(StartLocation, GetActorLocation());

		// Si ha superado la distancia máxima...
		if (DistanceTraveled >= MaxTravelDistance)
		{
			// ...activamos el modo de retorno e invertimos su velocidad.
			bIsReturning = true;
			ProjectileMovement->Velocity *= -1.f;
		}
	}
	else // Si ya está volviendo...
	{
		// ...calculamos la distancia al punto de origen.
		float DistanceToStart = FVector::Dist(StartLocation, GetActorLocation());

		// Si está muy cerca del origen, la destruimos.
		if (DistanceToStart < 100.f)
		{
			Destroy();
		}
	}
}