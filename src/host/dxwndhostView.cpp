// dxwndhostView.cpp : CDxwndhostView クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "shlwapi.h"    // for PathRemoveFileSpec - removes file extension

#include "dxwndhost.h"

#include "dxwndhostDoc.h"
#include "dxwndhostView.h"
#include "TargetDlg.h"

#include "..\utils\utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDxwndhostView

IMPLEMENT_DYNCREATE(CDxwndhostView, CListView)

BEGIN_MESSAGE_MAP(CDxwndhostView, CListView)
	//{{AFX_MSG_MAP(CDxwndhostView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_COMMAND(ID_ADD, OnAdd)
	ON_COMMAND(ID_MODIFY, OnModify)
	ON_COMMAND(ID_DELETE, OnDelete)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_RUN, OnRun)
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDxwndhostView クラスの構築/消滅

CDxwndhostView::CDxwndhostView()
{
}

CDxwndhostView::~CDxwndhostView()
{
	int i;
	EndHook();
	for(i = 0; i < MAXTARGETS; i ++){
        if(!TargetMaps[i].path[0]) break;
        WriteINISlot(i);
    }
    for(; i < MAXTARGETS; i ++){    // clear rest of file (don't need this in launch.exe-version)
        ZeroINISlot(i);
	}
}

BOOL CDxwndhostView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT | LVS_SINGLESEL | LVS_NOCOLUMNHEADER;
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDxwndhostView クラスの描画

void CDxwndhostView::OnDraw(CDC* pDC)
{
	CDxwndhostDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CDxwndhostView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	CListCtrl& listctrl = GetListCtrl();
	LV_COLUMN listcol;
	LV_ITEM listitem;
	int i;

	listcol.mask = LVCF_WIDTH;
	listcol.cx = 100;
	
	listctrl.InsertColumn(0, &listcol);
	GetCurrentDirectory(MAX_PATH, InitPath);
	strcat(InitPath, "\\dxwnd.ini");

    ZeroTargetMaps();
	for(i = 0; i < MAXTARGETS; i ++){
        LoadINISlot(i);
		if(!TargetMaps[i].path[0]) break;
        listitem.mask = LVIF_TEXT;
		listitem.iItem = i;
		listitem.iSubItem = 0;
		listitem.pszText = TargetMaps[i].path;
		listctrl.InsertItem(&listitem);
	}
	for(; i < MAXTARGETS; i ++) TargetMaps[i].path[0] = 0;
    Resize();
	SetTarget(TargetMaps);
	StartHook();

    // select first element in list
	listitem.mask = LVIF_STATE;
	listitem.iItem = 0;
    listitem.iSubItem = 0;
	listitem.state = LVIS_FOCUSED | LVIS_SELECTED;
    listitem.stateMask = LVIS_FOCUSED | LVIS_SELECTED;
	listctrl.SetItem(&listitem);

}

/////////////////////////////////////////////////////////////////////////////
// CDxwndhostView クラスの診断

#ifdef _DEBUG
void CDxwndhostView::AssertValid() const
{
	CListView::AssertValid();
}

void CDxwndhostView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CDxwndhostDoc* CDxwndhostView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDxwndhostDoc)));
	return (CDxwndhostDoc*)m_pDocument;
}
#endif //_DEBUG


void CDxwndhostView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRun();
	*pResult = 0;
}

void CDxwndhostView::OnModify() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	int i;
	CTargetDlg dlg;
	POSITION pos;
	LV_ITEM listitem;
	CListCtrl& listctrl = GetListCtrl();

	if(!listctrl.GetSelectedCount()) return;
	pos = listctrl.GetFirstSelectedItemPosition();
	i = listctrl.GetNextSelectedItem(pos);
    CurrTarget = i;                                 // must be set before calling dlg.DoModal()
    if(dlg.DoModal() == IDOK && dlg.m_FilePath.GetLength()){
        CListCtrl& listctrl = GetListCtrl();
		listitem.mask = LVIF_TEXT;
		listitem.iItem = i;
		listitem.iSubItem = 0;
		listitem.pszText = TargetMaps[i].path;
		listctrl.SetItem(&listitem);
		Resize();
		SetTarget(TargetMaps);		
	}
}

void CDxwndhostView::OnAdd() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	int i;
	CTargetDlg dlg;
	LV_ITEM listitem;

	for(i = 0; i < MAXTARGETS; i ++) if(!TargetMaps[i].path[0]) break;
    CurrTarget = i;
	if(dlg.DoModal() == IDOK && dlg.m_FilePath.GetLength()){
        CListCtrl& listctrl = GetListCtrl();
		listitem.mask = LVIF_TEXT;
		listitem.iItem = i;
		listitem.iSubItem = 0;
		listitem.pszText = TargetMaps[i].path;
		listctrl.InsertItem(&listitem);
		Resize();
		SetTarget(TargetMaps);	
	}
}

void CDxwndhostView::OnDelete() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	int i;
	POSITION pos;
	CListCtrl& listctrl = GetListCtrl();

	if(!listctrl.GetSelectedCount()) return ;
	pos = listctrl.GetFirstSelectedItemPosition();
	i = listctrl.GetNextSelectedItem(pos);
	listctrl.DeleteItem(i);
	for(; i < MAXTARGETS  - 1; i ++) TargetMaps[i] = TargetMaps[i + 1];
	Resize();
	SetTarget(TargetMaps);
}

void CDxwndhostView::Resize()
{
	CListCtrl& listctrl = GetListCtrl();
	LV_COLUMN listcol;
	int i, tmp, size = 0;
	
	for(i = 0; i < MAXTARGETS; i ++){
		tmp = listctrl.GetStringWidth(TargetMaps[i].path);
		if(size < tmp) size = tmp;
	}
	
	listcol.mask = LVCF_WIDTH;
	listcol.cx = size + 10;
	listctrl.SetColumn(0, &listcol);
}



void CDxwndhostView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CMenu popup;
	int res;
	
	ClientToScreen(&point);
	popup.LoadMenu(IDR_MENU_POPUP);
	res = popup.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, point.x, point.y, this);
	switch(res){
	case ID_PRUN:
		OnRun();
		break;
	case ID_PMODIFY:
		OnModify();
		break;
	case ID_PDELETE:
		OnDelete();
		break;
	case ID_PADD:
		OnAdd();
		break;
	}
	CListView::OnRButtonDown(nFlags, point);
}

void CDxwndhostView::OnRun() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CListCtrl& listctrl = GetListCtrl();
	POSITION pos;
	int i, ret;
	STARTUPINFO sinfo;
	PROCESS_INFORMATION pinfo;
    HANDLE hndl;
	char path[MAX_PATH], logfile[MAX_PATH];
    FILE *fp;

	if(!listctrl.GetSelectedCount()) return;
	pos = listctrl.GetFirstSelectedItemPosition();
	i = listctrl.GetNextSelectedItem(pos);
	ZeroMemory(&sinfo, sizeof(sinfo));
	sinfo.cb = sizeof(sinfo);
	strcpy(path, TargetMaps[i].path);
	PathRemoveFileSpec(path);

    // reset log file
    if(TargetMaps[i].flags & OUTTRACE){
        strcpy(logfile, path);
	    strcat(logfile, "\\dxwnd.log");
        fp = fopen(logfile, "w+");
        fclose(fp);
    }

	if(TargetMaps[i].flags & SETAFFINITY){
        ret = CreateProcess(0, TargetMaps[i].path, 0, 0, 0, CREATE_DEFAULT_ERROR_MODE | CREATE_SUSPENDED, 0, path, &sinfo, &pinfo);
        if(ret){
            hndl = GetModuleHandle(0);
            // 0x1 - 1st core, 0x2 - 2nd core, 0x4 - 3d core, 0x8 - 4th core
            //DWORD ProcessMask, SystemMask;
            //GetProcessAffinityMask(pinfo.hProcess, &ProcessMask, &SystemMask);
		    //fp = fopen(logfile, "w+");
		    //fprintf(fp, "*** HookDirectX: GetProcessAffinityMask: ret = %x hndl = %x ProcessMask = %x SystemMask = %x\n", ret, hndl, ProcessMask, SystemMask);
		    //fclose(fp);
            SetProcessAffinityMask(pinfo.hProcess, 0x1);
		    ResumeThread(pinfo.hThread);
        }
	}
    else
        CreateProcess(0, TargetMaps[i].path, 0, 0, 0, CREATE_DEFAULT_ERROR_MODE, 0, path, &sinfo, &pinfo);
}



void CDxwndhostView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar){
	case VK_RETURN:
		OnRun();
		break;
	case 'M':
		OnModify();
		break;
	case VK_DELETE:
    case 'D':
		OnDelete();
		break;
	case 'A':
		OnAdd();
		break;
	}

	CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}
