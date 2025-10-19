#include "PlayerStates/AirRollState.h"
#include "PlayerStates/IdleState.h"
#include "DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAirRollState::OnEnter(ADKCPlayerCharacter* Player)
{
    Super::OnEnter(Player);
    UE_LOG(LogTemp, Warning, TEXT("ENTERING AIR ROLL STATE"));

    if (PlayerCharacter)
    {
        // Opcional: Podríamos añadir un pequeño impulso hacia adelante aquí
        // PlayerCharacter->LaunchCharacter(PlayerCharacter->GetActorForwardVector() * 500.f, false, false);

        // TODO: En el futuro, aquí cambiaremos la animación a la de rodar.
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
}