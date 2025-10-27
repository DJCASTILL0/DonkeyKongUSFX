// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnguardeCharacter.generated.h"

//pa las camaras propias
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class DKCCLONE_API AEnguardeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnguardeCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Montar(ACharacter* Jinete);

private:
	UPROPERTY()
	ACharacter* JineteOriginal;

	// Funciones para el movimiento de Enguarde
	void MoverArriba(float Valor);
	void MoverDerecha(float Valor);
	void Embestir();
};
