
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