
#include "DialogueSystemEditorPrivatePCH.h"
#include "ShowPhrasesCustomization.h"
#include "Runtime/Engine/Classes/Matinee/MatineeActor.h"

#define LOCTEXT_NAMESPACE "DialogueSystem"

/////////////////////////////
//FTextPhrasesCustomization

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
	SoundToPlay = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextPhrase, SoundToPlay));
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

	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueTextPhrase, SoundToPlay)).ToSharedRef());
	ChildBuilder.AddChildContent(LOCTEXT("ShowingTime", "ShowingTime"))
		.NameContent()
		[
			ShowingTime->CreatePropertyNameWidget()
		]
	.ValueContent()
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.MaxWidth(109.0f)
			[
				ShowingTime->CreatePropertyValueWidget()
			]
			+ SHorizontalBox::Slot()
			.Padding(FMargin(8.0f, 0.0f))
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(this, &FTextPhrasesCustomization::GetTimeToolTip)
				.Font(FEditorStyle::GetFontStyle(TEXT("TinyText")))
				.ToolTipText(LOCTEXT("ShowingTimeToolTip", "Sound duration"))
			]
		];

}

FText FTextPhrasesCustomization::GetTimeToolTip() const
{
	FText Result = FText::Format(LOCTEXT("ShowingTime", "{0}+"), FText::AsNumber(0.0f));
	UObject* PhraseAudioObject;
	SoundToPlay->GetValue(PhraseAudioObject);
	if (USoundCue* Sound = Cast<USoundCue>(PhraseAudioObject))
	{
		Result = FText::Format(LOCTEXT("ShowingTime", "{0}+"), FText::AsNumber(Sound->GetDuration()));
	}

	return Result;
}

/////////////////////////////
//FTextOptionsCustomization

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


/////////////////////////////
//FCinematicOptionsCustomization

TSharedRef<IPropertyTypeCustomization> FCinematicOptionsCustomization::MakeInstance()
{
	return MakeShareable(new FCinematicOptionsCustomization());
}

void FCinematicOptionsCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
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

void FCinematicOptionsCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	bPlayMatinee = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueCinematicOptions, bPlayMatinee));
	bLoop = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueCinematicOptions, bLoop));
	Matinee = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueCinematicOptions, Matinee));

	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueCinematicOptions, bPlayMatinee)).ToSharedRef());
	ChildBuilder.AddChildProperty(StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBTDialogueCinematicOptions, bLoop)).ToSharedRef());

	ChildBuilder.AddChildContent(LOCTEXT("Matinee", "Matinee"))
		.NameContent()
		[
			Matinee->CreatePropertyNameWidget()
		]
	.ValueContent()
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.MaxWidth(109.0f)
			[
				SNew(SComboButton)
				.OnGetMenuContent(this, &FCinematicOptionsCustomization::OnGetMatineeList)
				.ContentPadding(FMargin(2.0f, 2.0f))
				.ButtonContent()
				[
					SNew(STextBlock)
					.Text(this, &FCinematicOptionsCustomization::GetCurrentMatineeName)
					.Font(IDetailLayoutBuilder::GetDetailFont())
				]
			]
		];
}

void FCinematicOptionsCustomization::OnSettingMatineeChange(FString NewValue)
{
	Matinee->SetValueFromFormattedString(NewValue);
}

TSharedRef<SWidget> FCinematicOptionsCustomization::OnGetMatineeList() const
{
	
	FMenuBuilder MenuBuilder(true, NULL);

	FUIAction ItemAction(FExecuteAction::CreateSP(this, &FCinematicOptionsCustomization::OnSettingMatineeChange, FString("None")));
	MenuBuilder.AddMenuEntry(FText::FromString(TEXT("None")), TAttribute<FText>(), FSlateIcon(), ItemAction);

	for (TObjectIterator<AMatineeActor> It; It; ++It)
	{
		AMatineeActor* MatineeActor = *It;
		FUIAction ItemAction(FExecuteAction::CreateSP(this, &FCinematicOptionsCustomization::OnSettingMatineeChange, MatineeActor->GetName()));
		MenuBuilder.AddMenuEntry(FText::FromString(MatineeActor->GetName()), TAttribute<FText>(), FSlateIcon(), ItemAction);
	}

	return MenuBuilder.MakeWidget();
}

FText FCinematicOptionsCustomization::GetCurrentMatineeName() const
{
	FText SettingName;
	Matinee->GetValueAsDisplayText(SettingName);
	for (TObjectIterator<AMatineeActor> It; It; ++It)
	{
		AMatineeActor* MatineeActor = *It;
		if (SettingName.EqualTo(FText::FromString(MatineeActor->GetName())))
		{
			return SettingName;
		}
	}

	Matinee->SetValueFromFormattedString(FString("None"));
	return FText::FromString("None");
}

#undef LOCTEXT_NAMESPACE