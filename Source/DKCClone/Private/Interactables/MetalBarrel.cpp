#include "Interactables/MetalBarrel.h"
#include "Enemies/EnemyBase.h"
#include "Components/HealthComponent.h"
#include "Components/StaticMeshComponent.h"

void AMetalBarrel::OnBarrelHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (BarrelMesh->IsSimulatingPhysics())
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
		if (Enemy)
		{
			// Si choca con un enemigo, le hace daño, pero NO se destruye.
			UHealthComponent* EnemyHealth = Enemy->HealthComponent;
			if (EnemyHealth)
			{
				EnemyHealth->TakeDamage(3.0f);
			}
		}

		// Lógica de rebote:
		// La "Normal" del golpe nos dice la dirección de la superficie con la que chocamos.
		// Al reflejar la velocidad del barril contra esa normal, obtenemos la nueva dirección de rebote.
		FVector CurrentVelocity = BarrelMesh->GetPhysicsLinearVelocity();
		FVector ReflectedVelocity = FMath::GetReflectionVector(CurrentVelocity, Hit.ImpactNormal);

		// Aplicamos la nueva velocidad al mesh.
		BarrelMesh->SetPhysicsLinearVelocity(ReflectedVelocity);
	}
}