#include "Enemies/KingKroolCharacter.h"
#include "TimerManager.h"

void AKingKroolCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Hacemos que el jefe no patrulle, as� que detenemos el movimiento de su padre.
	// La funci�n Tick se encargar� de su comportamiento.

	// Iniciamos un temporizador para que ataque cada 5 segundos.
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AKingKroolCharacter::ThrowCrown, 5.0f, true);
}

void AKingKroolCharacter::Tick(float DeltaTime)
{
	// Dejamos Super::Tick comentado o borrado para que no herede el movimiento de patrulla.
	// Super::Tick(DeltaTime); 
}

void AKingKroolCharacter::ThrowCrown()
{
	UE_LOG(LogTemp, Warning, TEXT("King K. Rool ataca lanzando su corona!"));
	// TAREA PENDIENTE: Aqu� ir� la l�gica para crear y lanzar el proyectil de la corona.
}