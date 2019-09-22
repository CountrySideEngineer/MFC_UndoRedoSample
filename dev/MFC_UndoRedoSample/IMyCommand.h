#pragma once
#include "CSection.h"

/**
 *	コマンドクラスのインターフェース
 */
class IMyCommand
{
public:
	virtual VOID Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr) = 0;
	virtual VOID UnExecute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr) = 0;
};
