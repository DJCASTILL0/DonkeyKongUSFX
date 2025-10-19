// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DKCClone : ModuleRules
{
	public DKCClone(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });
    }
}
