#include <windows.h>
#include <commctrl.h>

#include "DFGui.h"

void CreateGeneralsTab       (void);
void PopulateGeneralsTab     (void);
void ShowGenTabDivisionInfo  (const int gen, const bool show);
void setGenLocationControls  (const int gen);
int  compareOwnerGenVsCastle (const int gen);
void updateGeneralsTab       (const int gen);

LRESULT CALLBACK GenTabWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
