#include "Interactables/VineActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AVineActor::AVineActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Creamos la cápsula de overlap y la hacemos el componente raíz.
	OverlapCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("OverlapCapsule"));
	RootComponent = OverlapCapsule;

	// Configuramos la colisión de la cápsula para que sea un "Trigger".
	// Ignorará todo excepto al Pawn (nuestro jugador), con el que generará eventos de Overlap.
	OverlapCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapCapsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	// Creamos el mesh visual y lo adjuntamos a la cápsula.
	VineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VineMesh"));
	VineMesh->SetupAttachment(RootComponent);
	VineMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // El mesh es solo visual.

	// Asignamos un cilindro como liana temporal.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if (CylinderMesh.Succeeded())
	{
		VineMesh->SetStaticMesh(CylinderMesh.Object);
	}
}

void AVineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

