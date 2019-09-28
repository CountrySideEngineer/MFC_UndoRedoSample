#include "pch.h"
#include "CSection.h"
#include "CAddCommand.h"
#include "CSectionOriginator.h"

/**
 *	新規の部署情報を追加する。
 *
 *	@param	Index	新規の部署情報をする場所
 *	@param[in]	SectionArray	新規の部署の追加先
 */
VOID CAddCommand::Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	ASSERT(nullptr != SectionArray);

	//実行前の状況を確保
	SectionArray->InsertAt(Index, Section);
}
