#include "SGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Enemy/EnemyBase.h"
#include "Spawner.h"

void ASGameMode::BeginPlay() {
    Super::BeginPlay();

    ShowWidget(HUDWidget, HUDScreen);
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