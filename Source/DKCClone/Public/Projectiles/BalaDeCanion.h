// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BalaDeCanion.generated.h"
class UStaticMeshComponent;
class UProjectileMovementComponent;
UCLASS()
class DKCCLONE_API ABalaDeCanion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABalaDeCanion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MallaProyectil;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovimientoProyectil;

	UFUNCTION()
	void AlGolpear(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
