#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameMode.generated.h"


UCLASS()
class STORM_API ASGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:

	// --- TODO: probably move to a UI manager class
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDScreen;

	class UUserWidget* HUDWidget;
	// ----------------------------------------------

public:

	void ActorDied(AActor* DeadActor);

	// --- TODO: probably move to a UI manager class
	UFUNCTION(Blueprintcallable)
	void ShowWidget(UUserWidget* WidgetToShow, TSubclassOf<UUserWidget> WidgetClass);

	UFUNCTION(Blueprintcallable)
	void HideWidget(UUserWidget* WidgetToHide, TSubclassOf<UUserWidget> WidgetClass);
	// ----------------------------------------------

protected:

	virtual void BeginPlay() override;
	
};
