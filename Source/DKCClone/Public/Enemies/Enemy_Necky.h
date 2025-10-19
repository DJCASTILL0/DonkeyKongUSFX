#pragma once

#include "CoreMinimal.h"
#include "Enemies/EnemyBase.h"
#include "Enemy_Necky.generated.h"

UCLASS()
class DKCCLONE_API AEnemy_Necky : public AEnemyBase
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;

	// Variable para decirle al Necky qué clase de proyectil debe disparar.
	// La asignaremos desde el editor de Blueprints.
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectileBase> ProjectileClass;

	// El temporizador que controlará la cadencia de disparo.
	FTimerHandle FireTimerHandle;

	// La función que se llamará para disparar.
	void Fire();

	FTimerHandle TurnTimerHandle;
	void Turn();

};