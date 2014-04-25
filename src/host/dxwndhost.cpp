// dxwndhost.cpp : �A�v���P�[�V�����p�N���X�̋@�\��`���s���܂��B
//

#include "stdafx.h"
#include "dxwndhost.h"

#include "MainFrm.h"
#include "dxwndhostDoc.h"
#include "dxwndhostView.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDxwndhostApp

BEGIN_MESSAGE_MAP(CDxwndhostApp, CWinApp)
	//{{AFX_MSG_MAP(CDxwndhostApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDxwndhostApp �N���X�̍\�z

CDxwndhostApp::CDxwndhostApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CDxwndhostApp �I�u�W�F�N�g

CDxwndhostApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDxwndhostApp �N���X�̏�����

BOOL CDxwndhostApp::InitInstance()
{
	AfxEnableControlContainer();

	// �W���I�ȏ���������

#ifdef _AFXDLL
	Enable3dControls();		// ���L DLL �̒��� MFC ���g�p����ꍇ�ɂ͂������Ăяo���Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N���Ă���ꍇ�ɂ͂������Ăяo���Ă��������B
#endif

	// �h�L�������g �e���v���[�g��o�^���܂��B

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDxwndhostDoc),
		RUNTIME_CLASS(CMainFrame),       // ���C�� SDI �t���[�� �E�B���h�E
		RUNTIME_CLASS(CDxwndhostView));
	AddDocTemplate(pDocTemplate);

	
	// DDE�Afile open �ȂǕW���̃V�F�� �R�}���h�̃R�}���h���C������͂��܂��B
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// �R�}���h���C���Ńf�B�X�p�b�` �R�}���h���w�肵�܂��B
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	m_pMainWnd->SetWindowText("DXWnd (OG build)");
	RECT rect;
	m_pMainWnd->GetWindowRect(&rect);
	rect.right = rect.left + 320;
	rect.bottom = rect.top + 200;
	//m_pMainWnd->MoveWindow(&rect, TRUE);
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CDxwndhostApp ���b�Z�[�W �n���h��

void CDxwndhostApp::OnAppAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();	
}
