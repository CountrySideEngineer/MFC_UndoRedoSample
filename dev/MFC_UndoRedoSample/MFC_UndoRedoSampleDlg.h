
// MFC_UndoRedoSampleDlg.h : ヘッダー ファイル
//

#pragma once
#include "CSection.h"
#include "IMyCommand.h"


// CMFCUndoRedoSampleDlg ダイアログ
class CMFCUndoRedoSampleDlg : public CDialogEx
{
// コンストラクション
public:
	CMFCUndoRedoSampleDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_UNDOREDOSAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート
	virtual void UpdateViews(DWORD ExecIndex, IMyCommand* Command, CSection* Section = nullptr);
	virtual void CollectInputData(CSection* DstSection);

// 実装
protected:
	HICON m_hIcon;

	CArray<CSection*>	m_SectionArray;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnChangeSectionData(WPARAM wParam, LPARAM lParam);

	afx_msg void OnChangeSectionData2();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnLbnSelchangeListSectionList();
};
