#include "pch.h"
#include "IMyCommand.h"
#include "CSectionOriginator.h"

/**
 *	デストラクタ
 */
IMyCommand::~IMyCommand()
{
	delete this->m_PreState;
	delete this->m_PostState;
}

/**
 *	コマンド処理を実行しつつ、実行前後の状態を保持する。
 */
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