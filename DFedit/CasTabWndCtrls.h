#ifndef CASTABWNDCTRLS_H
#define CASTABWNDCTRLS_H

#include <windows.h>
#include <commctrl.h>

#include "DFGui.h"

void CreateCastlesTab   (void);
void PopulateCastlesTab (void);
int  findLeaderCasIndex (const int castle);
void updateCastlesTab   (const int cas);

LRESULT CALLBACK CasTabWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif
