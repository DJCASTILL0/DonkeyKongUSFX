#pragma once

#include "CoreMinimal.h"
#include "Enemies/EnemyBase.h"
#include "KritterCharacter.generated.h"

UCLASS()
class DKCCLONE_API AKritterCharacter : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Hacemos el override del Tick para controlar si se mueve o no
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	// Variable para decidir si este Kritter salta.
	// EditInstanceOnly nos permite cambiarla para cada Kritter individualmente en el nivel.
	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bDoesJump;

private:
	// El temporizador para el salto
	FTimerHandle JumpTimerHandle;

	// La función que se llamará para saltar
	void PerformJump();
};