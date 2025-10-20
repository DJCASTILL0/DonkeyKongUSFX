#include "Strategies/DonkeyKongStrategy.h"
#include "DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerStates/GroundRollState.h"
#include "PlayerStates/AirRollState.h"

void UDonkeyKongStrategy::ExecuteRoll()
{
    if (!PlayerCharacter) return;
    if (PlayerCharacter->GetCharacterMovement()->IsFalling())
    {
        PlayerCharacter->SwitchState(NewObject<UAirRollState>());
    }
    else
    {
        PlayerCharacter->SwitchState(NewObject<UGroundRollState>());
    }
}

void UDonkeyKongStrategy::AdjustMovementParameters()
{
    if (!PlayerCharacter) return;

    // Parámetros de DK: Salto más bajo, gravedad normal.
    PlayerCharacter->GetCharacterMovement()->JumpZVelocity = 600.f;
    PlayerCharacter->GetCharacterMovement()->GravityScale = 1.0f;
}