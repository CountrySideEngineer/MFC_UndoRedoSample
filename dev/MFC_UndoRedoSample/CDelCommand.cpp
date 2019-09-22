#include "pch.h"
#include "CDelCommand.h"

/**
 *	�V�K�̕�������ǉ�����B
 *
 *	@param	Index	�V�K�̕�����������ꏊ
 *	@param[in]	SectionArray	�V�K�̕����̒ǉ���
 */
VOID CDelCommand::Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	ASSERT(nullptr != SectionArray);

	if (SectionArray->GetCount() < Index) {
		//�w�肳�ꂽ�ԍ��̗v�f���A�z��ɑ��݂��Ȃ�
		//	���������Ȃ�
	} else {
		CSection* Item = SectionArray->GetAt(Index);
		delete Item;
		Item = nullptr;
		SectionArray->RemoveAt(Index);
	}
}

/**
 *	�V�K�̕����̒ǉ�����蒼��
 *
 *	@param	Index	�V�K�̕������̂�蒼�����s���ꏊ
 *	@param[in]	SectionArray	�V�K�̕����̒ǉ��̂�蒼����
 */
VOID CDelCommand::UnExecute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	ASSERT(nullptr != SectionArray);

	SectionArray->RemoveAt(Index);
}