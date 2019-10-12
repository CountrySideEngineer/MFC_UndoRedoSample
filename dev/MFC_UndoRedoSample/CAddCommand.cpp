#include "pch.h"
#include "CSection.h"
#include "CAddCommand.h"
#include "CSectionOriginator.h"

/**
 *	デフォルトコンストラクタ
 */
CAddCommand::CAddCommand()
{
	m_CmdParamIndex = 0;
	m_CmdParamSectionArray = nullptr;
	m_CmdParamSection = nullptr;
}

/**
 *	コマンドを実行するために必要なデータを設定する。
 *
 *	@param	Index				挿入する位置
 *	@param[in]	SectionArray	処理対象となる配列へのポインタ
 *	@param[in]	Section			挿入するデータ
 */
VOID CAddCommand::PrepCommand(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
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
VOID CAddCommand::ExecuteCommand()
{
	ASSERT(nullptr != this->m_CmdParamSectionArray);
	ASSERT(nullptr != this->m_CmdParamSection);

	this->m_CmdParamSectionArray->InsertAt(this->m_CmdParamIndex, this->m_CmdParamSection);
}
