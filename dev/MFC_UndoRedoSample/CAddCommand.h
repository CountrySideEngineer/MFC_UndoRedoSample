#pragma once
#include "IMyCommand.h"
#include "CSection.h"

/**
 *	�ǉ����s���R�}���h�N���X
 */
class CAddCommand :
	public IMyCommand
{
public:
	CAddCommand() {}
	virtual ~CAddCommand() {}
	
	virtual VOID Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr);
};

