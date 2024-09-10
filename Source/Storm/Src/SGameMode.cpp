#include "SGameMode.h"
#include "Blueprint/UserWidget.h"

void ASGameMode::BeginPlay() {
    Super::BeginPlay();

    ShowWidget(HUDWidget, HUDScreen);
}

void ASGameMode::ActorDied(AActor* DeadActor) {
    UE_LOG(LogTemp, Warning, TEXT("this actor died: %s"), *DeadActor->GetActorNameOrLabel());
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