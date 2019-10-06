#include "pch.h"
#include "IMyCommand.h"
#include "CSectionOriginator.h"

//	@brief	�R�}���h�̎��s
//			���łɃR�}���h�����s����Ă����ꍇ�ɂ́A��Ԃ����s��ɕύX����B
VOID IMyCommand::Execute()
{
	this->PreExecute();
	this->ExecuteCommand();
	this->PostExecute();
}

//	@brief	�R�}���h�̎��s�O�̏�Ԃɖ߂��B
VOID IMyCommand::UnDo()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	Instance->SetMemento(this->m_PreState);
}

//	@brief	�R�}���h�̎��s��̏�Ԃɖ߂��B
VOID IMyCommand::ReDo()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	Instance->SetMemento(this->m_PostState);
}


//	@brief	�R�}���h���s�O�̏�Ԃ�ۑ����Ă����B(Undo�p)
VOID IMyCommand::PreExecute()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	this->m_PreState = Instance->CreateMemento();
}

//	@brief	�R�}���h���s��̏�Ԃ�ۑ����Ă����B(Redo�p)
VOID IMyCommand::PostExecute()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	this->m_PostState = Instance->CreateMemento();
}