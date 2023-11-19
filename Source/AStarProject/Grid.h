#pragma once

#include "CoreMinimal.h"
#include "GridMesh.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

UCLASS()
class ASTARPROJECT_API AGrid : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGrid();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "GridProperties")
		TSubclassOf<AGridMesh> GridMesh_Class;
	TObjectPtr<AGridMesh> GridMesh;

	UPROPERTY(EditDefaultsOnly, Category = "GridProperties")
		int NumberOfRows;

	UPROPERTY(EditDefaultsOnly, Category = "GridProperties")
		int NumberOfColumns;

	UPROPERTY(EditDefaultsOnly, Category = "GridProperties")
		int GridSpacing;

	UPROPERTY(EditDefaultsOnly, Category = "GridProperties")
		int GridSpacingDiagonal;

	UPROPERTY(EditDefaultsOnly, Category = "GridProperties")
		int ColorOpacity;

	UPROPERTY(EditDefaultsOnly, Category = "GridProperties")
		TObjectPtr<UMaterialInterface> GridMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "GridProperties")
		FLinearColor WalkableSectionColor;

	UPROPERTY(EditDefaultsOnly, Category = "GridProperties")
		FLinearColor UnWalkableSectionColor;

	UPROPERTY(EditDefaultsOnly, Category = "GridProperties")
		FLinearColor PlayerPositionColor;

	UPROPERTY(EditAnywhere, Category = "PathFinding")
		AActor* StartNodePosition;

	UPROPERTY(EditAnywhere, Category = "PathFinding")
		AActor* EndNodePosition;

	void CreateGrid();
	UMaterialInstanceDynamic* CreateMaterialInstance(FLinearColor Color, int Opacity);
	void IsGridWalkable();
	void FindPath(FVector StartPosition, FVector Destination);
	void RetracePath(AGridMesh* StartNode, AGridMesh* EndNode);
	int GetDistanceBetweenNodes(AGridMesh* NodeA, AGridMesh* NodeB);
	AGridMesh* GetGridFromPosition(FVector WorldPosition);
	TArray<AGridMesh*> GetNeighborNodes(AGridMesh* Node);
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<TObjectPtr<AGridMesh>> Grids;
};
