// PlayerStates/PlayerBaseState.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerBaseState.generated.h"

// Declaraci�n anticipada (Forward Declaration) para evitar dependencias circulares.
// Le decimos al compilador "conf�a en m�, esta clase existe" sin necesidad de incluir el .h completo.
class ADKCPlayerCharacter;

UCLASS(Blueprintable)
class DKCCLONE_API UPlayerBaseState : public UObject
{
	GENERATED_BODY()

public:
	// --- El Contrato del Patr�n de Estado ---

	// Funci�n que se llama al entrar en el estado. Tiene una implementaci�n base.
	virtual void OnEnter(ADKCPlayerCharacter* Player);
	virtual void HandleJumpInput(); // <-- A�ADE ESTA L�NEA paso 11
	virtual void HandleRollInput(); // <-- A�ADE ESTA L�NEA paso 12
	virtual void HandleMoveUpInput(float Value); // <-- A�ADE ESTA L�NEA paso 23 la liana
	virtual void HandleMoveRightInput(float Value);
	// Funciones virtuales puras. Obligan a las clases hijas a implementarlas.
	// Usamos la macro PURE_VIRTUAL de Unreal.

	virtual void TickState(float DeltaTime) PURE_VIRTUAL(UPlayerBaseState::TickState, );
	virtual void OnExit() PURE_VIRTUAL(UPlayerBaseState::OnExit, );

protected:
	// Referencia a nuestro personaje para que cada estado pueda controlarlo.
	// UPROPERTY() asegura que el recolector de basura de Unreal no lo borre por accidente.
	UPROPERTY()
	ADKCPlayerCharacter* PlayerCharacter;
};