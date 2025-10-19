
// PlayerStates/PlayerBaseState.cpp
#include "PlayerStates/PlayerBaseState.h"
#include "DKCPlayerCharacter.h" // Ahora s� incluimos el header completo del personaje

// Al entrar en cualquier estado, guardamos una referencia al personaje.
// As� no tenemos que repetirlo en cada una de las clases hijas.
void UPlayerBaseState::OnEnter(ADKCPlayerCharacter* Player)
{
	PlayerCharacter = Player;
}
void UPlayerBaseState::HandleJumpInput()
{
    // Por defecto, un estado no hace nada al saltar.
    // Las clases hijas que s� puedan saltar la sobrescribir�n . paso 11
}

void UPlayerBaseState::HandleRollInput()
{
    // Por defecto, los estados ignoran este input. paso 12
}

void UPlayerBaseState::HandleMoveUpInput(float Value)
{
    // Por defecto, los estados ignoran este input.
}