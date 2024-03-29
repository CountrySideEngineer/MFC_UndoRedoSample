﻿
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
#include "CEditSectionCommand.h"

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

	this->m_IsEdited_SectionName = FALSE;
	this->m_IsEdited_SectionManager = FALSE;
	this->m_IsEdited_Description = FALSE;

	this->m_CurSelListBoxIndex = 0;
}

CMFCUndoRedoSampleDlg::~CMFCUndoRedoSampleDlg()
{
	for (INT_PTR Index = 0; Index < this->m_SectionArray.GetCount(); Index++) {
		CSection* SectionItem = this->m_SectionArray.GetAt(Index);
		delete SectionItem;
		SectionItem = NULL;
	}
	this->m_SectionArray.RemoveAll();

	delete this->m_CommandManager;

	CSectionOriginator::Destroy();
}

void CMFCUndoRedoSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SECTION_NAME, this->m_SectionNameEditText);
	DDX_Text(pDX, IDC_EDIT_SECTION_MANAGER_NAME, this->m_SectionManagerEditText);
	DDX_Text(pDX, IDC_EDIT_SECTION_WORK, this->m_DescriptionEditText);
	DDX_Control(pDX, IDC_LIST_SECTION_LIST, m_SectionNameListBox);
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
	ON_EN_CHANGE(IDC_EDIT_SECTION_NAME, &CMFCUndoRedoSampleDlg::OnEnChangeEdit_SectionName)
	ON_EN_CHANGE(IDC_EDIT_SECTION_MANAGER_NAME, &CMFCUndoRedoSampleDlg::OnEnChangeEdit_SectionManager)
	ON_EN_CHANGE(IDC_EDIT_SECTION_WORK, &CMFCUndoRedoSampleDlg::OnEnChangeEdit_Description)
	ON_EN_KILLFOCUS(IDC_EDIT_SECTION_NAME, &CMFCUndoRedoSampleDlg::OnEnKillfocusEdit_SectionName)
	ON_EN_KILLFOCUS(IDC_EDIT_SECTION_MANAGER_NAME, &CMFCUndoRedoSampleDlg::OnEnKillfocusEdit_SectionManager)
	ON_EN_KILLFOCUS(IDC_EDIT_SECTION_WORK, &CMFCUndoRedoSampleDlg::OnEnKillfocusEdit_Description)
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
	CEdit* SectionNameEdit = (CEdit*)GetDlgItem(IDC_EDIT_SECTION_NAME);
	CEdit* SectionManagerEdit = (CEdit*)GetDlgItem(IDC_EDIT_SECTION_MANAGER_NAME);
	CEdit* SectionWorkEdit = (CEdit*)GetDlgItem(IDC_EDIT_SECTION_WORK);
	CSectionOriginator* Instance = CSectionOriginator::GetInstance();
	Instance->InitInstance(this,
		&(this->m_SectionArray), 
		&(this->m_SectionNameEditText),
		&(this->m_SectionManagerEditText), 
		&(this->m_DescriptionEditText));

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
	INT_PTR CurIndex = this->m_SectionNameListBox.GetCurSel();
	if (CurIndex < 0) {
		CurIndex = 0;
	}
	
	this->UpdateData();	//コントロールの内容を、DDX変数に反映

	//入力済みデータを集めて、確保した領域に反映する。
	CSection* NewSection = new CSection();
	this->CollectInputData(NewSection);
	CAddCommand* Command = new CAddCommand();
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

	CDelCommand* Command = new CDelCommand();
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
	this->UpdateData();	//入力データを、DDX変数に反映。

	CListBox* ListBox = (CListBox*)GetDlgItem(IDC_LIST_SECTION_LIST);
	INT_PTR CurIndex = this->m_SectionNameListBox.GetCurSel();
	if (CurIndex < 0) {
		CurIndex = 0;
	}

	CSection* UpdateSection = new CSection();
	this->CollectInputData(UpdateSection);
	CUpdateCommand* Command = new CUpdateCommand();
	Command->PrepCommand(CurIndex, &(this->m_SectionArray), UpdateSection);
	this->CommandExecute(Command);
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

/**
 *	入力されたデータ(DDX反映済み)を集めて、引数で指定された領域にセットする。
 *
 *	@param[out]	DstSection	データの反映先へのポインタ
 */
void CMFCUndoRedoSampleDlg::CollectInputData(CSection* DstSection)
{
	ASSERT(nullptr != DstSection);

	DstSection->SetSectionName(this->m_SectionNameEditText);
	DstSection->SetManager(this->m_SectionManagerEditText);
	DstSection->SetDescription(this->m_DescriptionEditText);
}

/**
 *	部署名一覧リストのビュー(CListBox)において、選択されたアイテムが変更された場合の
 *	コールバック関数。
 */
void CMFCUndoRedoSampleDlg::OnLbnSelchangeListSectionList()
{
	this->UpdateData();	//リストコントロールの内容を、メンバ変数に反映

	this->m_CurSelListBoxIndex = this->m_SectionNameListBox.GetCurSel();	//ここから編集！
	if (this->m_CurSelListBoxIndex < 0) {
		this->m_CurSelListBoxIndex = 0;
	}

	if ((0 == this->m_SectionArray.GetCount()) || 
		(this->m_CurSelListBoxIndex < 0))
	{
		//リストの内容が空、あるいは不正なアイテムが選択された
		this->m_SectionNameEditText = _T("");
		this->m_SectionManagerEditText = _T("");
		this->m_DescriptionEditText = _T("");
	}
	else {
		CSection* CurSelection = this->m_SectionArray.GetAt(this->m_CurSelListBoxIndex);

		this->m_SectionNameEditText = CurSelection->GetSectionName();
		this->m_SectionManagerEditText = CurSelection->GetManager();
		this->m_DescriptionEditText = CurSelection->GetDescription();
	}
	this->UpdateData(FALSE);
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

/**
 *	セクション名のセルの内容が編集されたことのイベントハンドラ
 */
void CMFCUndoRedoSampleDlg::OnEnChangeEdit_SectionName()
{
	this->m_IsEdited_SectionName = TRUE;
}

/**
 *	管理者名のセルの内容が編集されたことのイベントハンドラ
 */
void CMFCUndoRedoSampleDlg::OnEnChangeEdit_SectionManager()
{
	this->m_IsEdited_SectionManager = TRUE;
}

/**
 *	業務内容のセルの内容が編集されたことのイベントハンドラ
 */
void CMFCUndoRedoSampleDlg::OnEnChangeEdit_Description()
{
	this->m_IsEdited_Description = TRUE;
}

/**
 *	CEditセルからフォーカスが外れたことのイベントハンドラ
 */
void CMFCUndoRedoSampleDlg::OnEnKillfocusEdit_SectionName()
{
	this->OnEnKillfocusEdit(this->m_IsEdited_SectionName);
}

void CMFCUndoRedoSampleDlg::OnEnKillfocusEdit_SectionManager()
{
	this->OnEnKillfocusEdit(this->m_IsEdited_SectionManager);
}

void CMFCUndoRedoSampleDlg::OnEnKillfocusEdit_Description()
{
	this->OnEnKillfocusEdit(this->m_IsEdited_Description);
}

void CMFCUndoRedoSampleDlg::OnEnKillfocusEdit(BOOL& IsEdited)
{
	if (IsEdited) {
		CEditSectionCommand* Command = new CEditSectionCommand();
		Command->PrepCommand(this);
		this->CommandExecute(Command);
	}
	else {
		//対象が未編集の場合には、何もしない。
	}
	IsEdited = FALSE;	//状態を「編集完了」/「未編集」にする。

}