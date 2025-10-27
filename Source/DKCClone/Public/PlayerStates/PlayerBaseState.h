// PlayerStates/PlayerBaseState.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerBaseState.generated.h"

// Declaración anticipada (Forward Declaration) para evitar dependencias circulares.
// Le decimos al compilador "confía en mí, esta clase existe" sin necesidad de incluir el .h completo.
class ADKCPlayerCharacter;

UCLASS(Blueprintable)
class DKCCLONE_API UPlayerBaseState : public UObject
{
	GENERATED_BODY()

public:
	// --- El Contrato del Patrón de Estado ---

	// Función que se llama al entrar en el estado. Tiene una implementación base.
	virtual void OnEnter(ADKCPlayerCharacter* Player);
	virtual void HandleJumpInput(); // <-- AÑADE ESTA LÍNEA paso 11
	virtual void HandleRollInput(); // <-- AÑADE ESTA LÍNEA paso 12
	virtual void HandleMoveUpInput(float Value); // <-- AÑADE ESTA LÍNEA paso 23 la liana
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