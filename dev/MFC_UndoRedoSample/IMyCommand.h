#pragma once
#include "CSection.h"

/**
 *	コマンドクラスのインターフェース
 */
class IMyCommand
{
public:
	virtual VOID PrepCommand(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr);
	virtual VOID Execute();
	virtual VOID UnExecute();

	virtual BOOL HasMement() { return this->m_HasMemento; }

protected:
	virtual VOID Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr) = 0;
	virtual VOID PreExecute();
	virtual VOID PostExecute();

protected:
	INT_PTR m_CmdParamIndex;
	CArray<CSection*>* m_CmdParamSectionArray;
	CSection* m_CmdParamSection;

	BOOL m_HasMemento;
	CArray<CSection*> m_PreState;
	CArray<CSection*> m_PostState;
};
