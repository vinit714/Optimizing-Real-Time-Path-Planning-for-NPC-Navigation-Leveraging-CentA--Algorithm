// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMesh.h"

// Sets default values
AGridMesh::AGridMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridComponent = CreateDefaultSubobject<UStaticMeshComponent>("GridComponent");

	this->RootComponent = GridComponent;
}

// Called when the game starts or when spawned
void AGridMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}