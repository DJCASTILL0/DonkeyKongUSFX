#pragma once

#include "CoreMinimal.h"
#include "PlayerStates/PlayerBaseState.h"
#include "ClimbingState.generated.h"

UCLASS()
class DKCCLONE_API UClimbingState : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	virtual void OnEnter(ADKCPlayerCharacter* Player) override;
	virtual void OnExit() override;

	// Sobrescribimos Tick y las funciones de input que nos interesan
	virtual void TickState(float DeltaTime) override;
	virtual void HandleJumpInput() override;
	virtual void HandleMoveUpInput(float Value) override;
};