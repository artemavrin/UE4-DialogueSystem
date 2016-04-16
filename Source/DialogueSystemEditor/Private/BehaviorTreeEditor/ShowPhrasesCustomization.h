// Copyright 2015 Mavrin Artem. All Rights Reserved.

#pragma once

#include "Editor/DetailCustomizations/Private/DetailCustomizationsPrivatePCH.h"

class FTextPhrasesCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	FText GetTimeToolTip() const;
private:
	/** Property handles of the properties we're editing */
	TSharedPtr<IPropertyHandle> Phrase;
	TSharedPtr<IPropertyHandle> SoundToPlay;
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

class FCinematicOptionsCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	void OnSettingMatineeChange(FString NewValue);
	TSharedRef<SWidget> OnGetMatineeList() const;
	FText GetCurrentMatineeName() const;
private:
	/** Property handles of the properties we're editing */
	TSharedPtr<IPropertyHandle> bPlayMatinee;
	TSharedPtr<IPropertyHandle> bLoop;
	TSharedPtr<IPropertyHandle> Matinee;
};