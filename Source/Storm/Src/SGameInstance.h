#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SGameInstance.generated.h"

UCLASS()
class STORM_API USGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	
public:

	virtual void Init() override;
};
