
// MFC_UndoRedoSampleDlg.h : ヘッダー ファイル
//

#pragma once
#include "CSection.h"
#include "IMyCommand.h"
#include "CCommandManager.h"


// CMFCUndoRedoSampleDlg ダイアログ
class CMFCUndoRedoSampleDlg : public CDialogEx
{
// コンストラクション
public:
	CMFCUndoRedoSampleDlg(CWnd* pParent = nullptr);	// 標準コンストラクター
	virtual ~CMFCUndoRedoSampleDlg();	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_UNDOREDOSAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート
	virtual void CommandExecute(IMyCommand* Command);
	virtual void CollectInputData(CSection* DstSection);

// 実装
protected:
	HICON m_hIcon;

	CArray<CSection*>	m_SectionArray;
	CMyCommandManager* m_CommandManager;

	BOOL m_IsEdited;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnChangeSectionData(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnLbnSelchangeListSectionList();
	afx_msg void OnBnClickedButtonUndo();
	afx_msg void OnBnClickedButtonRedo();
	afx_msg void OnEnChangeEdit();
	afx_msg void OnEnKillfocusEdit();
};
