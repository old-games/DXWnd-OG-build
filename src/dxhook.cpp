#define _WIN32_WINNT 0x0400
#define WIN32_LEAN_AND_MEAN

#define INITGUID    // see comments in basetyps.h on DEFINE_GUID

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "dxwnd.h"
#include "dxhook.h"

#include <ddraw.h>
#include <mapidefs.h>
#include <memory.h>


typedef HINSTANCE (WINAPI *LoadLibraryA_Type)(LPCTSTR);
typedef HRESULT (WINAPI *CoCreateInstance_Type)(REFCLSID, LPUNKNOWN, DWORD, REFIID, LPVOID *);
typedef int (WINAPI *GetDeviceCaps_Type)(HDC, int);
typedef BOOL (WINAPI *GetCursorPos_Type)(LPPOINT);
typedef BOOL (WINAPI *SetCursorPos_Type)(int, int);

HINSTANCE WINAPI extLoadLibraryA_Type(LPCTSTR);
STDAPI WINAPI extCoCreateInstance(REFCLSID, LPUNKNOWN, DWORD, REFIID, LPVOID *);
int WINAPI extGetDeviceCaps(HDC, int);
BOOL WINAPI extGetCursorPos(LPPOINT);
BOOL WINAPI extSetCursorPos(int, int);

CoCreateInstance_Type pCoCreateInstance;
LoadLibraryA_Type pLoadLibraryA;
GetDeviceCaps_Type pGetDeviceCaps;
GetCursorPos_Type pGetCursorPos;
SetCursorPos_Type pSetCursorPos;


DWORD dwFlags;
DWORD dwVersion;
BOOL  bActive = 1;
HWND  hWnd = 0;
DWORD dwWidth = 0;      // resolution defined by game
DWORD dwHeight = 0;
int ResX = 0;           // resolution (actual) and refresh rate at fullscreen mode
int ResY = 0;
int RefreshRate = 0;
int widescreen_delta;   // (Widescreen_Width - Width) / 2
int FPSLimitVal;        // is used in hddraw.cpp
float ratiox, ratioy;
bool  FullScreen_Auto = 0;

WNDPROC pWindowProc = 0;


void OutTrace(const char *format, ...)
{	va_list al;
	static char path[MAX_PATH];
	FILE *fp;

	if(!(dwFlags & OUTTRACE) || !(dwFlags & HOOKDD)) return;

	GetCurrentDirectory(MAX_PATH, path);
	strcat(path, "\\dxwnd.log");
	fp = fopen(path, "a+t");
	va_start(al, format);
    vfprintf(fp, format, al);
	va_end(al);
	fclose(fp);
}


void *HookAPI(const char *module, const char *api, void *hookproc)
{
	int i;
	DWORD base;
	PIMAGE_NT_HEADERS pnth;
	PIMAGE_IMPORT_DESCRIPTOR pidesc;
	DWORD rva;
	PSTR impmodule;
	PIMAGE_THUNK_DATA ptaddr;
	PIMAGE_THUNK_DATA ptname;
	PIMAGE_IMPORT_BY_NAME piname;
	DWORD oldprotect;
	void *org;

	//OutTrace("HookAPI: %s, %s\n", module, api);

	base = (DWORD)GetModuleHandle(0);
	if(!base) return 0;
	__try{
		pnth = PIMAGE_NT_HEADERS(PBYTE(base) + PIMAGE_DOS_HEADER(base)->e_lfanew);
		if(!pnth) return 0;
		rva = pnth->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
		if(!rva) return 0;
		pidesc = (PIMAGE_IMPORT_DESCRIPTOR)(base + rva);
		while(1){
			if(!pidesc->FirstThunk) return 0;
			impmodule = (PSTR)(base + pidesc->Name);
			if(!lstrcmpi(module, impmodule)) break;
			pidesc ++;
		}
		ptaddr = (PIMAGE_THUNK_DATA)(base + (DWORD)pidesc->FirstThunk);
		ptname = (PIMAGE_THUNK_DATA)(base + (DWORD)pidesc->OriginalFirstThunk);
		for(i = 0; (ptaddr + i)->u1.Function; i ++);
		while(1){
			if(!ptaddr->u1.Function) return 0;
			if(!IMAGE_SNAP_BY_ORDINAL(ptname->u1.Ordinal)){
				piname = (PIMAGE_IMPORT_BY_NAME)(base + (DWORD)ptname->u1.AddressOfData);
				if(!lstrcmpi(api, (char *)piname->Name)) break;
			}
			ptaddr ++;
			ptname ++;
		}
		org = ptaddr->u1.Function;
			if(org == hookproc) return 0;
		if(!VirtualProtect(&ptaddr->u1.Function, 4, PAGE_EXECUTE_READWRITE, &oldprotect)) return 0;
		ptaddr->u1.Function = (DWORD *)hookproc;
		VirtualProtect(&ptaddr->u1.Function, 4, oldprotect, &oldprotect);
	 }
	__except(EXCEPTION_EXECUTE_HANDLER)
	{       
		OutTrace("*** DXWND: %s:%s Hook Failed.\n", module, api);
		org = 0;
	}

	return org;
}


void *SetHook(void *target, void *hookproc)
{
	DWORD tmp, oldprot;
	
	tmp = *(DWORD *)target;
    if(tmp == (DWORD)hookproc){
        OutTrace(" *** DXWND: SetHook: already installed\n");
        return 0;
    }
	if(!VirtualProtect(target, 4, PAGE_READWRITE, &oldprot)) return 0;
	*(DWORD *)target = (DWORD)hookproc;
	VirtualProtect(target, 4, oldprot, &oldprot);
	return (void *)tmp;
}


void CaptureMouse(HWND hwnd)
{
    POINT p;
    RECT rect;

    if((dwFlags & CAPTUREMOUSE) && !(dwFlags & FULLSCREEN)){
        //SetCapture(hwnd);
        p.x = p.y = 0;
        GetClientRect(hwnd, &rect);
        ClientToScreen(hwnd, &p);
        OffsetRect(&rect, p.x, p.y);
        ClipCursor(&rect);
    }
}


void AdjustWindowFrame(HWND hwnd, DWORD width, DWORD height)
{
	RECT rect;
	POINT p = {0, 0};
	static BOOL check = 0;
    int maxx, maxy;

	//OutTrace("\n*** DXWND: AdjustWindowFrame\n");

	if(dwFlags & FULLSCREEN){
	    SetWindowLong(hwnd, GWL_STYLE, WS_POPUP);
		maxx = GetSystemMetrics(SM_CXSCREEN);
		maxy = GetSystemMetrics(SM_CYSCREEN);
		SetWindowPos(hwnd, HWND_TOP, 0, 0, maxx, maxy, 0);
	}
    else{
	    rect.top = 0;
	    rect.left = 0;
	    rect.right = ResX;
	    rect.bottom = ResY;
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	    SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);

        // SCUD doesn't work due to centering.
		maxx = GetSystemMetrics(SM_CXSCREEN);
		maxy = GetSystemMetrics(SM_CYSCREEN);

        p.x = rect.right - rect.left;
        p.y = rect.bottom - rect.top;
	    SetWindowPos(hwnd, HWND_TOP, (maxx/2 - p.x/2), (maxy/2 - p.y/2), p.x, p.y, 0);
        CaptureMouse(hwnd);

        /*p.x = rect.right - rect.left;
        p.y = rect.bottom - rect.top;
	    SetWindowPos(hwnd, HWND_TOP, rect.left, rect.top, p.x, p.y, 0);*/
	}

    ShowWindow(hwnd, SW_SHOWNORMAL);
    if(!(dwFlags & HIDECURSOR))
        ShowCursor(0);
	InvalidateRect(0, 0, TRUE);

   	if(check) return;
	check = 1;

    if(dwFlags & HOOKDD){
        pWindowProc = (WNDPROC)GetWindowLong(hwnd, GWL_WNDPROC);
	    if(!((DWORD)pWindowProc & 0xff000000))
		    (WNDPROC)SetWindowLong(hwnd, GWL_WNDPROC, (LONG)extWindowProc);
    }
}


LRESULT CALLBACK extWindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	POINT p;
	RECT rect;

	switch(message){
	case WM_ACTIVATE:
		bActive = (LOWORD(wparam) == WA_ACTIVE || LOWORD(wparam) == WA_CLICKACTIVE) ? 1 : 0;
        CaptureMouse(hwnd);
    case WM_NCACTIVATE:
		if(message == WM_NCACTIVATE) bActive = wparam;
		SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if(dwFlags & UNNOTIFY){
			DefWindowProc(hwnd, message, wparam, lparam);
			return false;
		}
		break;
    case WM_ERASEBKGND:
        return TRUE;
        break;
	case WM_NCMOUSEMOVE:
	    while(ShowCursor(1) < 0);
		break;
	case WM_MOUSEMOVE:
		p.x = LOWORD(lparam);
		p.y = HIWORD(lparam);
        if(!(dwFlags & HIDECURSOR)){
		    GetClientRect(hwnd, &rect);
		    if(p.x >= 0 && p.x < rect.right && p.y >= 0 && p.y < rect.bottom)
			    while(ShowCursor(0) >= 0);
		    else
			    while(ShowCursor(1) < 0);
        }
	case WM_MOUSEWHEEL:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDBLCLK:
		if(dwFlags & MODIFYMOUSE){
            // need to correct position if resolution is less then native
            // (and in windowed mode - GetCursorPos()/SetCursorPos())
            //if(dwFlags & FULLSCREEN){
                if(ratiox > 1.0){
			        p.x = (long)((float)(LOWORD(lparam)) * ratiox);
			        p.y = (long)((float)(HIWORD(lparam)) * ratioy);

                    //OutTrace("*** DXWND: Set mouse coordinates from x=%d, y=%d to x=%d, y=%d\n", 
                    //    LOWORD(lparam), HIWORD(lparam), p.x, p.y);
                    lparam = MAKELPARAM(p.x, p.y);
                }
            //}
		}
		break;
	case WM_SIZE:
		if(dwFlags & FULLSCREEN)
            break;
        float ratio;
		GetClientRect(hwnd, &rect);
		p.x = rect.right;
		p.y = rect.bottom;
//		if(GetAsyncKeyState(VK_SHIFT) & 0x8000){    // always preserve aspect ratio
			if(((float)p.x/dwWidth) > ((float)p.y/dwHeight)){
				ratio = (float)p.x/ResX;
				p.y = (int)((float)ResY * ratio);
			}
			else{
				ratio = (float)p.y/ResY;
				p.x = (int)((float)ResX * ratio);
			}
//		}
		if(GetAsyncKeyState(VK_CONTROL) & 0x8000){  // restore original size
			p.x = ResX;
			p.y = ResY;
		}
		p.x = p.x - rect.right;
		p.y = p.y - rect.bottom;
		if(p.x || p.y){
			GetWindowRect(hwnd, &rect);
			p.x = rect.right - rect.left + p.x;
			p.y = rect.bottom - rect.top + p.y;
			MoveWindow(hwnd, rect.left, rect.top, p.x, p.y, TRUE);
		}
        ratiox = (float)(dwWidth - 1) / (float)(rect.right - 1);
        ratioy = (float)(dwHeight - 1) / (float)(rect.bottom - 1);
 		break;
    case WM_DESTROY:
        if((dwFlags & CAPTUREMOUSE) && !(dwFlags & FULLSCREEN))
            ClipCursor(NULL);
	}
	if(pWindowProc) return (*pWindowProc)(hwnd, message, wparam, lparam);
	return DefWindowProc(hwnd, message, wparam, lparam);
}


STDAPI WINAPI extCoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter,
                                  DWORD dwClsContext,	REFIID riid, LPVOID * ppv)
{


    HRESULT res;
    OutTrace("CoCreateInstance: rclsid = %x, pUnkOuter = %x, dwClsContext = %x, riid = %x, ppv = %x\n",
        rclsid, pUnkOuter, dwClsContext, riid, ppv);

    res = CoCreateInstance(rclsid, pUnkOuter, dwClsContext, riid, ppv);
    return res;
}


HINSTANCE WINAPI extLoadLibraryA(LPCTSTR  lpLibFileName)
{
    HINSTANCE res;

    res = (*pLoadLibraryA)(lpLibFileName);
    OutTrace("LoadLibraryA: %s, res = %x\n", lpLibFileName, res);
    return res;
}


int WINAPI extGetDeviceCaps(HDC hdc, int nindex)
{
	int res;
	
	res = (*GetDeviceCaps)(hdc, nindex);
	OutTrace("GetDeviceCaps: hdc = %x index = %x res = %x\n", hdc, nindex, res);
	return res;
}


BOOL WINAPI extGetCursorPos(LPPOINT lppoint)
{

    (*pGetCursorPos)(lppoint);
	OutTrace("GetCursorPos: x = %i y = %i\n", lppoint->x, lppoint->y);

	if(dwFlags & MODIFYMOUSE)
		ScreenToClient(hWnd, lppoint);

    return 1;
}


BOOL WINAPI extSetCursorPos(int x, int y)
{
    POINT p;

	OutTrace("SetCursorPos: x = %i y = %i\n", x, y);

    p.x = x;
    p.y = y;

	if(dwFlags & MODIFYMOUSE)
		ClientToScreen(hWnd, &p);
    (*pSetCursorPos)(p.x, p.y);

    return 1;
}


int HookDirectX(TARGETMAP *target)
{
	void *tmp;
    char s[MAX_MODE_LEN];

	dwFlags = target->flags;

    if(dwFlags & HOOKDD){
	    tmp = HookAPI("kernel32.dll", "LoadLibraryA", extLoadLibraryA);
	    if(tmp) pLoadLibraryA = (LoadLibraryA_Type)tmp;

        tmp = HookAPI("ole32.dll", "CoCreateInstance", extCoCreateInstance);
	    if(tmp) pCoCreateInstance = (CoCreateInstance_Type)tmp;

	    tmp = HookAPI("gdi32.dll", "GetDeviceCaps", extGetDeviceCaps);
	    if(tmp) pGetDeviceCaps = (GetDeviceCaps_Type)tmp;
	    
	    if(dwFlags & MODIFYMOUSE){
		    tmp = HookAPI("user32.dll", "GetCursorPos", extGetCursorPos);
		    if(tmp) pGetCursorPos = (GetCursorPos_Type)tmp;
		    tmp = HookAPI("user32.dll", "SetCursorPos", extSetCursorPos);
		    if(tmp) pSetCursorPos = (SetCursorPos_Type)tmp;

	    }

	    if(dwFlags & HOOKDI){
		    HookDirectInput(target->dxversion);
		    InitPosition(target->initx, target->inity,
			    target->minx, target->miny, target->maxx, target->maxy);
	    }

    }

    // NOTE: code below can be called several times
    FPSLimitVal = target->FPSLimit;

    if(!strcmp(target->Mode, "(Auto)")){
        FullScreen_Auto = 1;
    }
    else{
        strcpy(s, target->Mode);
        ResX = atoi(strtok(s, "x"));
        ResY = atoi(strtok(0, "@"));
        RefreshRate	= atoi(strtok(0, ""));
        FullScreen_Auto = 0;
    }
    HookDirectDraw();
	HookDirect3D(target->dxversion);

	return 0;
}
