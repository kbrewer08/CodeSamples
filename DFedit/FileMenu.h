#include <windows.h>
#include <commctrl.h>

#include "DFGui.h"

void initializeOFNstruct (HWND hwnd);
BOOL DFMenuOpenFile      (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName);
BOOL openFileForReading  (void);
