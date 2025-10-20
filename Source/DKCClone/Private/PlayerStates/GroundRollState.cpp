#include "PlayerStates/GroundRollState.h"
#include "PlayerStates/WalkingState.h" 
#include "DKCPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
void UGroundRollState::OnEnter(ADKCPlayerCharacter* Player)
{
    Super::OnEnter(Player);
    UE_LOG(LogTemp, Warning, TEXT("ENTERING GROUND ROLL STATE"));

    RollDuration = 0.5f;

    if (PlayerCharacter)
    {
        PlayerCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
        // Aplicamos un impulso hacia adelante para simular la velocidad del roll.
        // El valor 2000.f es arbitrario, puedes ajustarlo para que se sienta bien.
        const FVector ForwardImpulse = PlayerCharacter->GetActorForwardVector() * 2000.f;
        PlayerCharacter->LaunchCharacter(ForwardImpulse, false, false);

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
    if (PlayerCharacter)
    {
        // Al salir, restauramos la colisión para que vuelva a bloquear a los enemigos
        PlayerCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
    }
}