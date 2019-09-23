#pragma once
#include "IMyCommand.h"
#include "CSection.h"

/**
 *	追加を行うコマンドクラス
 */
class CAddCommand :
	public IMyCommand
{
public:
	CAddCommand() {}
	virtual ~CAddCommand() {}
	
	virtual VOID Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr);
};

