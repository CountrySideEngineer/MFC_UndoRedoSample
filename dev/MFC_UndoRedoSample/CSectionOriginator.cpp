#include "pch.h"
#include "CSectionOriginator.h"

CSectionOriginator* CSectionOriginator::Instance;

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
	: m_Target(nullptr)
{}

/**
 *	Mementoの反映先を設定する。
 */
void CSectionOriginator::InitInstance(CArray<CSection*>* Target)
{
	CSectionOriginator* Instance = GetInstance();
	Instance->m_Target = Target;
}

/**
 *	Mementoを作成する。
 *
 *	@param	Mement	状態の反映先
 */
void CSectionOriginator::CreateMement(CArray<CSection*>* Mement)
{
	ASSERT(nullptr != Mement);

	for (INT_PTR Index = 0; Index < Mement->GetCount(); Index++) {
		CSection* MementItem = Mement->GetAt(Index);
		delete MementItem;
		MementItem = nullptr;
	}
	Mement->RemoveAll();

	for (INT_PTR MementoIndex = 0; MementoIndex < this->m_Target->GetCount(); MementoIndex++) {
		CSection* StateItem = this->m_Target->GetAt(MementoIndex);
		CSection* NewItem = new CSection(StateItem);
		Mement->Add(NewItem);
	}
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