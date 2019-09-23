#include "pch.h"
#include "CCommandManager.h"

/**
 *	デフォルトコンストラクタ
 */
CMyCommandManager::CMyCommandManager(INT_PTR MaxStack)
	: m_MaxStack(MaxStack)
	, m_StackIndex(0)
{}

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

		this->m_CommandStack.Add(Command);

		m_StackIndex++;
		return true;
	}
}

/**
 *	コマンドを実行後の状態にする
 */
VOID CMyCommandManager::UnDo()
{
	if (0 == this->m_CommandStack.GetCount()) {
		return;
	}
	else {
		--(this->m_StackIndex);
		if (this->m_StackIndex < 0) {
			this->m_StackIndex = 0;
		}
		else {
			IMyCommand* Command = this->m_CommandStack.GetAt(m_StackIndex);
			Command->UnExecute();
		}
	}
}

/**
 *	コマンドの実行を元に戻す。
 */
VOID CMyCommandManager::ReDo()
{
	if (0 == this->m_CommandStack.GetCount()) {
		return;
	}
	else {
		IMyCommand* Command = this->m_CommandStack.GetAt(m_StackIndex);
		Command->Execute();

		m_StackIndex++;
	}
}

/**
 *	コマンドの実行履歴をクリアする。
 */
VOID CMyCommandManager::RefreshStack()
{
	for (INT_PTR Index = 0; Index < m_CommandStack.GetCount(); Index++) {
		IMyCommand* CommandItem = m_CommandStack.GetAt(Index);
		delete CommandItem;
		CommandItem = nullptr;
	}
	m_CommandStack.RemoveAll();

	this->m_StackIndex = 0;
}