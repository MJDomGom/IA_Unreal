// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class IA_Zombies : ModuleRules
{
	public IA_Zombies(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "AIModule", "GameplayTasks", "GameplayTags", "GameplayBehaviorsModule", "SmartObjectsModule", "GameplayBehaviorSmartObjectsModule" });
	}
}
