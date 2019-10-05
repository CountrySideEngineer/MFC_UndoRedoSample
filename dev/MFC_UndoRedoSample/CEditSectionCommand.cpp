#include "pch.h"
#include "CEditSectionCommand.h"

VOID CEditSectionCommand::PrepCommand(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	this->m_CmdParamIndex = Index;
	this->m_CmdParamSectionArray = SectionArray;
	this->m_CmdParamSection = Section;
}
/**
 *	データ編集コマンド
 */
VOID CEditSectionCommand::Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	ASSERT(NULL != SectionArray);
	ASSERT(NULL != Section);

	CSection* DstSection = SectionArray->GetAt(Index);
	DstSection->SetDescription(Section->GetDescription());
	DstSection->SetManager(Section->GetManager());
	DstSection->SetSectionName(Section->GetSectionName());
}
