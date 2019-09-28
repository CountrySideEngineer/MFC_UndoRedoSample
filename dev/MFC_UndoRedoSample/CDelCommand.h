#pragma once
#include "IMyCommand.h"
#include "CSection.h"

class CDelCommand :
	public IMyCommand
{
public:
	CDelCommand() {}
	~CDelCommand() {}

	virtual VOID Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr);
};

