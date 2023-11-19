// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridMesh.generated.h"

UCLASS()
class ASTARPROJECT_API AGridMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UStaticMeshComponent> GridComponent;

	int GridX;
	int GridY;

	bool b_IsWalkable;
	FVector WorldPosition;

	int GCost;
	int HCost;
	AGridMesh* Parent;
	int FCost() const { return GCost + HCost; }
};
