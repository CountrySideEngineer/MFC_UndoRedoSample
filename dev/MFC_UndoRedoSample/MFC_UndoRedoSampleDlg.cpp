
// MFC_UndoRedoSampleDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MFC_UndoRedoSample.h"
#include "MFC_UndoRedoSampleDlg.h"
#include "afxdialogex.h"
#include "IMyCommand.h"
#include "CAddCommand.h"
#include "CDelCommand.h"
#include "CUpdateCommand.h"
#include "CSampleCommand.h"
#include "CCommandManager.h"
#include "CSectionOriginator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define IDM_UPDATE_LIST	(WM_APP + 1)
#define IDC_UPDATE_LIST	(WM_APP + 2)

// CMFCUndoRedoSampleDlg ダイアログ



CMFCUndoRedoSampleDlg::CMFCUndoRedoSampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_UNDOREDOSAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	this->m_CommandManager = new CMyCommandManager(10);

	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	Instance->InitInstance(&this->m_SectionArray);
}

void CMFCUndoRedoSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCUndoRedoSampleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMFCUndoRedoSampleDlg::OnBnClickedButtonAdd)
	ON_MESSAGE(IDM_UPDATE_LIST, &CMFCUndoRedoSampleDlg::OnChangeSectionData)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMFCUndoRedoSampleDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CMFCUndoRedoSampleDlg::OnBnClickedButtonUpdate)
	ON_LBN_SELCHANGE(IDC_LIST_SECTION_LIST, &CMFCUndoRedoSampleDlg::OnLbnSelchangeListSectionList)
	ON_BN_CLICKED(IDC_BUTTON_UNDO, &CMFCUndoRedoSampleDlg::OnBnClickedButtonUndo)
	ON_BN_CLICKED(IDC_BUTTON_REDO, &CMFCUndoRedoSampleDlg::OnBnClickedButtonRedo)
END_MESSAGE_MAP()



// CMFCUndoRedoSampleDlg メッセージ ハンドラー

BOOL CMFCUndoRedoSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。


	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMFCUndoRedoSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMFCUndoRedoSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/**
 *	[追加]ボタンのイベントハンドラ
 */
void CMFCUndoRedoSampleDlg::OnBnClickedButtonAdd()
{
	CListBox* ListBox = (CListBox*)GetDlgItem(IDC_LIST_SECTION_LIST);
	INT_PTR CurIndex = ListBox->GetCurSel();
	if (CurIndex < 0) {
		CurIndex = 0;
	}
	
	CSection* NewSection = new CSection();
	this->CollectInputData(NewSection);
	IMyCommand* Command = new CAddCommand();
	Command->PrepCommand(CurIndex, &this->m_SectionArray, NewSection);
	this->CommandExecute(Command);
}

/**
 *	[削除]ボタンのイベントハンドラ
 */
void CMFCUndoRedoSampleDlg::OnBnClickedButtonDelete()
{
	CListBox* ListBox = (CListBox*)GetDlgItem(IDC_LIST_SECTION_LIST);
	INT_PTR CurIndex = ListBox->GetCurSel();
	if (CurIndex < 0) {
		CurIndex = 0;
	}

	IMyCommand* Command = new CDelCommand();
	Command->PrepCommand(CurIndex, &this->m_SectionArray);
	this->CommandExecute(Command);

	//選択されたアイテムの更新確認
	if (CurIndex < this->m_SectionArray.GetCount()) {
		ListBox->SetCurSel(CurIndex);
	}
	else {
		INT_PTR IndexToSet = this->m_SectionArray.GetCount() - 1;
		ListBox->SetCurSel(IndexToSet);
	}

	this->OnLbnSelchangeListSectionList();
}

/**
 *	部署一覧のリストの表を更新する
 */
LRESULT CMFCUndoRedoSampleDlg::OnChangeSectionData(WPARAM wParam, LPARAM lParam)
{
	CListBox* ListBox = (CListBox*)GetDlgItem(IDC_LIST_SECTION_LIST);
	int ItemCount = ListBox->GetCount();
	while (0 < ListBox->GetCount()) {
		ListBox->DeleteString(0);
	}

	CArray<CSection*>* SectionArray = (CArray<CSection*>*)wParam;
	for (INT_PTR Index = 0; Index < SectionArray->GetCount(); Index++) {
		CSection* SectionItem = SectionArray->GetAt(Index);
		ListBox->AddString(SectionItem->GetSectionName());
	}

	return 0;
}

/**
 *	[更新]ボタンのイベントハンドラ
 */
void CMFCUndoRedoSampleDlg::OnBnClickedButtonUpdate()
{
	CListBox* ListBox = (CListBox*)GetDlgItem(IDC_LIST_SECTION_LIST);
	INT_PTR CurIndex = ListBox->GetCurSel();
	if (CurIndex < 0) {
		CurIndex = 0;
	}
	
	CSection* UpdateSection = new CSection();
	this->CollectInputData(UpdateSection);
	IMyCommand* Command = new CUpdateCommand();
	Command->PrepCommand(CurIndex, &this->m_SectionArray, UpdateSection);
	CommandExecute(Command);
}

/**
 *	コマンド実行
 */
void CMFCUndoRedoSampleDlg::CommandExecute(IMyCommand* Command)
{
	ASSERT(nullptr != Command);

	this->m_CommandManager->DoCommand(Command);

	//コマンド実行後は、実行結果を表示に反映する。
	SendMessage(IDM_UPDATE_LIST, (WPARAM)(&this->m_SectionArray));
}

void CMFCUndoRedoSampleDlg::CollectInputData(CSection* DstSection)
{
	ASSERT(nullptr != DstSection);

	CEdit* SectionNameEdit = (CEdit*)GetDlgItem(IDC_EDIT_SECTION_NAME);
	CEdit* ManagerNameEdit = (CEdit*)GetDlgItem(IDC_EDIT_SECTION_MANAGER_NAME);
	CEdit* DescriptionEdit = (CEdit*)GetDlgItem(IDC_EDIT_SECTION_WORK);

	CString SectionName;
	SectionNameEdit->GetWindowTextA(SectionName);
	CString ManagerName;
	ManagerNameEdit->GetWindowTextA(ManagerName);
	CString Description;
	DescriptionEdit->GetWindowTextA(Description);

	if (SectionName != CString(_T(""))) {
		DstSection->SetSectionName(SectionName);
	}
	DstSection->SetManager(ManagerName);
	DstSection->SetDescription(Description);
}

void CMFCUndoRedoSampleDlg::OnLbnSelchangeListSectionList()
{
	CListBox* ListBox = (CListBox*)GetDlgItem(IDC_LIST_SECTION_LIST);
	CEdit* SectionNameEdit = (CEdit*)GetDlgItem(IDC_EDIT_SECTION_NAME);
	CEdit* ManagerNameEdit = (CEdit*)GetDlgItem(IDC_EDIT_SECTION_MANAGER_NAME);
	CEdit* DescriptionEdit = (CEdit*)GetDlgItem(IDC_EDIT_SECTION_WORK);

	INT_PTR CurIndex = ListBox->GetCurSel();
	if ((0 == this->m_SectionArray.GetCount()) || (CurIndex < 0)) {
		//リストの内容が空 → 表示内容をクリアする。
		SectionNameEdit->SetWindowTextA(CString(_T("")));
		ManagerNameEdit->SetWindowTextA(CString(_T("")));
		DescriptionEdit->SetWindowTextA(CString(_T("")));

		return;
	}
	else {
		CSection* SelSection = this->m_SectionArray.GetAt(CurIndex);

		SectionNameEdit->SetWindowTextA(SelSection->GetSectionName());
		ManagerNameEdit->SetWindowTextA(SelSection->GetManager());
		DescriptionEdit->SetWindowTextA(SelSection->GetDescription());
	}
}

void CMFCUndoRedoSampleDlg::OnBnClickedButtonUndo()
{
	this->m_CommandManager->UnDo();
	SendMessage(IDM_UPDATE_LIST, (WPARAM)(&this->m_SectionArray));
}

void CMFCUndoRedoSampleDlg::OnBnClickedButtonRedo()
{
	this->m_CommandManager->ReDo();
	SendMessage(IDM_UPDATE_LIST, (WPARAM)(&this->m_SectionArray));
}
