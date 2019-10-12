#include "pch.h"
#include "CSectionOriginator.h"
#include "CMemento.h"

CSectionOriginator* CSectionOriginator::Instance = NULL;

/**
 *	CSectionOriginatorのインスタンスを取得する。
 */
CSectionOriginator* CSectionOriginator::GetInstance()
{
	if (nullptr == Instance) {
		Instance = new CSectionOriginator();
	}
	return Instance;
}

/**
 *	デフォルトコンストラクタ
 */
CSectionOriginator::CSectionOriginator() 
	: m_DestDialog(nullptr)
	, m_Target(nullptr)
	, m_SectionNameDdx(nullptr)
	, m_SectionManagerDdx(nullptr)
	, m_DescriptionDdx(nullptr)
{}

/**
 *	Mementoの反映先を設定する。
 */
void CSectionOriginator::InitInstance(CDialog* DestDialog, 
	CArray<CSection*>* Target,
	CString* SectionName,
	CString* SectionManager,
	CString* Description) 
{
	CSectionOriginator* Instance = GetInstance();
	Instance->m_DestDialog = DestDialog;
	Instance->m_Target = Target;
	Instance->m_SectionNameDdx = SectionName;
	Instance->m_SectionManagerDdx = SectionManager;
	Instance->m_DescriptionDdx = Description;
}

/**
 *	インスタンスを破棄する
 */
void CSectionOriginator::Destroy()
{
	if (nullptr != Instance) {
		delete Instance;
	}
}


/**
 *	Mementoを作成する。
 *
 *	@return	現在の状態を保持したメメント
 */
CMemento* CSectionOriginator::CreateMemento()
{
	CArray<CSection*>* Target = new CArray<CSection*>();
	if (NULL != this->m_Target) {
		for (INT_PTR Index = 0; Index < this->m_Target->GetCount(); Index++) {
			CSection* SectionItem = this->m_Target->GetAt(Index);
			CSection* SectionMemento = new CSection(SectionItem);
			Target->Add(SectionMemento);
		}
	}

	CMemento* Memento = new CMemento();
	Memento->SetTarget(Target);
	Memento->SetSectionName(*(this->m_SectionNameDdx));
	Memento->SetSectionManager(*(this->m_SectionManagerDdx));
	Memento->SetDescription(*(this->m_DescriptionDdx));

	return Memento;
}

/**
 *	Mementの内容を反映する。
 *
 *	@param	Mement	反映したい内容/状態へのポインタ
 */
void CSectionOriginator::SetMement(CArray<CSection*>* Mement)
{
	ASSERT(nullptr != Mement);
	ASSERT(nullptr != this->m_Target);

	for (INT_PTR Index = 0; Index < this->m_Target->GetCount(); Index++) {
		CSection* TargetItem = this->m_Target->GetAt(Index);
		delete TargetItem;
		TargetItem = nullptr;
	}
	this->m_Target->RemoveAll();

	for (INT_PTR MementoIndex = 0; MementoIndex < Mement->GetCount(); MementoIndex++) {
		CSection* StateItem = Mement->GetAt(MementoIndex);
		CSection* NewItem = new CSection(StateItem);
		this->m_Target->Add(NewItem);
	}
}

/**
 *	状態を元に戻す
 *
 *	@param[in]	Memento	元に戻したい状態を保持したCMementoオブジェクト
 *						へのポインタ。
 */
void CSectionOriginator::SetMemento(CMemento* Memento)
{
	ASSERT(nullptr != Memento);

	for (INT_PTR Index = 0; Index < this->m_Target->GetCount(); Index++) {
		CSection* TargetItem = this->m_Target->GetAt(Index);
		delete TargetItem;
		TargetItem = nullptr;
	}
	this->m_Target->RemoveAll();

	CArray<CSection*>* MementoTarget = Memento->GetTarget();
	if (nullptr != MementoTarget) {
		for (INT_PTR Index = 0; Index < MementoTarget->GetCount(); Index++) {
			CSection* SectionItem = MementoTarget->GetAt(Index);
			this->m_Target->InsertAt(Index, SectionItem);
		}
	}

	*(this->m_SectionNameDdx) = Memento->GetSectionName();
	*(this->m_SectionManagerDdx) = Memento->GetSectionManager();
	*(this->m_DescriptionDdx) = Memento->GetDescription();

	this->m_DestDialog->UpdateData(FALSE);	//DDX変数の内容をコントロールに反映する。
}