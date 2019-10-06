#pragma once
#include "IMyCommand.h"
#include "CSection.h"

/**
 *	追加を行うコマンドクラス
 */
class CAddCommand :
	public IMyCommand
{
public:
	CAddCommand();
	virtual ~CAddCommand() {}
	
	virtual VOID PrepCommand(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr);
	virtual VOID ExecuteCommand();

protected:
	INT_PTR m_CmdParamIndex;
	CArray<CSection*>* m_CmdParamSectionArray;
	CSection* m_CmdParamSection;
};

