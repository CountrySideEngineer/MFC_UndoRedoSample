#pragma once
#include "IMyCommand.h"
class CEditSectionCommand :
	public IMyCommand
{
public:
	CEditSectionCommand();
	virtual ~CEditSectionCommand() {}

	virtual VOID PrepCommand(CDialog* EditedDialog);

protected:
	virtual VOID ExecuteCommand();

protected:
	CDialog* m_EditedDialog;
};
