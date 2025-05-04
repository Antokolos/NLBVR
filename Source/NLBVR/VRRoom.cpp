#include "VRRoom.h"

AVRRoom::AVRRoom()
{
    PrimaryActorTick.bCanEverTick = true;

    // Создаем корневой компонент
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Создаем пол
    Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
    Floor->SetupAttachment(RootComponent);

    // Создаем потолок
    CeilingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ceiling"));
    CeilingMesh->SetupAttachment(RootComponent);

    // Создаем стены
    WallNorth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallNorth"));
    WallNorth->SetupAttachment(RootComponent);

    WallSouth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallSouth"));
    WallSouth->SetupAttachment(RootComponent);

    WallEast = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallEast"));
    WallEast->SetupAttachment(RootComponent);

    WallWest = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallWest"));
    WallWest->SetupAttachment(RootComponent);
}

void AVRRoom::BeginPlay()
{
    Super::BeginPlay();
}

void AVRRoom::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}