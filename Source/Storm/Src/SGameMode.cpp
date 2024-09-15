#include "SGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Enemy/EnemyBase.h"
#include "Spawner.h"
#include "Kismet/GameplayStatics.h"

void ASGameMode::BeginPlay() {
    Super::BeginPlay();

    MainMenuWidget = CreateWidget(GetWorld(), MainMenuScreen);
    SettingsWidget = CreateWidget(GetWorld(), SettingsScreen);
    CreditsWidget = CreateWidget(GetWorld(), CreditsScreen);
    PauseWidget = CreateWidget(GetWorld(), PauseScreen);
    HUDWidget = CreateWidget(GetWorld(), HUDScreen);

    PlayerController = GetWorld()->GetFirstPlayerController();

    ToggleGameplay(false);

    ShowMainMenuScreen();
}

void ASGameMode::ActorDied(AActor* DeadActor) {
    UE_LOG(LogTemp, Warning, TEXT("this actor died: %s"), *DeadActor->GetActorNameOrLabel());
    
    AEnemyBase* DeadEnemy = Cast<AEnemyBase>(DeadActor);
    if(DeadEnemy){
        DeadEnemy->ToggleIsDead(true);
        return;
    }

    ASpawner* Spawner = Cast<ASpawner>(DeadActor);
    if(Spawner) {
        Spawner->HandleDestruction();
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
    if(MainMenuWidget){
        if(CurrentWidget != nullptr){
            CurrentWidget->RemoveFromParent();
        }
        CurrentWidget = MainMenuWidget;
        CurrentWidget->AddToViewport();
    }
}

void ASGameMode::ShowSettingsScreen(){
    ToggleGameplay(false);
    if(SettingsWidget){
        if(CurrentWidget != nullptr){
            CurrentWidget->RemoveFromParent();
        }
        CurrentWidget = SettingsWidget;
        CurrentWidget->AddToViewport();
    }
}

void ASGameMode::ShowCreditsScreen(){
    ToggleGameplay(false);
    if(CreditsWidget){
        if(CurrentWidget != nullptr){
            CurrentWidget->RemoveFromParent();
        }
        CurrentWidget = CreditsWidget;
        CurrentWidget->AddToViewport();
    }
}

void ASGameMode::ShowPauseScreen(){
    ToggleGameplay(false);
    if(PauseWidget){
        if(CurrentWidget != nullptr){
            CurrentWidget->RemoveFromParent();
        }
        CurrentWidget = PauseWidget;
        CurrentWidget->AddToViewport();
    }
}

void ASGameMode::ShowHUDScreen(){
    bGameStarted = true;
    ToggleGameplay(true);
    if(HUDWidget){
        if(CurrentWidget != nullptr){
            CurrentWidget->RemoveFromParent();
        }
        CurrentWidget = HUDWidget;
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