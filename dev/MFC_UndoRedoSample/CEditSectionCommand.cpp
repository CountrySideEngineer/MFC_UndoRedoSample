#include "pch.h"
#include "CEditSectionCommand.h"

CEditSectionCommand::CEditSectionCommand()
	: m_EditedDialog(nullptr)
{}

/**
 *	�R�}���h�̎��s�������s���B
 *
 *	@param[in]	EditedDialog	
 */
VOID CEditSectionCommand::PrepCommand(CDialog* EditedDialog)
{
	ASSERT(nullptr != EditedDialog);

	this->m_EditedDialog = EditedDialog;
}
/**
 *	�f�[�^�ҏW�R�}���h
 */
VOID CEditSectionCommand::ExecuteCommand()
{
	ASSERT(nullptr != this->m_EditedDialog);

	this->m_EditedDialog->UpdateData();	//���͂��ꂽ�����ADDX�ϐ��ɔ��f����B
}
