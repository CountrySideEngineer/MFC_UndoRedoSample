#pragma once
#include "IMyCommand.h"

class CMyCommandManager
{
public:
	CMyCommandManager(INT_PTR MaxStack);
	virtual ~CMyCommandManager();

	virtual BOOL DoCommand(IMyCommand* Command);
	virtual VOID UnDo();
	virtual VOID ReDo();

protected:
	virtual VOID RefreshStack();
	virtual VOID ClearUnDoStack();
	virtual VOID ClearReDoStack();
	virtual VOID ClearStack(CList<IMyCommand*>& m_UnDoStack);

protected:
	INT_PTR m_MaxStack;
	INT_PTR m_StackIndex;

	CArray<IMyCommand*> m_CommandStack;
	CList<IMyCommand*> m_UnDoStack;
	CList<IMyCommand*> m_ReDoStack;
};
