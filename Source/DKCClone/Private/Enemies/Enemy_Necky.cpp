#include "Enemies/Enemy_Necky.h"
#include "TimerManager.h"
#include "Projectiles/ProjectileBase.h"

void AEnemy_Necky::BeginPlay()
{
	Super::BeginPlay();

	// Iniciamos el temporizador cuando el enemigo aparece en el mundo.
	// Llamar� a la funci�n 'Fire' cada 2.0 segundos, y se repetir�.
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AEnemy_Necky::Fire, 2.0f, true);

	// Inicia el temporizador de giro (cada 4 segundos)
	GetWorld()->GetTimerManager().SetTimer(TurnTimerHandle, this, &AEnemy_Necky::Turn, 4.0f, true);

}

void AEnemy_Necky::Fire()
{
	// Comprobamos que hemos asignado una clase de proyectil en el Blueprint.
	if (ProjectileClass)
	{
		// Definimos d�nde y con qu� rotaci�n aparecer� el proyectil.
		// En este caso, un poco por delante y por debajo del Necky.
		const FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 100.f) + (GetActorUpVector() * -50.f);
		const FRotator SpawnRotation = GetActorRotation();

		// Usamos GetWorld()->SpawnActor para crear una instancia del proyectil en el mundo.
		GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
	}
}

void AEnemy_Necky::Turn()
{
	// Giramos al actor 180 grados sobre su eje Z (Yaw).
	AddActorLocalRotation(FRotator(0.f, 180.f, 0.f));
}

void AEnemy_Necky::Tick(float DeltaTime)
{
	// NO llames a Super::Tick(DeltaTime);
	// D�jala vac�a para que el Necky no haga nada en cada frame,
	// ignorando as� el movimiento de su padre.
}