#pragma once

#include "CoreMinimal.h"
#include "Strategies/PlayerStrategy.h"
#include "DiddyKongStrategy.generated.h"

UCLASS()
class DKCCLONE_API UDiddyKongStrategy : public UPlayerStrategy
{
    GENERATED_BODY()
public:
    virtual void ExecuteRoll() override;
    virtual void AdjustMovementParameters() override;
};