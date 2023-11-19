// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NumberOfRows = 10;
	NumberOfColumns = 10;
	GridSpacing = 100;
	GridSpacingDiagonal = 141;
	ColorOpacity = 1;
	WalkableSectionColor = FLinearColor::White;
	UnWalkableSectionColor = FLinearColor::Black;
	PlayerPositionColor = FLinearColor::Blue;
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

	CreateGrid();
	IsGridWalkable();
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FindPath(StartNodePosition->GetActorLocation(), EndNodePosition->GetActorLocation());
}

void AGrid::CreateGrid()
{
	if (GridMesh_Class)
	{
		for (size_t i{ 0 }; i < NumberOfRows; i++)
		{
			for (size_t j{ 0 }; j < NumberOfColumns; j++)
			{
				const FVector GridSpawnLocation((GetActorLocation().X) + (i * GridSpacing), (GetActorLocation().Y) + (j * GridSpacing), GetActorLocation().Z);
				const FRotator GridSpawnRotation(FRotator::ZeroRotator);

				GridMesh = GetWorld()->SpawnActor<AGridMesh>(GridMesh_Class, GridSpawnLocation, GridSpawnRotation);
				GridMesh->WorldPosition = GridMesh->GetActorLocation();
				GridMesh->GridX = i;
				GridMesh->GridY = j;
				Grids.Add(GridMesh);
			}
		}
	}
}

UMaterialInstanceDynamic* AGrid::CreateMaterialInstance(FLinearColor Color, int Opacity)
{
	UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(GridMaterial, this);
	MaterialInstance->SetVectorParameterValue(FName("Color"), Color);
	MaterialInstance->SetScalarParameterValue(FName("Opacity"), Opacity);
	return MaterialInstance;
}

void AGrid::IsGridWalkable()
{
	if (GridMesh_Class)
	{
		for (AGridMesh* Grid : Grids)
		{
			TArray<FOverlapResult> OverlapResults;
			if (Grid->GridComponent->ComponentOverlapMulti(OverlapResults, GetWorld(), Grid->GridComponent->GetComponentLocation(), Grid->GridComponent->GetComponentQuat(), ECC_OverlapAll_Deprecated))
			{
				for (FOverlapResult Result : OverlapResults)
				{
					if (Result.GetComponent() != Grid->GridComponent && Result.GetActor() != Grid)
					{
						UMaterialInstanceDynamic* MaterialInstance = CreateMaterialInstance(UnWalkableSectionColor, ColorOpacity);
						Grid->GridComponent->SetMaterial(0, MaterialInstance);
						Grid->b_IsWalkable = false;
					}
					else
					{
						UMaterialInstanceDynamic* MaterialInstance = CreateMaterialInstance(WalkableSectionColor, ColorOpacity);
						Grid->GridComponent->SetMaterial(0, MaterialInstance);
						Grid->b_IsWalkable = true;
					}
				}
			}
			else
			{
				UMaterialInstanceDynamic* MaterialInstance = CreateMaterialInstance(WalkableSectionColor, ColorOpacity);
				Grid->GridComponent->SetMaterial(0, MaterialInstance);
				Grid->b_IsWalkable = true;
			}
		}
	}
}

void AGrid::FindPath(FVector StartPosition, FVector Destination)
{
	AGridMesh* StartNode = GetGridFromPosition(StartPosition);
	AGridMesh* DestinationNode = GetGridFromPosition(Destination);

	TArray<AGridMesh*> OpenNodes;
	TArray<AGridMesh*> ClosedNodes;

	OpenNodes.Add(StartNode);
	while(OpenNodes.Num() > 0)
	{
		AGridMesh* CurrentNode = OpenNodes[0];
		for(size_t i {1}; i < OpenNodes.Num(); i++)
		{
			if(OpenNodes[i]->FCost() < CurrentNode->FCost() || OpenNodes[i]->FCost() == CurrentNode->FCost() && OpenNodes[i]->HCost < CurrentNode->HCost)
			{
				CurrentNode = OpenNodes[i];
			}
		}

		OpenNodes.Remove(CurrentNode);
		ClosedNodes.Add(CurrentNode);

		if (CurrentNode == DestinationNode)
		{
			RetracePath(StartNode, DestinationNode);
			return;
		}

		for(AGridMesh* Neighbor: GetNeighborNodes(CurrentNode))
		{
			if(!Neighbor->b_IsWalkable || ClosedNodes.Contains(Neighbor))
			{
				continue;	
			}

			const int NewMovementCostToNeighbor = CurrentNode->GCost + GetDistanceBetweenNodes(CurrentNode, Neighbor);

			if(NewMovementCostToNeighbor < Neighbor->GCost || !OpenNodes.Contains(Neighbor))
			{
				Neighbor->GCost = NewMovementCostToNeighbor;
				Neighbor->HCost = GetDistanceBetweenNodes(Neighbor, DestinationNode);
				Neighbor->Parent = CurrentNode;

				if(!OpenNodes.Contains(Neighbor))
				{
					OpenNodes.Add(Neighbor);
				}
			}
		}
	}
}

void AGrid::RetracePath(AGridMesh* StartNode, AGridMesh* EndNode)
{
	TArray<AGridMesh*> Path;
	AGridMesh* CurrentNode = EndNode;

	while(CurrentNode != StartNode)
	{
		Path.Add(CurrentNode);
		CurrentNode = CurrentNode->Parent;
	}

	for(AGridMesh* Node: Path)
	{
		UMaterialInstanceDynamic* MaterialInstance = CreateMaterialInstance(FLinearColor::Yellow, ColorOpacity);
		Node->GridComponent->SetMaterial(0, MaterialInstance);
	}

}

int AGrid::GetDistanceBetweenNodes(AGridMesh* NodeA, AGridMesh* NodeB)
{
	const int DistanceX = UKismetMathLibrary::Abs(NodeA->GridX - NodeB->GridX);
	const int DistanceY = UKismetMathLibrary::Abs(NodeA->GridY - NodeB->GridY);

	if(DistanceX > DistanceY)
		return GridSpacingDiagonal * DistanceY + GridSpacing * (DistanceX - DistanceY);

	return GridSpacingDiagonal * DistanceX + GridSpacing * (DistanceY - DistanceX);
}

AGridMesh* AGrid::GetGridFromPosition(FVector WorldPosition)
{
	const float GridWidth = NumberOfColumns * GridSpacing;
	const float GridHeight = NumberOfRows * GridSpacing;

	const int Row = floor(((WorldPosition.X - GetActorLocation().X) / GridWidth) * NumberOfRows);
	const int Column = floor(((WorldPosition.Y - GetActorLocation().Y) / GridHeight) * NumberOfColumns);
	
	const float GridLocationX = (Row * GridSpacing) + GetActorLocation().X;
	const float	GridLocationY = (Column * GridSpacing) + GetActorLocation().Y;

	const FVector GridPos(GridLocationX, GridLocationY, GetActorLocation().Z);
	AGridMesh* Grid = Grids[0];
	for(AGridMesh* Grid_Test : Grids)
	{
		if(Grid_Test->GetActorLocation() == GridPos)
		{
			Grid = Grid_Test;
		}
	}

	return Grid;
}

TArray<AGridMesh*> AGrid::GetNeighborNodes(AGridMesh* Node)
{
	TArray<AGridMesh*> Neighbors;

	for(int x {-1}; x <= 1; x++)
	{
		for(int y {-1}; y <= 1; y++)
		{
			if(x == 0 && y == 0)
				continue;

			const int CheckX = Node->GridX + x;
			const int CheckY = Node->GridY + y;

			if(CheckX >= 0 && CheckX < NumberOfRows && CheckY >= 0 && CheckY < NumberOfColumns)
			{
				for (AGridMesh* Grid : Grids)
				{
					if (Grid->GridX == CheckX && Grid->GridY == CheckY)
					{
						Neighbors.Add(Grid);
					}
				}
			}
			
		}
	}

	return Neighbors;
}
