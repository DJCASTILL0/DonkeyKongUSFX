// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DKCCloneGameMode.generated.h"

class AEnemyBase;
class ACharacter; 

UCLASS(minimalapi)
class ADKCCloneGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADKCCloneGameMode();

	// Nuestro contenedor TArray para guardar todos los enemigos.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
	TArray<AEnemyBase*> ActiveEnemies;

	// Funciones para que los enemigos se a�adan o eliminen de la lista.
	void AddEnemyToArray(AEnemyBase* EnemyToAdd);
	void RemoveEnemyFromArray(AEnemyBase* EnemyToRemove);

	// Funci�n p�blica que el jugador llamar� al morir.
	void PlayerDied(ACharacter* DeadCharacter);

private:
	// Funci�n privada para reiniciar el nivel.
	void RestartLevel();

	// Temporizador para controlar el reinicio.
	FTimerHandle RestartTimerHandle;
};