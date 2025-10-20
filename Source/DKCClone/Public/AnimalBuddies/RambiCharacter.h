#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RambiCharacter.generated.h"
class USpringArmComponent;
class UCameraComponent;
UCLASS()
class DKCCLONE_API ARambiCharacter : public ACharacter
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
public:
	ARambiCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Mount(ACharacter* Rider);   // Función para que el jugador se monte en Rambi

private:
	UPROPERTY()
	ACharacter* OriginalRider;

	void MoveRight(float Value);	// Funciones para el movimiento de Rambi

};
