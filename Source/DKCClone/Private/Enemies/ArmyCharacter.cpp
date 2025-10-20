#include "Enemies/ArmyCharacter.h"
#include "PhysicsEngine/BodyInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/HealthComponent.h"
#include "DKCPlayerCharacter.h"
void AArmyCharacter::EnterShellState()
{
	if (bIsShell) return;

	bIsShell = true;

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->Deactivate();

	GetCapsuleComponent()->SetSimulatePhysics(true);
	GetCapsuleComponent()->SetCollisionProfileName("PhysicsActor");

	// Obtenemos la instancia del cuerpo físico para darle órdenes directas.
	FBodyInstance* BodyInst = GetCapsuleComponent()->GetBodyInstance();
	if (BodyInst)
	{
		// 1. Bloqueamos el movimiento en el eje de la profundidad (X).
		BodyInst->bLockXTranslation = true;

		// 2. Bloqueamos la rotación en los ejes Y y Z.
		//    Esto evita que se incline hacia los lados o gire como una peonza.
		//    Solo le permitimos rotar en el eje X (rodar hacia adelante).
		BodyInst->bLockYRotation = true;
		BodyInst->bLockZRotation = true;
	}

	// Limpiamos el vector de impulso para asegurarnos de que sea 100% 2D.
	const FVector RawDirection = GetActorForwardVector();
	const FVector ImpulseDirection = FVector(0.f, RawDirection.Y, 0.f).GetSafeNormal();

	GetCapsuleComponent()->AddImpulse(ImpulseDirection * 1500.f * GetCapsuleComponent()->GetMass());
}

void AArmyCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bIsShell)
	{
		AEnemyBase* OtherEnemy = Cast<AEnemyBase>(OtherActor);
		if (OtherEnemy && OtherEnemy != this)
		{
			if (OtherEnemy->HealthComponent)
			{
				OtherEnemy->HealthComponent->TakeDamage(3.0f);
			}
		}

		ADKCPlayerCharacter* Player = Cast<ADKCPlayerCharacter>(OtherActor);
		if (Player)
		{
			if (Player->GetHealthComponent())
			{
				Player->GetHealthComponent()->TakeDamage(1.0f);
			}
		}
	}
	else
	{
		Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	}
}