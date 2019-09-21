
// MFC_UndoRedoSample.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMFCUndoRedoSampleApp:
// このクラスの実装については、MFC_UndoRedoSample.cpp を参照してください
//

class CMFCUndoRedoSampleApp : public CWinApp
{
public:
	CMFCUndoRedoSampleApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFCUndoRedoSampleApp theApp;
