#pragma once
#include "IMyCommand.h"
class CEditSectionCommand :
	public IMyCommand
{
public:
	virtual VOID PrepCommand(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr);

protected:
	virtual VOID Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr);

protected:
};

