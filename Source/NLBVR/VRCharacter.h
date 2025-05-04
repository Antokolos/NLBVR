// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "InteractiveCube.h"
#include "VRCharacter.generated.h"

class UInputAction;

UCLASS()
class NLBVR_API AVRCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AVRCharacter();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Компоненты для VR
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
    UCameraComponent* VRCamera;

    // Компоненты для правого контроллера
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
    USceneComponent* RightControllerRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
    UStaticMeshComponent* RightHandMesh;

    // Компоненты для левого контроллера
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
    USceneComponent* LeftControllerRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
    UStaticMeshComponent* LeftHandMesh;

    // Функции взаимодействия
    void AttemptGrab();
    void AttemptRelease();

    // Указатель на текущий захваченный объект
    UPROPERTY()
    AInteractiveCube* CurrentlyGrabbedObject;

    // Радиус проверки для захвата
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    float GrabRadius;

private:
    /** Grab Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* GrabAction;

	/** Release Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ReleaseAction;

};
