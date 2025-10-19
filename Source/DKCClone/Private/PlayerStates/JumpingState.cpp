
// Private/PlayerStates/JumpingState.cpp

#include "PlayerStates/JumpingState.h"
#include "PlayerStates/IdleState.h"
#include "PlayerStates/AirRollState.h" 
#include "DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UJumpingState::OnEnter(ADKCPlayerCharacter* Player)
{
	Super::OnEnter(Player);
	UE_LOG(LogTemp, Warning, TEXT("Entering Jumping State"));

	// Usamos la función de salto que ya viene con ACharacter para aplicar el impulso.
	if (PlayerCharacter)
	{
		PlayerCharacter->Jump();
	}
}

void UJumpingState::TickState(float DeltaTime)
{
	// Mientras estamos en el aire, nuestra única preocupación es saber cuándo aterrizamos.
	// El CharacterMovementComponent tiene una función muy útil para esto: IsFalling().
	if (PlayerCharacter && !PlayerCharacter->GetCharacterMovement()->IsFalling())
	{
		// Si ya no estamos cayendo, significa que hemos aterrizado.
		// Volvemos al estado de reposo.
		PlayerCharacter->SwitchState(NewObject<UIdleState>());
	}
}

void UJumpingState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting Jumping State"));
}

void UJumpingState::HandleRollInput()
{
	// Si estamos saltando y recibimos el input de rodar, cambiamos al estado AirRollState.
	PlayerCharacter->SwitchState(NewObject<UAirRollState>());
}