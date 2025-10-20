#include "DKCPlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerStates/PlayerBaseState.h"
#include "PlayerStates/IdleState.h"
#include "Components/HealthComponent.h" 
#include "Components/CapsuleComponent.h" 
#include "Enemies/EnemyBase.h"
#include "Blueprint/UserWidget.h"
#include "Interactables/BarrelBase.h"
#include "Interactables/VineActor.h"
#include "PlayerStates/ClimbingState.h" 
#include "Components/InventoryComponent.h" 
#include "DKCCloneGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Strategies/PlayerStrategy.h"
#include "Strategies/DonkeyKongStrategy.h"
#include "Strategies/DiddyKongStrategy.h"
#include "AnimalBuddies/RambiCharacter.h"
#include "Enemies/ArmyCharacter.h"
#include "PlayerStates/GroundRollState.h" 
#include "PlayerStates/AirRollState.h"

ADKCPlayerCharacter::ADKCPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1. AJUSTAR LA POSICI�N Y ROTACI�N DEL MESH
	// El mesh (modelo 3D) debe estar dentro de la c�psula de colisi�n y mirando hacia adelante.
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// 2. BUSCAR Y ASIGNAR EL SKELETAL MESH (MODELO 3D)
	// Usamos el ConstructorHelpers para encontrar un asset en el editor al iniciar el juego.
	// La ruta la copiamos desde el Content Browser.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerMeshObject(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (PlayerMeshObject.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerMeshObject.Object);
	}

	// 3. BUSCAR Y ASIGNAR LA CLASE DE ANIMACI�N (ANIMATION BLUEPRINT)
	// Es importante a�adir "_C" al final de la ruta del Blueprint.
	// Esto le dice a C++ que use la clase compilada del Blueprint.
	static ConstructorHelpers::FClassFinder<UAnimInstance> PlayerAnimBPClass(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C"));
	if (PlayerAnimBPClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PlayerAnimBPClass.Class);
	}
	// 1. CONFIGURAR EL MOVIMIENTO DEL PERSONAJE
	// No rotes el personaje con el movimiento del rat�n/c�mara
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configura el movimiento para que el personaje rote en la direcci�n en la que se mueve
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...a esta velocidad

	// 1. Activamos la restricci�n a un plano.
	GetCharacterMovement()->bConstrainToPlane = true;

	// 2. Definimos el plano. Queremos que se mueva en los ejes Y (derecha/izquierda) y Z (arriba/abajo),
	//    pero que se quede fijo en el eje X (profundidad).
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(1.0f, 0.0f, 0.0f));

	// 2. CREAR EL "PALO SELFIE" (SPRING ARM)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent); // Lo enganchamos a la ra�z del personaje
	CameraBoom->SetRelativeLocation(FVector(0, 0, 60)); // Lo subimos un poco
	CameraBoom->TargetArmLength = 500.0f; // Distancia de la c�mara
	CameraBoom->bUsePawnControlRotation = true; // Permite que el control rote el brazo

	// 3. CREAR LA C�MARA
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // La enganchamos al final del "palo selfie"
	FollowCamera->bUsePawnControlRotation = false; // La c�mara no rota con el "palo selfie", as� se mantiene estable

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ADKCPlayerCharacter::OnPlayerHit);

	// Suscribimos nuestras funciones a los delegados de Overlap de la c�psula del jugador.
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADKCPlayerCharacter::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ADKCPlayerCharacter::OnEndOverlap);
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	CurrentStrategy = CreateDefaultSubobject<UDonkeyKongStrategy>(TEXT("DefaultStrategy"));
}


void ADKCPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Creamos una instancia de nuestro estado inicial
	CurrentState = NewObject<UIdleState>(this);
	if (CurrentState)
	{
		// Llamamos a su funci�n OnEnter para que se configure
		CurrentState->OnEnter(this);
	}

	// Comprobamos si hemos asignado una clase de widget en el editor.
	if (HUDWidgetClass)
	{
		// Creamos la instancia del widget.
		HUDWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		// Comprobamos si se cre� correctamente y lo a�adimos a la pantalla.
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
		}
	}
	// Nos suscribimos a nuestro propio evento de muerte
	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddDynamic(this, &ADKCPlayerCharacter::OnPlayerDeath);
	}

	if (CurrentStrategy)
	{
		CurrentStrategy->SetPlayerCharacter(this);
		CurrentStrategy->AdjustMovementParameters();
	}
}


void ADKCPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// En cada fotograma, en lugar de hacer algo, le decimos al estado actual que trabaje.
	if (CurrentState)
	{
		CurrentState->TickState(DeltaTime);
	}

}

void ADKCPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADKCPlayerCharacter::JumpPressed);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &ADKCPlayerCharacter::RollPressed);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ADKCPlayerCharacter::Interact);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADKCPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADKCPlayerCharacter::MoveUp);
	PlayerInputComponent->BindAction("SwitchCharacter", IE_Pressed, this, &ADKCPlayerCharacter::SwitchCharacter);

}

void ADKCPlayerCharacter::MoveRight(float Value)
{
	// A�ade movimiento en la direcci�n Y (que en el plano 2.5D es derecha/izquierda)
	// El valor "Value" ser� -1.0 para la tecla A y +1.0 para la tecla D.
	if (Controller != nullptr && Value != 0.0f)
	{
		AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
	}
}

void ADKCPlayerCharacter::SwitchState(UPlayerBaseState* NewState)
{
	if (CurrentState)
	{
		// Llama a la limpieza del estado viejo
		CurrentState->OnExit();
	}

	// Cambia al nuevo estado
	CurrentState = NewState;

	if (CurrentState)
	{
		// Llama a la configuraci�n del nuevo estado
		CurrentState->OnEnter(this);
	}
}

void ADKCPlayerCharacter::JumpPressed()
{
	if (CurrentState)
	{
		CurrentState->HandleJumpInput();
	}
}

void ADKCPlayerCharacter::RollPressed() 
{
	if (CurrentState)
	{
		CurrentStrategy->ExecuteRoll(); //delegamos al patron strategia
	}
}

void ADKCPlayerCharacter::OnPlayerHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
	if (Enemy)
	{
		// Si estamos cayendo (es un pisot�n)...
		if (GetVelocity().Z < 0)
		{
			// Damos el rebote al jugador.
			LaunchCharacter(FVector(0.f, 0.f, 600.f), false, false);

			// --- L�GICA MODIFICADA ---
			// Primero, intentamos ver si el enemigo es un Army.
			AArmyCharacter* Army = Cast<AArmyCharacter>(Enemy);
			if (Army)
			{
				// Si es un Army, lo convertimos en caparaz�n.
				Army->EnterShellState();
			}
			else
			{
				// Si no es un Army, le hacemos da�o como siempre.
				UHealthComponent* EnemyHealth = Enemy->HealthComponent;
				if (EnemyHealth)
				{
					EnemyHealth->TakeDamage(3.0f);
				}
			}
		}
		else // Choque lateral
		{
			if (HealthComponent)
			{
				HealthComponent->TakeDamage(1.0f);
			}
		}
	}
}

void ADKCPlayerCharacter::Interact()
{
	// Si ya estamos sosteniendo algo, lo soltamos. y hace da�o
	
	if (HeldObject)
	{
		// 1. Lo separamos del personaje.
		HeldObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		// 2. Reactivamos la colisi�n y f�sicas.
		HeldObject->BarrelMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		HeldObject->BarrelMesh->SetSimulatePhysics(true);

		// 4. Obtenemos la direcci�n en la que el personaje est� orientado.
		// Esto siempre ser� perfectamente a la derecha (Y=1) o a la izquierda (Y=-1).
		const FVector CharacterDirection = GetMesh()->GetRightVector();
		const float ThrowStrength = 2500.f;

		// 5. Aplicamos el impulso usando esta direcci�n pura.
		HeldObject->BarrelMesh->AddImpulse(CharacterDirection * ThrowStrength * HeldObject->BarrelMesh->GetMass());

		// 6. Rompemos nuestro v�nculo con el objeto.
		HeldObject = nullptr;
	}
	// Si no estamos sosteniendo nada, intentamos recoger algo.
	else
	{
		// Buscamos actores con los que podamos chocar cerca de nosotros.
		TArray<FHitResult> HitResults;
		FVector SweepStart = GetActorLocation();
		FVector SweepEnd = GetActorLocation();
		FCollisionShape Sphere = FCollisionShape::MakeSphere(150.f); // Un radio de 150 unidades

		bool bHit = GetWorld()->SweepMultiByChannel(HitResults, SweepStart, SweepEnd, FQuat::Identity, ECC_WorldDynamic, Sphere);

		if (bHit)
		{
			for (auto& Hit : HitResults)
			{
				ABarrelBase* Barrel = Cast<ABarrelBase>(Hit.GetActor());
				if (Barrel)
				{
					HeldObject = Barrel;
					// Desactivamos las f�sicas para que no se comporte de forma extra�a.
					HeldObject->BarrelMesh->SetSimulatePhysics(false);
					// Apagamos por completo su colisi�n.
					HeldObject->BarrelMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					// Pegamos el barril a un "socket" (punto de anclaje) en nuestro personaje.
					// Usaremos la pelvis por ahora, luego se puede crear un socket espec�fico en las manos.
					HeldObject->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("pelvis"));
					break; // Salimos del bucle una vez que encontramos un barril.
				}
			}
		}
	}
}

void ADKCPlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// --- L�GICA DE DEPURACI�N ---
	if (CurrentState)
	{
		// Imprimimos el nombre del estado actual para saber en qu� estado estamos al chocar.
		UE_LOG(LogTemp, Warning, TEXT("Overlap detectado. Estado actual: %s"), *CurrentState->GetName());
	}

	// �Estamos en un estado de roll?
	if (CurrentState && (CurrentState->IsA<UGroundRollState>() || CurrentState->IsA<UAirRollState>()))
	{
		UE_LOG(LogTemp, Warning, TEXT("CONDICI�N DE ROLL CUMPLIDA."));

		AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
		if (Enemy)
		{
			UE_LOG(LogTemp, Warning, TEXT("OVERLAP CON ENEMIGO MIENTRAS SE RUEDA. Aplicando da�o..."));

			UHealthComponent* EnemyHealth = Enemy->HealthComponent;
			if (EnemyHealth)
			{
				EnemyHealth->TakeDamage(3.0f);
			}
			return;
		}
	}

	// --- L�GICA ANTERIOR (LIANAS Y RAMBI) ---
	AVineActor* Vine = Cast<AVineActor>(OtherActor);
	if (Vine)
	{
		bIsOverlappingVine = true;
		OverlappingVine = Vine;
		UE_LOG(LogTemp, Warning, TEXT("OVERLAP CON LIANA INICIADO"));

		if (GetCharacterMovement()->IsFalling())
		{
			SwitchState(NewObject<UClimbingState>());
		}
		return;
	}

	ARambiCharacter* Rambi = Cast<ARambiCharacter>(OtherActor);
	if (Rambi)
	{
		Rambi->Mount(this);
	}
}

void ADKCPlayerCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AVineActor* Vine = Cast<AVineActor>(OtherActor);
	if (Vine)
	{
		bIsOverlappingVine = false;
		OverlappingVine = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("OVERLAP CON LIANA TERMINADO"));
	}
}

void ADKCPlayerCharacter::MoveUp(float Value)
{
	if (CurrentState)
	{
		CurrentState->HandleMoveUpInput(Value);
	}
}

void ADKCPlayerCharacter::OnPlayerDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("EL JUGADOR HA MUERTO."));

	// Desactivamos el input para que no se pueda mover mientras est� muerto
	DisableInput(nullptr);

	// Le notificamos al GameMode que hemos muerto
	ADKCCloneGameMode* GameMode = Cast<ADKCCloneGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->PlayerDied(this);
	}
}

void ADKCPlayerCharacter::SetStrategy(TSubclassOf<UPlayerStrategy> NewStrategyClass)
{
	if (NewStrategyClass)
	{
		CurrentStrategy = NewObject<UPlayerStrategy>(this, NewStrategyClass);
		if (CurrentStrategy)
		{
			CurrentStrategy->SetPlayerCharacter(this);
			CurrentStrategy->AdjustMovementParameters();
			UE_LOG(LogTemp, Warning, TEXT("Strategy Changed to: %s"), *CurrentStrategy->GetName());
		}
	}
}

void ADKCPlayerCharacter::SwitchCharacter()
{
	// Si la estrategia actual es la de DK, cambiamos a Diddy, y viceversa.
	if (CurrentStrategy->IsA<UDonkeyKongStrategy>())
	{
		SetStrategy(UDiddyKongStrategy::StaticClass());
		
	}
	else
	{
		SetStrategy(UDonkeyKongStrategy::StaticClass());
		
	}
}