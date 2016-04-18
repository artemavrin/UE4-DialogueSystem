//Copyright (c) 2016 Artem A. Mavrin and other contributors

#include "DialogueSystemEditorPrivatePCH.h"

#include "AssetToolsModule.h"

#include "QuestBookAssetTypeActions.h"
#include "DialogueSystemStyle.h"
#include "QuestBookEditor/QuestBookEditorCustomization.h"
#include "BehaviorTreeEditor/QuestionCustomization.h"
#include "BehaviorTreeEditor/ShowPhrasesCustomization.h"

#include "SNotificationList.h"
#include "NotificationManager.h"
#include "Developer/SimplygonSwarm/Public/SimplygonRESTClient.h"

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

		// register notifications
		RegisterNotifications();

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

	void RegisterNotifications()
	{
		TSharedRef<IHttpRequest> request = FHttpModule::Get().CreateRequest();
		FString server = "http://mavrinsoft.ru/GetCurrentVersion.php?";
		FString app = "DialogueSystem";
		FString major = "1";
		FString minor = "6";
		FString additional = "0";

		FString url = FString::Printf(TEXT("%sapp=%s&major=%s&minor=%s&additional=%s"), *server, *app, *major, *minor, *additional);
		request->SetURL(url);
		request->SetVerb(TEXT("GET"));

		request->OnProcessRequestComplete().BindRaw(this, &FDialogueSystemEditorModule::CurrentVersion_Response);
		request->ProcessRequest();
	}

	void CurrentVersion_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{

		if (bWasSuccessful)
		{
			TextResponse = Response->GetContentAsString();
			UE_LOG(LogTemp, Warning, TEXT("Response: %s "), *TextResponse);
			ShowNotification();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't connect to the server"));
		}
	}

	void ShowNotification()
	{
		if (TextResponse != "Plugin is up to date")
		{
			const FText NotificationErrorText = FText::Format(NSLOCTEXT("DialogueSystem", "NewVersionAvailebleTitle", "{0}"), FText::FromString(TextResponse));
			FNotificationInfo Info(NotificationErrorText);
			Info.Hyperlink = FSimpleDelegate::CreateStatic(&FDialogueSystemEditorModule::OpenSite);
			Info.HyperlinkText = LOCTEXT("ShowOutputLogHyperlink", "DOWNLOAD");
			Info.ExpireDuration = 5.0f;
			NewVersionNotification = FSlateNotificationManager::Get().AddNotification(Info);
		}
	}

	static void OpenSite()
	{
		FString TheURL = "http://mavrinsoft.ru";
		FPlatformProcess::LaunchURL(*TheURL, nullptr, nullptr);
	}
};

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogueSystemEditorModule, DialogueSystemEditor)