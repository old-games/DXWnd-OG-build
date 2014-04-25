// launch.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "shlwapi.h"    // for PathRemoveFileSpec
#include "launch.h"

#include "..\utils\utils.h"
#include "..\host\TargetDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLaunchApp

BEGIN_MESSAGE_MAP(CLaunchApp, CWinApp)
	//{{AFX_MSG_MAP(CLaunchApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLaunchApp construction

CLaunchApp::CLaunchApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLaunchApp object

CLaunchApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLaunchApp initialization

BOOL CLaunchApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


    // Get avialible modes
    EnumModes();

    GetCurrentDirectory(MAX_PATH, InitPath);        // Get/WritePrivateProfileString and dxwnd.dll
    PathAppend(InitPath, "dxwnd.ini");              // adds "\\dxwnd.ini"
    ZeroTargetMaps();
    CurrTarget = 0;                                 // only first slot in TargetMaps is used
    LoadINISlot(CurrTarget);

	CTargetDlg dlg;
	m_pMainWnd = &dlg;

    // see also ParseCommandLine()
    if((!strcmp(m_lpCmdLine, "--configure")) || (TargetMaps[CurrTarget].path[0] == 0)){
        
        int nResponse = dlg.DoModal();
	    if (nResponse == IDOK)
	    {
		    // TODO: Place code here to handle when the dialog is
		    //  dismissed with OK
            PathStripPath(TargetMaps[CurrTarget].path); // save only filename in ini
            WriteINISlot(CurrTarget);
            return FALSE;
	    }
	    else if (nResponse == IDCANCEL)
	    {
		    // TODO: Place code here to handle when the dialog is
		    //  dismissed with Cancel
            return FALSE;
	    }
    }

    STARTUPINFO sinfo;
    PROCESS_INFORMATION pinfo;
    HANDLE hndl;
    char path[MAX_PATH], logfile[MAX_PATH];
    FILE *fp;
    int ret;

    GetCurrentDirectory(MAX_PATH, path);
    PathAppend(path, TargetMaps[CurrTarget].path);
    strcpy(TargetMaps[CurrTarget].path, path);

    // run program
    SetTarget(TargetMaps);
    StartHook();

    ZeroMemory(&sinfo, sizeof(sinfo));
    sinfo.cb = sizeof(sinfo);
    PathRemoveFileSpec(path);                       // removes extension. Required by CreateProcess (?)

    // reset log file
    if(TargetMaps[0].flags & OUTTRACE){
        strcpy(logfile, "dxwnd.log");
        fp = fopen(logfile, "w+");
        fclose(fp);
    }

	if(TargetMaps[0].flags & SETAFFINITY){
        ret = CreateProcess(0, TargetMaps[0].path, 0, 0, 0, CREATE_DEFAULT_ERROR_MODE | CREATE_SUSPENDED, 0, path, &sinfo, &pinfo);
        if(ret){
            hndl = GetModuleHandle(0);
            // 0x1 - 1st core, 0x2 - 2nd core, 0x4 - 3d core, 0x8 - 4th core
            //DWORD ProcessMask, SystemMask;
            //GetProcessAffinityMask(pinfo.hProcess, &ProcessMask, &SystemMask);
		    //fp = fopen(logfile, "w+");
		    //fprintf(fp, "*** HookDirectX: GetProcessAffinityMask: ret = %x hndl = %x ProcessMask = %x SystemMask = %x\n", ret, hndl, ProcessMask, SystemMask);
		    //fclose(fp);
            SetProcessAffinityMask(pinfo.hProcess, 0x1);

            // ResumeThread() is also defined in afxwin.h (member of CWinThread class):
            // "error C2660: 'ResumeThread' : function does not take 1 parameters"
            // Call one from kernel32.dll
            //ResumeThread(pinfo.hThread);
            typedef DWORD (WINAPI *PRESUMETHREAD)(HANDLE hThread);
            PRESUMETHREAD pRT;
            pRT = (PRESUMETHREAD) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "ResumeThread");
            if(pRT)
                pRT(pinfo.hThread);
        }
	}
    else
        ret = CreateProcess(0, TargetMaps[0].path, 0, 0, 0, CREATE_DEFAULT_ERROR_MODE, 0, path, &sinfo, &pinfo);

    if(ret == 0){
        char szerr[255];
        sprintf(szerr, "Error: Cannot start %s", TargetMaps[CurrTarget].path);
        MessageBox(NULL, szerr, "DXWnd Launcher", MB_OK|MB_ICONERROR);
        return FALSE;
    }

    // wait for process to exit
    DWORD ExitCode = STILL_ACTIVE;
    while(ExitCode == STILL_ACTIVE){
        GetExitCodeProcess(pinfo.hProcess, &ExitCode);
        Sleep(500);                                 // 10 ms is enough
    };


    EndHook();    //??


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


