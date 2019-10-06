#pragma once
#include "CSection.h"
#include "CMemento.h"

/**
 *	コマンドクラスのインターフェース
 */
class IMyCommand
{
public:
	virtual VOID Execute();
	virtual VOID UnDo();
	virtual VOID ReDo();

protected:
	virtual VOID ExecuteCommand() = 0;
	virtual VOID PreExecute();
	virtual VOID PostExecute();

protected:
	INT_PTR m_CmdParamIndex;
	CArray<CSection*>* m_CmdParamSectionArray;
	CSection* m_CmdParamSection;

	CMemento* m_PreState;
	CMemento* m_PostState;
};
