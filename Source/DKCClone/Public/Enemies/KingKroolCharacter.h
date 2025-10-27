#pragma once

#include "CoreMinimal.h"
#include "Enemies/EnemyBase.h"
#include "KingKroolCharacter.generated.h"

// Enum para controlar las fases de ataque del jefe
UENUM(BlueprintType)
enum class EFaseJefe : uint8
{
	LanzandoCorona,
	LluviaDeBalas,
	Saltando
};

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
	// --- Variables para la IA del Jefe ---

	// Guarda la fase de ataque actual del jefe
	EFaseJefe FaseActual;
	UPROPERTY(EditDefaultsOnly, Category = "Combate")
	TSubclassOf<class ACrownProjectile> ClaseCorona;
	// Variable para saber qué clase de Bala de Canion debe crear. La asignaremos en el editor.
	UPROPERTY(EditDefaultsOnly, Category = "Combate")
	TSubclassOf<class ABalaDeCanion> ClaseBalaDeCanion;

	// Temporizadores para controlar los tiempos de los ataques y cambios de fase
	FTimerHandle TemporizadorDeFase;
	FTimerHandle TemporizadorLluviaDeBalas;
	FTimerHandle AttackTimerHandle; // Reutilizamos el nombre de la tarea anterior

	// --- Funciones de Comportamiento ---

	// Cambia entre la fase de lanzar la corona y la lluvia de balas
	void CambiarFase();

	// Inicia el ataque de lluvia de balas
	void IniciarLluviaDeBalas();

	// Genera una bala de canion en el mundo
	void LanzarBalaDeCanion();

	// Lanza el proyectil de la corona (nombre de la tarea anterior)
	void ThrowCrown();

	FTimerHandle JumpAttackTimerHandle;

	void StartJumpAttackPhase();
	void PerformJumpAttack();
};