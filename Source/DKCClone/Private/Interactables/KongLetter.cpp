// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactables/KongLetter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h" // Incluimos el componente de texto
#include "DKCPlayerCharacter.h"
#include "Components/InventoryComponent.h"

// En KongLetter.cpp
AKongLetter::AKongLetter()
{
	PrimaryActorTick.bCanEverTick = false;

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	RootComponent = OverlapSphere;
	OverlapSphere->SetCollisionProfileName("Trigger");
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &AKongLetter::OnOverlapBegin);

	// --- LÓGICA MODIFICADA ---
	// Creamos y configuramos el componente de malla estática
	LetterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LetterMesh"));
	LetterMesh->SetupAttachment(RootComponent);
	LetterMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Es solo visual
}
void AKongLetter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADKCPlayerCharacter* Player = Cast<ADKCPlayerCharacter>(OtherActor);
	if (Player)
	{
		UInventoryComponent* Inventory = Player->GetInventoryComponent();
		if (Inventory)
		{
			// Le pasamos la letra que somos al inventario
			Inventory->AddKongLetter(Letra);
		}
		Destroy();
	}
}

// Called when the game starts or when spawned
/* void AKongLetter::BeginPlay()
{
	Super::BeginPlay();
	
}*/

// Called every frame
void AKongLetter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

