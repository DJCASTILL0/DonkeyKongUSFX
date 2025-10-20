#include "Interactables/CannonBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Character.h" // Necesitamos saber qué es un ACharacter

ACannonBarrel::ACannonBarrel()
{
	PrimaryActorTick.bCanEverTick = false;

	// 1. Creamos el componente raíz invisible.
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	// 2. Creamos el mesh y lo "pegamos" a la raíz.
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
	BarrelMesh->SetupAttachment(RootComponent);
	BarrelMesh->SetCollisionProfileName("NoCollision"); // Sigue siendo solo visual.

	// 3. Creamos la esfera de overlap y la "pegamos" a la raíz.
	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->SetupAttachment(RootComponent);
	OverlapSphere->SetCollisionProfileName("Trigger");
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ACannonBarrel::OnOverlapBegin);

	// 4. Creamos la flecha y la "pegamos" a la raíz.
	LaunchArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("LaunchArrow"));
	LaunchArrow->SetupAttachment(RootComponent);
	LaunchArrow->ArrowSize = 5.0f;
	LaunchArrow->bIsScreenSizeScaled = true;

	// La velocidad de lanzamiento por defecto.
	LaunchVelocity = FVector(1500.f, 0.f, 1000.f);
}

void ACannonBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACannonBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACannonBarrel::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (PlayerCharacter)
	{
		// Obtenemos la rotación actual del barril cañón en el mundo.
		const FRotator CannonRotation = GetActorRotation();

		// Usamos esa rotación para transformar nuestro vector de velocidad (que ahora es local) a un vector en el espacio del mundo.
		const FVector WorldSpaceLaunchVelocity = CannonRotation.RotateVector(LaunchVelocity);

		// Lanzamos al jugador usando el nuevo vector calculado que sí respeta la rotación.
		PlayerCharacter->LaunchCharacter(WorldSpaceLaunchVelocity, true, true);
	}
}

