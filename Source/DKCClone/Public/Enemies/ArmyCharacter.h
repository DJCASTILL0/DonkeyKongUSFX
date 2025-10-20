
#pragma once

#include "CoreMinimal.h"
#include "Enemies/EnemyBase.h"
#include "ArmyCharacter.generated.h"

UCLASS()
class DKCCLONE_API AArmyCharacter : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Funci�n p�blica para que el jugador pueda "activar" el estado de caparaz�n.
	void EnterShellState();

protected:
	// Sobrescribimos la funci�n OnHit de nuestro padre para a�adir la l�gica de choque del caparaz�n.
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

private:
	// Variable para saber si estamos en estado de caparaz�n.
	bool bIsShell;
};