#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CaveGenerator.generated.h"

UCLASS()
class STORM_API UCaveGenerator : public UObject
{
	GENERATED_BODY()
	

private:

	TArray<TArray<int>> CaveGrid;

	void InitRandomGrid(int Width, int Height);

	void CellularAutomata();

	int CountWallNeighbors(int X, int Y);

	int TileSize = 20;

public:

	UCaveGenerator();

	void GenerateCave(int Width, int Height, int TileSize, int Iterations);

	TArray<TArray<int>> GetCaveGrid() const { return CaveGrid; }

	void VisualizeCave();
};
