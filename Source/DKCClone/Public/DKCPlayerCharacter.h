
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DKCPlayerCharacter.generated.h"

// Forward declaration para no tener que incluir los headers aquí
class UCameraComponent;
class USpringArmComponent;
class UPlayerBaseState;
class UHealthComponent; 
class ABarrelBase;
class AVineActor;
class UInventoryComponent;


UCLASS()
class DKCCLONE_API ADKCPlayerCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ADKCPlayerCharacter();
	void SwitchState(UPlayerBaseState* NewState);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	//paso 14
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent; // <-- AÑADE ESTA LÍNEA
	UPROPERTY()
	UPlayerBaseState* CurrentState;
	
	// Variable para guardar la CLASE de nuestro widget. La asignaremos en el editor.
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	// Variable para guardar la INSTANCIA del widget que creemos.
	UPROPERTY()
	class UUserWidget* HUDWidgetInstance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent; // <-- AÑADE ESTA LÍNEA para bananas creo
	// Sobrescribe la función BeginPlay (ya debería estar)
	virtual void BeginPlay() override;
	void MoveRight(float Value);

	void JumpPressed(); //<- añade erta linea paso 11
	void RollPressed(); // <-- AÑADE ESTA LÍNEA paso 12
	UFUNCTION()
	void OnPlayerHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY()
	ABarrelBase* HeldObject;
	//si va mortir o no
	UFUNCTION()
	void OnPlayerDeath();
	// Función que se llamará para intentar recoger o soltar un objeto.
	void Interact();
	// Variables para saber si estamos tocando una liana y cuál es.
	bool bIsOverlappingVine;
	AVineActor* OverlappingVine;

	// Funciones que se llamarán al empezar/terminar el overlap.
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void MoveUp(float Value);  //<--- paso 23 liana


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UHealthComponent* GetHealthComponent() const { return HealthComponent; }
	FORCEINLINE class AVineActor* GetOverlappingVine() const { return OverlappingVine; } // <- para usar protegidos
	FORCEINLINE UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
};
