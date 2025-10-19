#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CannonBarrel.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UArrowComponent;
class USceneComponent;

UCLASS()
class DKCCLONE_API ACannonBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	ACannonBarrel();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* BarrelMesh;

	// La zona que activará el lanzamiento
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* OverlapSphere;

	// Una flecha visible solo en el editor para saber a dónde apunta el cañón
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UArrowComponent* LaunchArrow;

	// Esta es la velocidad que le daremos al jugador.
	// EditInstanceOnly nos permite cambiarla para cada barril individualmente en el nivel.
	UPROPERTY(EditInstanceOnly, Category = "Cannon")
	FVector LaunchVelocity;

	// Función que se llamará cuando el jugador entre en la zona de activación.
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	virtual void Tick(float DeltaTime) override;

};
