#include "pch.h"
#include "CDelCommand.h"

/**
 *	デフォルトコンストラクタ
 */
CDelCommand::CDelCommand()
	: m_CmdParamIndex(0)
	, m_CmdParamSectionArray(nullptr)
	, m_CmdParamSection(nullptr)
{}

/**
 *	コマンドを実行するために必要なデータを設定する。
 *
 *	@param	Index				挿入する位置
 *	@param[in]	SectionArray	処理対象となる配列へのポインタ
 *	@param[in]	Section			挿入するデータ
 */
VOID CDelCommand::PrepCommand(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	this->m_CmdParamIndex = Index;
	this->m_CmdParamSectionArray = SectionArray;
	this->m_CmdParamSection = Section;
}

/**
 *	新規の部署情報を追加する。
 *
 *	@param	Index	新規の部署情報をする場所
 *	@param[in]	SectionArray	新規の部署の追加先
 */
VOID CDelCommand::ExecuteCommand()
{
	ASSERT(nullptr != this->m_CmdParamSectionArray);

	if (this->m_CmdParamSectionArray->GetCount() < this->m_CmdParamIndex) {
		/*
		 *	指定された番号の要素が存在しない
		 *		→何もしない
		 */
	}
	else {
		CSection* Item = this->m_CmdParamSectionArray->GetAt(this->m_CmdParamIndex);
		delete Item;
		Item = NULL;
		this->m_CmdParamSectionArray->RemoveAt(this->m_CmdParamIndex);
	}
}
