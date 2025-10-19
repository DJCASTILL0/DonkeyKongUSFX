#include "Interactables/BananaActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DKCPlayerCharacter.h"
#include "Components/InventoryComponent.h"


ABananaActor::ABananaActor()
{
	PrimaryActorTick.bCanEverTick = false;

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	RootComponent = OverlapSphere;
	OverlapSphere->SetCollisionProfileName("Trigger"); // Usamos el perfil "Trigger"
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ABananaActor::OnOverlapBegin);

	BananaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BananaMesh"));
	BananaMesh->SetupAttachment(RootComponent);
	BananaMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ABananaActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABananaActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABananaActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADKCPlayerCharacter* Player = Cast<ADKCPlayerCharacter>(OtherActor);
	if (Player)
	{
		UInventoryComponent* Inventory = Player->GetInventoryComponent();
		if (Inventory)
		{
			Inventory->AddBanana();
		}

		// La banana se destruye al ser recogida.
		Destroy();
	}
}
