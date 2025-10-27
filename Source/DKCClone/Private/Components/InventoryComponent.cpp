#include "Components/InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	BananaCount = 0;
	Vidas = 5;
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
	if (BananaCount >= 5)
	{
		BananaCount = 0; // Reiniciamos el contador
		AddLife(); // Añadimos una vida
	}
	// Emitimos el evento para que quien esté escuchando (el HUD) sepa del cambio.
	OnBananaCountChanged.Broadcast(BananaCount);
}

void UInventoryComponent::AddLife(int32 Amount)
{
	Vidas += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Vida añadida! Vidas totales: %d"), Vidas);
	OnLivesCountChanged.Broadcast(Vidas);
}

void UInventoryComponent::AddKongLetter(const FName& Letter)
{
	// Añadimos la letra al Set. Si ya estaba, no hace nada.
	LetrasKONGRecogidas.Add(Letter);
	UE_LOG(LogTemp, Warning, TEXT("Letra KONG recogida: %s"), *Letter.ToString());

	// Comprobamos si ya tenemos las 4
	if (LetrasKONGRecogidas.Num() >= 4)
	{
		// Comprobamos que de verdad tenemos K, O, N, y G
		if (LetrasKONGRecogidas.Contains(FName("K")) &&
			LetrasKONGRecogidas.Contains(FName("O")) &&
			LetrasKONGRecogidas.Contains(FName("N")) &&
			LetrasKONGRecogidas.Contains(FName("G")))
		{
			AddLife(); // Añadimos una vida
			LetrasKONGRecogidas.Empty(); // Vaciamos el set para poder volver a recogerlas
			UE_LOG(LogTemp, Warning, TEXT("PALABRA KONG COMPLETA! Vida extra!"));
		}
	}
}