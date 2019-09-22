#include "pch.h"
#include "CSection.h"

/**
 *	�f�t�H���g�R���X�g���N�^
 */
CSection::CSection()
	: m_SectionName(CString(_T("�V�����Z�N�V����")))
	, m_Manager(CString(_T("")))
	, m_Description(CString(_T("")))
{}

/**
 *	�����A���̃R���X�g���N�^
 *
 *	@param	Section	������
 *	@param	Manager	��������
 *	@param	Description	�����̐���/�Ɩ����e
 */
CSection::CSection(CString SectionName, CString Manager, CString Description)
	: m_SectionName(SectionName)
	, m_Manager(Manager)
	, m_Description(Description)
{}

/**
 *	�R�s�[�R���X�g���N�^
 *
 *	@param	Section	�R�s�[����CSection�I�u�W�F�N�g�ւ̃|�C���^
 */
CSection::CSection(const CSection* Section)
{
	ASSERT(NULL != Section);

	this->m_SectionName = Section->m_SectionName;
	this->m_Manager = Section->m_Manager;
	this->m_Description = Section->m_Description;
}

/**
 *	�R�s�[�R���X�g���N�^
 *
 *	@param	Section	�R�s�[���ւ̎Q��
 */
CSection::CSection(const CSection& Section)
{
	this->m_SectionName = Section.m_SectionName;
	this->m_Manager = Section.m_Manager;
	this->m_Description = Section.m_Description;
}