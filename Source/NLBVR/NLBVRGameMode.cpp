#include "NLBVRGameMode.h"
#include "VRCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANLBVRGameMode::ANLBVRGameMode()
{
    // Настройки по умолчанию для игрового режима
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/NLBVR/Blueprints/BP_VRCharacter"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}