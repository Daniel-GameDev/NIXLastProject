// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UECourse : ModuleRules
{
	public UECourse(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "AIModule", "GameplayTasks", "NavigationSystem" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "OnlineSubSystem", "OnlineSubsystemUtils" });
	}
}
