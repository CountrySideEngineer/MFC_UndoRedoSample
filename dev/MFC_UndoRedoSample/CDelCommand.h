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

protected:
	INT_PTR m_CmdParamIndex;
	CArray<CSection*>* m_CmdParamSectionArray;
	CSection* m_CmdParamSection;
};

