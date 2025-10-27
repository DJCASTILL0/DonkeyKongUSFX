#include "PlayerStates/PlayerBaseState.h"
#include "DKCPlayerCharacter.h"
// Al entrar en cualquier estado, guardamos una referencia al personaje.
// As� no tenemos que repetirlo en cada una de las clases hijas.
void UPlayerBaseState::OnEnter(ADKCPlayerCharacter* Player)
{
	PlayerCharacter = Player;
}
void UPlayerBaseState::HandleJumpInput()
{
    // Por defecto, un estado no hace nada al saltar.
    // Las clases hijas que s� puedan saltar la sobrescribir�n 
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