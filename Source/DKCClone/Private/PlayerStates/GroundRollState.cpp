#include "PlayerStates/GroundRollState.h"
#include "PlayerStates/WalkingState.h" // Incluimos el estado al que volveremos
#include "DKCPlayerCharacter.h"

void UGroundRollState::OnEnter(ADKCPlayerCharacter* Player)
{
    Super::OnEnter(Player);
    UE_LOG(LogTemp, Warning, TEXT("ENTERING GROUND ROLL STATE"));

    // Establecemos la duración del roll en segundos
    RollDuration = 0.5f;

    if (PlayerCharacter)
    {
        // Aplicamos un impulso hacia adelante para simular la velocidad del roll.
        // El valor 2000.f es arbitrario, puedes ajustarlo para que se sienta bien.
        const FVector ForwardImpulse = PlayerCharacter->GetActorForwardVector() * 2000.f;
        PlayerCharacter->LaunchCharacter(ForwardImpulse, false, false);

        // TODO: Aquí cambiaremos la animación a la de rodar.
    }
}

void UGroundRollState::TickState(float DeltaTime)
{
    // Restamos el tiempo transcurrido en cada frame
    RollDuration -= DeltaTime;

    // Si el temporizador llega a cero, terminamos de rodar
    if (RollDuration <= 0.f)
    {
        // Volvemos al estado de caminar
        PlayerCharacter->SwitchState(NewObject<UWalkingState>());
    }
}

void UGroundRollState::OnExit()
{
    UE_LOG(LogTemp, Warning, TEXT("Exiting Ground Roll State"));
}