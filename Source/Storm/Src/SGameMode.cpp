#include "SGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Enemy/EnemyBase.h"
#include "Spawner.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SGameInstance.h"

void ASGameMode::BeginPlay() {
    Super::BeginPlay();

    MainMenuWidget = CreateWidget(GetWorld(), MainMenuScreen);
    SettingsWidget = CreateWidget(GetWorld(), SettingsScreen);
    CreditsWidget = CreateWidget(GetWorld(), CreditsScreen);
    PauseWidget = CreateWidget(GetWorld(), PauseScreen);
    HUDWidget = CreateWidget(GetWorld(), HUDScreen);
    GameOverWidget = CreateWidget(GetWorld(), GameOverScreen);
    EndGameWidget = CreateWidget(GetWorld(), EndGameScreen);
    OpeningSceneWidget = CreateWidget(GetWorld(), OpeningSceneScreen);

    PlayerController = GetWorld()->GetFirstPlayerController();

    ToggleGameplay(false);

    ShowMainMenuScreen();
}

void ASGameMode::ActorDied(AActor* DeadActor) {
    UE_LOG(LogTemp, Warning, TEXT("this actor died: %s"), *DeadActor->GetActorNameOrLabel());
    
    AEnemyBase* DeadEnemy = Cast<AEnemyBase>(DeadActor);
    if(DeadEnemy){
        DeadEnemy->ToggleIsDead(true);
        NumberOfKilledEnemies++;
        return;
    }

    ASpawner* Spawner = Cast<ASpawner>(DeadActor);
    if(Spawner) {
        Spawner->HandleDestruction();
        CurrentNumberOfDestroyedSpawners++;
        // the win condition
        if(CurrentNumberOfDestroyedSpawners >= NumberOfSpawnersToDestroy){
            ShowEndGameScreen();
        }
        return;
    }

    APlayerCharacter* Player = Cast<APlayerCharacter>(DeadActor);
    if(Player) {
        Player->HandlePlayerDied();
        ShowGameOverScreen();
        return;
    }
}

void ASGameMode::AddToEnemies(AEnemyBase* Enemy) {
    Enemies.Add(Enemy);
}

AEnemyBase* ASGameMode::GetADeadEnemy() const {
    for(AEnemyBase* Enemy : Enemies){
        if(Enemy->GetIsDead() == true){
            return Enemy;
        }
    }

    return nullptr;
}

void ASGameMode::ToggleGameplay(bool bIsGameplayMode) {
    if(bIsGameplayMode) {
        UGameplayStatics::SetGamePaused(GetWorld(), false);

        if(PlayerController){
            PlayerController->SetShowMouseCursor(false);
            PlayerController->SetInputMode(FInputModeGameOnly());
        }
    }else {
        if(PlayerController){
            PlayerController->SetShowMouseCursor(true);
            PlayerController->SetInputMode(FInputModeUIOnly());
        }
        UGameplayStatics::SetGamePaused(GetWorld(), true);
    }
}

void ASGameMode::ShowMainMenuScreen(){
    bGameStarted = false;
    ToggleGameplay(false);
    SetCurrentWidgetToWidget(MainMenuWidget);
}

void ASGameMode::ShowSettingsScreen(){
    ToggleGameplay(false);
    SetCurrentWidgetToWidget(SettingsWidget);
}

void ASGameMode::ShowCreditsScreen(){
    ToggleGameplay(false);
    SetCurrentWidgetToWidget(CreditsWidget);
}

void ASGameMode::ShowPauseScreen(){
    ToggleGameplay(false);
    SetCurrentWidgetToWidget(PauseWidget);
}

void ASGameMode::ShowHUDScreen(){
    bGameStarted = true;
    ToggleGameplay(true);
    SetCurrentWidgetToWidget(HUDWidget);

    // TEMP CODE to test
    USGameInstance* GameInstance = Cast<USGameInstance>(GetWorld()->GetGameInstance());
    if(GameInstance) {
        GameInstance->GenerateCave();
    }

}

void ASGameMode::ShowGameOverScreen(){
    ToggleGameplay(false);
    SetCurrentWidgetToWidget(GameOverWidget);
}

void ASGameMode::ShowEndGameScreen(){
    ToggleGameplay(false);
    SetCurrentWidgetToWidget(EndGameWidget);
}

void ASGameMode::ShowOpeningSceneScreen() {
    SetCurrentWidgetToWidget(OpeningSceneWidget);
}

void ASGameMode::SetCurrentWidgetToWidget(class UUserWidget* Widget) {
    if(Widget){
        if(CurrentWidget != nullptr){
            CurrentWidget->RemoveFromParent();
        }
        CurrentWidget = Widget;
        CurrentWidget->AddToViewport();
    }
}

// TODO: probably make a different UFUNCTION for the intro cut scene play here and leave this one for just playing game
void ASGameMode::PlayGame() {

}

bool ASGameMode::IsGamePaused() const {
    return UGameplayStatics::IsGamePaused(GetWorld());
}

void ASGameMode::ShowWidget(UUserWidget* WidgetToShow, TSubclassOf<UUserWidget> WidgetClass) {
    if(!WidgetToShow) {
        WidgetToShow = CreateWidget(GetWorld(), WidgetClass);
    }

    if(!WidgetToShow->IsInViewport()) {
        WidgetToShow->AddToViewport();
    }
}

void ASGameMode::HideWidget(UUserWidget* WidgetToHide, TSubclassOf<UUserWidget> WidgetClass) {
    if(WidgetToHide && WidgetToHide->IsInViewport()) {
        WidgetToHide->RemoveFromParent();
        WidgetToHide = nullptr;
    }
}