//Copyright (c) 2016 Artem A. Mavrin and other contributors

#include "DialogueSystemEditorPrivatePCH.h"
#include "DialogueSystemStyle.h"
#include "SlateStyle.h"
#include "ClassIconFinder.h"
#include "IPluginManager.h"

#define IMAGE_PLUGIN_BRUSH( RelativePath, ... ) FSlateImageBrush( FDialogueSystemStyle::InContent( RelativePath, ".png" ), __VA_ARGS__ )
#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(StyleSet->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#define BOX_BRUSH(RelativePath, ...) FSlateBoxBrush(StyleSet->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#define TTF_FONT(RelativePath, ...) FSlateFontInfo(StyleSet->RootToContentDir(RelativePath, TEXT(".ttf")), __VA_ARGS__)
#define TTF_CORE_FONT(RelativePath, ...) FSlateFontInfo(StyleSet->RootToCoreContentDir(RelativePath, TEXT(".ttf") ), __VA_ARGS__)

FString FDialogueSystemStyle::InContent(const FString& RelativePath, const ANSICHAR* Extension)
{
	static FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("DialogueSystem"))->GetContentDir();
	return (ContentDir / RelativePath) + Extension;
}

TSharedPtr< FSlateStyleSet > FDialogueSystemStyle::StyleSet = nullptr;
TSharedPtr< class ISlateStyle > FDialogueSystemStyle::Get() { return StyleSet; }

FName FDialogueSystemStyle::GetStyleSetName()
{
	static FName DialogueSystemStyleName(TEXT("DialogueSystemStyle"));
	return DialogueSystemStyleName;
}

void FDialogueSystemStyle::Initialize()
{
	// Const icon sizes
	const FVector2D Icon8x8(8.0f, 8.0f);
	const FVector2D Icon16x16(16.0f, 16.0f);
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);
	const FVector2D Icon64x64(64.0f, 64.0f);

	// Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	
	// QuestBook editor
	{
		StyleSet->Set("QuestBookEditor.AddQuest", new IMAGE_PLUGIN_BRUSH(TEXT("Icons/QuestBookEditor/icon_Add_Quest_40x"), Icon40x40));
	}

	// Asset
	{
		StyleSet->Set("ClassIcon.QuestBook", new IMAGE_PLUGIN_BRUSH(TEXT("Icons/AssetIcons/QuestBook_16x"), Icon16x16));
		StyleSet->Set("ClassThumbnail.QuestBook", new IMAGE_PLUGIN_BRUSH(TEXT("Icons/AssetIcons/QuestBook_64x"), Icon64x64));

		StyleSet->Set("ClassIcon.DialogueSettings", new IMAGE_PLUGIN_BRUSH(TEXT("Icons/AssetIcons/DialogueSettings_16x"), Icon16x16));
		StyleSet->Set("ClassThumbnail.DialogueSettings", new IMAGE_PLUGIN_BRUSH(TEXT("Icons/AssetIcons/DialogueSettings_64x"), Icon64x64));
	}

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
	FClassIconFinder::RegisterIconSource(StyleSet.Get());
};

#undef IMAGE_PLUGIN_BRUSH
#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef TTF_FONT
#undef TTF_CORE_FONT

void FDialogueSystemStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		FClassIconFinder::UnregisterIconSource(StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}
