#pragma once
#include "IMyCommand.h"
class CUpdateCommand :
	public IMyCommand
{
public:
	virtual VOID Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr);
	virtual VOID UnExecute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr);
};

