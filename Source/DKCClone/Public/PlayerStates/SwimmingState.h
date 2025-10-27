#pragma once

#include "CoreMinimal.h"
#include "PlayerStates/PlayerBaseState.h"
#include "SwimmingState.generated.h"

UCLASS()
class DKCCLONE_API USwimmingState : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	virtual void OnEnter(ADKCPlayerCharacter* Player) override;
	virtual void OnExit() override;
	virtual void TickState(float DeltaTime) override;
	virtual void HandleMoveUpInput(float Value) override;
	virtual void HandleMoveRightInput(float Value) override; // Usaremos la misma función, pero con lógica diferente
};