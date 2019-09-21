#pragma once

/**
 *	Class of section, for example, in company.
 *	@author	CountrySideEngineer.
 *	@version	0.0.1
 */
class CSection
{
public:
	CSection();
	CSection(CString SectionName, CString Manager, CString Description);
	CSection(const CSection* Section);
	CSection(const CSection& Section);
	virtual ~CSection() {}

public:	//Getter/Setter
	CString	GetSectionName() const { return this->m_SectionName; }
	VOID SetSectionName(CString SectionName) { this->m_SectionName = SectionName; }
	CString GetManager() const { return this->m_Manager; }
	VOID SetManager(CString Manager) { this->m_Manager = Manager; }
	CString GetDescription() const { return this->m_Description; }
	VOID SetDescription(CString Description) { this->m_Description = Description; }

protected:
	CString m_SectionName;	//•”–¼
	CString	m_Manager;	//•”’·–¼
	CString m_Description;	//‹Æ–±“à—e

};

