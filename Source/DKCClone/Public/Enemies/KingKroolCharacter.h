#pragma once

#include "CoreMinimal.h"
#include "Enemies/EnemyBase.h"
#include "KingKroolCharacter.generated.h"

UCLASS()
class DKCCLONE_API AKingKroolCharacter : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Sobrescribimos Tick para controlar su IA
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	// Función para lanzar la corona
	void ThrowCrown();

	// Temporizador para controlar el ataque
	FTimerHandle AttackTimerHandle;
};