// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KongLetter.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DKCCLONE_API AKongLetter : public AActor
{
	GENERATED_BODY()
	
public:	
	AKongLetter();

protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* OverlapSphere;

	// Componente para mostrar la malla de la letra en el mundo
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LetterMesh; // <-- CAMBIADO de LetterText a LetterMesh

	// La letra que este actor representa. La configuraremos en el editor.
	UPROPERTY(EditInstanceOnly, Category = "Configuracion")
	FName Letra;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	virtual void Tick(float DeltaTime) override;

};
