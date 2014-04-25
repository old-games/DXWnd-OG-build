#include <stdio.h>
#include <windows.h>
#include <ddraw.h>
#include "dxwnd.h"


typedef HRESULT (WINAPI *DirectDrawCreate_Type)(GUID *, LPDIRECTDRAW *, IUnknown *);
//typedef HRESULT (WINAPI *DirectDrawCreateEx_Type)(GUID *, LPDIRECTDRAW *, REFIID, IUnknown *);
typedef HRESULT (WINAPI *QueryInterface_Type)(void *, REFIID, LPVOID *);
typedef HRESULT (WINAPI *CreateSurface_Type)(LPDIRECTDRAW, DDSURFACEDESC2 *, LPDIRECTDRAWSURFACE *, void *);
typedef HRESULT (WINAPI *SetCooperativeLevel_Type)(LPDIRECTDRAW, HWND, DWORD);
typedef HRESULT (WINAPI *GetAttachedSurface_Type)(void *, DDSCAPS *, LPDIRECTDRAWSURFACE *);
typedef HRESULT (WINAPI *SetDisplayMode1_Type)(LPDIRECTDRAW, DWORD, DWORD, DWORD);
typedef HRESULT (WINAPI *SetDisplayMode_Type)(LPDIRECTDRAW, DWORD, DWORD, DWORD, DWORD, DWORD);
typedef HRESULT (WINAPI *CreatePalette_Type)(LPDIRECTDRAW, DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE *, IUnknown *);
typedef HRESULT (WINAPI *Blt_Type)(LPDIRECTDRAWSURFACE, LPRECT, LPDIRECTDRAWSURFACE, LPRECT, DWORD, LPDDBLTFX);
typedef HRESULT (WINAPI *BltFast_Type)(LPDIRECTDRAWSURFACE, DWORD, DWORD, LPDIRECTDRAWSURFACE, LPRECT, DWORD);
typedef HRESULT (WINAPI *SetPalette_Type)(LPDIRECTDRAWSURFACE, LPDIRECTDRAWPALETTE);
typedef HRESULT (WINAPI *GetPalette_Type)(LPDIRECTDRAWSURFACE, LPDIRECTDRAWPALETTE *);
typedef HRESULT (WINAPI *GetDisplayMode_Type)(LPDIRECTDRAW, LPDDSURFACEDESC);
typedef HRESULT (WINAPI *WaitForVerticalBlank_Type)(LPDIRECTDRAW, DWORD, HANDLE);
typedef HRESULT (WINAPI *SetClipper_Type)(LPDIRECTDRAWSURFACE, LPDIRECTDRAWCLIPPER);
typedef HRESULT (WINAPI *Lock_Type)(LPDIRECTDRAWSURFACE, LPRECT, LPDDSURFACEDESC, DWORD, HANDLE);
typedef HRESULT (WINAPI *UnLock_Type)(LPDIRECTDRAWSURFACE, LPRECT);
typedef HRESULT (WINAPI *GetSurfaceDesc_Type)(LPDIRECTDRAWSURFACE, LPDDSURFACEDESC);
typedef HRESULT (WINAPI *Flip_Type)(LPDIRECTDRAWSURFACE, LPDIRECTDRAWSURFACE, DWORD);
typedef HRESULT (WINAPI *AddAttachedSurface_Type)(LPDIRECTDRAWSURFACE, LPDIRECTDRAWSURFACE);
typedef HRESULT (WINAPI *GetPixelFormat_Type)(LPDIRECTDRAWSURFACE, LPDDPIXELFORMAT);
typedef HRESULT (WINAPI *SetEntries_Type)(LPDIRECTDRAWPALETTE, DWORD, DWORD, DWORD, LPPALETTEENTRY);

HRESULT WINAPI extDirectDrawCreate(GUID FAR *, LPDIRECTDRAW FAR *, IUnknown FAR *);
//HRESULT WINAPI extDirectDrawCreateEx(GUID FAR *, LPDIRECTDRAW FAR *, REFIID, IUnknown FAR *);
HRESULT WINAPI extQueryInterfaceD(void *, REFIID, LPVOID *);
HRESULT WINAPI extQueryInterfaceS(void *, REFIID, LPVOID *);
HRESULT WINAPI extSetDisplayMode1(LPDIRECTDRAW, DWORD, DWORD, DWORD);               // IDirectDraw
HRESULT WINAPI extSetDisplayMode(LPDIRECTDRAW, DWORD, DWORD, DWORD, DWORD, DWORD);  // IDirectDraw2, 4, 7
HRESULT WINAPI extCreateSurface(LPDIRECTDRAW, DDSURFACEDESC2 *, LPDIRECTDRAWSURFACE *, void *);
HRESULT WINAPI extSetCooperativeLevel(LPDIRECTDRAW, HWND, DWORD);
HRESULT WINAPI extGetAttachedSurface(void *, DDSCAPS *, LPDIRECTDRAWSURFACE *);
HRESULT WINAPI extFlip(LPDIRECTDRAWSURFACE, LPDIRECTDRAWSURFACE, DWORD);
HRESULT WINAPI extBltFast(LPDIRECTDRAWSURFACE, DWORD, DWORD, LPDIRECTDRAWSURFACE, LPRECT, DWORD);
HRESULT WINAPI extCreatePalette(LPDIRECTDRAW, DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE *, IUnknown *);
HRESULT WINAPI extBlt(LPDIRECTDRAWSURFACE, LPRECT, LPDIRECTDRAWSURFACE, LPRECT, DWORD, LPDDBLTFX);
HRESULT WINAPI extGetPalette(LPDIRECTDRAWSURFACE, LPDIRECTDRAWPALETTE *);
HRESULT WINAPI extSetPalette(LPDIRECTDRAWSURFACE, LPDIRECTDRAWPALETTE);
HRESULT WINAPI extGetDisplayMode(LPDIRECTDRAW, LPDDSURFACEDESC);
HRESULT WINAPI extWaitForVerticalBlank(LPDIRECTDRAW, DWORD, HANDLE);
HRESULT WINAPI extSetClipper(LPDIRECTDRAWSURFACE, LPDIRECTDRAWCLIPPER);
HRESULT WINAPI extLock(LPDIRECTDRAWSURFACE, LPRECT, LPDDSURFACEDESC, DWORD, HANDLE);
HRESULT WINAPI extUnLock(LPDIRECTDRAWSURFACE, LPRECT);
HRESULT WINAPI extGetSurfaceDesc(LPDIRECTDRAWSURFACE, LPDDSURFACEDESC);
HRESULT WINAPI extAddAttachedSurface(LPDIRECTDRAWSURFACE, LPDIRECTDRAWSURFACE);
HRESULT WINAPI extGetPixelFormat(LPDIRECTDRAWSURFACE, LPDDPIXELFORMAT);
HRESULT WINAPI extSetEntries(LPDIRECTDRAWPALETTE, DWORD, DWORD, DWORD, LPPALETTEENTRY);

struct Methods_struct{

    LPDIRECTDRAW FAR lpdd;
    int Version;

    // IDirectDraw methods
    QueryInterface_Type pQueryInterfaceD;
    CreateSurface_Type pCreateSurface;
    GetDisplayMode_Type pGetDisplayMode;
    SetCooperativeLevel_Type pSetCooperativeLevel;
    SetDisplayMode_Type pSetDisplayMode;
    CreatePalette_Type pCreatePalette;
    WaitForVerticalBlank_Type pWaitForVerticalBlank;

    // IDirectDrawSurface methods
    QueryInterface_Type pQueryInterfaceS;
    GetAttachedSurface_Type pGetAttachedSurface;
    SetClipper_Type pSetClipper;
    GetPalette_Type pGetPalette;
    SetPalette_Type pSetPalette;
    Blt_Type pBlt;
    BltFast_Type pBltFast;
    Flip_Type pFlip;
    Lock_Type pLock;
    UnLock_Type pUnLock;
    GetSurfaceDesc_Type pGetSurfaceDesc;
    AddAttachedSurface_Type pAddAttachedSurface;
    GetPixelFormat_Type pGetPixelFormat;

    // IDirectDrawPalette methods
    SetEntries_Type pSetEntries;
};


Methods_struct apMethod[16];                        // store original methods pointers here
int apMethod_max = -1;

extern const char * DDError2Str(int);

extern HWND hWnd;
extern DWORD dwWidth;
extern DWORD dwHeight;
extern DWORD dwFlags;                               // bad names: this is dxwnd's internal variables
extern int FPSLimitVal;
extern float ratiox, ratioy;
extern int ResX;
extern int ResY;
extern int RefreshRate;
extern int widescreen_delta;
extern bool FullScreen_Auto;
// lpDDSEmu_Prim, lpDDSEmu_Back ~ desktop (dxwnd's) surfaces
// lpDDSPrim are passed to game (lpDDSPrimQ is filled
// when game queries other interface)
// lpDDSEmu_Back is used as intermediate surface for colour convertion
LPDIRECTDRAWSURFACE lpDDSPrim, lpDDSPrimQ, lpDDSEmu_Prim, lpDDSEmu_Back;
int lpDDSEmu_PrimSave = 0, lpDDSEmu_BackSave = 0;   // for release surfaces check

static int Emu_Surfaces_Created = 0;

//int Need_ColourConversion = 0;
int dwBPP;                                        // Bit depth, required by game (only for USEGDI)

LARGE_INTEGER QPcounter_curr, QPcounter_start;
LARGE_INTEGER QPfrequency;
long int next_ticks;


//----------------------------------------------------------------------------


// Switch to selected mode (with current depth - 
// it is changed at SetDisplayMode)
// Mode is restored by Windows at program exit
// Relies on dWidth, dwHeight (must be set beforehand)
void SetDXWndMode(bool RefreshRate_Valid)
{
	DEVMODE dm;
    LONG res = 0;
	float ratiod, ratiog;				// dxwnd's and game's screen ratios
	float nx, ny;                       // new draw area size (x-axis difference is a global)

    // mouse coordinats ranges from 0 to ResX(Y)-1
    ratiox = (float)(dwWidth - 1) / (float)(ResX - 1);
    ratioy = (float)(dwHeight - 1) / (float)(ResY - 1);

    if(dwFlags & FULLSCREEN){
        EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &dm);

        dm.dmPelsWidth	= ResX;
        dm.dmPelsHeight	= ResY;
        if(RefreshRate_Valid)
            dm.dmDisplayFrequency = RefreshRate;
        dm.dmFields	= DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
		res = ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
    }

    OutTrace("*** DXWND: Mode %ux%u@%u ratiox = %3.5f, ratioy = %3.5f (%x)\n",
        ResX, ResY, RefreshRate, ratiox, ratioy, res);

	ratiod = (float)ResX/(float)ResY;
	ratiog = (float)dwWidth/(float)dwHeight;
	
	nx = (float)ResY * ratiog;
	ny = (float)ResY;                       // unused
	widescreen_delta = (int)(((float)ResX - (float)nx) / 2.0);
	OutTrace("*** DXWND: GDIBlt: ratiod = %f ratiog = %f widescreen_delta = %f nx = %f ny = %f\n", ratiod, ratiog, widescreen_delta, nx, ny);
}


int GDIBlt(LPDIRECTDRAWSURFACE lpddsdst, LPRECT lpdestrect,
	LPDIRECTDRAWSURFACE lpddssrc, LPRECT lpsrcrect)
{

   	RECT rect, screen;
    HDC hDC_src, hDC_dst;
    DDSURFACEDESC2 ddsddst, ddsdsrc;
    GetSurfaceDesc_Type pGetSurfaceDescSrc, pGetSurfaceDescDst;
    int VersionSrc, VersionDst;


    if(!lpddssrc){                                  // sometimes Blt is called with lpddssrc = 0
        OutTrace("*** DXWND: GDIBlt: lpddssrc = 0\n");  // e.g., from d3dim.dll
        return 0;                                   
    }

    // Get surfaces interface version (S.C.A.R.S)
    // (other version interface can be requested via QueryInterface)
    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpddsdst) == (int)apMethod[i].lpdd){
            VersionDst = apMethod[i].Version;
            pGetSurfaceDescDst = apMethod[i].pGetSurfaceDesc;
            break;
        }

    for(i = 0; i <= apMethod_max; i++)
        if(*((int*)lpddssrc) == (int)apMethod[i].lpdd){
            VersionSrc = apMethod[i].Version;
            pGetSurfaceDescSrc = apMethod[i].pGetSurfaceDesc;
            break;
        }

    ddsddst.dwSize = (VersionDst < 4) ? sizeof(DDSURFACEDESC) : sizeof(DDSURFACEDESC2);
    ddsdsrc.dwSize = (VersionSrc < 4) ? sizeof(DDSURFACEDESC) : sizeof(DDSURFACEDESC2);
    
    (*pGetSurfaceDescDst)(lpddsdst, (LPDDSURFACEDESC)&ddsddst);
    (*pGetSurfaceDescSrc)(lpddssrc, (LPDDSURFACEDESC)&ddsdsrc);

    lpddssrc->GetDC(&hDC_src);
    lpddsdst->GetDC(&hDC_dst);

/*
    // like ddraw - interpolation when scaling
    SetStretchBltMode(hDC_dst, HALFTONE);
*/

    if(lpdestrect){
        screen = *lpdestrect;
    }
    else{
        screen.left = 0;
        screen.top = 0;
        screen.right = ddsddst.dwWidth;
        screen.bottom = ddsddst.dwHeight;
    }

    if(lpsrcrect){
        rect = *lpsrcrect;
    }
    else{
        rect.left = 0;
        rect.top = 0;
        rect.right = ddsdsrc.dwWidth;
        rect.bottom = ddsdsrc.dwHeight;
    }

    // NOTE: Can be slow when scaling
    StretchBlt(hDC_dst, screen.left, screen.top,
                        screen.right - screen.left, screen.bottom - screen.top,
               hDC_src, rect.left, rect.top,
                        rect.right - rect.left, rect.bottom - rect.top, SRCCOPY);


    lpddssrc->ReleaseDC(hDC_src);
    lpddsdst->ReleaseDC(hDC_dst);

    return 0;
}


void LimitFPS()
{
    static DWORD start_time = 0;
    static int nfps = 0;
    static float curr_fps;

    DWORD dt;
    static unsigned int fps_upd_interval = 1000; // in ms
    char s[255], sfps[255];

    // Calculate average fps 
    nfps++;
    dt = GetTickCount() - start_time;//timeGetTime();
    curr_fps = (float)(nfps*1000.0/(float)dt);

    if(dt > fps_upd_interval){
        nfps = 0;
        start_time = GetTickCount() + 1;//timeGetTime(); without +1 gives dt = 0 and divide error

        if(dwFlags & SHOWFPS)
            if(dwFlags & FULLSCREEN){
                OutTrace("*** DXWND: fps = %5.2f\n", curr_fps);
            }
            else{
                sprintf(sfps, " (fps: %5.2f)", curr_fps);
                GetWindowText(hWnd, s, 255);
                strtok(s, " (fps"); // write 0 at token
                strcat(s, sfps);
                SetWindowText(hWnd, s);
            }

    }


    if(dwFlags & LIMITFPS){
        // Adjust frame time
        // Since LARGE_INTEGER is 64-bit this effectively uses
        // LowPart only. Convert to float to get HighPart into account.
        QueryPerformanceCounter(&QPcounter_curr);
        while(QPcounter_curr.QuadPart <= (QPcounter_start.QuadPart + next_ticks)){
            if(curr_fps > FPSLimitVal){           // Sleep if needed
                if(dwFlags & SAVELOAD)
                    Sleep(1);
            }
            else                                    // break, if average fps is low
                break;

            QueryPerformanceCounter(&QPcounter_curr);
        }
        QueryPerformanceCounter(&QPcounter_start);
    }
}


// lpdds is lpDDSPrim or lpDDSPrimQ
void PrimaryBlt(LPDIRECTDRAWSURFACE lpdds)
{
   
    RECT screen;
    POINT p;
    Blt_Type pBlt;
    int sl, sr;                                     // save screen.left and screen.right here

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpDDSEmu_Prim) == (int)apMethod[i].lpdd){
            pBlt = apMethod[i].pBlt;
            break;
        }
    
    LimitFPS();

    // Blit primary surface
    OutTrace(" *** DXWND: PrimaryBlt ");
    p.x = p.y = 0;
    GetClientRect(hWnd, &screen);
    ClientToScreen(hWnd, &p);
    OffsetRect(&screen, p.x, p.y);


//    if(lpDDSPrim->IsLost() != DD_OK)            // Should be restored by game
//        lpDDSPrim->Restore();
    if(lpDDSEmu_Back->IsLost() != DD_OK)          // This allows Alt-TAB task switching
        lpDDSEmu_Back->Restore();
    if(lpDDSEmu_Prim->IsLost() != DD_OK)
        lpDDSEmu_Prim->Restore();

    // Blitting with StretchBlt effectively converts colour format
    // and allows window scaling without antialiasing
    if(dwFlags & COLOURCONVERT)
    //if((dwBPP == 8) || (Need_ColourConversion)) // works bad for Tunguska, Ubik
        GDIBlt(lpDDSEmu_Back, 0, lpdds, 0);
    else
        (*pBlt)(lpDDSEmu_Back, 0, lpdds, 0, DDBLT_WAIT, 0);


	// this should be correct RGB or index value (or use GDI BitBlt)
	// (index 0 might not be Black colour)
	DDBLTFX ddbltfx;
	ddbltfx.dwSize = sizeof(DDBLTFX);
	ddbltfx.dwFillColor = 0x0;

	
	sl = screen.left;
	sr = screen.right;

	screen.right = sl + widescreen_delta;
	(*pBlt)(lpDDSEmu_Prim, &screen, 0, 0, DDBLT_WAIT | DDBLT_COLORFILL, &ddbltfx);

	screen.left = sr - widescreen_delta;
	screen.right = sr;
	(*pBlt)(lpDDSEmu_Prim, &screen, 0, 0, DDBLT_WAIT | DDBLT_COLORFILL, &ddbltfx);

	screen.left = sl + widescreen_delta;
	screen.right = sr - widescreen_delta;
	(*pBlt)(lpDDSEmu_Prim, &screen, lpDDSEmu_Back, 0, DDBLT_WAIT, 0);
}


void HookDDMethods(LPDIRECTDRAW lpDD, int Version, void *extSetDisplayModeVer)
{
    void *tmp;

    apMethod_max++;
    apMethod[apMethod_max].lpdd = (LPDIRECTDRAW)(*(DWORD *)lpDD);

    apMethod[apMethod_max].Version = Version;

    tmp = SetHook((void *)(*(DWORD *)lpDD), extQueryInterfaceD);
	if(tmp) apMethod[apMethod_max].pQueryInterfaceD = (QueryInterface_Type)tmp;

    if((dwFlags & EXTENDED_LOG) && (dwFlags & OUTTRACE) && (dwFlags & HOOKDD)){
        tmp = SetHook((void *)(*(DWORD *)lpDD + 0x14), extCreatePalette);
    	if(tmp) apMethod[apMethod_max].pCreatePalette = (CreatePalette_Type)tmp;
        tmp = SetHook((void *)(*(DWORD *)lpDD + 0x58), extWaitForVerticalBlank);
	    if(tmp) apMethod[apMethod_max].pWaitForVerticalBlank = (WaitForVerticalBlank_Type)tmp;
    }

    tmp = SetHook((void *)(*(DWORD *)lpDD + 0x18), extCreateSurface);
	if(tmp) apMethod[apMethod_max].pCreateSurface = (CreateSurface_Type)tmp;
    tmp = SetHook((void *)(*(DWORD *)lpDD + 0x30), extGetDisplayMode);
	if(tmp) apMethod[apMethod_max].pGetDisplayMode = (GetDisplayMode_Type)tmp;
	tmp = SetHook((void *)(*(DWORD *)lpDD + 0x50), extSetCooperativeLevel);
	if(tmp) apMethod[apMethod_max].pSetCooperativeLevel = (SetCooperativeLevel_Type)tmp;
    tmp = SetHook((void *)(*(DWORD *)lpDD + 0x54), extSetDisplayModeVer);
	if(tmp) apMethod[apMethod_max].pSetDisplayMode = (SetDisplayMode_Type)tmp;
}


void HookDDSurfaceMethods(LPDIRECTDRAWSURFACE lpDDS, int Version)
{
    void *tmp;

    apMethod_max++;
    apMethod[apMethod_max].lpdd = (LPDIRECTDRAW)(*(DWORD *)lpDDS);

    apMethod[apMethod_max].Version = Version;

    tmp = SetHook((void *)(*(DWORD *)lpDDS), extQueryInterfaceS);
	if(tmp) apMethod[apMethod_max].pQueryInterfaceS = (QueryInterface_Type)tmp;
    tmp = SetHook((void *)(*(DWORD *)lpDDS + 0x14), extBlt);
	if(tmp) apMethod[apMethod_max].pBlt = (Blt_Type)tmp;
    tmp = SetHook((void *)(*(DWORD *)lpDDS + 0x1C), extBltFast);
	if(tmp) apMethod[apMethod_max].pBltFast = (BltFast_Type)tmp;
    tmp = SetHook((void *)(*(DWORD *)lpDDS + 0x2C), extFlip);
    if(tmp) apMethod[apMethod_max].pFlip = (Flip_Type)tmp;
    tmp = SetHook((void *)(*(DWORD *)lpDDS + 0x58), extGetSurfaceDesc);
    if(tmp) apMethod[apMethod_max].pGetSurfaceDesc = (GetSurfaceDesc_Type)tmp;
    tmp = SetHook((void *)(*(DWORD *)lpDDS + 0x64), extLock);
    if(tmp) apMethod[apMethod_max].pLock = (Lock_Type)tmp;
    tmp = SetHook((void *)(*(DWORD *)lpDDS + 0x70), extSetClipper);
    if(tmp) apMethod[apMethod_max].pSetClipper = (SetClipper_Type)tmp;
    tmp = SetHook((void *)(*(DWORD *)lpDDS + 0x80), extUnLock);
    if(tmp) apMethod[apMethod_max].pUnLock = (UnLock_Type)tmp;

    if((dwFlags & EXTENDED_LOG) && (dwFlags & OUTTRACE) && (dwFlags & HOOKDD)){
        tmp = SetHook((void *)(*(DWORD *)lpDDS + 0xC), extAddAttachedSurface);
	    if(tmp) apMethod[apMethod_max].pAddAttachedSurface = (AddAttachedSurface_Type)tmp;
        tmp = SetHook((void *)(*(DWORD *)lpDDS + 0x30), extGetAttachedSurface);
	    if(tmp) apMethod[apMethod_max].pGetAttachedSurface = (GetAttachedSurface_Type)tmp;
        tmp = SetHook((void *)(*(DWORD *)lpDDS + 0x50), extGetPalette);
	    if(tmp) apMethod[apMethod_max].pGetPalette = (GetPalette_Type)tmp;
        tmp = SetHook((void *)(*(DWORD *)lpDDS + 0x54), extGetPixelFormat);
	    if(tmp) apMethod[apMethod_max].pGetPixelFormat = (GetPixelFormat_Type)tmp;
        tmp = SetHook((void *)(*(DWORD *)lpDDS + 0x7C), extSetPalette);
	    if(tmp) apMethod[apMethod_max].pSetPalette = (SetPalette_Type)tmp;
    }
}


void HookDDPaletteMethods(LPDIRECTDRAWPALETTE lpDDP)
{
    void *tmp;

    apMethod_max++;
    apMethod[apMethod_max].lpdd = (LPDIRECTDRAW)(*(DWORD *)lpDDP);

    apMethod[apMethod_max].Version = 0;

    tmp = SetHook((void *)(*(DWORD *)lpDDP + 0x18), extSetEntries);
	if(tmp) apMethod[apMethod_max].pSetEntries = (SetEntries_Type)tmp;
}


int HookDirectDraw()
{
    static hooked = 0;
    DirectDrawCreate_Type pDirectDrawCreate = 0;
    int res;
	DDSURFACEDESC ddsd;
    LPDIRECTDRAW lpDD, lpDD2, lpDD4, lpDD7;
    LPDIRECTDRAWSURFACE lpDDS, lpDDS2, lpDDS3, lpDDS4, lpDDS7;

    LPDIRECTDRAWPALETTE lpDDP;
    DWORD colourtable[2] = {0, 1};

    // calculate number of ticks per frame for speed adjustment
    if(dwFlags & LIMITFPS){
        QueryPerformanceFrequency(&QPfrequency);
        next_ticks = (long int)((float)QPfrequency.QuadPart / (float)FPSLimitVal);
        QPcounter_curr.QuadPart = 0;
        QPcounter_start.QuadPart = 0;
        //OutTrace("*** DXWND: next_ticks = %d FPSLimitVal = %d\n", next_ticks, FPSLimitVal);
    }
    
    // Hook all known DirectDraw, DirectDrawSurface and DirectDrawPalette interfaces 
    if(!hooked){

        // Load ddraw.dll beforehand (or get handle in case it was already loaded
        // via imports). If game loads dll later via LoadLibrary it should just get handle.
        // NOTE: DirectDrawCreateEx is used to create IID_IDirectDraw7 only.
        // Assume that interfaces are the same
        res = (DWORD)LoadLibraryA("ddraw.dll");

        // Create test device
        pDirectDrawCreate = 
            (DirectDrawCreate_Type)GetProcAddress(GetModuleHandle("ddraw.dll"),
                                                  "DirectDrawCreate");
        (*pDirectDrawCreate)(NULL, &lpDD, NULL);
        lpDD->SetCooperativeLevel(NULL, DDSCL_NORMAL); 
        
        // Get default values (for games, that starts in windowed mode)
        // (Atripolis 2097 need this but X-COM: Interceptor don't)
        memset(&ddsd, 0, sizeof(ddsd));
	    ddsd.dwSize = sizeof(ddsd);
	    ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
        lpDD->GetDisplayMode(&ddsd);

        dwWidth = ddsd.dwWidth;
        dwHeight = ddsd.dwHeight;
        dwBPP = ddsd.ddpfPixelFormat.dwRGBBitCount;

        // Hook DirectDrawPalette interface
        lpDD->CreatePalette(DDPCAPS_1BIT, (LPPALETTEENTRY)colourtable, &lpDDP, NULL);
        HookDDPaletteMethods(lpDDP);
        lpDDP->Release();

        // Hook DirectDrawSurface interfaces
        memset(&ddsd, 0, sizeof(ddsd));
	    ddsd.dwSize = sizeof(ddsd);
	    ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
        ddsd.dwWidth = 100;
        ddsd.dwHeight = 100;
	    ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;
	    res = lpDD->CreateSurface(&ddsd, &lpDDS, NULL);

        lpDDS->QueryInterface(IID_IDirectDrawSurface2, (LPVOID*)&lpDDS2);
        lpDDS->QueryInterface(IID_IDirectDrawSurface3, (LPVOID*)&lpDDS3);
        lpDDS->QueryInterface(IID_IDirectDrawSurface4, (LPVOID*)&lpDDS4);
        lpDDS->QueryInterface(IID_IDirectDrawSurface7, (LPVOID*)&lpDDS7);

        HookDDSurfaceMethods(lpDDS, 1);
        HookDDSurfaceMethods(lpDDS2, 2);
        HookDDSurfaceMethods(lpDDS3, 3);
        HookDDSurfaceMethods(lpDDS4, 4);
        HookDDSurfaceMethods(lpDDS7, 7);

        lpDDS->Release();
        lpDDS2->Release();
        lpDDS3->Release();
        lpDDS4->Release();
        lpDDS7->Release();
        lpDD->Release();


        // Hook DirectDraw interfaces
        (*pDirectDrawCreate)(NULL, &lpDD, NULL);
        lpDD->QueryInterface(IID_IDirectDraw2, (LPVOID*)&lpDD2);
        lpDD->QueryInterface(IID_IDirectDraw4, (LPVOID*)&lpDD4);
        lpDD->QueryInterface(IID_IDirectDraw7, (LPVOID*)&lpDD7);

        HookDDMethods(lpDD, 1, extSetDisplayMode1);
        HookDDMethods(lpDD2, 2, extSetDisplayMode);
        HookDDMethods(lpDD4, 4, extSetDisplayMode);
        HookDDMethods(lpDD7, 7, extSetDisplayMode);

        lpDD->Release();
        lpDD2->Release();
        lpDD4->Release();
        lpDD7->Release();

        hooked = 1;
    }

	return 0;
}


HRESULT WINAPI extQueryInterfaceD(void *lpdd, REFIID riid, LPVOID *obp)
{
	QueryInterface_Type pQueryInterfaceD;
    HRESULT res;
    int ver;
    int i;
    
    // find method's pointers for current interface
    for(i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdd) == (int)apMethod[i].lpdd){
            pQueryInterfaceD = apMethod[i].pQueryInterfaceD;
            break;
        }

    // 0 means unknown interface
    // 1x means D3D interface
	switch(riid.Data1){
        case 0x6C14DB80:
            ver = 1;
            break;
	    case 0xB3A6F3E0:		// IID_IDirectDraw2 (ddraw.h)
		    ver = 2;
            break;
        case 0x9c59509a:
		    ver = 4;
            break;
        case 0x15e65ec0:
            ver = 7;
            break;

        case 0x3BBA0080:        // IID_IDirect3D (d3d.h)
            ver = 11;
            break;
        case 0x6aae1ec1:        // IID_IDirect3D2
            ver = 12;
            break;
        case 0xbb223240:        // IID_IDirect3D3
            ver = 13;
            break;
        case 0xf5049e77:        // IID_IDirect3D7
            ver = 17;
            break;
        default:
            ver = 0;
    }

    OutTrace("lpDD->QueryInterfaceD: lpDD = %x REFIID = %s%d ",
        lpdd,
        (ver < 10) ? "IID_IDirectDraw" : "IID_IDirect3D",
        (ver < 10) ? ver : ver - 10);

    res = (*pQueryInterfaceD)(lpdd, riid, obp);
    OutTrace(" (%s obp = %x)\n", DDError2Str(res), *obp);
	return res;
}


HRESULT WINAPI extQueryInterfaceS(void *lpdds, REFIID riid, LPVOID *obp)
{
    QueryInterface_Type pQueryInterfaceS;
	HRESULT res;
    int ver;

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdds) == (int)apMethod[i].lpdd){
	        pQueryInterfaceS = apMethod[i].pQueryInterfaceS;
            break;
        }
    
    switch(riid.Data1){
        case 0x6C14DB81:
            ver = 1;
            break;
        case 0x57805885:        // IID_IDirectDrawSurface2
            ver = 2;
            break;
        case 0xDA044E00:
            ver = 3;
            break;
        case 0x0B2B8630:
            ver = 4;
            break;
        case 0x06675a80:
            ver = 7;
            break;

        case 0x2CDCD9E0:        // IID_IDirect3DTexture
            ver = 11;
            break;
        case 0x93281502:        // IID_IDirect3DTexture2
            ver = 12;
            break;
        default:
            ver = 0;
    }
	
    OutTrace("lpDDS->QueryInterfaceS: lpdds = %x REFIID = %s%d ",
		lpdds,
        (ver < 10) ? "IID_IDirectDrawSurface" : "IID_IDirect3DTexture",
        (ver < 10) ? ver : ver - 10);

    res = (*pQueryInterfaceS)(lpdds, riid, obp);
    if(!(dwFlags & HOOKDD))
        return res;

   	if(lpdds == lpDDSPrim){                         // Barrage, UBIK uses new interfaces
    	lpDDSPrimQ = (LPDIRECTDRAWSURFACE)*obp;     // S.C.A.R.S. asks new interface
        OutTrace (" lpDDSPrimQ is valid now");      // but uses old!
	}

   	if(lpdds == lpDDSPrimQ)
    	OutTrace ("\nWARNING: New interface for Primary Surface was queried more than once!\n");

    OutTrace(" (%s obp = %x)\n", DDError2Str(res), *obp);
	return res;
}


HRESULT WINAPI extGetDisplayMode(LPDIRECTDRAW lpdd, LPDDSURFACEDESC lpddsd)
{
    GetDisplayMode_Type pGetDisplayMode;
    HRESULT res;

    OutTrace("GetDisplayMode");

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdd) == (int)apMethod[i].lpdd){
            pGetDisplayMode = apMethod[i].pGetDisplayMode;
            break;
        }

    res = (*pGetDisplayMode)(lpdd, lpddsd);
    if(!(dwFlags & HOOKDD))
        return res;

	lpddsd->dwWidth = dwWidth;
	lpddsd->dwHeight = dwHeight;

    if(dwFlags & USEGDI){
        lpddsd->dwFlags |= DDSD_PIXELFORMAT;
    	lpddsd->ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	    lpddsd->ddpfPixelFormat.dwFlags |= DDPF_RGB;
    	lpddsd->ddpfPixelFormat.dwRGBBitCount = dwBPP;
    }   // need to set RGBA masks here?

    OutTrace(" (%s)\n", DDError2Str(res));
	return res;
}


HRESULT WINAPI extSetDisplayMode1(LPDIRECTDRAW lpdd,
	DWORD dwwidth, DWORD dwheight, DWORD dwbpp)
{
    SetDisplayMode1_Type pSetDisplayMode;
    GetDisplayMode_Type pGetDisplayMode;
	DDSURFACEDESC ddsd;
	HRESULT res = 0;
    int Version;


    OutTrace("SetDisplayMode1: dwWidth = %i dwHeight = %i dwBPP = %i",
		dwwidth, dwheight, dwbpp);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdd) == (int)apMethod[i].lpdd){
            pSetDisplayMode = (SetDisplayMode1_Type)apMethod[i].pSetDisplayMode;
            pGetDisplayMode = apMethod[i].pGetDisplayMode;
            Version = apMethod[i].Version;
            break;
        }


    if(!(dwFlags & HOOKDD))
        return (*pSetDisplayMode)(lpdd, dwwidth, dwheight, dwbpp);

    dwWidth = dwwidth;
	dwHeight = dwheight;
    dwBPP = dwbpp;

    if(FullScreen_Auto){
        ResX = dwwidth;
        ResY = dwheight;
    }

    SetDXWndMode(0);

    if(hWnd) AdjustWindowFrame(hWnd, dwwidth, dwheight);
    
    if(dwFlags & USEGDI){
        OutTrace(" (default 0)\n");
	    return 0;
    }

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = (Version < 4) ? sizeof(DDSURFACEDESC) : sizeof(DDSURFACEDESC2);
	ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
	ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	ddsd.ddpfPixelFormat.dwFlags = DDPF_RGB;
    (*pGetDisplayMode)(lpdd, (LPDDSURFACEDESC)&ddsd);

    if(ddsd.ddpfPixelFormat.dwRGBBitCount != dwbpp){
		res = (*pSetDisplayMode)(lpdd, ddsd.dwWidth, ddsd.dwHeight, dwbpp);
        OutTrace(" (%s)\n", DDError2Str(res));
	    return res;
    }

    OutTrace(" (default 0)\n");
	return 0;
}


HRESULT WINAPI extSetDisplayMode(LPDIRECTDRAW lpdd,
	DWORD dwwidth, DWORD dwheight, DWORD dwbpp, DWORD dwrefreshrate, DWORD dwflags)
{
    SetDisplayMode_Type pSetDisplayMode;
    GetDisplayMode_Type pGetDisplayMode;
    DDSURFACEDESC2 ddsd;
    HRESULT res = 0;
    int Version;


    OutTrace("SetDisplayMode: dwWidth = %i dwHeight = %i dwBPP = %i dwRefresh = %i dwFlags = %x",
        dwwidth, dwheight, dwbpp, dwrefreshrate, dwflags);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdd) == (int)apMethod[i].lpdd){
            pSetDisplayMode = apMethod[i].pSetDisplayMode;
            pGetDisplayMode = apMethod[i].pGetDisplayMode;
            Version = apMethod[i].Version;
            break;
        }

    if(!(dwFlags & HOOKDD))
        return (*pSetDisplayMode)(lpdd, dwwidth, dwheight, dwbpp, dwrefreshrate, dwflags);

    dwWidth = dwwidth;
	dwHeight = dwheight;
    dwBPP = dwbpp;

    if(FullScreen_Auto){
        ResX = dwwidth;
        ResY = dwheight;
        RefreshRate = dwrefreshrate;
    }

    SetDXWndMode(1);
    
    if(hWnd) AdjustWindowFrame(hWnd, dwwidth, dwheight);
    
    if(dwFlags & USEGDI){
        OutTrace(" (default 0)\n");
        return 0;
    }

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = (Version < 4) ? sizeof(DDSURFACEDESC) : sizeof(DDSURFACEDESC2);
	ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT | DDSD_REFRESHRATE;
	ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	ddsd.ddpfPixelFormat.dwFlags = DDPF_RGB;
	(*pGetDisplayMode)(lpdd, (LPDDSURFACEDESC)&ddsd);

    if(ddsd.ddpfPixelFormat.dwRGBBitCount != dwbpp){
        res =  (*pSetDisplayMode)(lpdd, ddsd.dwWidth, ddsd.dwHeight, dwbpp, ddsd.dwRefreshRate, 0);
        OutTrace(" (%s)\n", DDError2Str(res));
	    return res;
    }

    OutTrace(" (default 0)\n");
    return 0;
}


HRESULT WINAPI extSetCooperativeLevel(LPDIRECTDRAW lpdd, HWND hwnd, DWORD dwflags)
{
    SetCooperativeLevel_Type pSetCooperativeLevel;
	hWnd = hwnd;
    HRESULT res;

	OutTrace("SetCooperativeLevel: hwnd = %x dwFlags = %x", hwnd, dwflags);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdd) == (int)apMethod[i].lpdd){
            pSetCooperativeLevel = apMethod[i].pSetCooperativeLevel;
            break;
        }

    if(!(dwFlags & HOOKDD))
        return (*pSetCooperativeLevel)(lpdd, hwnd, dwflags);

	if(dwWidth) AdjustWindowFrame(hwnd, dwWidth, dwHeight);

    res =  (*pSetCooperativeLevel)(lpdd, hwnd, DDSCL_NORMAL);
    OutTrace(" (%s)\n", DDError2Str(res));
    return res;
}


HRESULT WINAPI extCreateSurface(LPDIRECTDRAW lpdd, DDSURFACEDESC2 *lpddsd,
	LPDIRECTDRAWSURFACE *lplpdds, void *pu)
{
    CreateSurface_Type pCreateSurface;
    SetClipper_Type pSetClipper;
	HRESULT res;
	DDSURFACEDESC2 ddsd;
    LPDIRECTDRAWCLIPPER lpDDC;

	OutTrace("CreateSurface: lpDD = %x Flags = %x Width = %i Height = %i Caps = %x",
		lpdd, lpddsd->dwFlags, lpddsd->dwWidth, lpddsd->dwHeight, lpddsd->ddsCaps.dwCaps);

    if(lpddsd->dwFlags & DDSD_BACKBUFFERCOUNT)
        OutTrace(" dwBackBufferCount = %i", lpddsd->dwBackBufferCount);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdd) == (int)apMethod[i].lpdd){
            pCreateSurface = apMethod[i].pCreateSurface;
            break;
        }
    
    if(!(dwFlags & HOOKDD)){
        res = (*pCreateSurface)(lpdd, lpddsd, lplpdds, pu);
        if(lpddsd->ddsCaps.dwCaps & DDSCAPS_PRIMARYSURFACE)
            lpDDSPrim = *lplpdds;
        return res;
    }

    memcpy(&ddsd, lpddsd, lpddsd->dwSize);          // original lpddsd remains untouched

    // zbuffer dimensions must be equal to backbuffer's one
    // Also hardware zbuffer (in videomemory) can't be attached to software backbuffer
    if(lpddsd->ddsCaps.dwCaps & DDSCAPS_ZBUFFER){
			ddsd.dwFlags |= DDSD_WIDTH | DDSD_HEIGHT;

        OutTrace(" ZBufferBitDepth = %i", ((DDSURFACEDESC*)lpddsd)->dwZBufferBitDepth);

        if(dwFlags & SYSTEMMEMORY){
            ddsd.ddsCaps.dwCaps &= ~DDSCAPS_VIDEOMEMORY;
            ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
        }
        if(dwFlags & VIDEOMEMORY){
            ddsd.ddsCaps.dwCaps &= ~DDSCAPS_SYSTEMMEMORY;
            ddsd.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;
        } // if (dwFlags & AUTOMEMORY) - don't change caps
        ddsd.dwWidth = dwWidth;
        ddsd.dwHeight = dwHeight;
        res = (*pCreateSurface)(lpdd, &ddsd, lplpdds, 0);
        OutTrace(" (%s surface = %x)\n", DDError2Str(res), *lplpdds);
        return res;
    }


    // Havoc doesn't set ddsd.dwFlags properly
	//if((ddsd.dwFlags & DDSD_CAPS) && (ddsd.ddsCaps.dwCaps & DDSCAPS_PRIMARYSURFACE)){
    if(lpddsd->ddsCaps.dwCaps & DDSCAPS_PRIMARYSURFACE){
        
        // First create offscreen surfaces that are passed to game
        // In general we need offscreen surfaces in system memory
        // But Ubik requires DDSCAPS_VIDEOMEMORY (while Tunguska - only DDSCAPS_SYSTEMMEMORY)
        ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
        ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

        if((dwFlags & SYSTEMMEMORY) ||
            ((dwFlags & AUTOMEMORY) && (lpddsd->ddsCaps.dwCaps & DDSCAPS_SYSTEMMEMORY)))
            ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
        if((dwFlags & VIDEOMEMORY) ||
            ((dwFlags & AUTOMEMORY) && (lpddsd->ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY)))
            ddsd.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;

        // Add 3DDEVICE flag if necessary
        if(lpddsd->ddsCaps.dwCaps & DDSCAPS_3DDEVICE)
            ddsd.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;

        if(lpddsd->dwFlags & DDSD_BACKBUFFERCOUNT){
            ddsd.dwFlags |= DDSD_BACKBUFFERCOUNT;
            if(lpddsd->ddsCaps.dwCaps & DDSCAPS_COMPLEX)
                ddsd.ddsCaps.dwCaps |= DDSCAPS_COMPLEX;
            if(lpddsd->ddsCaps.dwCaps & DDSCAPS_FLIP)
                ddsd.ddsCaps.dwCaps |= DDSCAPS_FLIP;
        }

        ddsd.dwWidth = dwWidth;
        ddsd.dwHeight = dwHeight;

        if(dwFlags & USEGDI){                                   // set bit depth of surface,
            ddsd.dwFlags |= DDSD_PIXELFORMAT;                   // since video mode is not switched
            ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
            ddsd.ddpfPixelFormat.dwFlags = DDPF_RGB;
            ddsd.ddpfPixelFormat.dwRGBBitCount = dwBPP;
            if(dwBPP == 8)
                ddsd.ddpfPixelFormat.dwFlags |= DDPF_PALETTEINDEXED8;
            else if(dwBPP == 16){                               // Andretti Racing needs this
                 ddsd.ddpfPixelFormat.dwRBitMask = 0x0000F800;  // Also exists other masks
                 ddsd.ddpfPixelFormat.dwGBitMask = 0x000007E0;  // for each bit depth
                 ddsd.ddpfPixelFormat.dwBBitMask = 0x0000001F;
            }
            else if(dwBPP == 24){
                 ddsd.ddpfPixelFormat.dwRBitMask = 0x00FF0000;
                 ddsd.ddpfPixelFormat.dwGBitMask = 0x0000FF00;
                 ddsd.ddpfPixelFormat.dwBBitMask = 0x000000FF;
            }
            else if(dwBPP == 32){
                 ddsd.ddpfPixelFormat.dwRBitMask = 0x00FF0000;
                 ddsd.ddpfPixelFormat.dwGBitMask = 0x0000FF00;
                 ddsd.ddpfPixelFormat.dwBBitMask = 0x000000FF;
                 ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0x00000000;
            }
        }

        res = (*pCreateSurface)(lpdd, &ddsd, lplpdds, 0);

        lpDDSPrim = *lplpdds;
        lpDDSPrimQ = 0;

        if(res != DD_OK){
            OutTrace(" ERROR: lpDDSPrim (%s): Flags = %x Width = %i Height = %i Caps = %x BackBufferCount = %i\n",
                    DDError2Str(res), ddsd.dwFlags, ddsd.dwWidth, ddsd.dwHeight, ddsd.ddsCaps.dwCaps, ddsd.dwBackBufferCount);   
            return res;
        }

        // Create actual (dxwnd's) surfaces
        // NOTE: lpDDSEmu_Prim takes whole screen
        // while dimensions of lpDDSEmu_Back is dwWidth x dwHeight

        // Release actual primary and back buffers 
        // if they were already created and was not "lost"
        // (Barrage switches resolution and primary surface is freed
        // in ddraw.dll) - *(int*)lpDDSEmu_Prim doesn't point to interface)
        if(Emu_Surfaces_Created){
            if(*(int*)lpDDSEmu_Prim == lpDDSEmu_PrimSave)
                lpDDSEmu_Prim->Release();

            if(*(int*)lpDDSEmu_Back == lpDDSEmu_BackSave)
                lpDDSEmu_Back->Release(); // Barrage!
        }

        ddsd.dwFlags = DDSD_CAPS;
        ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
        (*pCreateSurface)(lpdd, &ddsd, &lpDDSEmu_Prim, 0);

        for(int i = 0; i <= apMethod_max; i++)
            if(*((int*)lpDDSEmu_Prim) == (int)apMethod[i].lpdd){
                pSetClipper = apMethod[i].pSetClipper;
                break;
            }

        // Set clipper to perform blitting only to client area of a window
        lpdd->CreateClipper(0, &lpDDC, NULL);
        lpDDC->SetHWnd(0, hWnd);
        (*pSetClipper)(lpDDSEmu_Prim, lpDDC);

        ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
        ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
        ddsd.dwWidth = dwWidth;
        ddsd.dwHeight = dwHeight;
        (*pCreateSurface)(lpdd, &ddsd, &lpDDSEmu_Back, 0);

        lpDDSEmu_PrimSave = *(int*)lpDDSEmu_Prim;
        lpDDSEmu_BackSave = *(int*)lpDDSEmu_Back;
        Emu_Surfaces_Created = 1;

        OutTrace("\n*** DXWND: lpDDSPrim = %x lpDDSEmu_Prim = %x lpDDSEmu_Back = %x\n", \
            lpDDSPrim, lpDDSEmu_Prim, lpDDSEmu_Back);
        
        OutTrace(" (default 0)\n");
		return 0;
	} // if(ddsd.dwFlags & ... DDSCAPS_PRIMARYSURFACE ...


    if((dwFlags & USEGDI) && !(ddsd.dwFlags & DDSD_PIXELFORMAT) &&
        !(ddsd.ddsCaps.dwCaps & DDSCAPS_3DDEVICE) &&        
        (ddsd.dwFlags & DDSD_WIDTH) && (ddsd.dwFlags & DDSD_HEIGHT)){ // this should leave
                                                            // surfaces with DDSCAPS_RESERVED2,
                                                            // DDSCAPS_LIVEVIDEO  untouched
        //!(ddsd.ddsCaps.dwCaps & DDSCAPS_RESERVED2)){      // Tom Clancy's SSN
        ddsd.ddsCaps.dwCaps |= DDSCAPS_OFFSCREENPLAIN;
		ddsd.dwFlags |= DDSD_PIXELFORMAT;
		ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
        ddsd.ddpfPixelFormat.dwFlags = DDPF_RGB;
        ddsd.ddpfPixelFormat.dwRGBBitCount = dwBPP;
        if(dwBPP == 8)
            ddsd.ddpfPixelFormat.dwFlags |= DDPF_PALETTEINDEXED8;
        else if(dwBPP == 16){
             ddsd.ddpfPixelFormat.dwRBitMask = 0x0000F800;
             ddsd.ddpfPixelFormat.dwGBitMask = 0x000007E0;
             ddsd.ddpfPixelFormat.dwBBitMask = 0x0000001F;
        }
        else if(dwBPP == 24){
             ddsd.ddpfPixelFormat.dwRBitMask = 0x00FF0000;
             ddsd.ddpfPixelFormat.dwGBitMask = 0x0000FF00;
             ddsd.ddpfPixelFormat.dwBBitMask = 0x000000FF;
        }
        else if(dwBPP == 32){
             ddsd.ddpfPixelFormat.dwRBitMask = 0x00FF0000;
             ddsd.ddpfPixelFormat.dwGBitMask = 0x0000FF00;
             ddsd.ddpfPixelFormat.dwBBitMask = 0x000000FF;
             ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0x00000000;
        }
        //Need_ColourConversion = 1;
		res = (*pCreateSurface)(lpdd, &ddsd, lplpdds, 0);
		OutTrace(" EmuSub Return (%s surface = %x)\n", DDError2Str(res), *lplpdds);
		return res;
	}

    // So, it can be safely set to 0
	res = (*pCreateSurface)(lpdd, lpddsd, lplpdds, pu);
    OutTrace(" (%s surface = %x)\n", DDError2Str(res), *lplpdds);
	return res;
}


HRESULT WINAPI extBlt(LPDIRECTDRAWSURFACE lpdds, LPRECT lpdestrect,
	LPDIRECTDRAWSURFACE lpddssrc, LPRECT lpsrcrect, DWORD dwflags, LPDDBLTFX lpddbltfx)
{
    Blt_Type pBlt;
    HRESULT res;

	OutTrace("Blt: dest = %x src = %x dwFlags = %x",
		lpdds, lpddssrc, dwflags);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdds) == (int)apMethod[i].lpdd){
            pBlt = apMethod[i].pBlt;
            break;
        }

    res = (*pBlt)(lpdds, lpdestrect, lpddssrc, lpsrcrect, dwflags, lpddbltfx);

    if((lpdds == lpDDSPrim) || (lpdds == lpDDSPrimQ)){
        if(!(dwFlags & HOOKDD)){
            LimitFPS();
            return res;
        }

        OutTrace(" (Primary Surface)");
        PrimaryBlt(lpdds); 
    }

    OutTrace(" (%s)\n", DDError2Str(res));
    return 0;
}


HRESULT WINAPI extBltFast(LPDIRECTDRAWSURFACE lpdds, DWORD dwx, DWORD dwy, 
	LPDIRECTDRAWSURFACE lpddssrc, LPRECT lpsrcrect, DWORD dwtrans)
{
	RECT r;
	POINT p = {0, 0};
	DWORD flags = 0;
	DDSURFACEDESC2 ddsd;
    BltFast_Type pBltFast;
    GetSurfaceDesc_Type pGetSurfaceDesc;
    int Version;
    int i;

	OutTrace("BltFast: dest = %x src = %x dwTrans = %x (default 0 - passed to Blt)\n",
		lpdds, lpddssrc, dwtrans);

    for(i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdds) == (int)apMethod[i].lpdd){
            pBltFast = apMethod[i].pBltFast;
            break;
        }

    for(i = 0; i <= apMethod_max; i++)
        if(*((int*)lpddssrc) == (int)apMethod[i].lpdd){
            pBltFast = apMethod[i].pBltFast;
            Version = apMethod[i].Version;
            pGetSurfaceDesc = apMethod[i].pGetSurfaceDesc;
            break;
        }

    if(!(dwFlags & HOOKDD)){
        if((lpdds == lpDDSPrim) || (lpdds == lpDDSPrimQ))
            LimitFPS();
        return (*pBltFast)(lpdds, dwx, dwy, lpddssrc, lpsrcrect, dwtrans);
    }

	if(dwtrans & DDBLTFAST_WAIT) flags |= DDBLT_WAIT;
	if(dwtrans & DDBLTFAST_DESTCOLORKEY) flags |= DDBLT_KEYDEST;
	if(dwtrans & DDBLTFAST_SRCCOLORKEY) flags |= DDBLT_KEYSRC;

	r.left = dwx;
	r.top = dwy;
	if(lpsrcrect){
		r.right = r.left + lpsrcrect->right - lpsrcrect->left;
		r.bottom = r.top + lpsrcrect->bottom - lpsrcrect->top;
	}
	else{
		ddsd.dwSize = (Version < 4) ? sizeof(DDSURFACEDESC) : sizeof(DDSURFACEDESC2);
		ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT;    // Help says it's not required ?
		(*pGetSurfaceDesc)(lpddssrc, (LPDDSURFACEDESC)&ddsd);
		r.right = r.left + ddsd.dwWidth;
		r.bottom = r.top + ddsd.dwHeight;
	}
	return lpdds->Blt(&r, lpddssrc, lpsrcrect, flags, 0);
}


HRESULT WINAPI extFlip(LPDIRECTDRAWSURFACE lpdds, LPDIRECTDRAWSURFACE lpddst, DWORD dwflags)
{
    HRESULT res;
    Flip_Type pFlip;

    OutTrace("Flip: target = %x src = %x dwFlags = %x", lpdds, lpddst, dwflags);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdds) == (int)apMethod[i].lpdd){
            pFlip = apMethod[i].pFlip;
            break;
        }

    res = (*pFlip)(lpdds, lpddst, dwflags);

    if((lpdds == lpDDSPrim) || (lpdds == lpDDSPrimQ)){

        if(!(dwFlags & HOOKDD)){
            LimitFPS();
            return res;
        }

        OutTrace(" (Primary Surface)");
        PrimaryBlt(lpdds);
        res = DD_OK;
    }

    OutTrace(" (%s)\n", DDError2Str(res));
    return res;

}


HRESULT WINAPI extWaitForVerticalBlank(LPDIRECTDRAW lpdd, DWORD dwflags, HANDLE hevent)
{
	static DWORD time = 0;
	static BOOL step = 0;

    WaitForVerticalBlank_Type pWaitForVerticalBlank;

    OutTrace(" WaitForVerticalBlank: dwFlags = %x\n", dwflags);
    
    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdd) == (int)apMethod[i].lpdd){
            pWaitForVerticalBlank = apMethod[i].pWaitForVerticalBlank;
            break;
        }

    return (*pWaitForVerticalBlank)(lpdd, dwflags, hevent);
}


HRESULT WINAPI extSetClipper(LPDIRECTDRAWSURFACE lpdds, LPDIRECTDRAWCLIPPER lpddc)
{
    SetClipper_Type pSetClipper;
    HRESULT res;

    OutTrace("SetClipper: surface = %x", lpdds);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdds) == (int)apMethod[i].lpdd){
            pSetClipper = apMethod[i].pSetClipper;
            break;
        }

	res = (*pSetClipper)(lpdds, lpddc);
    OutTrace(" (%s)\n", DDError2Str(res));
    return res;
}


HRESULT WINAPI extLock(LPDIRECTDRAWSURFACE lpdds, LPRECT rect, LPDDSURFACEDESC ddsd,
                       DWORD dwflags, HANDLE hevent)
{
    Lock_Type pLock;
    HRESULT res;

    OutTrace("Lock: lpdds = %x rect = %x Flags = %x", lpdds, rect, dwflags);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdds) == (int)apMethod[i].lpdd){
            pLock = apMethod[i].pLock;
            break;
        }

    if((lpdds == lpDDSPrim) || (lpdds == lpDDSPrimQ))
        OutTrace(" (Primary Surface)");

	res = (*pLock)(lpdds, rect, ddsd, dwflags, hevent);
    OutTrace(" (%s)\n", DDError2Str(res));
    return res;
}


HRESULT WINAPI extUnLock(LPDIRECTDRAWSURFACE lpdds, LPRECT rect)
{
    UnLock_Type pUnLock;
    HRESULT res;

    OutTrace("UnLock: lpdds = %x rect = %x", lpdds, rect);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdds) == (int)apMethod[i].lpdd){
            pUnLock = apMethod[i].pUnLock;
            break;
        }

    res = (*pUnLock)(lpdds, rect);

    // Primary surface was locked
    // So it must have been changed. Blit it.
    if((lpdds == lpDDSPrim) || (lpdds == lpDDSPrimQ)){

        if(!(dwFlags & HOOKDD)){
            LimitFPS();
            return res;
        }

        OutTrace(" (Primary Surface)");
        PrimaryBlt(lpdds);
    }

    OutTrace(" (%s)\n", DDError2Str(res));
    return res;
}


HRESULT WINAPI extSetEntries(LPDIRECTDRAWPALETTE lpddp, DWORD dwflags, DWORD dwstart, DWORD dwcount, LPPALETTEENTRY lpentries)
{
	HRESULT res;
    LPDIRECTDRAWSURFACE lpdds;
    SetEntries_Type pSetEntries;


	OutTrace("SetEntries: Flags = %x StartingEntry = %i Count = %i lpEntries = %x",
        dwflags, dwstart, dwcount, lpentries);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpddp) == (int)apMethod[i].lpdd){
            pSetEntries = apMethod[i].pSetEntries;
            break;
        }

	res = (*pSetEntries)(lpddp, dwflags, dwstart, dwcount, lpentries);

    // NOTE: Limit FPS and blit primary surface
    // for any palette change, not only for primary surface's palette (Havoc)
    if(!(dwFlags & HOOKDD)){
        LimitFPS();
        return res;
    }

    // Which surface to blit: lpDDSPrim or lpDDSPrimQ?
    // (NOTE: S.C.A.R.S. asks new interface but uses old)
    lpdds = (lpDDSPrimQ != 0) ? lpDDSPrimQ : lpDDSPrim;
    PrimaryBlt(lpdds);
    
    OutTrace(" (%s)\n", DDError2Str(res));
	return res;
}

/*----------------------------------------------------------------------------

  Methods below are not used, but can give additional debug information
  if EXTENDED_LOG was enabled

----------------------------------------------------------------------------*/

HRESULT WINAPI extGetAttachedSurface(void *lpdds, LPDDSCAPS lpddsc, 
	LPDIRECTDRAWSURFACE *lplpddas)
{
    GetAttachedSurface_Type pGetAttachedSurface;
    HRESULT res;

    OutTrace("GetAttachedSurface: lpdds = %x Caps = %x", lpdds, lpddsc->dwCaps);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdds) == (int)apMethod[i].lpdd){
            pGetAttachedSurface = apMethod[i].pGetAttachedSurface;
            break;
        }

    if((lpdds == lpDDSPrim) || (lpdds == lpDDSPrimQ))
		OutTrace(" (Backbuffer)");

	res = (*pGetAttachedSurface)(lpdds, lpddsc, lplpddas);
    OutTrace(" (%s lplpddas = %x)\n", DDError2Str(res), *lplpddas);
    return res;
}


HRESULT WINAPI extAddAttachedSurface(LPDIRECTDRAWSURFACE lpdds, LPDIRECTDRAWSURFACE lpddas)
{
    AddAttachedSurface_Type pAddAttachedSurface;
    HRESULT res;

    OutTrace("AddAttachedSurface: lpdds = %x lpddas = %x", lpdds, lpddas);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdds) == (int)apMethod[i].lpdd){
            pAddAttachedSurface = apMethod[i].pAddAttachedSurface;
            break;
        }

    if((lpdds == lpDDSPrim) || (lpdds == lpDDSPrimQ))
		OutTrace(" (Backbuffer)");

    res = (*pAddAttachedSurface)(lpdds, lpddas);
    OutTrace(" (%s)\n", DDError2Str(res));
    return res;
}


HRESULT WINAPI extCreatePalette(LPDIRECTDRAW lpdd, DWORD dwflags, LPPALETTEENTRY lpddpa,
	LPDIRECTDRAWPALETTE *lplpddp, IUnknown *pu)
{
    CreatePalette_Type pCreatePalette;
    HRESULT res;
	
    OutTrace("CreatePalette: Flags = %x ColorArray = %x", dwflags, lpddpa);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdd) == (int)apMethod[i].lpdd){
            pCreatePalette = apMethod[i].pCreatePalette;
            break;
        }

	res = (*pCreatePalette)(lpdd, dwflags, lpddpa, lplpddp, pu);
    OutTrace(" (%s)\n", DDError2Str(res));    
    return res;
}


HRESULT WINAPI extGetPalette(LPDIRECTDRAWSURFACE lpdds, LPDIRECTDRAWPALETTE *lplpddp)
{

    GetPalette_Type pGetPalette;
    HRESULT res;

    OutTrace("GetPalette: surface = %x", lpdds);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdds) == (int)apMethod[i].lpdd){
            pGetPalette = apMethod[i].pGetPalette;
            break;
        }

    if((lpdds == lpDDSPrim) || (lpdds == lpDDSPrimQ))
        OutTrace(" (Primary Surface)");

    res = (*pGetPalette)(lpdds, lplpddp);
    OutTrace(" (%s)\n", DDError2Str(res));
    return res;
}


HRESULT WINAPI extSetPalette(LPDIRECTDRAWSURFACE lpdds, LPDIRECTDRAWPALETTE lpddp)
{
    SetPalette_Type pSetPalette;
	HRESULT res;

	OutTrace("SetPalette: surface = %x lpddp = %x", lpdds, lpddp);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdds) == (int)apMethod[i].lpdd){
            pSetPalette = apMethod[i].pSetPalette;
            break;
        }

    if((lpdds == lpDDSPrim) || (lpdds == lpDDSPrimQ))
        OutTrace(" (Primary Surface)");
        //(*pSetPalette)(lpDDSEmu_Prim, lpddp);     // Havoc palette fix for non-USEGDI mode

    res = (*pSetPalette)(lpdds, lpddp);
    OutTrace(" (%s)\n", DDError2Str(res));
    return res;
}


HRESULT WINAPI extGetPixelFormat(LPDIRECTDRAWSURFACE lpdds, LPDDPIXELFORMAT lpDDPixelFormat)
{
	HRESULT res;
    GetPixelFormat_Type pGetPixelFormat;

	OutTrace("GetPixelFormat: surface = %x", lpdds);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdds) == (int)apMethod[i].lpdd){
            pGetPixelFormat = apMethod[i].pGetPixelFormat;
            break;
        }

    if((lpdds == lpDDSPrim) || (lpdds == lpDDSPrimQ))
        OutTrace(" (Primary Surface)");

    res = (*pGetPixelFormat)(lpdds, lpDDPixelFormat);

    OutTrace(" (%s)\n", DDError2Str(res));
    return res;
}


HRESULT WINAPI extGetSurfaceDesc(LPDIRECTDRAWSURFACE lpdds, LPDDSURFACEDESC lpddsd)
{
    GetSurfaceDesc_Type pGetSurfaceDesc;
    HRESULT res;

    OutTrace("GetSurfaceDesc: surface = %x", lpdds);

    for(int i = 0; i <= apMethod_max; i++)
        if(*((int*)lpdds) == (int)apMethod[i].lpdd){
            pGetSurfaceDesc = apMethod[i].pGetSurfaceDesc;
            break;
        }

    if((lpdds == lpDDSPrim) || (lpdds == lpDDSPrimQ))
        OutTrace(" (Primary Surface)");

    res = (*pGetSurfaceDesc)(lpdds, lpddsd);

    OutTrace(" (%s)\n", DDError2Str(res));
    return res;
}
