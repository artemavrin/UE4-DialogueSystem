// Copyright 2015 Mavrin Artem. All Rights Reserved.

using UnrealBuildTool;

public class DialogueSystem : ModuleRules
{
	public DialogueSystem(TargetInfo Target)
	{

		PrivateIncludePaths.AddRange(
			new string[] {"DialogueSystem/Private"});

        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
                "UMG",
                "SlateCore",
                "Slate",
                "AIModule"
			}
		);
	}
}
