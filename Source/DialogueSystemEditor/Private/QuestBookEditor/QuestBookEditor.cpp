//Copyright (c) 2016 Artem A. Mavrin and other contributors

#pragma once
#include "DialogueSystemEditorPrivatePCH.h"
#include "QuestBookEditor.h"

#include "SDockTab.h"
#include "Editor/PropertyEditor/Public/PropertyEditorModule.h"

#define LOCTEXT_NAMESPACE "DialogueSystem"

const FName QuestBookEditorAppName = FName(TEXT("QuestBookEditorAppName"));

struct FQuestBookEditorTabs
{
	// Tab identifiers
	static const FName DetailsID;
};

//////////////////////////////////////////////////////////////////////////

const FName FQuestBookEditorTabs::DetailsID(TEXT("Details"));

FName FQuestBookEditor::GetToolkitFName() const
{
	return FName("QuestBookEditor");
}

FText FQuestBookEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "QuestBook Editor");
}

FText FQuestBookEditor::GetToolkitName() const
{
	
	FFormatNamedArguments Args;
	Args.Add(TEXT("QuestBookName"), FText::FromString(QuestBookBeingEdited->GetName()));
	return FText::Format(LOCTEXT("QuestBookEditorAppLabel", "{QuestBookName}"), Args);
}

FText FQuestBookEditor::GetToolkitToolTipText() const
{
	return FAssetEditorToolkit::GetToolTipTextForObject(QuestBookBeingEdited);
}

FString FQuestBookEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("QuestBookEditor");
}

FLinearColor FQuestBookEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

FString FQuestBookEditor::GetDocumentationLink() const
{
	return TEXT("mavrinsoft.ru");
}

void FQuestBookEditor::OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit)
{

}

void FQuestBookEditor::OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit)
{

}

void FQuestBookEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(QuestBookBeingEdited);
}

void FQuestBookEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_QuestBookEditor", "QuestBook Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(FQuestBookEditorTabs::DetailsID, FOnSpawnTab::CreateSP(this, &FQuestBookEditor::SpawnTab_Details))
		.SetDisplayName(LOCTEXT("DetailsTab", "Quest list"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

}

void FQuestBookEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}

TSharedRef<SDockTab> FQuestBookEditor::SpawnTab_Details(const FSpawnTabArgs& Args)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs(/*bUpdateFromSelection=*/ true, /*bLockable=*/ true, /*bAllowSearch=*/ true, /*InNameAreaSettings=*/ FDetailsViewArgs::HideNameArea, /*bHideSelectionTip=*/ true);
	TSharedRef<IDetailsView> PropertyEditorRef = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	PropertyEditorRef->SetObject(QuestBookBeingEdited);
		
	PropertyEditor = PropertyEditorRef;

	PropertyEditorRef->OnFinishedChangingProperties().AddSP(this, &FQuestBookEditor::OnFinishedChangingProperties);

	// Spawn the tab
	return SNew(SDockTab)
		.Label(FText::FromString("Quest list"))
		[
			PropertyEditorRef
		];
}

void FQuestBookEditor::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property != nullptr)
	{
		const FName PropertyName(PropertyChangedEvent.Property->GetFName());

		if (PropertyName == GET_MEMBER_NAME_CHECKED(UQuestBook, Quests))
		{
			if (QuestNum < QuestBookBeingEdited->Quests.Num())
			{
				QuestBookBeingEdited->SetUniqueID();
			}
		}

		QuestNum = QuestBookBeingEdited->Quests.Num();
	}
}


void FQuestBookEditor::ExtendList()
{

}

void FQuestBookEditor::InitQuestBookEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UQuestBook* InitQuestBook)
{
	FAssetEditorManager::Get().CloseOtherEditors(InitQuestBook, this);
	QuestBookBeingEdited = InitQuestBook;

	// Default layout
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_QuestBookEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)	
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->SetHideTabWell(true)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(

				FTabManager::NewStack()
				->SetSizeCoefficient(1.0f)
				->SetHideTabWell(true)
				->AddTab(FQuestBookEditorTabs::DetailsID, ETabState::OpenedTab)

			)
		);

	// Initialize the asset editor and spawn nothing (dummy layout)
	InitAssetEditor(Mode, InitToolkitHost, QuestBookEditorAppName, StandaloneDefaultLayout, /*bCreateDefaultStandaloneMenu=*/ true, /*bCreateDefaultToolbar=*/ true, InitQuestBook);
	RegenerateMenusAndToolbars();
}