
// Private/PlayerStates/WalkingState.cpp

#include "PlayerStates/WalkingState.h"
#include "PlayerStates/IdleState.h" // Importante: incluimos el estado al que podemos transicionar
#include "PlayerStates/JumpingState.h"
#include "PlayerStates/GroundRollState.h"
#include "DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWalkingState::OnEnter(ADKCPlayerCharacter* Player)
{
	// Llamamos a la implementación base primero
	Super::OnEnter(Player);

	// Usamos UE_LOG para ver en la consola que hemos entrado en este estado. ¡Muy útil para depurar!
	UE_LOG(LogTemp, Warning, TEXT("Entering Walking State"));
}

void UWalkingState::TickState(float DeltaTime)
{
	// Mientras estamos caminando, nuestra única preocupación es saber cuándo parar.
	// Si nuestra velocidad es casi cero, significa que el jugador ha soltado las teclas.
	if (PlayerCharacter && PlayerCharacter->GetVelocity().Size() < 0.1f)
	{
		// Es hora de volver al estado de reposo.
		PlayerCharacter->SwitchState(NewObject<UIdleState>());
	}
}

void UWalkingState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting Walking State"));
}

void UWalkingState::HandleJumpInput()  //<- paso 11
{
	PlayerCharacter->SwitchState(NewObject<UJumpingState>());
}

void UWalkingState::HandleRollInput()
{
	// Si estamos caminando y recibimos el input de rodar, cambiamos al estado GroundRollState.
	PlayerCharacter->SwitchState(NewObject<UGroundRollState>());
}