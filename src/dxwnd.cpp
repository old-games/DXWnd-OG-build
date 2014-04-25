/*
DXWnd/dxwnd.cpp
DirectX Hook Module
Copyright(C) SFB7

2004/07/03 v1.02
2004/07/31 v1.03    縦横比固定リサイズ、負荷セーブ機能追加
2004/07/31 v1.03b   バグフィックス
2004/08/10 v1.10	バグフィックス、非アクティブ時入力が入る現象を一部修正
2004/08/27 v1.20	相対座標モードに対応
*/

#include <windows.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "dxwnd.h"

#define MAXTARGETS 256
#define VERSION "1.20 (OG build 6)"

LRESULT CALLBACK HookProc(int ncode, WPARAM wparam, LPARAM lparam);

HINSTANCE hInst;
HHOOK hHook;
HANDLE hMapping;
TARGETMAP *pMapping;
HANDLE hMutex;
int Test;

BOOL APIENTRY DllMain(HANDLE hmodule, 
                       DWORD  dwreason, 
                       LPVOID preserved
					)
{
	if(dwreason == DLL_PROCESS_DETACH){
		UnmapViewOfFile(pMapping);
		CloseHandle(hMapping);
	}
    if(dwreason != DLL_PROCESS_ATTACH) return TRUE;
	hInst = (HINSTANCE)hmodule;
	hMapping = CreateFileMapping((HANDLE)0xffffffff, NULL, PAGE_READWRITE,
		0, sizeof(TARGETMAP)*MAXTARGETS, "UniWind_TargetList");
	pMapping = (TARGETMAP *)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0,
		sizeof(TARGETMAP)*MAXTARGETS);
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "UniWind_Mutex");
	if(!hMutex) hMutex = CreateMutex(0, FALSE, "UniWind_Mutex");
	return true;
}

int SetTarget(TARGETMAP *targets){
	int i, j;

	WaitForSingleObject(hMutex, INFINITE);
	for(i = 0; targets[i].path[0]; i ++){
		pMapping[i] = targets[i];
		for(j = 0; pMapping[i].path[j]; j ++)
			pMapping[i].path[j] = tolower(pMapping[i].path[j]);
	}
	pMapping[i].path[0] = 0;
	ReleaseMutex(hMutex);
	return i;
}

int StartHook(void)
{
	hHook = SetWindowsHookEx(WH_CALLWNDPROC, HookProc, hInst, 0);
	return 0;
}

int EndHook(void)
{
	UnhookWindowsHookEx(hHook);
	return 0;
}

void GetDllVersion(char *dest)
{
	strcpy(dest, VERSION);
}


LRESULT CALLBACK HookProc(int ncode, WPARAM wparam, LPARAM lparam)
{
	char name[MAX_PATH];
	HWND hwnd;
	int i;

	hwnd = ((CWPSTRUCT *)lparam)->hwnd;
	if(((CWPSTRUCT *)lparam)->message == WM_CREATE){
		GetModuleFileName(0, name, MAX_PATH);
		for(i = 0; name[i]; i ++)
            name[i] = tolower(name[i]);

		WaitForSingleObject(hMutex, INFINITE);
		for(i = 0; pMapping[i].path[0]; i ++)
            if(!strncmp(name, pMapping[i].path, strlen(name))){
                //OutTrace("HookProc: %s\n", name);
				HookDirectX(&pMapping[i]);
            }

        ReleaseMutex(hMutex);
	}
	return CallNextHookEx(hHook, ncode, wparam, lparam);
}
