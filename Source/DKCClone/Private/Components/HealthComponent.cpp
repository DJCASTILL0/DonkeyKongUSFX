#include "Components/HealthComponent.h"
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxHealth = 3.f;
	CurrentHealth = MaxHealth;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::TakeDamage(float DamageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("TakeDamage llamado en %s. Daño: %f"), *GetOwner()->GetName(), DamageAmount);
	if (CurrentHealth <= 0.f)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(CurrentHealth);

	if (CurrentHealth <= 0.f)
	{
		OnDeath.Broadcast();
	}
}