#include "pch.h"
#include "IMyCommand.h"
#include "CSectionOriginator.h"

//	@brief	コマンドの実行
//			すでにコマンドが実行されていた場合には、状態を実行後に変更する。
VOID IMyCommand::Execute()
{
	this->PreExecute();
	this->ExecuteCommand();
	this->PostExecute();
}

//	@brief	コマンドの実行前の状態に戻す。
VOID IMyCommand::UnDo()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	Instance->SetMemento(this->m_PreState);
}

//	@brief	コマンドの実行後の状態に戻す。
VOID IMyCommand::ReDo()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	Instance->SetMemento(this->m_PostState);
}


//	@brief	コマンド実行前の状態を保存しておく。(Undo用)
VOID IMyCommand::PreExecute()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	this->m_PreState = Instance->CreateMemento();
}

//	@brief	コマンド実行後の状態を保存しておく。(Redo用)
VOID IMyCommand::PostExecute()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	this->m_PostState = Instance->CreateMemento();
}