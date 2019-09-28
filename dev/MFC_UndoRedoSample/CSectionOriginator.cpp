#include "pch.h"
#include "CSectionOriginator.h"

CSectionOriginator* CSectionOriginator::Instance;

/**
 *	CSectionOriginator�̃C���X�^���X���擾����B
 */
CSectionOriginator* CSectionOriginator::GetInstance()
{
	if (nullptr == Instance) {
		Instance = new CSectionOriginator();
	}
	return Instance;
}

/**
 *	�f�t�H���g�R���X�g���N�^
 */
CSectionOriginator::CSectionOriginator() 
	: m_Target(nullptr)
{}

/**
 *	Memento�̔��f���ݒ肷��B
 */
void CSectionOriginator::InitInstance(CArray<CSection*>* Target)
{
	CSectionOriginator* Instance = GetInstance();
	Instance->m_Target = Target;
}

/**
 *	Memento���쐬����B
 *
 *	@param	Mement	��Ԃ̔��f��
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
 *	Mement�̓��e�𔽉f����B
 *
 *	@param	Mement	���f���������e/��Ԃւ̃|�C���^
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