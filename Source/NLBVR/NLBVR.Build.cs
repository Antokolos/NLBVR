// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class NLBVR : ModuleRules
{
	public NLBVR(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
    
        PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore",
            "HeadMountedDisplay",
            "EnhancedInput"
        });

        // Ð”Ð¾Ð±Ð°Ð²Ð»ÑÐµÐ¼ ÑÑ‚Ð¸ Ð¼Ð¾Ð´ÑƒÐ»Ð¸ Ð´Ð»Ñ OpenXR
        if (Target.Platform == UnrealTargetPlatform.Win64 || 
            Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicDependencyModuleNames.AddRange(new string[] {
                "OpenXRHMD", 
                "OpenXRInput"
            });
        }
	}
}
