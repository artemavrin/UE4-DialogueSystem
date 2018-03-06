//Copyright (c) 2016 Artem A. Mavrin and other contributors

using UnrealBuildTool;

public class PluginSystemEditor : ModuleRules
{
    public PluginSystemEditor(ReadOnlyTargetRules Target) : base (Target)
	{

		PrivateIncludePaths.AddRange(
            new string[] { "" });

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
