#ifndef KINGDOMTABWNDCTRLS_H
#define KINGDOMTABWNDCTRLS_H

#include <windows.h>
#include <commctrl.h>

#include "DFGui.h"

#define GENERALS_LIST 630
#define CAPTIVES_LIST 631
#define CASTLES_LIST  632

void createStaticKingdomControls (void);
void getKingdomsStaticTextSize   (const HWND hwnd, const char* str, RECT* rect);
void CreateKingdomsTab           (void);
void updateKingdomsTab           (void);
void enableKingdomRadioControls  (void);
void showKingdomOwnedResources   (const int listToShow);

LRESULT CALLBACK KingdomTabWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif
