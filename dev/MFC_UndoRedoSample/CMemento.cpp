#include "pch.h"
#include "CMemento.h"

CMemento::CMemento()
	: m_Target(nullptr)
	, m_SectionName(_T(""))
	, m_SectionManager(_T(""))
	, m_Description(_T(""))
{}

CMemento::~CMemento()
{
	if (nullptr != this->m_Target) {
		for (INT_PTR Index = 0; Index < this->m_Target->GetCount(); Index++) {
			CSection* TargetItem = this->m_Target->GetAt(Index);
			delete TargetItem;
			TargetItem = NULL;
		}
		this->m_Target->RemoveAll();
		delete this->m_Target;
	}
}