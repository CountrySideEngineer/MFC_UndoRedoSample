#pragma once
#include "IMyCommand.h"
class CUpdateCommand :
	public IMyCommand
{
public:
	virtual VOID PrepCommand(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr);

protected:
	virtual VOID ExecuteCommand();
};

