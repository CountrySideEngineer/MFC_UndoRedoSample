#pragma once
#include "IMyCommand.h"

class CMyCommandManager
{
public:
	CMyCommandManager(INT_PTR MaxStack);

	virtual BOOL DoCommand(IMyCommand* Command);
	virtual VOID UnDo();
	virtual VOID ReDo();

protected:
	virtual VOID RefreshStack();

protected:
	INT_PTR m_MaxStack;
	INT_PTR m_StackIndex;

	CArray<IMyCommand*> m_CommandStack;
};
