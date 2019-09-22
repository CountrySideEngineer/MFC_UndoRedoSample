#pragma once
#include "CSection.h"

/**
 *	�R�}���h�N���X�̃C���^�[�t�F�[�X
 */
class IMyCommand
{
public:
	virtual VOID Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr) = 0;
	virtual VOID UnExecute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section = nullptr) = 0;
};
