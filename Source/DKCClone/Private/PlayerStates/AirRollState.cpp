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
        // Opcional: Podr�amos a�adir un peque�o impulso hacia adelante aqu�
        // PlayerCharacter->LaunchCharacter(PlayerCharacter->GetActorForwardVector() * 500.f, false, false);

        // TODO: En el futuro, aqu� cambiaremos la animaci�n a la de rodar.
    }
}

void UAirRollState::TickState(float DeltaTime)
{
    // La l�gica es id�ntica a la de JumpingState: esperamos a aterrizar.
    if (PlayerCharacter && !PlayerCharacter->GetCharacterMovement()->IsFalling())
    {
        PlayerCharacter->SwitchState(NewObject<UIdleState>());
    }
}

void UAirRollState::OnExit()
{
    UE_LOG(LogTemp, Warning, TEXT("Exiting Air Roll State"));
}