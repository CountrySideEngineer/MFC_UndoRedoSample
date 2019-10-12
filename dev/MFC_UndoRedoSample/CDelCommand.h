#pragma once
#include "IMyCommand.h"
#include "CSection.h"

class CDelCommand :
	public IMyCommand
{
public:
	CDelCommand();
	virtual ~CDelCommand() {}

	virtual VOID PrepCommand(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr);
	virtual VOID ExecuteCommand();
};

