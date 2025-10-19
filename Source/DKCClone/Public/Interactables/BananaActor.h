#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BananaActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DKCCLONE_API ABananaActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABananaActor();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* OverlapSphere;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BananaMesh;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	

public:	
	virtual void Tick(float DeltaTime) override;

};
