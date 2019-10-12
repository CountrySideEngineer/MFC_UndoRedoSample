#include "pch.h"
#include "CUpdateCommand.h"


VOID CUpdateCommand::PrepCommand(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	this->m_CmdParamIndex = Index;
	this->m_CmdParamSectionArray = SectionArray;
	this->m_CmdParamSection = Section;
}

/**
 *	編集コマンドを実行する。
 */
VOID CUpdateCommand::ExecuteCommand()
{
	ASSERT(nullptr != this->m_CmdParamSectionArray);
	ASSERT(nullptr != this->m_CmdParamSection);

	if (0 == this->m_CmdParamSectionArray->GetCount()) {
		//配列にデータが存在しない場合には、末尾(先頭)にデータを追加する。
		this->m_CmdParamSectionArray->Add(this->m_CmdParamSection);
	}
	else {
		if (this->m_CmdParamSectionArray->GetCount() < this->m_CmdParamIndex) {
			//指定されたインデックスが範囲外の場合には、
			//そこまでに空白を埋めつつ、データを追加する。
			this->m_CmdParamSectionArray->InsertAt(this->m_CmdParamIndex, this->m_CmdParamSection);
		}
		else {
			//引数で指定されたデータが存在した場合のみ、
			//データを更新する。
			CSection* SectionItem = this->m_CmdParamSectionArray->GetAt(this->m_CmdParamIndex);
			delete SectionItem;
			SectionItem = nullptr;
			this->m_CmdParamSectionArray->SetAt(this->m_CmdParamIndex, this->m_CmdParamSection);
		}
	}
}
