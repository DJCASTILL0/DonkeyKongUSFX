// Public/PlayerStates/WalkingState.h

#pragma once

#include "CoreMinimal.h"
#include "PlayerStates/PlayerBaseState.h"
#include "WalkingState.generated.h"

UCLASS()
class DKCCLONE_API UWalkingState : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	virtual void OnEnter(ADKCPlayerCharacter* Player) override;
	virtual void TickState(float DeltaTime) override;
	virtual void OnExit() override;
	virtual void HandleJumpInput() override;
	virtual void HandleRollInput() override; // <-- AÑADE ESTA LÍNEA paso 13
};