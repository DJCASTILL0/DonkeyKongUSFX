// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BarrelBase.generated.h"


class UPrimitiveComponent;
struct FHitResult;

UCLASS()
class DKCCLONE_API ABarrelBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ABarrelBase();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BarrelMesh;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBarrelHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	virtual void Tick(float DeltaTime) override;

};
