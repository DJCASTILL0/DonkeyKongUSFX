#include "AnimalBuddies/RambiCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
ARambiCharacter::ARambiCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bConstrainToPlane = true; //pared insisivle (2)
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(1.0f, 0.0f, 0.0f));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(0, 0, 60)); // Ajusta la altura si es necesario
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bUsePawnControlRotation = true;

	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));// Crear la cámara (3)
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ARambiCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	DisableInput(nullptr);// Por defecto, Rambi no está controlado por nadie y no puede moverse.
}

void ARambiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARambiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UE_LOG(LogTemp, Warning, TEXT("SETUPPLAYERINPUTCOMPONENT EN RAMBI LLAMADO!"));
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);// Rambi usa lo del JugPrincipal
	PlayerInputComponent->BindAxis("MoveRight", this, &ARambiCharacter::MoveRight);
}

void ARambiCharacter::Mount(ACharacter* Rider)
{
	if (!Rider) return;

	OriginalRider = Rider;

	// Obtenemos el controlador genérico.
	AController* GenericController = Rider->GetController();

	// Intentamos convertirlo al tipo específico de jugador.
	APlayerController* PlayerController = Cast<APlayerController>(GenericController);

	if (PlayerController)
	{
		// 1. El controlador deja de poseer al personaje original.
		GenericController->UnPossess();

		// 2. AHORA, el controlador toma posesión de Rambi.
		GenericController->Possess(this);

		// 3. Y FINALMENTE, con Rambi ya poseído, habilitamos su input.
		EnableInput(PlayerController);
	}

	// Ocultamos al jinete original y lo pegamos a la espalda de Rambi
	OriginalRider->SetActorHiddenInGame(true);
	OriginalRider->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Spine_03"));
}

void ARambiCharacter::MoveRight(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("MoveRight en Rambi llamado con valor: %f"), Value);
	if (Controller != nullptr && Value != 0.0f)
	{
		AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
	}
}