#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

#include "DFGui.h"

static OPENFILENAME ofName;

void initializeOFNstruct(HWND hwnd)
{
     static TCHAR szFilter[] = TEXT("All Files (*.*)\0*.*\0\0");
     
     ofName.lStructSize       = sizeof(OPENFILENAME);
     ofName.hwndOwner         = hwnd;
     ofName.hInstance         = NULL;
     ofName.lpstrFilter       = szFilter;
     ofName.lpstrCustomFilter = NULL;
     ofName.nMaxCustFilter    = 0;
     ofName.nFilterIndex      = 0;
     ofName.lpstrFile         = NULL;          // Set in Open and Close functions
     ofName.nMaxFile          = MAX_PATH;
     ofName.lpstrFileTitle    = NULL;          // Set in Open and Close functions
     ofName.nMaxFileTitle     = MAX_PATH;
     ofName.lpstrInitialDir   = NULL;
     ofName.lpstrTitle        = NULL;
     ofName.Flags             = 0;             // Set in Open and Close functions
     ofName.nFileOffset       = 0;
     ofName.nFileExtension    = 0;
     ofName.lpstrDefExt       = NULL;
     ofName.lCustData         = 0L;
     ofName.lpfnHook          = NULL;
     ofName.lpTemplateName    = NULL;

    return;
}

BOOL DFMenuOpenFile(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
     ofName.hwndOwner         = hwnd;
     ofName.lpstrFile         = pstrFileName;
     ofName.lpstrFileTitle    = pstrTitleName;
     ofName.Flags             = OFN_FILEMUSTEXIST;
     
     return GetOpenFileName(&ofName);
}

BOOL openFileForReading(void)
{
    return dr.fr.openFileForRead();
}
