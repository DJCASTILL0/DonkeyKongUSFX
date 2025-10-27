#include "PlayerStates/SwimmingState.h"
#include "DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void USwimmingState::OnEnter(ADKCPlayerCharacter* Player)
{
	Super::OnEnter(Player);
	UE_LOG(LogTemp, Warning, TEXT("Entering Swimming State"));

	if (PlayerCharacter)
	{
		// Ajustamos los parámetros para el nado
		UCharacterMovementComponent* MoveComp = PlayerCharacter->GetCharacterMovement();
		MoveComp->GravityScale = 0.f; // Desactivamos la gravedad
		MoveComp->MaxSwimSpeed = 300.f; // Velocidad de nado
		MoveComp->BrakingDecelerationSwimming = 100.f; // Fricción en el agua
	}
}
void USwimmingState::TickState(float DeltaTime)
{
	// Esta función ahora cumple el contrato.
	// No necesitamos ninguna lógica de tick por ahora, pero la función debe existir.
}
void USwimmingState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting Swimming State"));

	if (PlayerCharacter)
	{
		// Restauramos la gravedad al salir
		PlayerCharacter->GetCharacterMovement()->GravityScale = 1.0f;
	}
}

void USwimmingState::HandleMoveUpInput(float Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->AddMovementInput(FVector(0, 0, 1), Value);
	}
}

void USwimmingState::HandleMoveRightInput(float Value)
{
	if (PlayerCharacter)
	{
		// En este estado, el input de "MoveRight" mueve al personaje en el eje Y
		PlayerCharacter->AddMovementInput(FVector(0, 1, 0), Value);
	}
}