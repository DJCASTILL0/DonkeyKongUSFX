#include "PlayerStates/ClimbingState.h"
#include "DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interactables/VineActor.h"
#include "PlayerStates/JumpingState.h"

void UClimbingState::OnEnter(ADKCPlayerCharacter* Player)
{
	Super::OnEnter(Player);
	UE_LOG(LogTemp, Warning, TEXT("Entering Climbing State"));

	if (PlayerCharacter)
	{
		// Cambiamos el modo de movimiento a "Flying" para desactivar la gravedad y permitir movimiento libre.
		PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		// Detenemos cualquier movimiento lateral que tuviéramos.
		PlayerCharacter->GetCharacterMovement()->StopMovementImmediately();
	}
}

void UClimbingState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting Climbing State"));

	if (PlayerCharacter)
	{
		// Al salir del estado, volvemos al modo de movimiento normal (caminar/caer).
		PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void UClimbingState::TickState(float DeltaTime)
{
	// Opcional: Centrar al personaje en la liana suavemente
	if (PlayerCharacter && PlayerCharacter->GetOverlappingVine())
	{
		const FVector VineLocation = PlayerCharacter->GetOverlappingVine()->GetActorLocation();
		const FVector PlayerLocation = PlayerCharacter->GetActorLocation();

		// Mantenemos al jugador alineado horizontalmente con la liana
		PlayerCharacter->SetActorLocation(FVector(VineLocation.X, VineLocation.Y, PlayerLocation.Z));
	}
}

void UClimbingState::HandleJumpInput()
{
	if (PlayerCharacter)
	{
		// Al saltar, nos lanzamos hacia arriba y hacia adelante y cambiamos al estado de salto.
		const FVector JumpDirection = PlayerCharacter->GetActorForwardVector() + FVector(0, 0, 1);
		PlayerCharacter->LaunchCharacter(JumpDirection * 800.f, false, true);
		PlayerCharacter->SwitchState(NewObject<UJumpingState>());
	}
}

void UClimbingState::HandleMoveUpInput(float Value)
{
	if (PlayerCharacter)
	{
		// Añadimos movimiento en el eje Z (arriba/abajo)
		PlayerCharacter->AddMovementInput(FVector(0, 0, 1), Value);
	}
}