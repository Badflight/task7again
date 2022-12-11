// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Task7Again : ModuleRules
{
	public Task7Again(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore", 
			"HeadMountedDisplay",
			"AIModule",
			"GameplayTasks",
			"NavigationSystem"});
	}
}
