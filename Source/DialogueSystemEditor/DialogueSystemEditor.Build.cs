//Copyright (c) 2016 Artem A. Mavrin and other contributors

using UnrealBuildTool;

public class DialogueSystemEditor : ModuleRules
{
    public DialogueSystemEditor(ReadOnlyTargetRules Target) : base (Target)
	{
        //PCHUsage = ModuleRules.PCHUsageMode.NoSharedPCHs;
       // PrivatePCHHeaderFile = "Private/DialogueSystemEditorPrivatePCH.h";

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
                "LevelSequence",
                "CinematicCamera",
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
