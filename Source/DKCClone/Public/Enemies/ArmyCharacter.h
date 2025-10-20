
#pragma once

#include "CoreMinimal.h"
#include "Enemies/EnemyBase.h"
#include "ArmyCharacter.generated.h"

UCLASS()
class DKCCLONE_API AArmyCharacter : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Función pública para que el jugador pueda "activar" el estado de caparazón.
	void EnterShellState();

protected:
	// Sobrescribimos la función OnHit de nuestro padre para añadir la lógica de choque del caparazón.
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

private:
	// Variable para saber si estamos en estado de caparazón.
	bool bIsShell;
};