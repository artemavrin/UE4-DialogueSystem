//Copyright (c) 2016 Artem A. Mavrin and other contributors
#pragma once

#include "BTComposite_Context.h"

#include "BTContextNode_Interface.generated.h"

UINTERFACE()
class UBTContextNode_Interface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IBTContextNode_Interface
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void GetPhrasesContext(const UBTNode * CurrentNode, FFormatNamedArguments& FormatNamedArguments, UBlackboardComponent * Blackboard) const;

};