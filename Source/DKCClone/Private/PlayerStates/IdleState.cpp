// PlayerStates/IdleState.cpp
#include "PlayerStates/IdleState.h"
#include "PlayerStates/WalkingState.h"
#include "PlayerStates/JumpingState.h"
#include "DKCPlayerCharacter.h" // Necesario para acceder a datos del personaje
#include "GameFramework/CharacterMovementComponent.h" // Necesario para obtener la velocidad
void UIdleState::OnEnter(ADKCPlayerCharacter* Player) // <-- A�ADIMOS ESTA FUNCI�N
{
	Super::OnEnter(Player);
	UE_LOG(LogTemp, Warning, TEXT("Entering Idle State"));
}
void UIdleState::TickState(float DeltaTime)
{
	// La l�gica de este estado es simple: comprobar si el personaje ha empezado a moverse.
	// PlayerCharacter->GetVelocity().Size() nos da la velocidad total del personaje.
	// Si la velocidad es mayor que un n�mero peque�o (para evitar errores de precisi�n),
	// significa que el jugador est� presionando una tecla de movimiento.
	if (PlayerCharacter && PlayerCharacter->GetVelocity().Size() > 0.1f)
	{
		// Si nos movemos, debemos cambiar al estado de caminar.
		// A�N NO PODEMOS HACER ESTO, porque nuestro personaje no tiene la funci�n SwitchState().
		// Dejamos un recordatorio para cuando la creemos en la siguiente tarea.
		PlayerCharacter->SwitchState(NewObject<UWalkingState>());
		// PlayerCharacter->SwitchState(WalkingState); // <-- TAREA PENDIENTE
	}
}

void UIdleState::OnExit()
{
	// Esta funci�n se llamar� justo antes de cambiar a otro estado.
	// Aqu� podr�amos poner l�gica de "limpieza", si fuera necesario.
	// Por ahora, no necesita hacer nada.
	UE_LOG(LogTemp, Warning, TEXT("Exiting Idle State"));
}

void UIdleState::HandleJumpInput() // O UWalkingState::HandleJumpInput() paso 11
{
	PlayerCharacter->SwitchState(NewObject<UJumpingState>());
}