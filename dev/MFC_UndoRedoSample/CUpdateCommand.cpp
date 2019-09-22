#include "pch.h"
#include "CUpdateCommand.h"

VOID CUpdateCommand::Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	ASSERT(nullptr != SectionArray);
	ASSERT(nullptr != Section);

	if (0 == SectionArray->GetCount()) {
		//配列にデータが存在しない場合には、末尾(先頭)にデータを追加する。
		SectionArray->Add(Section);
	}
	else {
		if (SectionArray->GetCount() < Index) {
			//指定されたインデックスが範囲外の場合には、
			//そこまでに空白を埋めつつ、データを追加する。
			SectionArray->InsertAt(Index, Section);
		}
		else {
			//引数で指定されたデータが存在した場合のみ、
			//データを更新する。
			CSection* SectionItem = SectionArray->GetAt(Index);
			delete SectionItem;
			SectionItem = nullptr;
			SectionArray->SetAt(Index, Section);
		}
	}
}

VOID CUpdateCommand::UnExecute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{

}