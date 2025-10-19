
#pragma once

#include "CoreMinimal.h"
#include "PlayerStates/PlayerBaseState.h"
#include "AirRollState.generated.h"

UCLASS()
class DKCCLONE_API UAirRollState : public UPlayerBaseState
{
    GENERATED_BODY()

public:
    virtual void OnEnter(ADKCPlayerCharacter* Player) override;
    virtual void TickState(float DeltaTime) override;
    virtual void OnExit() override;
};