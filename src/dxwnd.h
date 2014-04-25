#ifndef DXWND_H
#define DXWND_H

#include <windows.h>


#define MAXTARGETS			256
#define UNNOTIFY			0x0001
#define EXTENDED_LOG	    0x0002
#define CAPTUREMOUSE  	    0x0004
#define HIDECURSOR			0x0008
#define HOOKDI				0x0010
#define MODIFYMOUSE			0x0020
#define OUTTRACE			0x0040
#define SAVELOAD			0x0080
#define FULLSCREEN			0x0100
#define SHOWFPS 			0x0200
#define LIMITFPS 			0x0400
#define USEGDI   			0x0800
#define SYSTEMMEMORY        0x1000
#define VIDEOMEMORY         0x2000
//#define ASYNCBLT            0x4000
#define SETAFFINITY         0x4000
#define COLOURCONVERT	    0x8000
#define AUTOMEMORY  	0x00010000
#define HOOKDD        	0x00020000

#define MAX_MODE_LEN    16

typedef struct TARGETMAP
{
	char path[MAX_PATH];
	int dxversion;      // obsolete
	int flags;
	int initx;
	int inity;
	int minx;
	int miny;
	int maxx;
	int maxy;
    int FPSLimit;
    char Mode[MAX_MODE_LEN];
}TARGETMAP;


struct DDRAW_DEVICE_STRUCT
{

    DWORD dwModeNum;
    char aModeDesc[1024][MAX_MODE_LEN];
};


int SetTarget(TARGETMAP *);
int StartHook(void);
int EndHook(void);
void GetDllVersion(char *);
int HookDirectX(TARGETMAP *);

void *SetHook(void *, void *);
void OutTrace(const char *, ...);
void *HookAPI(const char *, const char *, void *);
void AdjustWindowFrame(HWND, DWORD, DWORD);
LRESULT CALLBACK extWindowProc(HWND, UINT, WPARAM, LPARAM);

#endif // #ifndef DXWND_H
