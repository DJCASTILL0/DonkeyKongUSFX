// PlayerStates/IdleState.cpp
#include "PlayerStates/IdleState.h"
#include "PlayerStates/WalkingState.h"
#include "PlayerStates/JumpingState.h"
#include "DKCPlayerCharacter.h" // Necesario para acceder a datos del personaje
#include "GameFramework/CharacterMovementComponent.h" // Necesario para obtener la velocidad
void UIdleState::OnEnter(ADKCPlayerCharacter* Player) // <-- AÑADIMOS ESTA FUNCIÓN
{
	Super::OnEnter(Player);
	UE_LOG(LogTemp, Warning, TEXT("Entering Idle State"));
}
void UIdleState::TickState(float DeltaTime)
{
	// La lógica de este estado es simple: comprobar si el personaje ha empezado a moverse.
	// PlayerCharacter->GetVelocity().Size() nos da la velocidad total del personaje.
	// Si la velocidad es mayor que un número pequeño (para evitar errores de precisión),
	// significa que el jugador está presionando una tecla de movimiento.
	if (PlayerCharacter && PlayerCharacter->GetVelocity().Size() > 0.1f)
	{
		// Si nos movemos, debemos cambiar al estado de caminar.
		// AÚN NO PODEMOS HACER ESTO, porque nuestro personaje no tiene la función SwitchState().
		// Dejamos un recordatorio para cuando la creemos en la siguiente tarea.
		PlayerCharacter->SwitchState(NewObject<UWalkingState>());
		// PlayerCharacter->SwitchState(WalkingState); // <-- TAREA PENDIENTE
	}
}

void UIdleState::OnExit()
{
	// Esta función se llamará justo antes de cambiar a otro estado.
	// Aquí podríamos poner lógica de "limpieza", si fuera necesario.
	// Por ahora, no necesita hacer nada.
	UE_LOG(LogTemp, Warning, TEXT("Exiting Idle State"));
}

void UIdleState::HandleJumpInput() // O UWalkingState::HandleJumpInput() paso 11
{
	PlayerCharacter->SwitchState(NewObject<UJumpingState>());
}