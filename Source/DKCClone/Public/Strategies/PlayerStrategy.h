#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerStrategy.generated.h"

class ADKCPlayerCharacter;

UCLASS(Blueprintable)
class DKCCLONE_API UPlayerStrategy : public UObject
{
    GENERATED_BODY()

public:
    // "Contrato" que todas las estrategias deben seguir.
    virtual void SetPlayerCharacter(ADKCPlayerCharacter* Player);
    virtual void ExecuteRoll() PURE_VIRTUAL(UPlayerStrategy::ExecuteRoll, );
    virtual void AdjustMovementParameters() PURE_VIRTUAL(UPlayerStrategy::AdjustMovementParameters, );

protected:
    UPROPERTY()
    ADKCPlayerCharacter* PlayerCharacter;
};