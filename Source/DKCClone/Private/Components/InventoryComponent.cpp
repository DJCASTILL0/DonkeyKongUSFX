#include "Components/InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	BananaCount = 0;
	
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInventoryComponent::AddBanana()
{
	BananaCount++;
	UE_LOG(LogTemp, Warning, TEXT("Banana collected! Total: %d"), BananaCount);

	// Emitimos el evento para que quien esté escuchando (el HUD) sepa del cambio.
	OnBananaCountChanged.Broadcast(BananaCount);
}