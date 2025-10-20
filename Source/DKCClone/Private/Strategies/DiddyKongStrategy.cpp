#include "Strategies/DiddyKongStrategy.h"
#include "DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerStates/GroundRollState.h"
#include "PlayerStates/AirRollState.h"

void UDiddyKongStrategy::ExecuteRoll()
{
    if (!PlayerCharacter) return;

    // La voltereta de Diddy usa la misma l�gica de estado por ahora
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

    // Par�metros de Diddy: Salto m�s alto, gravedad ligeramente mayor para una ca�da m�s r�pida.
    PlayerCharacter->GetCharacterMovement()->JumpZVelocity = 850.f;
    PlayerCharacter->GetCharacterMovement()->GravityScale = 1.2f;
}