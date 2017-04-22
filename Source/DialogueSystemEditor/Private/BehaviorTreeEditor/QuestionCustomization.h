//Copyright (c) 2016 Artem A. Mavrin and other contributors
#pragma once

#include "IDetailCustomization.h"

class IDetailLayoutBuilder;
class IPropertyHandle;
class SWidget;

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