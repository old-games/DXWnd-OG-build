// TargetDlg.cpp : ÉCÉìÉvÉäÉÅÉìÉeÅ[ÉVÉáÉì ÉtÉ@ÉCÉã
//

#include "stdafx.h"
#include "dxwndhost.h"
#include "TargetDlg.h"
//#include "MainFrm.h"
#include "AboutDlg.h"

#include "..\utils\utils.h"     // g_Modes, g_ModeSel

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CTargetDlg É_ÉCÉAÉçÉO


CTargetDlg::CTargetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTargetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTargetDlg)
	m_HookDI = FALSE;
	m_ModifyMouse = FALSE;
	m_OutTrace = FALSE;
	m_UnNotify = FALSE;
	m_FilePath = _T("");
	m_SaveLoad = FALSE;
	m_InitX = 0;
	m_InitY = 0;
	m_MaxX = 0;
	m_MaxY = 0;
	m_MinX = 0;
	m_MinY = 0;
	m_FullScreen = FALSE;
	m_ShowFPS = FALSE;
	m_FPSLimitVal = 0;
	m_FPSLimit = FALSE;
	m_ModeNum = -1;
	m_HideMouse = FALSE;
	m_SurfaceType = -1;
	m_ColourConvert = FALSE;
	m_ExtendedLog = FALSE;
	m_HookDD = FALSE;
	m_UseGDI = FALSE;
	m_CaptureMouse = FALSE;
	m_SetAffinity = FALSE;
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); // was added manually
}

void CTargetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTargetDlg)
	DDX_Control(pDX, IDC_FILE, m_File);
	DDX_Check(pDX, IDC_HOOKDI, m_HookDI);
	DDX_Check(pDX, IDC_MODIFYMOUSE, m_ModifyMouse);
	DDX_Check(pDX, IDC_OUTTRACE, m_OutTrace);
	DDX_Check(pDX, IDC_UNNOTIFY, m_UnNotify);
	DDX_Text(pDX, IDC_FILE, m_FilePath);
	DDX_Check(pDX, IDC_SAVELOAD, m_SaveLoad);
	DDX_Text(pDX, IDC_INITX, m_InitX);
	DDX_Text(pDX, IDC_INITY, m_InitY);
	DDX_Text(pDX, IDC_MAXX, m_MaxX);
	DDX_Text(pDX, IDC_MAXY, m_MaxY);
	DDX_Text(pDX, IDC_MINX, m_MinX);
	DDX_Text(pDX, IDC_MINY, m_MinY);
	DDX_Check(pDX, IDC_FULLSCREEN, m_FullScreen);
	DDX_Check(pDX, IDC_SHOWFPS, m_ShowFPS);
	DDX_Text(pDX, IDC_FPSLIMITVAL, m_FPSLimitVal);
	DDV_MinMaxInt(pDX, m_FPSLimitVal, 0, 1000000);
	DDX_Check(pDX, IDC_FPSLIMIT, m_FPSLimit);
	DDX_CBIndex(pDX, IDC_MODES, m_ModeNum);
	DDX_Check(pDX, IDC_HIDEMOUSE, m_HideMouse);
	DDX_CBIndex(pDX, IDC_SURFACETYPE, m_SurfaceType);
	DDX_Check(pDX, IDC_COLCONVERT, m_ColourConvert);
	DDX_Check(pDX, IDC_EXTDEBUG, m_ExtendedLog);
	DDX_Check(pDX, IDC_HOOKDD, m_HookDD);
	DDX_Check(pDX, IDC_USEGDI, m_UseGDI);
	DDX_Check(pDX, IDC_CAPTUREMOUSE, m_CaptureMouse);
	DDX_Check(pDX, IDC_SETAFFINITY, m_SetAffinity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTargetDlg, CDialog)
	//{{AFX_MSG_MAP(CTargetDlg)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_FULLSCREEN, OnFullscreen)
	ON_CBN_SELENDOK(IDC_MODES, OnSelendokModes)
	ON_BN_CLICKED(IDC_OUTTRACE, OnOuttrace)
	ON_BN_CLICKED(IDC_HOOKDI, OnHookdi)
	ON_BN_CLICKED(IDC_FPSLIMIT, OnFpslimit)
	ON_BN_CLICKED(IDC_HOOKDD, OnHookDD)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTargetDlg ÉÅÉbÉZÅ[ÉW ÉnÉìÉhÉâ

void CTargetDlg::OnOpen() 
{
	// TODO: Ç-Ç≥à≥íuÇ£ÉRÉìÉgÉçÅ[Éãí≥ímÉnÉìÉhÉâópÇ≥ÉRÅ[ÉhÇí≥â+Ç≥Ç-Ç≠Ç-Ç≥Ç¢
    char path[MAX_PATH];
	m_File.GetWindowText(path, MAX_PATH);
	CFileDialog dlg(TRUE, "*.*", path, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        "Program (*.exe)|*.exe|All Files (*.*)|*.*||", this);
    if(dlg.DoModal() == IDOK) m_File.SetWindowText(dlg.GetPathName());
}


// Is called after OnCreate()
BOOL CTargetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	unsigned int i;

	// TODO: Add extra initialization here

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_STRINGABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


    // Set the icon for this dialog.
	SetIcon(m_hIcon, TRUE);                             // FALSE - Set big icon

    OnFullscreen();
    OnOuttrace();
    OnHookdi();
    OnFpslimit();
    OnHookDD();

    CWnd *combo_wnd;
    combo_wnd = (CComboBox *)GetDlgItem(IDC_MODES);

    // Fill in "Mode" combo box with modes
    for(i = 0; i < g_Modes.dwModeNum; i++)
        ((CComboBox*)combo_wnd)->AddString(LPCTSTR (g_Modes.aModeDesc[i]));

    // set selection
    ((CComboBox*)combo_wnd)->SetCurSel(0);
    for(i = 0; i < g_Modes.dwModeNum; i++)
        if(!strcmpi(g_Modes.aModeDesc[i], g_ModeSel))
            ((CComboBox*)combo_wnd)->SetCurSel(i);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CTargetDlg::OnFullscreen() 
{
	// TODO: Add your control notification handler code here
    CWnd *cap_wnd;
    //combo_wnd = GetDlgItem(IDC_MODES);
	cap_wnd = GetDlgItem(IDC_CAPTUREMOUSE);

    if(IsDlgButtonChecked(IDC_FULLSCREEN)){
        //combo_wnd->EnableWindow(1);
		cap_wnd->EnableWindow(0);
	}
    else{
        //combo_wnd->EnableWindow(0);
		cap_wnd->EnableWindow(1);
	}
}


void CTargetDlg::OnSelendokModes() 
{
	// TODO: Add your control notification handler code here
    CWnd *combo_wnd;
    combo_wnd = GetDlgItem(IDC_MODES);

    // copy selected mode to g_ModeSel
    ((CComboBox*)combo_wnd)->GetLBText(((CComboBox*)combo_wnd)->GetCurSel(), g_ModeSel);
}


/*
void CTargetDlg::OnTestmode() 
{
	// TODO: Add your control notification handler code here
	TestMode();
}
*/


void CTargetDlg::OnOuttrace() 
{
	// TODO: Add your control notification handler code here
	CWnd *ed_ext;
    ed_ext = GetDlgItem(IDC_EXTDEBUG);

    if(IsDlgButtonChecked(IDC_OUTTRACE)){
        ed_ext->EnableWindow(1);
    }
    else{
        ed_ext->EnableWindow(0);
//        ((CButton*)ed_ext)->SetCheck(0);
    }	

}

void CTargetDlg::OnHookdi() 
{
	// TODO: Add your control notification handler code here
    CWnd *w1, *w2, *w3, *w4, *w5, *w6;
    w1 = GetDlgItem(IDC_INITX);
    w2 = GetDlgItem(IDC_INITY);
    w3 = GetDlgItem(IDC_MINX);
    w4 = GetDlgItem(IDC_MINY);
    w5 = GetDlgItem(IDC_MAXX);
    w6 = GetDlgItem(IDC_MAXY);

    if(IsDlgButtonChecked(IDC_HOOKDI)){
        w1->EnableWindow(1);
        w2->EnableWindow(1);
        w3->EnableWindow(1);
        w4->EnableWindow(1);
        w5->EnableWindow(1);
        w6->EnableWindow(1);
    }
    else{
        w1->EnableWindow(0);
        w2->EnableWindow(0);
        w3->EnableWindow(0);
        w4->EnableWindow(0);
        w5->EnableWindow(0);
        w6->EnableWindow(0);
    }	
}

void CTargetDlg::OnFpslimit() 
{
	// TODO: Add your control notification handler code here
    CWnd *w1, *w2;
    w1 = GetDlgItem(IDC_FPSLIMITVAL);
    w2 = GetDlgItem(IDC_SAVELOAD);

    if(IsDlgButtonChecked(IDC_FPSLIMIT)){
        w1->EnableWindow(1);
        w2->EnableWindow(1);
    }
    else{
        w1->EnableWindow(0);
        w2->EnableWindow(0);
    }	
}

void CTargetDlg::OnHookDD() 
{
	// TODO: Add your control notification handler code here
	CWnd *w1, *w2, *w5, *w3, *w6, *w7, *w8, *w9, *w10, *w11, *w12, *w13, *w14,
        *w21, *w22, *w23, *w24, *w25, *w26;

    w1 = GetDlgItem(IDC_COLCONVERT);
    w2 = GetDlgItem(IDC_SURFACETYPE);
    w3 = GetDlgItem(IDC_USEGDI);
    w5 = GetDlgItem(IDC_FULLSCREEN);
    w6 = GetDlgItem(IDC_MODES);
    
    w7 = GetDlgItem(IDC_UNNOTIFY);
    w8 = GetDlgItem(IDC_MODIFYMOUSE);
    w9 = GetDlgItem(IDC_HIDEMOUSE);
    w10 = GetDlgItem(IDC_OUTTRACE);
    w11 = GetDlgItem(IDC_EXTDEBUG);
    w12 = GetDlgItem(IDC_HOOKDI);
    w13 = GetDlgItem(IDC_SHOWFPS);
    w14 = GetDlgItem(IDC_CAPTUREMOUSE);
    
    w21 = GetDlgItem(IDC_INITX);
    w22 = GetDlgItem(IDC_INITY);
    w23 = GetDlgItem(IDC_MINX);
    w24 = GetDlgItem(IDC_MINY);
    w25 = GetDlgItem(IDC_MAXX);
    w26 = GetDlgItem(IDC_MAXY);

    OnFullscreen();
    OnOuttrace();
    OnHookdi();

    if(IsDlgButtonChecked(IDC_HOOKDD)){
        w1->EnableWindow(1);
        w2->EnableWindow(1);
        w3->EnableWindow(1);
        w5->EnableWindow(1);
        w6->EnableWindow(1);
        w7->EnableWindow(1);
        w8->EnableWindow(1);
        w9->EnableWindow(1);
        w10->EnableWindow(1);
        //w11->EnableWindow(1);
        w12->EnableWindow(1);
        w13->EnableWindow(1);
        //w14->EnableWindow(1);
    }
    else{
        w1->EnableWindow(0);
        w2->EnableWindow(0);
        w3->EnableWindow(0);
        w5->EnableWindow(0);
        w6->EnableWindow(0);
        w7->EnableWindow(0);
        w8->EnableWindow(0);
        w9->EnableWindow(0);
        w10->EnableWindow(0);
        w11->EnableWindow(0);
        w12->EnableWindow(0);
        w13->EnableWindow(0);
        w14->EnableWindow(0);

        w21->EnableWindow(0);
        w22->EnableWindow(0);
        w23->EnableWindow(0);
        w24->EnableWindow(0);
        w25->EnableWindow(0);
        w26->EnableWindow(0);
    }	
}

void CTargetDlg::OnOK() 
{
	// TODO: Add extra validation here

	CDialog::OnOK();
    

    strcpy(TargetMaps[CurrTarget].path, m_FilePath);
    TargetMaps[CurrTarget].dxversion = 0; // "Autodetect"
    TargetMaps[CurrTarget].flags = 0;
    if(m_UnNotify) TargetMaps[CurrTarget].flags |= UNNOTIFY;
    if(m_HookDI) TargetMaps[CurrTarget].flags |= HOOKDI;
    if(m_HookDD) TargetMaps[CurrTarget].flags |= HOOKDD;
    if(m_ModifyMouse) TargetMaps[CurrTarget].flags |= MODIFYMOUSE;
    if(m_OutTrace) TargetMaps[CurrTarget].flags |= OUTTRACE;
    if(m_SaveLoad) TargetMaps[CurrTarget].flags |= SAVELOAD;
    if(m_FullScreen) TargetMaps[CurrTarget].flags |= FULLSCREEN;
    if(m_ShowFPS) TargetMaps[CurrTarget].flags |= SHOWFPS;
    if(m_FPSLimit) TargetMaps[CurrTarget].flags |= LIMITFPS;
    if(m_UseGDI) TargetMaps[CurrTarget].flags |= USEGDI;
    if(m_ColourConvert) TargetMaps[CurrTarget].flags |= COLOURCONVERT;
    if(m_ExtendedLog) TargetMaps[CurrTarget].flags |= EXTENDED_LOG;
    if(m_HideMouse) TargetMaps[CurrTarget].flags |= HIDECURSOR;
    if(m_CaptureMouse) TargetMaps[CurrTarget].flags |= CAPTUREMOUSE;
    if(m_SetAffinity) TargetMaps[CurrTarget].flags |= SETAFFINITY;
    if(m_SurfaceType == 0) TargetMaps[CurrTarget].flags |= AUTOMEMORY;
    if(m_SurfaceType == 1) TargetMaps[CurrTarget].flags |= SYSTEMMEMORY;
    if(m_SurfaceType == 2) TargetMaps[CurrTarget].flags |= VIDEOMEMORY;
    TargetMaps[CurrTarget].initx = m_InitX;
    TargetMaps[CurrTarget].inity = m_InitY;
    TargetMaps[CurrTarget].minx = m_MinX;
    TargetMaps[CurrTarget].miny = m_MinY;
    TargetMaps[CurrTarget].maxx = m_MaxX;
    TargetMaps[CurrTarget].maxy = m_MaxY;
    TargetMaps[CurrTarget].FPSLimit = m_FPSLimitVal;
    strcpy(g_ModeSel, g_Modes.aModeDesc[m_ModeNum]);    // save selection in global variable
    strcpy(TargetMaps[CurrTarget].Mode, g_ModeSel);
    


}

// Is called before OnInitDialog()
int CTargetDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if(CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here

	m_FilePath = TargetMaps[CurrTarget].path;
	m_UnNotify = TargetMaps[CurrTarget].flags & UNNOTIFY ? 1 : 0;
	m_HookDI = TargetMaps[CurrTarget].flags & HOOKDI ? 1 : 0;
    m_HookDD = TargetMaps[CurrTarget].flags & HOOKDD ? 1 : 0;
	m_ModifyMouse = TargetMaps[CurrTarget].flags & MODIFYMOUSE ? 1 : 0;
	m_OutTrace = TargetMaps[CurrTarget].flags & OUTTRACE ? 1 : 0;
	m_SaveLoad = TargetMaps[CurrTarget].flags & SAVELOAD ? 1 : 0;
    m_FullScreen = TargetMaps[CurrTarget].flags & FULLSCREEN ? 1 : 0;
    m_ShowFPS = TargetMaps[CurrTarget].flags & SHOWFPS ? 1 : 0;
    m_FPSLimit = TargetMaps[CurrTarget].flags & LIMITFPS ? 1 : 0;
    m_UseGDI = TargetMaps[CurrTarget].flags & USEGDI ? 1 : 0;
    m_ColourConvert = TargetMaps[CurrTarget].flags & COLOURCONVERT ? 1 : 0;
    m_ExtendedLog = TargetMaps[CurrTarget].flags & EXTENDED_LOG ? 1 : 0;
    m_HideMouse = TargetMaps[CurrTarget].flags & HIDECURSOR ? 1 : 0;
    m_CaptureMouse = TargetMaps[CurrTarget].flags & CAPTUREMOUSE ? 1 : 0;
    m_SetAffinity = TargetMaps[CurrTarget].flags & SETAFFINITY ? 1 : 0;
    if(TargetMaps[CurrTarget].flags & AUTOMEMORY)
        m_SurfaceType = 0;
    if(TargetMaps[CurrTarget].flags & SYSTEMMEMORY)
        m_SurfaceType = 1;
    if(TargetMaps[CurrTarget].flags & VIDEOMEMORY)
        m_SurfaceType = 2;
	m_InitX = TargetMaps[CurrTarget].initx;
	m_InitY = TargetMaps[CurrTarget].inity;
	m_MinX = TargetMaps[CurrTarget].minx;
	m_MinY = TargetMaps[CurrTarget].miny;
	m_MaxX = TargetMaps[CurrTarget].maxx;
	m_MaxY = TargetMaps[CurrTarget].maxy;
    m_FPSLimitVal = TargetMaps[CurrTarget].FPSLimit;
    strcpy(g_ModeSel, TargetMaps[CurrTarget].Mode);          // save selection in global variable    

	return 0;
}


// Change "Message Filter" in "Class Info" tab in Class Wizard to see OnSysCommand message
void CTargetDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	if((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	    CAboutDlg aboutDlg;
	    aboutDlg.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}	

}
