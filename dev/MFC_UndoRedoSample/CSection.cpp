#include "pch.h"
#include "CSection.h"

/**
 *	デフォルトコンストラクタ
 */
CSection::CSection()
	: m_SectionName(CString(_T("新しいセクション")))
	, m_Manager(CString(_T("")))
	, m_Description(CString(_T("")))
{}

/**
 *	引数アリのコンストラクタ
 *
 *	@param	Section	部署名
 *	@param	Manager	部署長名
 *	@param	Description	部署の説明/業務内容
 */
CSection::CSection(CString SectionName, CString Manager, CString Description)
	: m_SectionName(SectionName)
	, m_Manager(Manager)
	, m_Description(Description)
{}

/**
 *	コピーコンストラクタ
 *
 *	@param	Section	コピー元のCSectionオブジェクトへのポインタ
 */
CSection::CSection(const CSection* Section)
{
	ASSERT(NULL != Section);

	this->m_SectionName = Section->m_SectionName;
	this->m_Manager = Section->m_Manager;
	this->m_Description = Section->m_Description;
}

/**
 *	コピーコンストラクタ
 *
 *	@param	Section	コピー元への参照
 */
CSection::CSection(const CSection& Section)
{
	this->m_SectionName = Section.m_SectionName;
	this->m_Manager = Section.m_Manager;
	this->m_Description = Section.m_Description;
}