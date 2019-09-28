#include "pch.h"
#include "CCommandManager.h"

/**
 *	デフォルトコンストラクタ
 */
CMyCommandManager::CMyCommandManager(INT_PTR MaxStack)
	: m_MaxStack(MaxStack)
	, m_StackIndex(0)
{
	this->m_ReDoStack.RemoveAll();
	this->m_UnDoStack.RemoveAll();
}

CMyCommandManager::~CMyCommandManager()
{
	this->RefreshStack();
}

/**
 *	コマンドを実行する。
 *
 *	@param	Command	実行するコマンド
 */
BOOL CMyCommandManager::DoCommand(IMyCommand* Command)
{
	ASSERT(nullptr != Command);

	if (this->m_MaxStack < this->m_CommandStack.GetCount()) {
		return false;
	}
	else {
		Command->Execute();
		this->m_UnDoStack.AddTail(Command);
		this->ClearReDoStack();
		return true;
	}
}

/**
 *	コマンドを実行後の状態にする
 */
VOID CMyCommandManager::UnDo()
{
	if (0 < this->m_UnDoStack.GetCount()) {
		IMyCommand* Command = this->m_UnDoStack.RemoveTail();
		Command->UnDo();
		this->m_ReDoStack.AddTail(Command);
	}
	else {
		//前の状態がない場合には、何もしない。
	}
}

/**
 *	コマンドの実行を元に戻す。
 */
VOID CMyCommandManager::ReDo()
{
	if (0 < this->m_ReDoStack.GetCount()) {
		IMyCommand* Command = this->m_ReDoStack.GetTail();
		Command->ReDo();
		this->m_UnDoStack.AddTail(Command);
	}
	else {
		//実行後の状態がない場合は、何もしない。
	}
}

/**
 *	コマンドの実行履歴をクリアする。
 */
VOID CMyCommandManager::RefreshStack()
{
	this->ClearUnDoStack();
	this->ClearReDoStack();
}

/**
 *	「元に戻す」用のスタックをクリアする。
 */
VOID CMyCommandManager::ClearUnDoStack()
{
	this->ClearStack(this->m_UnDoStack);
}

/**
 *	「進める」用のスタックをクリアする。
 */
VOID CMyCommandManager::ClearReDoStack()
{
	this->ClearStack(this->m_ReDoStack);
}

/**
 *	指定されたスタック(CList)をクリアする。
 */
VOID CMyCommandManager::ClearStack(CList<IMyCommand*>& m_UnDoStack)
{
	POSITION StackPosition = m_UnDoStack.GetHeadPosition();
	for (INT_PTR nIndex = 0; nIndex < m_UnDoStack.GetCount(); nIndex++) {
		IMyCommand* Command = m_UnDoStack.GetAt(StackPosition);
		delete Command;
		Command = NULL;
	}
	m_UnDoStack.RemoveAll();
}