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

	// !!! ---------------------------------- EXTREMELY IMPORTANT to have UPROPERTY() to ensure that widgets don't get garbage collected
	UPROPERTY()
	class UUserWidget* HUDWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screens", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> MainMenuScreen;

	UPROPERTY()
	class UUserWidget* MainMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screens", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> SettingsScreen;

	UPROPERTY()
	class UUserWidget* SettingsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screens", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> CreditsScreen;

	UPROPERTY()
	class UUserWidget* CreditsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screens", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> PauseScreen;

	UPROPERTY()
	class UUserWidget* PauseWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screens", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> GameOverScreen;

	UPROPERTY()
	class UUserWidget* GameOverWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screens", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> EndGameScreen;

	UPROPERTY()
	class UUserWidget* EndGameWidget;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

	void HideAllActiveWidgets();

	void ToggleGameplay(bool bIsGameplayMode);

	void SetCurrentWidgetToWidget(class UUserWidget* Widget);

	APlayerController* PlayerController;

	bool bGameStarted = false;

	// ----------------------------------------------

	TArray<class AEnemyBase*> Enemies;

	int NumberOfKilledEnemies = 0;

	int CurrentNumberOfDestroyedSpawners = 0;

public:

	UPROPERTY(EditAnywhere)
	int MaxNumberOfEntities = 25;

	UPROPERTY(EditAnywhere)
	int NumberOfSpawnersToDestroy = 1;

	void ActorDied(AActor* DeadActor);

	// --- TODO: probably move to a UI manager class
	UFUNCTION(Blueprintcallable)
	void ShowWidget(UUserWidget* WidgetToShow, TSubclassOf<UUserWidget> WidgetClass);

	UFUNCTION(Blueprintcallable)
	void HideWidget(UUserWidget* WidgetToHide, TSubclassOf<UUserWidget> WidgetClass);

	UFUNCTION(Blueprintcallable)
	void ShowMainMenuScreen();

	UFUNCTION(Blueprintcallable)
	void ShowSettingsScreen();

	UFUNCTION(Blueprintcallable)
	void ShowCreditsScreen();

	UFUNCTION(Blueprintcallable)
	void ShowPauseScreen();

	UFUNCTION(Blueprintcallable)
	void ShowHUDScreen();

	UFUNCTION(Blueprintcallable)
	void ShowGameOverScreen();

	UFUNCTION(Blueprintcallable)
	void ShowEndGameScreen();

	UFUNCTION(Blueprintcallable)
	void PlayGame();

	UFUNCTION(Blueprintcallable)
	bool IsGameStarted() const { return bGameStarted; }

	// ----------------------------------------------

	int GetCurrentNumberOfSpawnedEnemies() const { return Enemies.Num(); }

	class AEnemyBase* GetADeadEnemy() const;

	TArray<class AEnemyBase*> GetEnemies() const { return Enemies; }

	void AddToEnemies(AEnemyBase* Enemy);

	bool IsGamePaused() const;

	UFUNCTION(Blueprintcallable)
	int GetNumberOfKilledEnemies() const { return NumberOfKilledEnemies; }

protected:

	virtual void BeginPlay() override;
	
};
