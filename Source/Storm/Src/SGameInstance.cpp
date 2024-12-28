#include "SGameInstance.h"
#include "World/CaveGenerator.h"

void USGameInstance::Init() {
    Super::Init();
    CaveGenerator = NewObject<UCaveGenerator>(this);
}

void USGameInstance::GenerateCave() {
    if(CaveGenerator){
        CaveGenerator->GenerateCave(CaveWidth, CaveHeight, CaveTileSize, CaveAlgSteps);
    }
}