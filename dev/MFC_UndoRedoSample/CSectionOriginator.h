#pragma once
#include "CSection.h"

class CSectionOriginator
{
public:
	static void InitInstance(CArray<CSection*>* Target);
	static CSectionOriginator* GetInstance();

	virtual void CreateMement(CArray<CSection*>* Mement);
	virtual void SetMement(CArray<CSection*>* Mement);

protected:
	CSectionOriginator();

protected:
	CArray<CSection*>* m_Target;

	static CSectionOriginator* Instance;
};

