#include "AnimalBuddies/EnguardeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


AEnguardeCharacter::AEnguardeCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Enguarde no usa la rotación del control y debe estar siempre en modo "nadando"
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Swimming);
	GetCharacterMovement()->GravityScale = 0.f; // La gravedad no le afecta
	GetCharacterMovement()->MaxSwimSpeed = 500.f;

	// --- AÑADE ESTA PARED INVISIBLE ---
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(1.0f, 0.0f, 0.0f));

	// --- AÑADE ESTE BLOQUE DE CÁMARA COMPLETO ---
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(0, 0, 60));
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	// --- FIN DEL BLOQUE DE CÁMARA ---

}

void AEnguardeCharacter::BeginPlay()
{
	Super::BeginPlay();
	DisableInput(nullptr);
}

void AEnguardeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Enguarde usará los mismos ejes que el jugador nadando, y el botón de roll para embestir
	PlayerInputComponent->BindAxis("MoveUp", this, &AEnguardeCharacter::MoverArriba);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEnguardeCharacter::MoverDerecha);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &AEnguardeCharacter::Embestir);
}
void AEnguardeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AEnguardeCharacter::Montar(ACharacter* Jinete)
{
	if (!Jinete) return;

	JineteOriginal = Jinete;

	AController* ControladorGenerico = Jinete->GetController();
	APlayerController* ControladorJugador = Cast<APlayerController>(ControladorGenerico);

	if (ControladorJugador)
	{
		ControladorGenerico->UnPossess();
		ControladorGenerico->Possess(this);
		EnableInput(ControladorJugador);
		// Detenemos cualquier movimiento heredado del personaje anterior.
		GetCharacterMovement()->StopMovementImmediately();
	}

	JineteOriginal->SetActorHiddenInGame(true);
	JineteOriginal->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AEnguardeCharacter::MoverArriba(float Valor)
{
	if (Controller && Valor != 0.0f)
	{
		AddMovementInput(FVector(0, 0, 1), Valor);
	}
}

void AEnguardeCharacter::MoverDerecha(float Valor)
{
	if (Controller && Valor != 0.0f)
	{
		AddMovementInput(FVector(0, 1, 0), Valor);
	}
}

void AEnguardeCharacter::Embestir()
{
	// Le damos un impulso fuerte hacia adelante para simular la embestida
	const FVector DireccionImpulso = GetActorForwardVector() * 3000.f;
	LaunchCharacter(DireccionImpulso, false, false);
	UE_LOG(LogTemp, Warning, TEXT("Enguarde embiste!"));
}

