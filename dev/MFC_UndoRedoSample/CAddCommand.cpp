#include "pch.h"
#include "CSection.h"
#include "CAddCommand.h"

/**
 *	新規の部署情報を追加する。
 *
 *	@param	Index	新規の部署情報をする場所
 *	@param[in]	SectionArray	新規の部署の追加先
 */
VOID CAddCommand::Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	ASSERT(nullptr != SectionArray);

	SectionArray->InsertAt(Index, Section);
}

/**
 *	新規の部署の追加をやり直す
 *
 *	@param	Index	新規の部署情報のやり直しを行う場所
 *	@param[in]	SectionArray	新規の部署の追加のやり直し先
 */
VOID CAddCommand::UnExecute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	ASSERT(nullptr != SectionArray);

	SectionArray->RemoveAt(Index);
}