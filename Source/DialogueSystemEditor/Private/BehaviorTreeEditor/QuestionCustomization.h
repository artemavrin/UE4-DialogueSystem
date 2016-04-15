// Copyright 2015 Mavrin Artem. All Rights Reserved.
#pragma once

#include "Editor/DetailCustomizations/Private/DetailCustomizationsPrivatePCH.h"

#pragma once

class FQuestionDetails : public IDetailCustomization
{
public:
	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedRef<IDetailCustomization> MakeInstance();

	/** IDetailCustomization interface */
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	TSharedPtr<IPropertyHandle> SettingNameProperty;
	TSharedPtr<IPropertyHandle> SettingsProperty;
	
	void OnSettingNameChange(FString NewValue);
	TSharedRef<SWidget> OnGetVariableList() const;
	FText GetCurrentSettingName() const;
	TArray<FString> GetVariableList() const;
};