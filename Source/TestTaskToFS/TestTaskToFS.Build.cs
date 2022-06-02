// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestTaskToFS : ModuleRules
{
	public TestTaskToFS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		PublicIncludePaths.AddRange(new string[]
		{
			"TestTaskToFS/Public/Characters",
			"TestTaskToFS/Public/Components",
			"TestTaskToFS/Public/GameModes",
			"TestTaskToFS/Public/Weapons",
			"TestTaskToFS/Public/Pickups",
			"TestTaskToFS/Public/Ammo",
			"TestTaskToFS/Public/UI",
			"TestTaskToFS/Public/UI/Elements",
			"TestTaskToFS/Public/Targets",
		});
	}
}
