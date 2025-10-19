// Copyright Epic Games, Inc. All Rights Reserved.
#include "DKCCloneGameMode.h"
#include "DKCPlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Enemies/EnemyBase.h"
#include "Kismet/GameplayStatics.h" // Necesario para OpenLevel
#include "TimerManager.h" // Necesario para los Timers
ADKCCloneGameMode::ADKCCloneGameMode()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	} --> no lo usamso porque ya tenemos DKCPlayerCharacter*/ 
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