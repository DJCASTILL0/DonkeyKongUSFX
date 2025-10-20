
#include "PlayerStates/IdleState.h"
#include "PlayerStates/WalkingState.h"
#include "PlayerStates/JumpingState.h"
#include "DKCPlayerCharacter.h" // Necesario para acceder a datos del personaje
#include "GameFramework/CharacterMovementComponent.h" // Necesario para obtener la velocidad
void UIdleState::OnEnter(ADKCPlayerCharacter* Player) 
{
	Super::OnEnter(Player);
	UE_LOG(LogTemp, Warning, TEXT("Entering Idle State"));
}
void UIdleState::TickState(float DeltaTime)
{
	
	if (PlayerCharacter && PlayerCharacter->GetVelocity().Size() > 0.1f)
	{
		
		PlayerCharacter->SwitchState(NewObject<UWalkingState>());
	}
}

void UIdleState::OnExit()
{

	UE_LOG(LogTemp, Warning, TEXT("Exiting Idle State"));
}

void UIdleState::HandleJumpInput() 
{
	PlayerCharacter->SwitchState(NewObject<UJumpingState>());
}