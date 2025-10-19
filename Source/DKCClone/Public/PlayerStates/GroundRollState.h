#pragma once

#include "CoreMinimal.h"
#include "PlayerStates/PlayerBaseState.h"
#include "GroundRollState.generated.h"

UCLASS()
class DKCCLONE_API UGroundRollState : public UPlayerBaseState
{
    GENERATED_BODY()

public:
    virtual void OnEnter(ADKCPlayerCharacter* Player) override;
    virtual void TickState(float DeltaTime) override;
    virtual void OnExit() override;

private:
    // Un simple temporizador para controlar la duración del roll
    float RollDuration;
};