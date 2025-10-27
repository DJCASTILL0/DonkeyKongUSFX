#pragma once

#include "CoreMinimal.h"
#include "Projectiles/ProjectileBase.h"
#include "CrownProjectile.generated.h"

UCLASS()
class DKCCLONE_API ACrownProjectile : public AProjectileBase
{
	GENERATED_BODY()

public:
	ACrownProjectile();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	// Variable para guardar el punto de inicio y saber a d�nde volver
	FVector StartLocation;

	// Distancia m�xima que recorrer� la corona antes de volver
	float MaxTravelDistance;

	// Bandera para saber si la corona est� volviendo
	bool bIsReturning;
};