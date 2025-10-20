#include "Enemies/KritterCharacter.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"

void AKritterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Si este Kritter está configurado para saltar...
	if (bDoesJump)
	{
		// ...iniciamos un temporizador que llamará a la función PerformJump cada 3 segundos.
		GetWorld()->GetTimerManager().SetTimer(JumpTimerHandle, this, &AKritterCharacter::PerformJump, 3.0f, true);
	}
}

void AKritterCharacter::Tick(float DeltaTime)
{
	// Si el Kritter NO es un saltador, entonces ejecuta la lógica de su padre (patrullar).
	if (!bDoesJump)
	{
		Super::Tick(DeltaTime);
	}
	// Si es un saltador, no hacemos nada en el Tick, dejando que el temporizador se encargue del salto.
}

void AKritterCharacter::PerformJump()
{
	// Usamos la función de salto que viene con ACharacter.
	Jump();
}