// Copyright 2015 Mavrin Artem. All Rights Reserved.

#include "DialogueSystemEditorPrivatePCH.h"

#include "QuestBookAssetTypeActions.h"
#include "QuestBookEditor/QuestBookEditor.h"

#define LOCTEXT_NAMESPACE "DialogueSystem"

//////////////////////////////////////////////////////////////////////////
// FQuestBookAssetTypeActions

FQuestBookAssetTypeActions::FQuestBookAssetTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FText FQuestBookAssetTypeActions::GetName() const
{
	return LOCTEXT("FQuestBookAssetTypeActionsName", "Quest book");
}

FColor FQuestBookAssetTypeActions::GetTypeColor() const
{
	return FColor(0, 179, 255);
}

UClass* FQuestBookAssetTypeActions::GetSupportedClass() const
{
	return UQuestBook::StaticClass();
}

void FQuestBookAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UQuestBook* QuestBook = Cast<UQuestBook>(*ObjIt))
		{
			TSharedRef<FQuestBookEditor> NewQuestBookEditor(new FQuestBookEditor());
			NewQuestBookEditor->InitQuestBookEditor(Mode, EditWithinLevelEditor, QuestBook);
		}
	}
}

uint32 FQuestBookAssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::None | MyAssetCategory;
}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE