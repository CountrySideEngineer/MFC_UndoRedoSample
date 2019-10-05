#pragma once
#include "CSection.h"
#include "CMemento.h"

class CSectionOriginator
{
public:
	static void InitInstance(CArray<CSection*>* Target, 
		CEdit* SectionNameEdit, 
		CEdit* SectionManagerEdit, 
		CEdit* DescriptionEdit);
	static CSectionOriginator* GetInstance();

	virtual void CreateMement(CArray<CSection*>* Mement);
	virtual CMemento* CreateMemento();
	virtual void SetMement(CArray<CSection*>* Mement);
	virtual void SetMemento(CMemento* Memento);

protected:
	CSectionOriginator();

protected:
	CArray<CSection*>* m_Target;
	CEdit* m_SectionNameEdit;
	CEdit* m_SectionManagerEdit;
	CEdit* m_DescriptionEdit;

	static CSectionOriginator* Instance;
};

