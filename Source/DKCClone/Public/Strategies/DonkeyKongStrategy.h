#pragma once

#include "CoreMinimal.h"
#include "Strategies/PlayerStrategy.h"
#include "DonkeyKongStrategy.generated.h"

UCLASS()
class DKCCLONE_API UDonkeyKongStrategy : public UPlayerStrategy
{
    GENERATED_BODY()
public:
    virtual void ExecuteRoll() override;
    virtual void AdjustMovementParameters() override;
};