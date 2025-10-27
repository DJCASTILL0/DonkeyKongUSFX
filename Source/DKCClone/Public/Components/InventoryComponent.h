#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Set.h"
#include "InventoryComponent.generated.h"

// Delegate para notificar cuando el número de bananas cambie (Patrón Observador)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBananaCountChanged, int32, NewBananaCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLivesCountChanged, int32, NewLivesCount);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DKCCLONE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();
	void AddBanana();  //<-- añadir bananas funxion
	void AddLife(int32 Amount = 1);
	int32 GetLives() const { return Vidas; }
	UPROPERTY(BlueprintAssignable)   //  -<<delegadoq ue lo emititra
	FOnBananaCountChanged OnBananaCountChanged;
	UPROPERTY(BlueprintAssignable)
	FOnLivesCountChanged OnLivesCountChanged;
	void AddKongLetter(const FName& Letter);
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 BananaCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventario")
	int32 Vidas;
	// Usamos un TSet para guardar las letras. Un Set no permite duplicados.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventario")
	TSet<FName> LetrasKONGRecogidas;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
