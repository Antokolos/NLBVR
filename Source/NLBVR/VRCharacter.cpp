#include "VRCharacter.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "InputCoreTypes.h"
#include "GameFramework/PlayerStart.h"
#include "IXRTrackingSystem.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AVRCharacter::AVRCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Настройка капсулы
    GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
    GetCapsuleComponent()->SetCapsuleRadius(40.0f);

    // Создаем VR камеру
    VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
    VRCamera->SetupAttachment(GetCapsuleComponent());
    VRCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
    VRCamera->bLockToHmd = true;

    // Создаем корневые компоненты для контроллеров
    RightControllerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RightControllerRoot"));
    RightControllerRoot->SetupAttachment(GetCapsuleComponent());
    RightControllerRoot->SetRelativeLocation(FVector(0.0f, 50.0f, 0.0f));

    // Создаем меш для правой руки
    RightHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHandMesh"));
    RightHandMesh->SetupAttachment(RightControllerRoot);
    RightHandMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    // Создаем левый контроллер
    LeftControllerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("LeftControllerRoot"));
    LeftControllerRoot->SetupAttachment(GetCapsuleComponent());
    LeftControllerRoot->SetRelativeLocation(FVector(0.0f, -50.0f, 0.0f));

    // Создаем меш для левой руки
    LeftHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHandMesh"));
    LeftHandMesh->SetupAttachment(LeftControllerRoot);
    LeftHandMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    // Настраиваем параметры захвата
    GrabRadius = 20.0f;
    CurrentlyGrabbedObject = nullptr;
}

void AVRCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (GEngine->XRSystem.IsValid() && GEngine->XRSystem->IsHeadTrackingAllowed())
    {
        GEngine->XRSystem->SetTrackingOrigin(EHMDTrackingOrigin::LocalFloor);
    }
    // Настройка VR трекинга будет выполнена через настройки проекта
    // или Blueprint персонажа
    // Найти Player Start
    // AActor* PlayerStart = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass());
    // if (PlayerStart)
    // {
    //     // Принудительно установить позицию и поворот
    //     SetActorLocation(PlayerStart->GetActorLocation());
    //     SetActorRotation(PlayerStart->GetActorRotation());
    //     // Логи для отладки
    //     UE_LOG(LogTemp, Warning, TEXT("Player positioned at PlayerStart location: %s"), *PlayerStart->GetActorLocation().ToString());
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("No PlayerStart found in level!"));
    // }
}

void AVRCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    // Здесь можно добавить пользовательскую логику обновления положения контроллеров
    // в Blueprint можно будет настроить получение данных с контроллеров
}

void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Triggered, this, &AVRCharacter::AttemptGrab);
		EnhancedInputComponent->BindAction(ReleaseAction, ETriggerEvent::Triggered, this, &AVRCharacter::AttemptRelease);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AVRCharacter::AttemptGrab()
{
    UE_LOG(LogTemp, Warning, TEXT("Attempting to grab..."));
    
    if (CurrentlyGrabbedObject == nullptr)
    {
        // Получаем позицию правой руки
        FVector HandLocation = RightHandMesh->GetComponentLocation();
        UE_LOG(LogTemp, Warning, TEXT("Hand location: %s"), *HandLocation.ToString());
        
        // Ищем ближайший объект для захвата
        TArray<AActor*> OverlappingActors;
        GetOverlappingActors(OverlappingActors, AInteractiveCube::StaticClass());
        
        float ClosestDistance = GrabRadius;
        AInteractiveCube* ClosestCube = nullptr;
        
        for (AActor* Actor : OverlappingActors)
        {
            AInteractiveCube* Cube = Cast<AInteractiveCube>(Actor);
            if (Cube)
            {
                float Distance = FVector::Dist(HandLocation, Cube->GetActorLocation());
                if (Distance < ClosestDistance)
                {
                    ClosestDistance = Distance;
                    ClosestCube = Cube;
                }
            }
        }
        
        // Если нашли объект в зоне досягаемости
        if (ClosestCube)
        {
            // Делаем меш руки невидимым
            RightHandMesh->SetVisibility(false);
            
            ClosestCube->Grab(RightHandMesh);
            CurrentlyGrabbedObject = ClosestCube;
        }
    }
}

void AVRCharacter::AttemptRelease()
{
    if (CurrentlyGrabbedObject)
    {
        CurrentlyGrabbedObject->Release();
        CurrentlyGrabbedObject = nullptr;
        
        // Возвращаем видимость меша руки
        RightHandMesh->SetVisibility(true);
    }
}