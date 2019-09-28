#include "pch.h"
#include "IMyCommand.h"
#include "CSectionOriginator.h"

//	@brief	�R�}���h���s����������
//
//	@param	Index	�R�}���h�ő���ΏۂƂ���f�[�^�̔ԍ�
//	@param	SectionArray	�R�}���h���s�Ώۂ̃f�[�^
//	@param	Section	�R�}���h���s�̃f�[�^
VOID IMyCommand::PrepCommand(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	this->m_CmdParamIndex = Index;
	this->m_CmdParamSectionArray = SectionArray;
	this->m_CmdParamSection = Section;
}

//	@brief	�R�}���h�̎��s
//			���łɃR�}���h�����s����Ă����ꍇ�ɂ́A��Ԃ����s��ɕύX����B
VOID IMyCommand::Execute()
{
	this->PreExecute();
	this->Execute(this->m_CmdParamIndex, this->m_CmdParamSectionArray, this->m_CmdParamSection);
	this->PostExecute();
}

//	@brief	�R�}���h�̎��s�O�̏�Ԃɖ߂��B
VOID IMyCommand::UnDo()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	Instance->SetMement(&(this->m_PreState));
}

//	@brief	�R�}���h�̎��s��̏�Ԃɖ߂��B
VOID IMyCommand::ReDo()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	Instance->SetMement(&(this->m_PostState));
}


//	@brief	�R�}���h���s�O�̏�Ԃ�ۑ����Ă����B(Undo�p)
VOID IMyCommand::PreExecute()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	Instance->CreateMement(&(this->m_PreState));
}

//	@brief	�R�}���h���s��̏�Ԃ�ۑ����Ă����B(Redo�p)
VOID IMyCommand::PostExecute()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	Instance->CreateMement(&(this->m_PostState));
}