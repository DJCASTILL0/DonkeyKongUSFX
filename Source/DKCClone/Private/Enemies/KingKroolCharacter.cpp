#include "Enemies/KingKroolCharacter.h"
#include "TimerManager.h"
#include "Projectiles/CrownProjectile.h"
#include "Projectiles/BalaDeCanion.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h" // Necesario para GetPlayerCharacter

void AKingKroolCharacter::BeginPlay()
{
	Super::BeginPlay();

	// El jefe comienza en su primera fase de ataque.
	FaseActual = EFaseJefe::LanzandoCorona;
	// Inicia el temporizador para lanzar la corona cada 5 segundos.
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AKingKroolCharacter::ThrowCrown, 5.0f, true);

	// Inicia un temporizador que cambiará de fase cada 15 segundos.
	GetWorld()->GetTimerManager().SetTimer(TemporizadorDeFase, this, &AKingKroolCharacter::CambiarFase, 15.0f, true);
}

void AKingKroolCharacter::Tick(float DeltaTime)
{
	// Dejamos el Tick del padre vacío a propósito para que King K. Rool no herede
	// el comportamiento de patrulla de los enemigos comunes. Se quedará quieto.
	// Super::Tick(DeltaTime); 
}

void AKingKroolCharacter::ThrowCrown()
{
	UE_LOG(LogTemp, Warning, TEXT("JEFE: Lanzando Corona!"));

	// --- LÓGICA CORREGIDA ---
	// Usamos nuestra nueva variable, que es mucho más segura.
	if (ClaseCorona)
	{
		const FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 150.f);
		const FRotator SpawnRotation = GetActorRotation();

		GetWorld()->SpawnActor<ACrownProjectile>(ClaseCorona, SpawnLocation, SpawnRotation);
	}
}

void AKingKroolCharacter::CambiarFase()
{
	// Usaremos un switch para que la rotación de fases sea más clara y escalable
	switch (FaseActual)
	{
	case EFaseJefe::LanzandoCorona:
		// De Corona pasamos a Lluvia de Balas
		FaseActual = EFaseJefe::LluviaDeBalas;
		GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
		IniciarLluviaDeBalas();
		UE_LOG(LogTemp, Warning, TEXT("JEFE: Cambiando a fase de Lluvia de Balas!"));
		break;

	case EFaseJefe::LluviaDeBalas:
		// De Lluvia de Balas pasamos a Salto
		FaseActual = EFaseJefe::Saltando;
		GetWorld()->GetTimerManager().ClearTimer(TemporizadorLluviaDeBalas);
		StartJumpAttackPhase();
		UE_LOG(LogTemp, Warning, TEXT("JEFE: Cambiando a fase de Salto!"));
		break;

	case EFaseJefe::Saltando:
		// De Salto volvemos a Corona, completando el ciclo
		FaseActual = EFaseJefe::LanzandoCorona;
		GetWorld()->GetTimerManager().ClearTimer(JumpAttackTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AKingKroolCharacter::ThrowCrown, 5.0f, true);
		UE_LOG(LogTemp, Warning, TEXT("JEFE: Cambiando a fase de Lanzar Corona!"));
		break;
	}
}

void AKingKroolCharacter::IniciarLluviaDeBalas()
{
	// Iniciamos un temporizador que llama a LanzarBalaDeCanion muy rápido (cada 0.5 segundos).
	GetWorld()->GetTimerManager().SetTimer(TemporizadorLluviaDeBalas, this, &AKingKroolCharacter::LanzarBalaDeCanion, 0.5f, true);
}

void AKingKroolCharacter::LanzarBalaDeCanion()
{
	if (ClaseBalaDeCanion)
	{
		ACharacter* Jugador = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (Jugador)
		{
			// Hacemos que la bala aparezca en una posición aleatoria por encima del jugador.
			FVector PosicionJugador = Jugador->GetActorLocation();
			float OffsetAleatorio = FMath::RandRange(-500.f, 500.f); // Variación aleatoria a izquierda/derecha.
			FVector PosicionDeSpawn = FVector(PosicionJugador.X, PosicionJugador.Y + OffsetAleatorio, PosicionJugador.Z + 1000.f);

			// La bala siempre apuntará hacia abajo.
			FRotator RotacionDeSpawn = FRotator(-90.f, 0, 0);

			GetWorld()->SpawnActor<ABalaDeCanion>(ClaseBalaDeCanion, PosicionDeSpawn, RotacionDeSpawn);
		}
	}
}

void AKingKroolCharacter::StartJumpAttackPhase()
{
	// Iniciamos un temporizador que llama a PerformJumpAttack cada 3 segundos.
	GetWorld()->GetTimerManager().SetTimer(JumpAttackTimerHandle, this, &AKingKroolCharacter::PerformJumpAttack, 3.0f, true);
}

void AKingKroolCharacter::PerformJumpAttack()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player)
	{
		// 1. Obtenemos la ubicación del jugador.
		FVector PlayerLocation = Player->GetActorLocation();

		// 2. Calculamos la dirección cruda del salto.
		FVector RawDirection = PlayerLocation - GetActorLocation();

		// 3. --- LÓGICA MEJORADA ---
		// Creamos una versión "limpia" del vector, forzando a que no tenga profundidad (X=0).
		// Lo normalizamos para que solo represente dirección.
		FVector LaunchDirection = FVector(0.f, RawDirection.Y, RawDirection.Z).GetSafeNormal();

		// 4. Creamos la velocidad de lanzamiento usando la dirección limpia.
		FVector LaunchVelocity = (LaunchDirection * 1000.f) + FVector(0, 0, 800.f);

		// 5. Lanzamos al jefe.
		LaunchCharacter(LaunchVelocity, false, false);
		UE_LOG(LogTemp, Warning, TEXT("JEFE: Realizando ataque de salto!"));
	}
}