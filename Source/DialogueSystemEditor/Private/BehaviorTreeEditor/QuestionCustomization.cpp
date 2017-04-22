//Copyright (c) 2016 Artem A. Mavrin and other contributors
#pragma once

#include "DialogueSystemEditorPrivatePCH.h"
#include "QuestionCustomization.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailPropertyRow.h"
#include "DetailCategoryBuilder.h"

#define LOCTEXT_NAMESPACE "DialogueSystem"

TSharedRef<IDetailCustomization> FQuestionDetails::MakeInstance()
{
	return MakeShareable(new FQuestionDetails);
}

void FQuestionDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
		
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Question");
	SettingsProperty = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UBTComposite_Question, DialogueSettings));
	SettingNameProperty = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UBTComposite_Question, SettingName));

	Category.AddProperty(GET_MEMBER_NAME_CHECKED(UBTComposite_Question, QuestionThumbnail));

	IDetailCategoryBuilder& VisibilityCategory = DetailBuilder.EditCategory("QuestionVisibility");
	VisibilityCategory.AddProperty(GET_MEMBER_NAME_CHECKED(UBTComposite_Question, bVisible));
	VisibilityCategory.AddProperty(GET_MEMBER_NAME_CHECKED(UBTComposite_Question, bHideAfterSelect));
	VisibilityCategory.AddProperty(GET_MEMBER_NAME_CHECKED(UBTComposite_Question, DialogueSettings));

	IDetailPropertyRow& SettingName = VisibilityCategory.AddProperty(SettingNameProperty);
	SettingName.CustomWidget()
		.NameContent()
		[
			SettingNameProperty->CreatePropertyNameWidget()
		]
		.ValueContent()
		[
			SNew(SComboButton)
			.OnGetMenuContent(this, &FQuestionDetails::OnGetVariableList)
			.ContentPadding(FMargin(2.0f, 2.0f))
			.ButtonContent()
			[
				SNew(STextBlock)
				.Text(this, &FQuestionDetails::GetCurrentSettingName)
				.Font(IDetailLayoutBuilder::GetDetailFont())
			]
		];
}

void FQuestionDetails::OnSettingNameChange(FString NewValue)
{
	SettingNameProperty->SetValueFromFormattedString(NewValue);
}

TSharedRef<SWidget> FQuestionDetails::OnGetVariableList() const
{
	TArray<FString> VariableList = GetVariableList();
	FMenuBuilder MenuBuilder(true, NULL);

	for (int32 i = 0; i < VariableList.Num(); i++)
	{
		FUIAction ItemAction(FExecuteAction::CreateSP(this, &FQuestionDetails::OnSettingNameChange, VariableList[i]));
		MenuBuilder.AddMenuEntry(FText::FromString(VariableList[i]), TAttribute<FText>(), FSlateIcon(), ItemAction);
	}

	return MenuBuilder.MakeWidget();
}

FText FQuestionDetails::GetCurrentSettingName() const
{
	FText SettingName;
	TArray<FString> VariableList = GetVariableList();
	SettingNameProperty->GetValueAsDisplayText(SettingName);
	for (int32 i = 0; i < VariableList.Num(); i++)
	{
		if (SettingName.EqualTo(FText::FromString(VariableList[i])))
		{
			return SettingName;
		}
	}

	SettingNameProperty->SetValueFromFormattedString(FString("None"));
	return FText::FromString("None");
}

TArray<FString> FQuestionDetails::GetVariableList() const
{
	UObject* QuetionSettings;
	TArray<FString> List;
	FPropertyAccess::Result Result = SettingsProperty->GetValue(QuetionSettings);
	if (Result == FPropertyAccess::Success && QuetionSettings != NULL)
	{
		UBlueprintGeneratedClass* BP = Cast<UBlueprintGeneratedClass>(QuetionSettings);
		if (BP)
		{
			ADialogueSettings* DialogueSettings = Cast<ADialogueSettings>(BP->ClassDefaultObject);
			if (DialogueSettings)
			{
				List = DialogueSettings->GetBoolVariables();
			}
		}
	}

	return List;
}

#undef LOCTEXT_NAMESPACE