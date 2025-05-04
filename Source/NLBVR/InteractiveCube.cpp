// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractiveCube.h"

AInteractiveCube::AInteractiveCube()
{
    PrimaryActorTick.bCanEverTick = true;

    // Создаем меш кубика
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    RootComponent = CubeMesh;

    // Настраиваем физику для меша
    CubeMesh->SetSimulatePhysics(true);
    CubeMesh->SetEnableGravity(true);
    CubeMesh->SetCollisionProfileName(TEXT("PhysicsActor"));

    // Создаем коллайдер для взаимодействия
    InteractionCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionCollider"));
    InteractionCollider->SetupAttachment(CubeMesh);
    InteractionCollider->SetBoxExtent(FVector(25.0f, 25.0f, 25.0f));
    InteractionCollider->SetCollisionProfileName(TEXT("OverlapAll"));

    bIsGrabbed = false;
}

void AInteractiveCube::BeginPlay()
{
    Super::BeginPlay();
}

void AInteractiveCube::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AInteractiveCube::Grab(USceneComponent* AttachTo)
{
    if (AttachTo && !bIsGrabbed)
    {
        // Отключаем физику при захвате
        CubeMesh->SetSimulatePhysics(false);

        // Присоединяем к компоненту (руке)
        CubeMesh->AttachToComponent(AttachTo, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

        bIsGrabbed = true;
    }
}

void AInteractiveCube::Release()
{
    if (bIsGrabbed)
    {
        // Отсоединяем от руки
        CubeMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

        // Включаем физику обратно
        CubeMesh->SetSimulatePhysics(true);

        bIsGrabbed = false;
    }
}