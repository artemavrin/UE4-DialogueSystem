// Copyright 2015 Mavrin Artem. All Rights Reserved.

using UnrealBuildTool;

public class DialogueSystemEditor : ModuleRules
{
    public DialogueSystemEditor(TargetInfo Target)
	{

		PrivateIncludePaths.AddRange(
            new string[] { "DialogueSystemEditor/Private" });

        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
                "UMG",
                "SlateCore",
                "Projects",
                "Slate",
                "UnrealEd",
                "DetailCustomizations",
                "PropertyEditor",
                "EditorStyle",
                "InputCore",
                "HTTP",
                "DialogueSystem"
			}
		);

        PrivateIncludePathModuleNames.AddRange(
            new string[] {
                "AssetTools"
            }
        );

        DynamicallyLoadedModuleNames.AddRange(
            new string[] {
                "AssetTools"
            }
        );
    }
}
