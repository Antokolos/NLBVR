#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "VRRoom.generated.h"

UCLASS()
class NLBVR_API AVRRoom : public AActor
{
    GENERATED_BODY()

public:
    AVRRoom();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* Floor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* CeilingMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* WallNorth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* WallSouth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* WallEast;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* WallWest;
};