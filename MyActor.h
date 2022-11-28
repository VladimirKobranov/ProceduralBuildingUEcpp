// Fill out your copyright notice in the Description page of Project Settings.
// may be later then

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"


UENUM(BlueprintType)
enum EStairsLocation
{
	Front     UMETA(DisplayName = "Front"),
	Back      UMETA(DisplayName = "Back"),
	Left   UMETA(DisplayName = "Left"),
	Right   UMETA(DisplayName = "Right"),
};

UCLASS()
class MYPROJECT_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = default)
	TEnumAsByte<EStairsLocation> StairsLocation;


	UFUNCTION(BlueprintCallable)
	void SpawnFun(TArray<UStaticMesh*> MainWall, TArray<UStaticMesh*> FirstFloorWall, TArray<UStaticMesh*> LastFloorWall, TArray<UStaticMesh*> RoofCap, TArray<UStaticMesh*> InteriorMesh, UStaticMesh* FirstWallCorner, UStaticMesh* LastWallCorner, UStaticMesh* MainWallCorner, TArray<UStaticMesh*>MainWallAccessories, TArray<UStaticMesh*>FirstFloorAccessories, TArray<UStaticMesh*>RoofCapAccessories, TArray<UStaticMesh*>Stairs, TArray<UStaticMesh*>BrandMauerMainWall, TArray<UStaticMesh*>BrandMauerFirstFloor, TArray<UStaticMesh*>BrandMauerLastFloor, TArray<UStaticMesh*>BrandMauerLastFloorCorner, TArray<UStaticMesh*>BrandMauerFirstFloorCorner, TArray<UStaticMesh*>BrandMauerMainWallCorner, int xTile, int yTile, int zTile, int xNumber, int yNumber, int zNumber, double zRotation, int testValue, int seed, float MainWallAccessoriesPercentage, float FirstFloorAccessoriesPercentage, float RoofCapAccessoriesPercentage, int StairsPosition, bool BrandMauer, bool RandomStairsPosition);
	void SpawnArrayMesh(TArray<UStaticMesh*> SelectedMesh, FTransform newTransform, int n);
	void SpawnMesh(UStaticMesh* SelectedMesh, FTransform newTransform);
};
