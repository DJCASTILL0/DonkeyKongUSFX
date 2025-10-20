#include "Strategies/DiddyKongStrategy.h"
#include "DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerStates/GroundRollState.h"
#include "PlayerStates/AirRollState.h"

void UDiddyKongStrategy::ExecuteRoll()
{
    if (!PlayerCharacter) return;

    // La voltereta de Diddy usa la misma lógica de estado por ahora
    if (PlayerCharacter->GetCharacterMovement()->IsFalling())
    {
        PlayerCharacter->SwitchState(NewObject<UAirRollState>());
    }
    else
    {
        PlayerCharacter->SwitchState(NewObject<UGroundRollState>());
    }
}

void UDiddyKongStrategy::AdjustMovementParameters()
{
    if (!PlayerCharacter) return;

    // Parámetros de Diddy: Salto más alto, gravedad ligeramente mayor para una caída más rápida.
    PlayerCharacter->GetCharacterMovement()->JumpZVelocity = 850.f;
    PlayerCharacter->GetCharacterMovement()->GravityScale = 1.2f;
}