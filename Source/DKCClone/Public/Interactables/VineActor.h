#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VineActor.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;


UCLASS()
class DKCCLONE_API AVineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AVineActor();

protected:
	virtual void BeginPlay() override;
	// La cápsula que detectará la superposición con el jugador.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCapsuleComponent* OverlapCapsule;

	// El mesh para la apariencia visual de la liana.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* VineMesh;

public:	
	virtual void Tick(float DeltaTime) override;

};
