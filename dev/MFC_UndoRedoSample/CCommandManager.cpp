#include "pch.h"
#include "CCommandManager.h"

/**
 *	�f�t�H���g�R���X�g���N�^
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
 *	�R�}���h�����s����B
 *
 *	@param	Command	���s����R�}���h
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
 *	�R�}���h�����s��̏�Ԃɂ���
 */
VOID CMyCommandManager::UnDo()
{
	if (0 < this->m_UnDoStack.GetCount()) {
		IMyCommand* Command = this->m_UnDoStack.RemoveTail();
		Command->UnDo();
		this->m_ReDoStack.AddTail(Command);
	}
	else {
		//�O�̏�Ԃ��Ȃ��ꍇ�ɂ́A�������Ȃ��B
	}
}

/**
 *	�R�}���h�̎��s�����ɖ߂��B
 */
VOID CMyCommandManager::ReDo()
{
	if (0 < this->m_ReDoStack.GetCount()) {
		IMyCommand* Command = this->m_ReDoStack.GetTail();
		Command->ReDo();
		this->m_UnDoStack.AddTail(Command);
	}
	else {
		//���s��̏�Ԃ��Ȃ��ꍇ�́A�������Ȃ��B
	}
}

/**
 *	�R�}���h�̎��s�������N���A����B
 */
VOID CMyCommandManager::RefreshStack()
{
	this->ClearUnDoStack();
	this->ClearReDoStack();
}

/**
 *	�u���ɖ߂��v�p�̃X�^�b�N���N���A����B
 */
VOID CMyCommandManager::ClearUnDoStack()
{
	this->ClearStack(this->m_UnDoStack);
}

/**
 *	�u�i�߂�v�p�̃X�^�b�N���N���A����B
 */
VOID CMyCommandManager::ClearReDoStack()
{
	this->ClearStack(this->m_ReDoStack);
}

/**
 *	�w�肳�ꂽ�X�^�b�N(CList)���N���A����B
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