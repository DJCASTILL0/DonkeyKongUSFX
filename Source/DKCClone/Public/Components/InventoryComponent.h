#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

// Delegate para notificar cuando el número de bananas cambie (Patrón Observador)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBananaCountChanged, int32, NewBananaCount);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DKCCLONE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();
	void AddBanana();  //<-- añadir bananas funxion

	UPROPERTY(BlueprintAssignable)   //  -<<delegadoq ue lo emititra
	FOnBananaCountChanged OnBananaCountChanged;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 BananaCount;


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
