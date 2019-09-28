#include "pch.h"
#include "CSampleCommand.h"

CSampleCommand::CSampleCommand(INT_PTR Count)
	: m_Count(Count)
{}

VOID CSampleCommand::Execute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	TRACE("Execute Command - %5d\r\n", this->m_Count);
}

VOID CSampleCommand::UnExecute(INT_PTR Index, CArray<CSection*>* SectionArray, CSection* Section)
{
	TRACE("UnExecute Command - %5d\r\n", this->m_Count);
}
