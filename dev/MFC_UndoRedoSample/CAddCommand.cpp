#include "pch.h"
#include "CSection.h"
#include "CAddCommand.h"
#include "CSectionOriginator.h"

/**
 *	�V�K�̕�������ǉ�����B
 *
 *	@param	Index	�V�K�̕�����������ꏊ
 *	@param[in]	SectionArray	�V�K�̕����̒ǉ���
 */
VOID CAddCommand::Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	ASSERT(nullptr != SectionArray);

	//���s�O�̏󋵂��m��
	SectionArray->InsertAt(Index, Section);
}
