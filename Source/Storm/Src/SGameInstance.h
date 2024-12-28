#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SGameInstance.generated.h"

UCLASS()
class STORM_API USGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (AllowPrivateAccess = "true"))
	class UCaveGenerator* CaveGenerator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (AllowPrivateAccess = "true"))
	int CaveWidth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (AllowPrivateAccess = "true"))
	int CaveHeight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (AllowPrivateAccess = "true"))
	int CaveTileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (AllowPrivateAccess = "true"))
	int CaveAlgSteps;

public:

	virtual void Init() override;

	UCaveGenerator* GetCaveGenerator() const { return CaveGenerator; }

	void GenerateCave();

};
