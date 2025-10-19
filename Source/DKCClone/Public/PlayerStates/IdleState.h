#include "CoreMinimal.h"
#include "PlayerStates/PlayerBaseState.h"
#include "IdleState.generated.h"

UCLASS()
class DKCCLONE_API UIdleState : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	// Sobrescribimos las funciones del contrato
	virtual void OnEnter(ADKCPlayerCharacter* Player) override; // <-- A�ADE ESTA L�NEA paso 10
	virtual void TickState(float DeltaTime) override;
	virtual void OnExit() override;
	virtual void HandleJumpInput() override;
	// Nota: No necesitamos sobrescribir OnEnter aqu�, porque la implementaci�n
	// de la clase base (que guarda la referencia al jugador) ya es suficiente para nosotros.
};