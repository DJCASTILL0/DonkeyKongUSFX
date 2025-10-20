#include "PlayerStates/AirRollState.h"
#include "PlayerStates/IdleState.h"
#include "DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

void UAirRollState::OnEnter(ADKCPlayerCharacter* Player)
{
    Super::OnEnter(Player);
    UE_LOG(LogTemp, Warning, TEXT("ENTERING AIR ROLL STATE"));

    if (PlayerCharacter)
    {
        PlayerCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    }
}

void UAirRollState::TickState(float DeltaTime)
{
    // La lógica es idéntica a la de JumpingState: esperamos a aterrizar.
    if (PlayerCharacter && !PlayerCharacter->GetCharacterMovement()->IsFalling())
    {
        PlayerCharacter->SwitchState(NewObject<UIdleState>());
    }
}

void UAirRollState::OnExit()
{
    UE_LOG(LogTemp, Warning, TEXT("Exiting Air Roll State"));

    if (PlayerCharacter)
    {
        PlayerCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
    }
}