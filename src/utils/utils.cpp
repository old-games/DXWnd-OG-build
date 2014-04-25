#include <stdio.h>

#include "utils.h"


DDRAW_DEVICE_STRUCT g_Modes;
char g_ModeSel[MAX_MODE_LEN];

char InitPath[MAX_PATH];
TARGETMAP TargetMaps[MAXTARGETS];
int CurrTarget;

//----------------------------------------------------------------------------

void WriteINISlot(int i)
{
	char key[32], val[32];

    sprintf(key, "path%i", i);
    WritePrivateProfileString("target", key, TargetMaps[i].path, InitPath);
    sprintf(key, "ver%i", i);
    sprintf(val, "%i", TargetMaps[i].dxversion);
    WritePrivateProfileString("target", key, val, InitPath);
    sprintf(key, "flag%i", i);
    sprintf(val, "%i", TargetMaps[i].flags);
    WritePrivateProfileString("target", key, val, InitPath);
    sprintf(key, "initx%i", i);
    sprintf(val, "%i", TargetMaps[i].initx);
    WritePrivateProfileString("target", key, val, InitPath);
    sprintf(key, "inity%i", i);
    sprintf(val, "%i", TargetMaps[i].inity);
    WritePrivateProfileString("target", key, val, InitPath);
    sprintf(key, "minx%i", i);
    sprintf(val, "%i", TargetMaps[i].minx);
    WritePrivateProfileString("target", key, val, InitPath);
    sprintf(key, "miny%i", i);
    sprintf(val, "%i", TargetMaps[i].miny);
    WritePrivateProfileString("target", key, val, InitPath);
    sprintf(key, "maxx%i", i);
    sprintf(val, "%i", TargetMaps[i].maxx);
    WritePrivateProfileString("target", key, val, InitPath);
    sprintf(key, "maxy%i", i);
    sprintf(val, "%i", TargetMaps[i].maxy);
    WritePrivateProfileString("target", key, val, InitPath);
    sprintf(key, "FPSLimit%i", i);
    sprintf(val, "%i", TargetMaps[i].FPSLimit);
    WritePrivateProfileString("target", key, val, InitPath);
    sprintf(key, "Mode%i", i);
    WritePrivateProfileString("target", key, TargetMaps[i].Mode, InitPath);
}


void LoadINISlot(int i)
{
	char key[32];

    sprintf(key, "path%i", i);
    GetPrivateProfileString("target", key, "", TargetMaps[i].path, MAX_PATH, InitPath);
    if(!TargetMaps[i].path[0]) return;      // leave default values from ZeroINISlot()
    sprintf(key, "ver%i", i);
    TargetMaps[i].dxversion = GetPrivateProfileInt("target", key, 0, InitPath);
    sprintf(key, "flag%i", i);
    TargetMaps[i].flags = GetPrivateProfileInt("target", key, 0, InitPath);
    sprintf(key, "initx%i", i);
    TargetMaps[i].initx = GetPrivateProfileInt("target", key, 0, InitPath);
    sprintf(key, "inity%i", i);
    TargetMaps[i].inity = GetPrivateProfileInt("target", key, 0, InitPath);
    sprintf(key, "minx%i", i);
    TargetMaps[i].minx = GetPrivateProfileInt("target", key, 0, InitPath);
    sprintf(key, "miny%i", i);
    TargetMaps[i].miny = GetPrivateProfileInt("target", key, 0, InitPath);
    sprintf(key, "maxx%i", i);
    TargetMaps[i].maxx = GetPrivateProfileInt("target", key, 0, InitPath);
    sprintf(key, "maxy%i", i);
    TargetMaps[i].maxy = GetPrivateProfileInt("target", key, 0, InitPath);
    sprintf(key, "FPSLimit%i", i);
    TargetMaps[i].FPSLimit = GetPrivateProfileInt("target", key, 0, InitPath);
    sprintf(key, "Mode%i", i);
    GetPrivateProfileString("target", key, "", TargetMaps[i].Mode, MAX_MODE_LEN, InitPath);
    strcpy(g_ModeSel, TargetMaps[i].Mode);  // copy mode to global variable
}


void ZeroINISlot(int i)
{
	char key[32];

    sprintf(key, "path%i", i);
    WritePrivateProfileString("target", key, 0, InitPath);
    sprintf(key, "ver%i", i);
    WritePrivateProfileString("target", key, 0, InitPath);
    sprintf(key, "flag%i", i);
    WritePrivateProfileString("target", key, 0, InitPath);
    sprintf(key, "initx%i", i);
    WritePrivateProfileString("target", key, 0, InitPath);
    sprintf(key, "inity%i", i);
    WritePrivateProfileString("target", key, 0, InitPath);
    sprintf(key, "minx%i", i);
    WritePrivateProfileString("target", key, 0, InitPath);
    sprintf(key, "miny%i", i);
    WritePrivateProfileString("target", key, 0, InitPath);
    sprintf(key, "maxx%i", i);
    WritePrivateProfileString("target", key, 0, InitPath);
    sprintf(key, "maxy%i", i);
    WritePrivateProfileString("target", key, 0, InitPath);
    sprintf(key, "FPSLimit%i", i);
    WritePrivateProfileString("target", key, 0, InitPath);
    sprintf(key, "Mode%i", i);
    WritePrivateProfileString("target", key, 0, InitPath);
}


// Set default values here
void ZeroTargetMaps()
{

	for(int i = 0; i < MAXTARGETS; i++){
        TargetMaps[i].path[0] = 0;
	    TargetMaps[i].dxversion = 0;
	    TargetMaps[i].flags = SAVELOAD | AUTOMEMORY;
	    TargetMaps[i].initx = 0;
	    TargetMaps[i].inity = 0;
	    TargetMaps[i].minx = 0;
	    TargetMaps[i].miny = 0;
	    TargetMaps[i].maxx = 639;
	    TargetMaps[i].maxy = 439;
        TargetMaps[i].FPSLimit = 60;
        strcpy(TargetMaps[i].Mode, "(Auto)");
    }
}


void EnumModes()
{

    DEVMODE dm;
    DWORD iModeNum = 0;
    char s[MAX_MODE_LEN];
    unsigned int i;

    g_Modes.dwModeNum = 0;

    sprintf(g_Modes.aModeDesc[g_Modes.dwModeNum], "%s", "(Auto)");
    g_Modes.dwModeNum++;

    while(EnumDisplaySettings(0, iModeNum, &dm)){

        for(i = 0; i < g_Modes.dwModeNum; i++){
            sprintf(s, "%ux%u@%u Hz", dm.dmPelsWidth, dm.dmPelsHeight, dm.dmDisplayFrequency);
            if(!strcmpi(g_Modes.aModeDesc[i], s))
                break;
        }

        // add mode if such mode is not in list
        // and frequency != "Default" (1)
        if((i == g_Modes.dwModeNum) && (dm.dmDisplayFrequency != 1)){
            sprintf(g_Modes.aModeDesc[g_Modes.dwModeNum], "%ux%u@%u Hz",
                     dm.dmPelsWidth, dm.dmPelsHeight, dm.dmDisplayFrequency);
            g_Modes.dwModeNum++;
        }

        iModeNum++;
        
    };
}

