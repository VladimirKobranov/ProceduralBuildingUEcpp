// Fill out your copyright notice in the Description page of Project Settings.
#include "BuildingConfigurator.h"


// Sets default values
ABuildingConfigurator::ABuildingConfigurator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuildingConfigurator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingConfigurator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildingConfigurator::BuildFunction(UStaticMesh* mesh, float Length, float Width, float Height)
{
	FTransform Trans;

	float xTile = 300;
	float xNumber = ceil(Length / xTile);
	float xHalfSize = ((xNumber - 1) * xTile) / 2;

	float yTile = 300;
	float yNumber = ceil(Width / yTile);
	float yHalfSize = ((yNumber - 1) * yTile) / 2;

	float zTile = 350;
	float zNumber = ceil(Height / zTile);
	float zHalfSize = zTile / 2;

	for (int x = 0; x < xNumber; x++)
	{
		for (int z = 0; z < zNumber; z++)
		{
			Trans.SetLocation(FVector3d(x * xTile - xHalfSize, yHalfSize+yTile/2, z*zTile));
			UStaticMeshComponent* NewStaticMeshComp = Cast<UStaticMeshComponent>(AddComponentByClass(UStaticMeshComponent::StaticClass(), false, Trans, false));
			NewStaticMeshComp->SetStaticMesh(mesh);
		}
	}
	for (int x = 0; x < xNumber; x++)
	{
		for (int z = 0; z < zNumber; z++)
		{
			Trans.SetRotation(FQuat4d(FRotator3d(0.0, 180.0, 0.0)));
			Trans.SetLocation(FVector3d(x * xTile - xHalfSize,0-yHalfSize- yTile / 2, z * zTile));
			UStaticMeshComponent* NewStaticMeshComp = Cast<UStaticMeshComponent>(AddComponentByClass(UStaticMeshComponent::StaticClass(), false, Trans, false));
			NewStaticMeshComp->SetStaticMesh(mesh);
		}
	}

	for (int y = 0; y < yNumber; y++)
	{
		for (int z = 0; z < zNumber; z++)
		{
			Trans.SetRotation(FQuat4d(FRotator3d(0.0, 90.0, 0.0)));
			Trans.SetLocation(FVector3d(0 - xHalfSize-xTile/2, y*yTile-yHalfSize, z * zTile));
			UStaticMeshComponent* NewStaticMeshComp = Cast<UStaticMeshComponent>(AddComponentByClass(UStaticMeshComponent::StaticClass(), false, Trans, false));
			NewStaticMeshComp->SetStaticMesh(mesh);
		}
	}
	for (int y = 0; y < yNumber; y++)
	{
		for (int z = 0; z < zNumber; z++)
		{
			Trans.SetRotation(FQuat4d(FRotator3d(0.0, 270.0, 0.0)));
			Trans.SetLocation(FVector3d(xHalfSize+ xTile / 2, y * yTile - yHalfSize, z * zTile));
			UStaticMeshComponent* NewStaticMeshComp = Cast<UStaticMeshComponent>(AddComponentByClass(UStaticMeshComponent::StaticClass(), false, Trans, false));
			NewStaticMeshComp->SetStaticMesh(mesh);
		}
	}
}

