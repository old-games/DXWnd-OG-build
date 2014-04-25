; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTargetDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dxwndhost.h"
LastPage=0

ClassCount=6
Class1=CDxwndhostApp
Class2=CTargetDlg
Class3=CDxwndhostDoc
Class4=CDxwndhostView
Class5=CMainFrame

ResourceCount=8
Resource1=IDR_MAINFRAME (English (U.K.))
Resource2=IDD_ABOUTBOX (English (U.K.))
Resource3=IDR_MENU_POPUP (English (U.K.))
Resource4=IDD_TARGET (English (U.K.))
Resource5=IDD_ABOUTBOX
Resource6=IDR_MENU_POPUP
Resource7=IDR_MAINFRAME
Class6=CAboutDlg
Resource8=IDD_TARGET

[CLS:CDxwndhostApp]
Type=0
BaseClass=CWinApp
HeaderFile=dxwndhost.h
ImplementationFile=dxwndhost.cpp
LastObject=ID_APP_ABOUT
Filter=N
VirtualFilter=AC

[CLS:CDxwndhostDoc]
Type=0
BaseClass=CDocument
HeaderFile=dxwndhostDoc.h
ImplementationFile=dxwndhostDoc.cpp
LastObject=CDxwndhostDoc

[CLS:CDxwndhostView]
Type=0
BaseClass=CListView
HeaderFile=dxwndhostView.h
ImplementationFile=dxwndhostView.cpp
LastObject=CDxwndhostView
Filter=C
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CTargetDlg]
Type=0
BaseClass=CDialog
HeaderFile=TargetDlg.h
ImplementationFile=TargetDlg.cpp
Filter=W
VirtualFilter=dWC
LastObject=IDC_SETAFFINITY

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_VERSION,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342177283
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_TARGET]
Type=1
Class=CTargetDlg
ControlCount=42
Control1=IDC_FILE,edit,1350631552
Control2=IDC_OPEN,button,1342242816
Control3=IDC_UNNOTIFY,button,1342242819
Control4=IDC_HOOKDI,button,1342242819
Control5=IDC_INITX,edit,1350639744
Control6=IDC_INITY,edit,1350639744
Control7=IDC_MINX,edit,1350631552
Control8=IDC_MINY,edit,1350631552
Control9=IDC_MAXX,edit,1350631552
Control10=IDC_MAXY,edit,1350631552
Control11=IDC_MODIFYMOUSE,button,1342242819
Control12=IDC_OUTTRACE,button,1342242819
Control13=IDC_SAVELOAD,button,1342242819
Control14=IDOK,button,1342242817
Control15=IDCANCEL,button,1342242816
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308363
Control18=IDC_STATIC,static,1342308363
Control19=IDC_STATIC,static,1342308363
Control20=IDC_STATIC,static,1342308363
Control21=IDC_STATIC,static,1342308363
Control22=IDC_STATIC,static,1342308363
Control23=IDC_STATIC,static,1342308363
Control24=IDC_FULLSCREEN,button,1342242819
Control25=IDC_SHOWFPS,button,1342242819
Control26=IDC_FPSLIMITVAL,edit,1350631554
Control27=IDC_FPSLIMIT,button,1342242819
Control28=IDC_MODES,combobox,1344339971
Control29=IDC_HIDEMOUSE,button,1342242819
Control30=IDC_SURFACETYPE,combobox,1344339971
Control31=IDC_COLCONVERT,button,1342242819
Control32=IDC_STATIC,button,1342177287
Control33=IDC_STATIC,button,1342177287
Control34=IDC_EXTDEBUG,button,1342242819
Control35=IDC_STATIC,button,1342177287
Control36=IDC_STATIC,static,1342308352
Control37=IDC_HOOKDD,button,1342242819
Control38=IDC_STATIC,button,1342177287
Control39=IDC_USEGDI,button,1342242819
Control40=IDC_CAPTUREMOUSE,button,1342242819
Control41=IDC_STATIC,static,1342308352
Control42=IDC_SETAFFINITY,button,1342242819

[MNU:IDR_MENU_POPUP (English (U.K.))]
Type=1
Class=?
Command1=ID_PRUN
Command2=ID_PMODIFY
Command3=ID_PDELETE
Command4=ID_PADD
CommandCount=4

[MNU:IDR_MAINFRAME (English (U.K.))]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_RUN
Command3=ID_MODIFY
Command4=ID_DELETE
Command5=ID_ADD
Command6=ID_APP_ABOUT
CommandCount=6

[DLG:IDD_ABOUTBOX (English (U.K.))]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_VERSION,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342177283
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_TARGET (English (U.K.))]
Type=1
Class=CTargetDlg
ControlCount=43
Control1=IDC_FILE,edit,1350631552
Control2=IDC_OPEN,button,1342242816
Control3=IDC_AUTO,button,1342308361
Control4=IDC_DIRECTX1,button,1342177289
Control5=IDC_DIRECTX7,button,1342177289
Control6=IDC_DIRECTX8,button,1342177289
Control7=IDC_DIRECTX9,button,1342177289
Control8=IDC_UNNOTIFY,button,1342242819
Control9=IDC_EMULATEPAL,button,1342242819
Control10=IDC_HOOKDI,button,1342242819
Control11=IDC_INITX,edit,1350639744
Control12=IDC_INITY,edit,1350639744
Control13=IDC_MINX,edit,1350631552
Control14=IDC_MINY,edit,1350631552
Control15=IDC_MAXX,edit,1350631552
Control16=IDC_MAXY,edit,1350631552
Control17=IDC_MODIFYMOUSE,button,1342242819
Control18=IDC_OUTTRACE,button,1342242819
Control19=IDC_SAVELOAD,button,1342242819
Control20=IDOK,button,1342242817
Control21=IDCANCEL,button,1342242816
Control22=IDC_STATIC,button,1342308359
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308363
Control25=IDC_STATIC,static,1342308363
Control26=IDC_STATIC,static,1342308363
Control27=IDC_STATIC,static,1342308363
Control28=IDC_STATIC,static,1342308363
Control29=IDC_STATIC,static,1342308363
Control30=IDC_STATIC,static,1342308363
Control31=IDC_FULLSCREEN,button,1342242819
Control32=IDC_SHOWFPS,button,1342242819
Control33=IDC_FPSLIMITVAL,edit,1350631552
Control34=IDC_FPSLIMIT,button,1342242819
Control35=IDC_USEGDI,button,1342242819
Control36=IDC_MODES,combobox,1344339971
Control37=IDC_STATICRESOLUTION,static,1342308352
Control38=IDC_HIDEMOUSE,button,1342242819
Control39=IDC_OFFSCREEN,button,1342242819
Control40=IDC_SURFACETYPE,combobox,1344339971
Control41=IDC_ASYNCBLT,button,1342242819
Control42=IDC_ASYNCBLTVAL,edit,1350631552
Control43=IDC_FPSHOOK,combobox,1344339971

[ACL:IDR_MAINFRAME (English (U.K.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_RUN
Command3=ID_MODIFY
Command4=ID_DELETE
Command5=ID_ADD
Command6=ID_APP_ABOUT
CommandCount=6

[MNU:IDR_MENU_POPUP]
Type=1
Class=?
Command1=ID_PRUN
Command2=ID_PMODIFY
Command3=ID_PDELETE
Command4=ID_PADD
CommandCount=4

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_NEXT_PANE
Command9=ID_PREV_PANE
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_EDIT_CUT
Command13=ID_EDIT_UNDO
CommandCount=13

[CLS:CAboutDlg]
Type=0
HeaderFile=AboutDlg.h
ImplementationFile=AboutDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAboutDlg
VirtualFilter=dWC

