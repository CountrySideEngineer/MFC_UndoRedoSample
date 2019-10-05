#include "pch.h"
#include "CSectionOriginator.h"
#include "CMemento.h"

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
	, m_SectionNameEdit(nullptr)
	, m_SectionManagerEdit(nullptr)
	, m_DescriptionEdit(nullptr)
{}

/**
 *	Memento�̔��f���ݒ肷��B
 */
void CSectionOriginator::InitInstance(CArray<CSection*>* Target,
	CEdit* SectionNameEdit,
	CEdit* SectionManagerEdit,
	CEdit* DescriptionEdit)
{
	CSectionOriginator* Instance = GetInstance();
	Instance->m_Target = Target;
	Instance->m_SectionNameEdit = SectionNameEdit;
	Instance->m_SectionManagerEdit = SectionManagerEdit;
	Instance->m_DescriptionEdit = DescriptionEdit;
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

#define	GET_WINDOW_TEXT(EditControl, EditString)					\
	do {															\
		if (NULL != EditControl) {									\
			EditControl->GetWindowText(EditString);					\
		}															\
		else {														\
			EditString = _T("");									\
		}															\
	} while(0)

/**
 *	Memento���쐬����B
 *
 *	@return	���݂̏�Ԃ�ێ������������g
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
	
	CString SectionName = _T("");
	GET_WINDOW_TEXT(this->m_SectionNameEdit, SectionName);

	CString SectionManager = _T("");
	GET_WINDOW_TEXT(this->m_SectionManagerEdit, SectionManager);

	CString Descriptoin = _T("");
	GET_WINDOW_TEXT(this->m_DescriptionEdit, Descriptoin);

	CMemento* Memento = new CMemento();
	Memento->SetTarget(Target);
	Memento->SetSectionName(SectionName);
	Memento->SetSectionManager(SectionManager);
	Memento->SetDescription(Descriptoin);

	return Memento;
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

#define	SET_WINDOW_TEXT(EditControl, EditString)					\
	do {															\
		if (NULL != EditControl) {									\
			EditControl->SetWindowText(EditString);					\
		}															\
	} while(0)

/**
 *	��Ԃ����ɖ߂�
 *
 *	@param[in]	Memento	���ɖ߂�������Ԃ�ێ�����CMemento�I�u�W�F�N�g
 *						�ւ̃|�C���^�B
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

	SET_WINDOW_TEXT(this->m_SectionNameEdit, Memento->GetSectionName());
	SET_WINDOW_TEXT(this->m_SectionManagerEdit, Memento->GetSectionManager());
	SET_WINDOW_TEXT(this->m_DescriptionEdit, Memento->GetDescription());
}