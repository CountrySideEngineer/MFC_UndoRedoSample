#include "pch.h"
#include "CUpdateCommand.h"

VOID CUpdateCommand::Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	ASSERT(nullptr != SectionArray);
	ASSERT(nullptr != Section);

	if (0 == SectionArray->GetCount()) {
		//�z��Ƀf�[�^�����݂��Ȃ��ꍇ�ɂ́A����(�擪)�Ƀf�[�^��ǉ�����B
		SectionArray->Add(Section);
	}
	else {
		if (SectionArray->GetCount() < Index) {
			//�w�肳�ꂽ�C���f�b�N�X���͈͊O�̏ꍇ�ɂ́A
			//�����܂łɋ󔒂𖄂߂A�f�[�^��ǉ�����B
			SectionArray->InsertAt(Index, Section);
		}
		else {
			//�����Ŏw�肳�ꂽ�f�[�^�����݂����ꍇ�̂݁A
			//�f�[�^���X�V����B
			CSection* SectionItem = SectionArray->GetAt(Index);
			delete SectionItem;
			SectionItem = nullptr;
			SectionArray->SetAt(Index, Section);
		}
	}
}

VOID CUpdateCommand::UnExecute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{

}