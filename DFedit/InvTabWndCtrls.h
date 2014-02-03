#ifndef INVTABWNDCTRLS_H
#define INVTABWNDCTRLS_H

#include <windows.h>
#include <commctrl.h>

#include "DFGui.h"

void CreateItemsTab   (void);
void PopulateItemsTab (void);
void updateInvList    (void);

LRESULT CALLBACK ItemsTabWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif
