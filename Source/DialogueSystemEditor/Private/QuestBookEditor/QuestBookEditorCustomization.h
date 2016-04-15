// Copyright 2015 Mavrin Artem. All Rights Reserved.

#pragma once

#include "Editor/DetailCustomizations/Private/DetailCustomizationsPrivatePCH.h"

class FQuestBookEditorCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	FText GetTitleText() const;

private:
	/** Property handles of the properties we're editing */
	TSharedPtr<IPropertyHandle> ID;
	TSharedPtr<IPropertyHandle> Title;
	TSharedPtr<IPropertyHandle> Description;
	TSharedPtr<IPropertyHandle> IntroText;
	TSharedPtr<IPropertyHandle> ProgressText;
	TSharedPtr<IPropertyHandle> FinishText;
	TSharedPtr<IPropertyHandle> Tasks;
	TSharedPtr<IPropertyHandle> Experience;

	FText Title_Value;
	
	/** Editable text widget */
	TSharedPtr< SMultiLineEditableTextBox > EditableText;
};

class FTextPhrasesCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

private:
	/** Property handles of the properties we're editing */
	TSharedPtr<IPropertyHandle> Phrase;
	TSharedPtr<IPropertyHandle> ShowingTime;
};

class FTextOptionsCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	EVisibility GetDelayVisibility() const;
private:
	/** Property handles of the properties we're editing */
	TSharedPtr<IPropertyHandle> bShowTextPhrases;
	TSharedPtr<IPropertyHandle> bHideLastPhrase;
	TSharedPtr<IPropertyHandle> GeneralShowingTime;
	TSharedPtr<IPropertyHandle> UseGeneralTime;
	TSharedPtr<IPropertyHandle> DialoguePhraseSlotName;
	TSharedPtr<IPropertyHandle> DialogueQuestionsSlotName;
	TSharedPtr<IPropertyHandle> Phrases;
	TSharedPtr<IPropertyHandle> TextEffect;
	TSharedPtr<IPropertyHandle> Delay;
};