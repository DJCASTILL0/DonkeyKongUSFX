// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/BarrelBase.h"
#include "Enemies/EnemyBase.h"
#include "Components/HealthComponent.h"
// Sets default values
ABarrelBase::ABarrelBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
	RootComponent = BarrelMesh;

	// Buscamos un mesh de barril en el Starter Content
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BarrelMeshAsset(TEXT("/Game/StarterContent/Props/SM_Rock.SM_Rock"));
	if (BarrelMeshAsset.Succeeded())
	{
		BarrelMesh->SetStaticMesh(BarrelMeshAsset.Object);
	}
	// Habilitamos la simulación de físicas para que el barril pueda rodar por el suelo
	BarrelMesh->SetSimulatePhysics(true);

	BarrelMesh->OnComponentHit.AddDynamic(this, &ABarrelBase::OnBarrelHit);

}

// Called when the game starts or when spawned
void ABarrelBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarrelBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABarrelBase::OnBarrelHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Solo hacemos daño si el barril ha sido lanzado (y por tanto, está simulando físicas).
	if (BarrelMesh->IsSimulatingPhysics())
	{
		// Intentamos convertir el actor con el que chocamos a un enemigo.
		AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
		if (Enemy)
		{
			// Si es un enemigo, le aplicamos daño y el barril se destruye.
			UHealthComponent* EnemyHealth = Enemy->HealthComponent;
			if (EnemyHealth)
			{
				EnemyHealth->TakeDamage(3.0f); // Suficiente para matar de un golpe.
			}
			Destroy(); // El barril se rompe.
		}
	}
}