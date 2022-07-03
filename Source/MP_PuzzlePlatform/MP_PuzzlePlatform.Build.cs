// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MP_PuzzlePlatform : ModuleRules
{
	public MP_PuzzlePlatform(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
	}
}
