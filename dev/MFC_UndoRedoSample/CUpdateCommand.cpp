#include "pch.h"
#include "CUpdateCommand.h"


VOID CUpdateCommand::PrepCommand(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	this->m_CmdParamIndex = Index;
	this->m_CmdParamSectionArray = SectionArray;
	this->m_CmdParamSection = Section;
}

/**
 *	�ҏW�R�}���h�����s����B
 */
VOID CUpdateCommand::ExecuteCommand()
{
	ASSERT(nullptr != this->m_CmdParamSectionArray);
	ASSERT(nullptr != this->m_CmdParamSection);

	if (0 == this->m_CmdParamSectionArray->GetCount()) {
		//�z��Ƀf�[�^�����݂��Ȃ��ꍇ�ɂ́A����(�擪)�Ƀf�[�^��ǉ�����B
		this->m_CmdParamSectionArray->Add(this->m_CmdParamSection);
	}
	else {
		if (this->m_CmdParamSectionArray->GetCount() < this->m_CmdParamIndex) {
			//�w�肳�ꂽ�C���f�b�N�X���͈͊O�̏ꍇ�ɂ́A
			//�����܂łɋ󔒂𖄂߂A�f�[�^��ǉ�����B
			this->m_CmdParamSectionArray->InsertAt(this->m_CmdParamIndex, this->m_CmdParamSection);
		}
		else {
			//�����Ŏw�肳�ꂽ�f�[�^�����݂����ꍇ�̂݁A
			//�f�[�^���X�V����B
			CSection* SectionItem = this->m_CmdParamSectionArray->GetAt(this->m_CmdParamIndex);
			delete SectionItem;
			SectionItem = nullptr;
			this->m_CmdParamSectionArray->SetAt(this->m_CmdParamIndex, this->m_CmdParamSection);
		}
	}
}
