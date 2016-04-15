
#include "DialogueSystemEditorPrivatePCH.h"
#include "QuestBookEditor/QuestBookEditorCustomization.h"

#define LOCTEXT_NAMESPACE "DialogueSystem"

TSharedRef<IPropertyTypeCustomization> FQuestBookEditorCustomization::MakeInstance()
{
	return MakeShareable(new FQuestBookEditorCustomization());
}

void FQuestBookEditorCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	ID = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuest, ID));
	Title = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuest, Title));
	FText ID_Value; ID->GetValueAsDisplayText(ID_Value);
	Title->GetValueAsDisplayText(Title_Value);

	HeaderRow.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget(ID_Value, Title_Value)
		]
	.ValueContent()
		.MinDesiredWidth(500)
		[
			SNew(STextBlock)
			//.Text(FText::FromString(TEXT("QUEST")))
			.Text(this, &FQuestBookEditorCustomization::GetTitleText)
			.Font(IDetailLayoutBuilder::GetDetailFont())
		];
}

FText FQuestBookEditorCustomization::GetTitleText() const
{
	FText Value;
	Title->GetValueAsDisplayText(Value);
	return Value;
}

void FQuestBookEditorCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	Title = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuest, Title));
	Description = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuest, Description));
	IntroText = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuest, IntroText));
	ProgressText = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuest, ProgressText));
	FinishText = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuest, FinishText));
	Experience = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuest, Experience));
	Tasks = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuest, Tasks));

	ChildBuilder.AddChildContent(LOCTEXT("Title", "Title"))
		.NameContent()
		[
			Title->CreatePropertyNameWidget()
		]
	.ValueContent()
		.HAlign(HAlign_Fill)
		[
			Title->CreatePropertyValueWidget()
		];
	ChildBuilder.AddChildContent(LOCTEXT("Description", "Description"))
		.NameContent()
		[
			Description->CreatePropertyNameWidget()
		]
	.ValueContent()
		.HAlign(HAlign_Fill)
		[
			Description->CreatePropertyValueWidget()
		];
	ChildBuilder.AddChildContent(LOCTEXT("IntroText", "IntroText"))
		.NameContent()
		[
			IntroText->CreatePropertyNameWidget()
		]
	.ValueContent()
		.HAlign(HAlign_Fill)
		[
			IntroText->CreatePropertyValueWidget()
		];
	ChildBuilder.AddChildContent(LOCTEXT("ProgressText", "ProgressText"))
		.NameContent()
		[
			ProgressText->CreatePropertyNameWidget()
		]
	.ValueContent()
		.HAlign(HAlign_Fill)
		[
			ProgressText->CreatePropertyValueWidget()
		];
	ChildBuilder.AddChildContent(LOCTEXT("FinishText", "FinishText"))
		.NameContent()
		[
			FinishText->CreatePropertyNameWidget()
		]
	.ValueContent()
		.HAlign(HAlign_Fill)
		[
			FinishText->CreatePropertyValueWidget()
		];

	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuest, Experience)).ToSharedRef());
	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuest, Tasks)).ToSharedRef());

}



TSharedRef<IPropertyTypeCustomization> FTextPhrasesCustomization::MakeInstance()
{
	return MakeShareable(new FTextPhrasesCustomization());
}

void FTextPhrasesCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	HeaderRow.NameContent()
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("")))
		]
	.ValueContent()
		.MinDesiredWidth(500)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Phrase")))
			.Font(IDetailLayoutBuilder::GetDetailFont())
		];
}

void FTextPhrasesCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	Phrase = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextPhrase, Phrase));
	ShowingTime = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextPhrase, ShowingTime));

	ChildBuilder.AddChildContent(LOCTEXT("Phrase", "Phrase"))
		.NameContent()
		[
			Phrase->CreatePropertyNameWidget()
		]
	.ValueContent()
		.HAlign(HAlign_Fill)
		[
			Phrase->CreatePropertyValueWidget()
		];
	
	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextPhrase, ShowingTime)).ToSharedRef());

}


#undef LOCTEXT_NAMESPACE

TSharedRef<IPropertyTypeCustomization> FTextOptionsCustomization::MakeInstance()
{
	return MakeShareable(new FTextOptionsCustomization());
}

void FTextOptionsCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	// We'll set up reset to default ourselves
	const bool bDisplayResetToDefault = false;
	const FText DisplayNameOverride = FText::GetEmpty();
	const FText DisplayToolTipOverride = FText::GetEmpty();

	HeaderRow
		.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget(DisplayNameOverride, DisplayToolTipOverride, bDisplayResetToDefault)
		];
}

void FTextOptionsCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	bShowTextPhrases = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, bShowTextPhrases));
	bHideLastPhrase = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, bHideLastPhrase));
	GeneralShowingTime = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, GeneralShowingTime));
	UseGeneralTime = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, UseGeneralTime));
	DialoguePhraseSlotName = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, DialoguePhraseSlotName));
	DialogueQuestionsSlotName = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, DialogueQuestionsSlotName));
	Phrases = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, Phrases));
	TextEffect = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, TextEffect));
	Delay = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, Delay));

	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, bShowTextPhrases)).ToSharedRef());
	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, bHideLastPhrase)).ToSharedRef());
	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, GeneralShowingTime)).ToSharedRef());
	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, UseGeneralTime)).ToSharedRef());
	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, DialoguePhraseSlotName)).ToSharedRef());
	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, DialogueQuestionsSlotName)).ToSharedRef());
	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, Phrases)).ToSharedRef());
	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, TextEffect)).ToSharedRef());
	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextOptions, Delay)).ToSharedRef()).Visibility(TAttribute<EVisibility>(this, &FTextOptionsCustomization::GetDelayVisibility));
}

EVisibility FTextOptionsCustomization::GetDelayVisibility() const
{
	uint8 Value;
	TextEffect->GetValue(Value);
	if (Value == 1)
	{
		return EVisibility::Visible;
	}
	else
	{
		return EVisibility::Hidden;
	}
}
