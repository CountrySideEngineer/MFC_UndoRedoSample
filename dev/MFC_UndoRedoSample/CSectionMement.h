#pragma once
#include "afxtempl.h"
#include "CSection.h"
#include "CMement.h"

class CSectionMement : CMement<CArray<CSection*>>
{
public:
	CSectionMement(CArray<CSection*>* Memento);
	virtual ~CSectionMement() {}

	CArray<CSection*>* GetState() const { return (CArray<CSection*>*)(&(this->m_Memento)); }
	void SetState(CArray<CSection*>* Memento) {}

protected:
	CArray<CSection*> m_Memento;
};
