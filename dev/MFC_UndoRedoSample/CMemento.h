#pragma once
#include "CSection.h"
class CMemento
{
public:
	CMemento();
	~CMemento();

public:
	CArray<CSection*>* GetTarget() { return this->m_Target; }
	VOID SetTarget(CArray<CSection*>* Target) { this->m_Target = Target; }
	CString GetSectionName() const { return this->m_SectionName; }
	VOID SetSectionName(CString SectionName) { this->m_SectionName = SectionName; }
	CString GetSectionManager() const { return this->m_SectionManager; }
	VOID SetSectionManager(CString SectionManager) { this->m_SectionManager = SectionManager; }
	CString GetDescription() const { return this->m_Description; }
	VOID SetDescription(CString Description) { this->m_Description = Description; }

protected:
	CArray<CSection*>* m_Target;
	CString	m_SectionName;
	CString m_SectionManager;
	CString m_Description;
};

