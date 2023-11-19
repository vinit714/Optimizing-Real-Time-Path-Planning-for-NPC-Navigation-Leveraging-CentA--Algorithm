// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckN.h"

// Sets default values
ACheckN::ACheckN()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckN::BeginPlay()
{
	Super::BeginPlay();
	FVector Parent;

}

// Called every frame
void ACheckN::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckN::NearestA(FVector StartNode, FVector EndNode)
{
	ACheckN* StartNode;
	ACheckN* EndNode;
	ACheckN* Parent;
	FVector Parent;
	FVector StartN;
	FVector EndN;
	FVector MinX;
	FVector MinY;
	FVector Min;

	TArray<ACheckN*> OpenNodes;
	TArray<ACheckN*> ClosedNodes;
	TArray<ACheckN*> MinDist;
	TArray<ACheckN*> MinDist2;


	int  x = 0, y = 0,i,j;



	while (OpenNodes.Num() > 0) {
		ACheckN* StartNode = OpenNodes[0];
		for (size_t i{ 1 }; i < OpenNodes.Num(); i++) {
			if (OpenNodes[i] == Parent) { StartNode == OpenNodes[i]; x++; }
			else { StartNode == ClosedNodes[i]; }
		}
		ACheckN* EndNode = OpenNodes[0];
		for (size_t i{ 1 }; i < OpenNodes.Num(); i++) {
			if (OpenNodes[i] == Parent) { EndNode == OpenNodes[i]; x++; }
			else { EndNode == ClosedNodes[i]; }
		}
	}

	for (i = 0; i < x; i++) {
			ACheckN* MinX = OpenNodes[0];
			ACheckN* MinY = OpenNodes[0];
			ACheckN* Min = OpenNodes[0];
			MinX == MinDist[i];
			for (j = 0; j < x; j++) {
				MinY == MinDist2[j];
		}
	}

}

void ACheckN::MinCheck(FVector MinX, FVector MinY)
{
	FVector MinX;
	FVector MinY;
	FVector Min;
	FVector Dist = MinX - MinY;

	TArray<ACheckN*> OpenNodes;
	TArray<ACheckN*> ClosedNodes;
	TArray<ACheckN*> MinDist;
	TArray<ACheckN*> MinDist2;

	while (OpenNodes.Num() > 0) {
		ACheckN* MinDist = OpenNodes[0];
		ACheckN* StartNode = OpenNodes[0];
		for (size_t i{ 1 }; i < OpenNodes.Num(); i++) {
			if (Dist[i] <= Dist[i-1]) { StartNode == OpenNodes[i];}
			else { StartNode == ClosedNodes[i]; }
		}
		ACheckN* EndNode = OpenNodes[0];
		for (size_t i{ 1 }; i < OpenNodes.Num(); i++) {
			if (Dist[i] <= Dist[i-1]) { EndNode == OpenNodes[i]; }
			else { EndNode == ClosedNodes[i]; }
		}
	}

}


