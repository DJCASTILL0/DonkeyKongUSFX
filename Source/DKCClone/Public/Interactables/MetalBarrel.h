
#pragma once

#include "CoreMinimal.h"
#include "Interactables/BarrelBase.h"
#include "MetalBarrel.generated.h"

UCLASS()
class DKCCLONE_API AMetalBarrel : public ABarrelBase
{
	GENERATED_BODY()

protected:
	// Sobrescribimos la función OnBarrelHit de la clase padre.
	virtual void OnBarrelHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};