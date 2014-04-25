// dxwndhost.h : DXWNDHOST アプリケーションのメイン ヘッダー ファイル
//

#if !defined(AFX_DXWNDHOST_H__C68B92A2_C45F_4B59_986D_5BBC6BAD3AD8__INCLUDED_)
#define AFX_DXWNDHOST_H__C68B92A2_C45F_4B59_986D_5BBC6BAD3AD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CDxwndhostApp:
// このクラスの動作の定義に関しては dxwndhost.cpp ファイルを参照してください。
//

class CDxwndhostApp : public CWinApp
{
public:
	CDxwndhostApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDxwndhostApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
	//{{AFX_MSG(CDxwndhostApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DXWNDHOST_H__C68B92A2_C45F_4B59_986D_5BBC6BAD3AD8__INCLUDED_)
