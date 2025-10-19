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
			// Si choca con un enemigo, le hace da�o, pero NO se destruye.
			UHealthComponent* EnemyHealth = Enemy->HealthComponent;
			if (EnemyHealth)
			{
				EnemyHealth->TakeDamage(3.0f);
			}
		}

		// L�gica de rebote:
		// La "Normal" del golpe nos dice la direcci�n de la superficie con la que chocamos.
		// Al reflejar la velocidad del barril contra esa normal, obtenemos la nueva direcci�n de rebote.
		FVector CurrentVelocity = BarrelMesh->GetPhysicsLinearVelocity();
		FVector ReflectedVelocity = FMath::GetReflectionVector(CurrentVelocity, Hit.ImpactNormal);

		// Aplicamos la nueva velocidad al mesh.
		BarrelMesh->SetPhysicsLinearVelocity(ReflectedVelocity);
	}
}