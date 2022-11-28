// Fill out your copyright notice in the Description page of Project Settings.
// may be later then

#include "MyActor.h"
#include "Math/UnrealMathUtility.h"
#include "Containers/Array.h"
#include "Math/RandomStream.h"
#include "UObject/Class.h"

// Sets default values
AMyActor::AMyActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

//spawn fucntion 
void AMyActor::SpawnArrayMesh(TArray<UStaticMesh*> SelectedMesh, FTransform newTransform, int n)
{
    UStaticMeshComponent* NewStaticMeshComp = Cast<UStaticMeshComponent>(AddComponentByClass(UStaticMeshComponent::StaticClass(), false, newTransform, false));
    NewStaticMeshComp->SetStaticMesh(SelectedMesh[n]);
}

void AMyActor::SpawnMesh(UStaticMesh* SelectedMesh, FTransform newTransform)
{
    UStaticMeshComponent* NewStaticMeshComp = Cast<UStaticMeshComponent>(AddComponentByClass(UStaticMeshComponent::StaticClass(), false, newTransform, false));
    NewStaticMeshComp->SetStaticMesh(SelectedMesh);
}


void AMyActor::SpawnFun(TArray<UStaticMesh*> MainWall, TArray<UStaticMesh*> FirstFloorWall, TArray<UStaticMesh*> LastFloorWall, TArray<UStaticMesh*> RoofCap, TArray<UStaticMesh*> InteriorMesh, UStaticMesh* FirstWallCorner, UStaticMesh* LastWallCorner, UStaticMesh* MainWallCorner, TArray<UStaticMesh*>MainWallAccessories, TArray<UStaticMesh*>FirstFloorAccessories, TArray<UStaticMesh*>RoofCapAccessories, TArray<UStaticMesh*>Stairs, TArray<UStaticMesh*>BrandMauerMainWall, TArray<UStaticMesh*>BrandMauerFirstFloor, TArray<UStaticMesh*>BrandMauerLastFloor, TArray<UStaticMesh*>BrandMauerLastFloorCorner, TArray<UStaticMesh*>BrandMauerFirstFloorCorner, TArray<UStaticMesh*>BrandMauerMainWallCorner, int xTile, int yTile, int zTile, int xNumber, int yNumber, int zNumber, double zRotation, int testValue, int seed, float MainWallAccessoriesPercentage, float FirstFloorAccessoriesPercentage, float RoofCapAccessoriesPercentage, int StairsPosition, bool BrandMauer, bool RandomStairsPosition)
{
    //local variables
    FTransform Trans;
    //Stream Initialization
    const FRandomStream RandStream = FRandomStream(seed);

    //check random stairs position
    if (RandomStairsPosition == true && (EStairsLocation::Front || EStairsLocation::Back))
    {
        const int RandomStairsPositionRandom = RandStream.FRandRange(1, xNumber - 1);
        StairsPosition = RandomStairsPositionRandom;
    }
    else if (RandomStairsPosition == true && (EStairsLocation::Left || EStairsLocation::Right))
    {
        const int RandomStairsPositionRandom = RandStream.FRandRange(1, yNumber - 1);
        StairsPosition = RandomStairsPositionRandom;
    }

    //loop
    for (int x = 0; x < xNumber; x++)
    {
        for (int y = 0; y < yNumber; y++)
        {
            for (int z = 0; z < zNumber; z++)
            { 
                //random values
                const int MainWallMeshRandom = RandStream.FRandRange(0, MainWall.Num());
                const int FirstFloorWallRandom = RandStream.FRandRange(0, FirstFloorWall.Num());
                const int LastFloorWallRandom = RandStream.FRandRange(0, LastFloorWall.Num());
                const int RoofCapRandom = RandStream.FRandRange(0, RoofCap.Num());
                const int InteriorMeshRandom = RandStream.FRandRange(0, InteriorMesh.Num());
                const int MainWallAccessoriesRandom = RandStream.FRandRange(0, MainWallAccessories.Num());
                const int FirstFloorAccessoriesRandom = RandStream.FRandRange(0, FirstFloorAccessories.Num());
                const int RoofCapAccessoriesRandom = RandStream.FRandRange(0, RoofCapAccessories.Num());
                const int RandomNumber = RandStream.FRandRange(0, 100);
                const int BrandMauerMainWallRandom = RandStream.FRandRange(0, BrandMauerMainWall.Num());
                const int BrandMauerFirstFloorRandom = RandStream.FRandRange(0, BrandMauerFirstFloor.Num());
                const int BrandMauerLastFloorRandom = RandStream.FRandRange(0, BrandMauerLastFloor.Num());
                const int BrandMauerMainWallCornerRandom = RandStream.FRandRange(0, BrandMauerMainWallCorner.Num());
                const int BrandMauerFirstFloorCornerRandom = RandStream.FRandRange(0, BrandMauerFirstFloorCorner.Num());
                const int BrandMauerLastFloorCornerRandom = RandStream.FRandRange(0, BrandMauerLastFloorCorner.Num());


                //set transform location
                Trans.SetLocation(FVector3d(x * xTile - float((xNumber - 1) * xTile) / 2, y * yTile - float((yNumber - 1) * yTile) / 2, z * zTile + float(zTile / 2)));

                //stairs enum
                switch (StairsLocation) {
                case EStairsLocation::Front:
                        if (x * xTile == StairsPosition * xTile && z * zTile > 1 * zTile && z * zTile < zTile*(zNumber-1) && y * yTile == yTile * (yNumber - 1))
                        {//main floor stairs
                            SpawnMesh(Stairs[1], Trans);
                        }
                        else if (x * xTile == StairsPosition * xTile && z * zTile == 1 * zTile && y * yTile == yTile * (yNumber-1))
                        {//first floor stairs
                            SpawnMesh(Stairs[0], Trans);
                        }
                        else if (x * xTile == StairsPosition * xTile && y * yTile == yTile * (yNumber - 1) && z * zTile == zTile * (zNumber-1))
                        {//last floor stairs
                            SpawnMesh(Stairs[2], Trans);
                        }
                        break;
                    case EStairsLocation::Back:
                        if (x * xTile == StairsPosition * xTile && z * zTile > 1 * zTile && z * zTile < zTile * (zNumber - 1) && y * yTile == 0)
                        {//main floor stairs
                            SpawnMesh(Stairs[1], Trans);
                        }
                        else if (x * xTile == StairsPosition * xTile && z * zTile == 1 * zTile && y * yTile == 0)
                        {//first floor stairs
                            SpawnMesh(Stairs[0], Trans);
                        }
                        else if (x * xTile == StairsPosition * xTile && y * yTile == 0 && z * zTile == zTile * (zNumber - 1))
                        {//last floor stairs
                            SpawnMesh(Stairs[2], Trans);
                        }
                        break;
                    case EStairsLocation::Left:
                        if (BrandMauer == false)
                        {
                            if (x * xTile == 0 && z * zTile > 1 * zTile && z * zTile < zTile * (zNumber - 1) && y * yTile == StairsPosition * yTile)
                            {//main floor stairs
                                SpawnMesh(Stairs[1], Trans);
                            }
                            else if (x * xTile == 0 && z * zTile == 1 * zTile && y * yTile == StairsPosition * yTile)
                            {//first floor stairs
                                SpawnMesh(Stairs[0], Trans);
                            }
                            else if (x * xTile == 0 && z * zTile == zTile * (zNumber - 1) && y * yTile == StairsPosition * yTile)
                            {//last floor stairs
                                SpawnMesh(Stairs[2], Trans);
                            }
                        }
                        else
                        {

                        }
                        break;
                    case EStairsLocation::Right:
                        if (BrandMauer == false)
                        {
                            if (x * xTile == xTile * (xNumber - 1) && z * zTile > 1 * zTile && z * zTile < zTile * (zNumber - 1) && y * yTile == StairsPosition * yTile)
                            {//main floor stairs
                                SpawnMesh(Stairs[1], Trans);
                            }
                            else if (x * xTile == xTile * (xNumber - 1) && z * zTile == 1 * zTile && y * yTile == StairsPosition * yTile)
                            {//first floor stairs
                                SpawnMesh(Stairs[0], Trans);
                            }
                            else if (x * xTile == xTile * (xNumber - 1) && z * zTile == zTile * (zNumber - 1) && y * yTile == StairsPosition * yTile)
                            {//last floor stairs
                                SpawnMesh(Stairs[2], Trans);
                            }
                        }
                        else 
                        {

                        }
                        break;
                }

                //Filter 
                if (z * zTile == 0)
                {
                    //FIRST FLOOR
                    if (y * yTile == (yNumber - 1) * yTile)
                    {
                        //front corners
                        if (x * xTile == 0 || x * xTile == (xNumber - 1) * xTile)
                        {
                            if (x * xTile == 0)
                            {
                                //left corner
                                if (BrandMauer == true)
                                {
                                    //brandmauer corner
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 0, 0.0)));
                                    SpawnArrayMesh(BrandMauerFirstFloorCorner, Trans, BrandMauerFirstFloorCornerRandom);
                                }
                                else
                                {
                                    //regular corner
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 0, 0.0)));
                                    SpawnMesh(FirstWallCorner, Trans);
                                }
                            }
                            else if(x * xTile == (xNumber - 1) * xTile)
                            {
                                //right corner
                                if (BrandMauer == true)
                                {
                                    //brandmauer corner
                                    Trans.SetScale3D(FVector3d(-1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 0.0, 0.0)));
                                    SpawnArrayMesh(BrandMauerFirstFloorCorner, Trans, BrandMauerFirstFloorCornerRandom);
                                }
                                else
                                {
                                    //regular corner
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 270, 0.0)));
                                    SpawnMesh(FirstWallCorner, Trans);
                                }
                            }
                        }
                        else
                        {
                            //front facade
                            Trans.SetRotation(FQuat4d(FRotator3d(0.0, 0, 0.0)));
                            SpawnArrayMesh(FirstFloorWall, Trans, FirstFloorWallRandom);

                            if (RandomNumber < FirstFloorAccessoriesPercentage)
                            {
                                //accessories first front wall
                                SpawnArrayMesh(FirstFloorAccessories, Trans, FirstFloorAccessoriesRandom);
                            }
                        }
                    }
                    else if (y* yTile == 0)
                    {
                        //back corners
                        if (x * xTile == 0 || x * xTile == (xNumber - 1) * xTile)
                        {
                            if (x * xTile == 0)
                            {
                                //left corner
                                if (BrandMauer == true)
                                {
                                    //brandmauer corner
                                    Trans.SetScale3D(FVector3d(-1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 180, 0.0)));
                                    SpawnArrayMesh(BrandMauerFirstFloorCorner, Trans,BrandMauerFirstFloorCornerRandom);
                                }
                                else
                                {
                                    //regular corner
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 90, 0.0)));
                                    SpawnMesh(FirstWallCorner, Trans);
                                }
                            }
                            else if (x * xTile == (xNumber - 1) * xTile)
                            {
                                //right corner
                                if (BrandMauer == true)
                                {
                                    //brandmauer corner
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 180, 0.0)));
                                    SpawnArrayMesh(BrandMauerFirstFloorCorner, Trans, BrandMauerFirstFloorCornerRandom);
                                }
                                else
                                {
                                    //regular corner
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 180, 0.0)));
                                    SpawnMesh(FirstWallCorner, Trans);
                                }
                            }
                        }
                        else
                        {
                            //back facade
                            Trans.SetRotation(FQuat4d(FRotator3d(0.0, 180, 0.0)));
                            SpawnArrayMesh(FirstFloorWall, Trans, FirstFloorWallRandom);

                            if (RandomNumber < FirstFloorAccessoriesPercentage)
                            {
                                //accessories first back wall
                                SpawnArrayMesh(FirstFloorAccessories, Trans, FirstFloorAccessoriesRandom);
                            }
                        }
                    }
                    else if (x*xNumber == 0)
                    {
                        //left facade
                        Trans.SetRotation(FQuat4d(FRotator3d(0.0, 90, 0.0)));

                        if (BrandMauer == true)
                        {
                            //brandmauer wall
                            SpawnArrayMesh(BrandMauerFirstFloor, Trans, BrandMauerFirstFloorRandom);
                        }
                        else
                        {
                            //regular wall
                            SpawnArrayMesh(FirstFloorWall, Trans, FirstFloorWallRandom);

                            if (RandomNumber < FirstFloorAccessoriesPercentage)
                            {
                                //accessories first left wall
                                SpawnArrayMesh(FirstFloorAccessories, Trans, FirstFloorAccessoriesRandom);
                            }
                        }
                    }
                    else if (x * xTile == (xNumber - 1)*xTile)
                    {
                        //right  facade
                        Trans.SetRotation(FQuat4d(FRotator3d(0.0, 270, 0.0)));

                        if (BrandMauer == true)
                        {
                            //brandmauer wall
                            SpawnArrayMesh(BrandMauerFirstFloor, Trans, BrandMauerFirstFloorRandom);
                        }
                        else
                        {
                            //regular wall
                            SpawnArrayMesh(FirstFloorWall, Trans, FirstFloorWallRandom);

                            if (RandomNumber < FirstFloorAccessoriesPercentage)
                            {
                                //accessories first left wall
                                SpawnArrayMesh(FirstFloorAccessories, Trans, FirstFloorAccessoriesRandom);
                            }
                        }
                    }
                    else {
                        //inner objects 
                        Trans.SetRotation(FQuat4d(FRotator3d(0.0, 0.0, 0.0)));
                        SpawnArrayMesh(InteriorMesh, Trans, InteriorMeshRandom);
                    }

                }else if (z*zTile == (zNumber-1)*zTile)
                {	
                    //LAST FLOOR
                    if (y * yTile == (yNumber - 1) * yTile)
                    {
                        //front corners
                        if (x * xTile == 0 || x * xTile == (xNumber - 1) * xTile)
                        {
                            if (x * xTile == 0)
                            {
                                //left corner
                                if (BrandMauer == true)
                                {
                                    //brandmauer corner
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 0, 0.0)));
                                    SpawnArrayMesh(BrandMauerLastFloorCorner, Trans,BrandMauerLastFloorCornerRandom);
                                }
                                else
                                {
                                    //regular corners 
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 0, 0.0)));
                                    SpawnMesh(LastWallCorner, Trans);
                                }
                            }
                            else if (x * xTile == (xNumber - 1) * xTile)
                            {
                                //right corner
                                if (BrandMauer == true)
                                {
                                    //brandmauer corner
                                    Trans.SetScale3D(FVector3d(-1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 0, 0.0)));
                                    SpawnArrayMesh(BrandMauerLastFloorCorner, Trans, BrandMauerLastFloorCornerRandom);
                                }
                                else
                                {
                                    //regular corners 
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 270, 0.0)));
                                    SpawnMesh(LastWallCorner, Trans);
                                }
                            }
                        }
                        else
                        {
                            //front facade
                            Trans.SetRotation(FQuat4d(FRotator3d(0.0, 0, 0.0)));
                            SpawnArrayMesh(LastFloorWall, Trans, LastFloorWallRandom);
                        }
                    }
                    else if (y * yTile == 0)
                    {
                        //back corners
                        if (x * xTile == 0 || x * xTile == (xNumber - 1) * xTile)
                        {
                            if (x * xTile == 0)
                            {
                                //left corner
                                if (BrandMauer == true)
                                {
                                    //brandmauer corner
                                    Trans.SetScale3D(FVector3d(-1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 180, 0.0)));
                                    SpawnArrayMesh(BrandMauerLastFloorCorner, Trans, BrandMauerLastFloorCornerRandom);
                                }
                                else
                                {
                                    //regular corners 
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 90, 0.0)));
                                    SpawnMesh(LastWallCorner, Trans);
                                }
                            }
                            else if (x * xTile == (xNumber - 1) * xTile)
                            {
                                //right corner
                                if (BrandMauer == true)
                                {
                                    //brandmauer corner
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 180, 0.0)));
                                    SpawnArrayMesh(BrandMauerLastFloorCorner, Trans, BrandMauerLastFloorCornerRandom);
                                }
                                else
                                {
                                    //regular corners 
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 180, 0.0)));
                                    SpawnMesh(LastWallCorner, Trans);
                                }
                            }
                        }
                        else
                        {
                            //back facade
                            Trans.SetRotation(FQuat4d(FRotator3d(0.0, 180, 0.0)));
                            SpawnArrayMesh(LastFloorWall, Trans, LastFloorWallRandom);

                        }
                    }
                    else if (x * xNumber == 0)
                    {
                        //left facade
                        Trans.SetRotation(FQuat4d(FRotator3d(0.0, 90, 0.0)));

                        if (BrandMauer == true)
                        {
                            //brandmauer wall
                            SpawnArrayMesh(BrandMauerLastFloor, Trans, BrandMauerLastFloorRandom);
                        }
                        else
                        {
                            //main wall
                            SpawnArrayMesh(LastFloorWall, Trans, LastFloorWallRandom);
                        }
                    }
                    else if (x * xTile == (xNumber - 1) * xTile)
                    {
                        //right  facade
                        Trans.SetRotation(FQuat4d(FRotator3d(0.0, 270, 0.0)));

                        if (BrandMauer == true)
                        {
                            //brandmauer wall
                            SpawnArrayMesh(BrandMauerLastFloor, Trans, BrandMauerLastFloorRandom);
                        }
                        else
                        {
                            //main wall
                            SpawnArrayMesh(LastFloorWall, Trans, LastFloorWallRandom);
                        }
                    }
                    else {
                        //roof cap
                        Trans.SetRotation(FQuat4d(FRotator3d(0.0, 0.0, 0.0)));
                        SpawnArrayMesh(RoofCap, Trans,RoofCapRandom);

                        if (RandomNumber < RoofCapAccessoriesPercentage)
                        {
                            //accessories roof cap 
                            SpawnArrayMesh(RoofCapAccessories, Trans, RoofCapAccessoriesRandom);
                        }
                    }
                }else
                { 
                    //MAIN FLOOR
                    if (y * yTile == (yNumber - 1) * yTile)
                    {
                        //front corners
                        if (x * xTile == 0 || x * xTile == (xNumber - 1) * xTile)
                        {
                            if (x * xTile == 0)
                            {
                                //left corner
                                if (BrandMauer == true)
                                {
                                    //brandmaer corner
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 0, 0.0)));
                                    SpawnArrayMesh(BrandMauerMainWallCorner, Trans, BrandMauerMainWallCornerRandom);
                                }
                                else
                                {
                                    //regular corner
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 0, 0.0)));
                                    SpawnMesh(MainWallCorner, Trans);
                                }
                            }
                            else if (x * xTile == (xNumber - 1) * xTile)
                            {
                                //right corner
                                SpawnMesh(MainWallCorner, Trans);

                                if (BrandMauer == true)
                                {
                                    //brandmaer corner
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 270, 0.0)));
                                    SpawnArrayMesh(BrandMauerMainWallCorner, Trans, BrandMauerMainWallCornerRandom);
                                }
                                else
                                {
                                    //regular corner
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 270, 0.0)));
                                    SpawnMesh(MainWallCorner, Trans);
                                }
                            }
                        }
                        else 
                        {
                            //front facade
                            Trans.SetRotation(FQuat4d(FRotator3d(0.0, 0, 0.0)));
                            SpawnArrayMesh(MainWall, Trans, MainWallMeshRandom);

                            if (RandomNumber < MainWallAccessoriesPercentage)
                            {
                                //accessories main front wall
                                SpawnArrayMesh(MainWallAccessories, Trans, MainWallAccessoriesRandom);
                            }
                        }
                    }
                    else if (y* yTile == 0)
                    {
                        //back corners
                        if (x * xTile == 0 || x * xTile == (xNumber - 1) * xTile)
                        {
                            if (x * xTile == 0)
                            {
                                //left corner
                                if (BrandMauer == true)
                                {
                                    //brandmaer corner
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 90, 0.0)));
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    SpawnArrayMesh(BrandMauerMainWallCorner, Trans,BrandMauerMainWallCornerRandom);
                                }
                                else
                                {
                                    //regular corner
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 90, 0.0)));
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    SpawnMesh(MainWallCorner, Trans);
                                }
                            }
                            else if (x * xTile == (xNumber - 1) * xTile)
                            {
                                //right corner

                                if (BrandMauer == true)
                                {
                                    //brandmauer corner
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 180, 0.0)));
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    SpawnArrayMesh(BrandMauerMainWallCorner, Trans, BrandMauerMainWallCornerRandom);
                                }
                                else
                                {
                                    //regular corner
                                    Trans.SetRotation(FQuat4d(FRotator3d(0.0, 180, 0.0)));
                                    Trans.SetScale3D(FVector3d(1.0, 1.0, 1.0));
                                    SpawnMesh(MainWallCorner, Trans);
                                }
                            }
                        }
                        else
                        {
                            //back facade
                            Trans.SetRotation(FQuat4d(FRotator3d(0.0, 180, 0.0)));
                            SpawnArrayMesh(MainWall, Trans, MainWallMeshRandom);

                            if (RandomNumber < MainWallAccessoriesPercentage)
                            {
                                //accessories main back wall
                                SpawnArrayMesh(MainWallAccessories, Trans, MainWallAccessoriesRandom);
                            }
                        }
                    }
                    else if (x*xNumber == 0)
                    {

                        //left facade
                        Trans.SetRotation(FQuat4d(FRotator3d(0.0, 90, 0.0)));
                        if (BrandMauer == true)
                        {
                            //brandmauer
                            SpawnArrayMesh(BrandMauerMainWall, Trans, BrandMauerMainWallRandom);
                        }
                        else 
                        {
                            //regular wall
                            SpawnArrayMesh(MainWall, Trans, MainWallMeshRandom);

                            if (FMath::FRandRange(0, 100) < MainWallAccessoriesPercentage)
                            {
                                //accessories main left wall
                                SpawnArrayMesh(MainWallAccessories, Trans, MainWallAccessoriesRandom);
                            }
                        }
                    }
                    else if (x * xTile == (xNumber - 1)*xTile)
                    {
                        //right  facade
                        Trans.SetRotation(FQuat4d(FRotator3d(0.0, 270, 0.0)));

                        if (BrandMauer == true)
                        {
                            //brandmauer wall
                            SpawnArrayMesh(BrandMauerMainWall, Trans, BrandMauerMainWallRandom);
                        }
                        else
                        {
                            //regular wall
                            SpawnArrayMesh(MainWall, Trans, MainWallMeshRandom);

                            if (RandomNumber < MainWallAccessoriesPercentage)
                            {
                                //accessories main right wall
                                SpawnArrayMesh(MainWallAccessories, Trans, MainWallAccessoriesRandom);
                            }
                        }
                    }
                    else {
                        //inner objects
                        Trans.SetRotation(FQuat4d(FRotator3d(0.0, 0.0, 0.0)));
                        SpawnArrayMesh(InteriorMesh, Trans, InteriorMeshRandom);
                    }
                }
            }
        }
    } 
}
