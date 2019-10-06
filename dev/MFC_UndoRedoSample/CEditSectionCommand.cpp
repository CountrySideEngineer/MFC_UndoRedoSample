#include "pch.h"
#include "CEditSectionCommand.h"

CEditSectionCommand::CEditSectionCommand()
	: m_EditedDialog(nullptr)
{}

/**
 *	コマンドの実行準備を行う。
 *
 *	@param[in]	EditedDialog	
 */
VOID CEditSectionCommand::PrepCommand(CDialog* EditedDialog)
{
	ASSERT(nullptr != EditedDialog);

	this->m_EditedDialog = EditedDialog;
}
/**
 *	データ編集コマンド
 */
VOID CEditSectionCommand::ExecuteCommand()
{
	ASSERT(nullptr != this->m_EditedDialog);

	this->m_EditedDialog->UpdateData();	//入力された情報を、DDX変数に反映する。
}
