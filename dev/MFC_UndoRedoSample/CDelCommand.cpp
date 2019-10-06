#include "pch.h"
#include "CDelCommand.h"

/**
 *	�f�t�H���g�R���X�g���N�^
 */
CDelCommand::CDelCommand()
	: m_CmdParamIndex(0)
	, m_CmdParamSectionArray(nullptr)
	, m_CmdParamSection(nullptr)
{}

/**
 *	�R�}���h�����s���邽�߂ɕK�v�ȃf�[�^��ݒ肷��B
 *
 *	@param	Index				�}������ʒu
 *	@param[in]	SectionArray	�����ΏۂƂȂ�z��ւ̃|�C���^
 *	@param[in]	Section			�}������f�[�^
 */
VOID CDelCommand::PrepCommand(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
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
VOID CDelCommand::ExecuteCommand()
{
	ASSERT(nullptr != this->m_CmdParamSectionArray);

	if (this->m_CmdParamSectionArray->GetCount() < this->m_CmdParamIndex) {
		/*
		 *	�w�肳�ꂽ�ԍ��̗v�f�����݂��Ȃ�
		 *		���������Ȃ�
		 */
	}
	else {
		CSection* Item = this->m_CmdParamSectionArray->GetAt(this->m_CmdParamIndex);
		delete Item;
		Item = NULL;
		this->m_CmdParamSectionArray->RemoveAt(this->m_CmdParamIndex);
	}
}
