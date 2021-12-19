// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheZombies : ModuleRules
{
	public TheZombies(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "AIModule", "GameplayTasks", "NavigationSystem" });
	}
}
