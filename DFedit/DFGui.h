#ifndef DFGUI_H
#define DFGUI_H

typedef unsigned short ushort;
typedef unsigned char uchar;

#include "MainTabParent.h"
#include "CasTabWndCtrls.h"
#include "DivTabWndCtrls.h"
#include "GenTabWndCtrls.h"
#include "InvTabWndCtrls.h"
#include "MassEditTabWndCtrls.h"
#include "KingdomsTabWndCtrls.h"

#include "DragonForce.h"
#include "FileMenu.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "General.h"

#include "resource.h"

extern DragonForce dr;
extern int alreadyOpened;

extern const char* DFeditVersion;
extern const char g_szClassName[];
extern       int  g_IsFileOpen;

extern HWND hMainWindow; // main window
extern HWND hDlgCurrent; //for the message loop thing
extern WNDPROC g_MainWndProc; //for saving main message loop process

extern HINSTANCE hThisInst;

void InitComCtls (void);

void    SetDefaultFont        (HWND hwnd);
BOOL    CALLBACK AboutDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc      (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif
