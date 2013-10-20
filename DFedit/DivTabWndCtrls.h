#ifndef DIVTABWNDCTRLS_H
#define DIVTABWNDCTRLS_H

#include <windows.h>
#include <commctrl.h>

#include "DFGui.h"

void CreateDivisionsTab   (void);
void PopulateDivisionsTab (void);
int  findLeaderDivIndex   (const int division);
void updateDivisionsTab   (const int div);
void updateLocalDivArr    (void);

LRESULT CALLBACK DivTabWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif
