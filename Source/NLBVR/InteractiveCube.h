// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "InteractiveCube.generated.h"

UCLASS()
class NLBVR_API AInteractiveCube : public AActor
{
    GENERATED_BODY()

public:
    AInteractiveCube();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Основной меш кубика
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* CubeMesh;

    // Коллайдер для взаимодействия
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UBoxComponent* InteractionCollider;

    // Функция для захвата объекта
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void Grab(USceneComponent* AttachTo);

    // Функция для отпускания объекта
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void Release();

    // Флаг, указывающий, поднят ли кубик
    UPROPERTY(BlueprintReadOnly, Category = "Interaction")
    bool bIsGrabbed;
};
