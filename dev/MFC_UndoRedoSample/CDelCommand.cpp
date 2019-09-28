#include "pch.h"
#include "CDelCommand.h"

/**
 *	新規の部署情報を追加する。
 *
 *	@param	Index	新規の部署情報をする場所
 *	@param[in]	SectionArray	新規の部署の追加先
 */
VOID CDelCommand::Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	ASSERT(nullptr != SectionArray);

	if (SectionArray->GetCount() < Index) {
		//指定された番号の要素が、配列に存在しない
		//	→何もしない
	} else {
		CSection* Item = SectionArray->GetAt(Index);
		delete Item;
		Item = nullptr;
		SectionArray->RemoveAt(Index);
	}
}
