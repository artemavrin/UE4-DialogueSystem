//Copyright (c) 2016 Artem A. Mavrin and other contributors

#pragma once

#include "IPropertyTypeCustomization.h"

class IPropertyHandle;

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
