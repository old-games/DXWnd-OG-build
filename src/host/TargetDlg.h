#if !defined(AFX_TARGETDLG_H__683E529D_7282_484C_A403_367A6A90CC57__INCLUDED_)
#define AFX_TARGETDLG_H__683E529D_7282_484C_A403_367A6A90CC57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TargetDlg.h : ヘッダー ファイル
//


/////////////////////////////////////////////////////////////////////////////
// CTargetDlg ダイアログ

class CTargetDlg : public CDialog
{
// コンストラクション
public:
	CTargetDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CTargetDlg)
	enum { IDD = IDD_TARGET };
	CEdit	m_File;
	BOOL	m_HookDI;
	BOOL	m_ModifyMouse;
	BOOL	m_OutTrace;
	BOOL	m_UnNotify;
	CString	m_FilePath;
	BOOL	m_SaveLoad;
	int		m_InitX;
	int		m_InitY;
	int		m_MaxX;
	int		m_MaxY;
	int		m_MinX;
	int		m_MinY;
	BOOL	m_FullScreen;
	BOOL	m_ShowFPS;
	int		m_FPSLimitVal;
	BOOL	m_FPSLimit;
	int		m_ModeNum;
	BOOL	m_HideMouse;
	int		m_SurfaceType;
	BOOL	m_ColourConvert;
	BOOL	m_ExtendedLog;
	BOOL	m_HookDD;
	BOOL	m_UseGDI;
	BOOL	m_CaptureMouse;
	BOOL	m_SetAffinity;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CTargetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CTargetDlg)
	afx_msg void OnOpen();
	virtual BOOL OnInitDialog();
	afx_msg void OnFullscreen();
	afx_msg void OnSelendokModes();
	afx_msg void OnOuttrace();
	afx_msg void OnHookdi();
	afx_msg void OnFpslimit();
	afx_msg void OnHookDD();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    HICON m_hIcon;      // was added manually
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_TARGETDLG_H__683E529D_7282_484C_A403_367A6A90CC57__INCLUDED_)
