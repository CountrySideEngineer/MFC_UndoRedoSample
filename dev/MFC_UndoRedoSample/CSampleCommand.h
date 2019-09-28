#pragma once
#include "IMyCommand.h"

class CSampleCommand : public IMyCommand
{
public:
	CSampleCommand(INT_PTR Count);

	virtual VOID Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr);
	virtual VOID UnExecute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr);

protected:
	INT_PTR m_Count;
};

