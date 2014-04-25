// Holds code common for dxwndhost and launch

#ifndef UTILS_H
#define UTILS_H

#include "..\dxwnd.h"      // for DDRAW_DEVICE_STRUCT


extern DDRAW_DEVICE_STRUCT g_Modes;
extern char g_ModeSel[MAX_MODE_LEN];     // holds last selected mode


extern char InitPath[MAX_PATH];
extern TARGETMAP TargetMaps[MAXTARGETS];
extern int CurrTarget;                  // holds last (free) target. Must be set before calling dlg.DoModal()

void EnumModes();
void WriteINISlot(int slot);
void LoadINISlot(int slot);
void ZeroINISlot(int slot);
void ZeroTargetMaps();

#endif // UTILS_H