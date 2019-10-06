#pragma once
#include "CSection.h"
#include "CMemento.h"

class CSectionOriginator
{
public:
	static void InitInstance(CDialog* DestDialog,
		CArray<CSection*>* Target, 
		CString* SectionName,
		CString* SectionManager,
		CString* Description);
	static CSectionOriginator* GetInstance();

	virtual CMemento* CreateMemento();
	virtual void SetMement(CArray<CSection*>* Mement);
	virtual void SetMemento(CMemento* Memento);

protected:
	CSectionOriginator();

protected:
	CDialog* m_DestDialog;
	CArray<CSection*>* m_Target;
	CString* m_SectionNameDdx;
	CString* m_SectionManagerDdx;
	CString* m_DescriptionDdx;

	static CSectionOriginator* Instance;
};

