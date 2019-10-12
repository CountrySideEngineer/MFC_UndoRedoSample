#include "pch.h"
#include "CSection.h"
#include "CAddCommand.h"
#include "CSectionOriginator.h"

/**
 *	�f�t�H���g�R���X�g���N�^
 */
CAddCommand::CAddCommand()
{
	m_CmdParamIndex = 0;
	m_CmdParamSectionArray = nullptr;
	m_CmdParamSection = nullptr;
}

/**
 *	�R�}���h�����s���邽�߂ɕK�v�ȃf�[�^��ݒ肷��B
 *
 *	@param	Index				�}������ʒu
 *	@param[in]	SectionArray	�����ΏۂƂȂ�z��ւ̃|�C���^
 *	@param[in]	Section			�}������f�[�^
 */
VOID CAddCommand::PrepCommand(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	this->m_CmdParamIndex = Index;
	this->m_CmdParamSectionArray = SectionArray;
	this->m_CmdParamSection = Section;
}

/**
 *	�V�K�̕�������ǉ�����B
 *
 *	@param	Index	�V�K�̕�����������ꏊ
 *	@param[in]	SectionArray	�V�K�̕����̒ǉ���
 */
VOID CAddCommand::ExecuteCommand()
{
	ASSERT(nullptr != this->m_CmdParamSectionArray);
	ASSERT(nullptr != this->m_CmdParamSection);

	this->m_CmdParamSectionArray->InsertAt(this->m_CmdParamIndex, this->m_CmdParamSection);
}
