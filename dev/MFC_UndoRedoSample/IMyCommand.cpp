#include "pch.h"
#include "IMyCommand.h"
#include "CSectionOriginator.h"

//	@brief	コマンド実行を準備する
//
//	@param	Index	コマンドで操作対象とするデータの番号
//	@param	SectionArray	コマンド実行対象のデータ
//	@param	Section	コマンド実行のデータ
VOID IMyCommand::PrepCommand(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	this->m_CmdParamIndex = Index;
	this->m_CmdParamSectionArray = SectionArray;
	this->m_CmdParamSection = Section;

	this->m_HasMemento = FALSE;
}

//	@brief	コマンドの実行
//			すでにコマンドが実行されていた場合には、状態を実行後に変更する。
VOID IMyCommand::Execute()
{
	if (FALSE == this->m_HasMemento) {
		this->PreExecute();
		this->Execute(this->m_CmdParamIndex, this->m_CmdParamSectionArray, this->m_CmdParamSection);
		this->PostExecute();
	}
	else {
		CSectionOriginator* Instance = CSectionOriginator::GetInstance();
		Instance->SetMement(&(this->m_PostState));
	}
}

//	@brief	コマンドの実行を元に戻す
VOID IMyCommand::UnExecute()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	Instance->SetMement(&(this->m_PreState));
}

//	@brief	コマンド実行前の状態を保存しておく。(Undo用)
VOID IMyCommand::PreExecute()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	Instance->CreateMement(&(this->m_PreState));

	this->m_HasMemento = TRUE;
}

//	@brief	コマンド実行後の状態を保存しておく。(Redo用)
VOID IMyCommand::PostExecute()
{
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	Instance->CreateMement(&(this->m_PostState));
}