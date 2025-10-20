#include "DKCCloneGameMode.h"
#include "DKCPlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Enemies/EnemyBase.h"
#include "Kismet/GameplayStatics.h" 
#include "TimerManager.h" 
ADKCCloneGameMode::ADKCCloneGameMode()
{
	
}

void ADKCCloneGameMode::AddEnemyToArray(AEnemyBase* EnemyToAdd)
{
	if (EnemyToAdd)
	{
		ActiveEnemies.Add(EnemyToAdd);
		UE_LOG(LogTemp, Warning, TEXT("Enemy Added! Total Enemies: %d"), ActiveEnemies.Num());
	}
}

void ADKCCloneGameMode::RemoveEnemyFromArray(AEnemyBase* EnemyToRemove)
{
	if (EnemyToRemove)
	{
		ActiveEnemies.Remove(EnemyToRemove);
		UE_LOG(LogTemp, Warning, TEXT("Enemy Removed! Total Enemies: %d"), ActiveEnemies.Num());
	}
}

void ADKCCloneGameMode::PlayerDied(ACharacter* DeadCharacter)
{
	// Cuando el jugador muere, ponemos un temporizador de 3 segundos antes de reiniciar.
	GetWorld()->GetTimerManager().SetTimer(RestartTimerHandle, this, &ADKCCloneGameMode::RestartLevel, 3.f, false);
}



void ADKCCloneGameMode::RestartLevel()
{
	// Recargamos el nivel actual.
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}