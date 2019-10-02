//Copyright (c) 2016 Artem A. Mavrin and other contributors

#pragma once

#include "IPropertyTypeCustomization.h"
#include "Runtime/Engine/Classes/Matinee/MatineeActor.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "IDetailChildrenBuilder.h"
class IPropertyHandle;


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
	TSharedPtr<IPropertyHandle> bShowRandomPhrase;
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

	void OnSettingSequenceChange(FString NewValue);
	TSharedRef<SWidget> OnGetSequenceList() const;
	FText GetCurrentSequenceName() const;
private:
	TSharedPtr<IPropertyHandle> bPlayMatinee;
	TSharedPtr<IPropertyHandle> Matinee;
	/** Property handles of the properties we're editing */
	TSharedPtr<IPropertyHandle> bPlaySeq;
	TSharedPtr<IPropertyHandle> bLoop;
	TSharedPtr<IPropertyHandle> bAutoPlay;
	TSharedPtr<IPropertyHandle> bDialogueCamType;
	TSharedPtr<IPropertyHandle> bUseCam;
	TSharedPtr<IPropertyHandle> Sequence;
};