#include "PlayerStates/PlayerBaseState.h"
#include "DKCPlayerCharacter.h"
// Al entrar en cualquier estado, guardamos una referencia al personaje.
// Así no tenemos que repetirlo en cada una de las clases hijas.
void UPlayerBaseState::OnEnter(ADKCPlayerCharacter* Player)
{
	PlayerCharacter = Player;
}
void UPlayerBaseState::HandleJumpInput()
{
    // Por defecto, un estado no hace nada al saltar.
    // Las clases hijas que sí puedan saltar la sobrescribirán 
}

void UPlayerBaseState::HandleRollInput()
{

}

void UPlayerBaseState::HandleMoveUpInput(float Value)
{

}
void UPlayerBaseState::HandleMoveRightInput(float Value)
{
    // Por defecto, los estados ignoran este input.
}