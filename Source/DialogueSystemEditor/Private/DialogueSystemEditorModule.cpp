//Copyright (c) 2016 Artem A. Mavrin and other contributors

#include "DialogueSystemEditorPrivatePCH.h"

#include "AssetToolsModule.h"

#include "QuestBookAssetTypeActions.h"
#include "DialogueSystemStyle.h"
#include "QuestBookEditor/QuestBookEditorCustomization.h"
#include "BehaviorTreeEditor/QuestionCustomization.h"
#include "BehaviorTreeEditor/ShowPhrasesCustomization.h"


#define LOCTEXT_NAMESPACE "DialogueSystem"


//////////////////////////////////////////////////////////////////////////
// FDialogueSystemModule

class FDialogueSystemEditorModule : public IDialogueSystemEditorModule
{
public:
	// IDialogueSystemEditorModule interface
	virtual TSharedPtr<FExtensibilityManager> GetQuestBookEditorToolBarExtensibilityManager() override { return QuestBookEditor_ToolBarExtensibilityManager; }
	virtual uint32 GetDialogueSystemAssetCategory() const override { return DialogueSystemAssetCategoryBit; }
	// End of IDialogueSystemEditorModule


private:
	/** All created asset type actions.  Cached here so that we can unregister them during shutdown. */
	TArray< TSharedPtr<IAssetTypeActions> > CreatedAssetTypeActions;
	TSharedPtr<FExtensibilityManager> QuestBookEditor_ToolBarExtensibilityManager;
	EAssetTypeCategories::Type DialogueSystemAssetCategoryBit;
	TWeakPtr<SNotificationItem> NewVersionNotification;
	FString TextResponse;
	

public:
	virtual void StartupModule() override
	{
		// Register slate style overrides
		FDialogueSystemStyle::Initialize();

		//Custom detail views
		
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.RegisterCustomPropertyTypeLayout(FQuest::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FQuestBookEditorCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout(FBTDialogueTextPhrase::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FTextPhrasesCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout(FBTDialogueTextOptions::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FTextOptionsCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout(FBTDialogueCinematicOptions::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FCinematicOptionsCustomization::MakeInstance));
		PropertyModule.RegisterCustomClassLayout(UBTComposite_Question::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FQuestionDetails::MakeInstance));

		QuestBookEditor_ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);

		// Register asset types
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		DialogueSystemAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("DialogueSystem")), LOCTEXT("DialogueSystemAssetCategory", "Dialogue System"));

		RegisterAssetTypeAction(AssetTools, MakeShareable(new FQuestBookAssetTypeActions(DialogueSystemAssetCategoryBit)));

	};
	virtual void ShutdownModule() override
	{
		QuestBookEditor_ToolBarExtensibilityManager.Reset();
		CreatedAssetTypeActions.Empty();

		// Unregister slate style overrides
		FDialogueSystemStyle::Shutdown();
	};



private:
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
	{
		AssetTools.RegisterAssetTypeActions(Action);
		CreatedAssetTypeActions.Add(Action);
	}
};

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogueSystemEditorModule, DialogueSystemEditor)