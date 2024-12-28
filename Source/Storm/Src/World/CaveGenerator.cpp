#include "CaveGenerator.h"
#include "DrawDebugHelpers.h"

UCaveGenerator::UCaveGenerator() { }

void UCaveGenerator::GenerateCave(int Width, int Height, int _TileSize, int Iterations) {
    TileSize = _TileSize;
    InitRandomGrid(Width, Height);

    for(int i = 0; i < Iterations; i++){
        CellularAutomata();
    }

    VisualizeCave();
}

void UCaveGenerator::InitRandomGrid(int Width, int Height) {
    CaveGrid.SetNum(Height);
    for(int y = 0; y < Height; y++) {
        CaveGrid[y].SetNum(Width);
        for(int x = 0; x < Width; x++) {
            CaveGrid[y][x] = (FMath::RandRange(0.0f, 1.0f) < 0.46f) ? 0 : 1;
        }
    }
}

void UCaveGenerator::CellularAutomata() {

    TArray<TArray<int>> TempGrid = CaveGrid;

    for (int y = 0; y < CaveGrid.Num(); y++) {
        for (int x = 0; x < CaveGrid[y].Num(); x++) {
            
            int NeighborWalls = CountWallNeighbors(x, y);

            if (CaveGrid[y][x] == 1) {
                // Floor
                TempGrid[y][x] = (NeighborWalls >= 5) ? 0 : 1;
            }
            else {
                // Wall
                TempGrid[y][x] = (NeighborWalls >= 4) ? 0 : 1;
            }
        }
    }
    
    CaveGrid = TempGrid;
}

int UCaveGenerator::CountWallNeighbors(int X, int Y)
{
    int WallCount = 0;

    for (int OffsetY = -1; OffsetY <= 1; OffsetY++) {
        for (int OffsetX = -1; OffsetX <= 1; OffsetX++) {

            if (OffsetX == 0 && OffsetY == 0) {
                continue;
            }

            int NeighborX = X + OffsetX;
            int NeighborY = Y + OffsetY;

            if (NeighborX >= 0 && NeighborX < CaveGrid[0].Num() && NeighborY >= 0 && NeighborY < CaveGrid.Num()) {
                if (CaveGrid[NeighborY][NeighborX] == 0) {
                    WallCount++;
                }
            }
            else {
                WallCount++;
            }
        }
    }

    return WallCount;
}

void UCaveGenerator::VisualizeCave() {

    FVector TileHalfSize = FVector(TileSize * 0.5f, TileSize * 0.5f, 500.f);

    for(int y = 0; y < CaveGrid.Num(); y++) {
        for(int x = 0; x < CaveGrid[y].Num(); x++) {
            FVector Location = FVector(x * TileSize, y * TileSize, -0.5f);
            if(CaveGrid[y][x] == 0){
                // we have a wall
                DrawDebugBox(GetWorld(), Location, TileHalfSize, FColor::Green, true, -1.f, 0, 5.0f);
            }
        }
    }
}