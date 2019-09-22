#include "pch.h"
#include "CSection.h"
#include "CAddCommand.h"

/**
 *	�V�K�̕�������ǉ�����B
 *
 *	@param	Index	�V�K�̕�����������ꏊ
 *	@param[in]	SectionArray	�V�K�̕����̒ǉ���
 */
VOID CAddCommand::Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	ASSERT(nullptr != SectionArray);

	SectionArray->InsertAt(Index, Section);
}

/**
 *	�V�K�̕����̒ǉ�����蒼��
 *
 *	@param	Index	�V�K�̕������̂�蒼�����s���ꏊ
 *	@param[in]	SectionArray	�V�K�̕����̒ǉ��̂�蒼����
 */
VOID CAddCommand::UnExecute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	ASSERT(nullptr != SectionArray);

	SectionArray->RemoveAt(Index);
}