#define _WIN32_IE 0x0301

#include <windows.h>
#include <commctrl.h>

#include "resource.h"

#include "DFGui.h"

const TCHAR* DFeditVersion = TEXT("DFedit 2.31");

HWND hMainWindow = NULL; // main window
HWND hDlgCurrent = NULL; //for the message loop thing

HINSTANCE hThisInst = NULL;

const TCHAR g_szClassName[] = TEXT("myWindowClass");
      int  g_IsFileOpen    = 0;

int alreadyOpened = 0;

DragonForce dr;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    MSG        msg;

    hThisInst = hInstance;
    
    InitComCtls();

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENUBAR);
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, TEXT("Window Registration Failed!"), TEXT("Error!"),
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hMainWindow = CreateWindowEx(
        0,
        g_szClassName,
        TEXT("Dragon Force Edit 2.31"),
        (WS_SYSMENU | WS_MINIMIZEBOX | WS_TABSTOP) & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1024,
        768,
        NULL,
        NULL,
        hInstance,
        NULL);

    if(hMainWindow == NULL)
    {
        MessageBox(NULL, TEXT("Window Creation Failed!"), TEXT("Error!"),
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    CreateTabControl();
    CreateGeneralsTab();
    CreateCastlesTab();
    CreateDivisionsTab();
    CreateMassEditTab();

    ShowWindow(hMainWindow, nCmdShow);
    UpdateWindow(hMainWindow);

    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        if((!hDlgCurrent) || (!IsDialogMessage(hDlgCurrent, &msg))) //works if hdlgcurrent in isdialogmessage is changed to hTabGenerals
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static TCHAR szFileName[MAX_PATH];
    static TCHAR szTitleName[MAX_PATH];
    char   windowTitle[46];

    switch(msg)
    {
        case WM_CREATE:
            initializeOFNstruct(hwnd);
            break;
        case WM_ACTIVATE:
            if(wParam == 0)
                hDlgCurrent = NULL;
            else
                hDlgCurrent = hwnd;
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_FILE_OPEN:
                    if (DFMenuOpenFile(hwnd, szFileName, szTitleName))
                    {
                        DragonForce dfTemp;
                        dr = dfTemp;
                        if(dr.drFileName.c_str() != NULL)
                            if(dr.fr.fpSavegame.is_open())
                                dr.fr.closeFile();
                        dr.drFileName      = szFileName;
                        dr.fr.savefileName = szFileName;
                        dr.fw.savefileName = szFileName;
                        if (!openFileForReading())
                        {
                            MessageBox(hwnd, TEXT("Could not open file."), DFeditVersion, MB_OK | MB_ICONERROR);
                            szFileName[0]  = '\0';
                            szTitleName[0] = '\0';
                            dr.drFileName = "";
                        }
                        else
                        {
                            if(dr.fr.checkFileSize())
                            {
                                PopulateGeneralsTab();
                                PopulateCastlesTab();
                                PopulateDivisionsTab();
                                PopulateMassEditTab();
                                sprintf(windowTitle, "Dragon Force Edit 2.31 - Playing as %s", generalsNameList[dr.playingAs]);
                                SetWindowText(hMainWindow, windowTitle);
                                alreadyOpened = 1;
                            }
                            else
                                MessageBox(hwnd, TEXT("File does not appear to be a valid SSF Dragon Force savefile."), DFeditVersion, MB_OK | MB_ICONERROR);
                        }
                    }
                break;
                case ID_FILE_EXIT:
                    PostMessage(hwnd, WM_CLOSE, 0, 0);
                break;
                case ID_ABOUT:
                {
                    int ret = DialogBox(GetModuleHandle(NULL), 
                        MAKEINTRESOURCE(ID_ABOUT), hwnd, AboutDlgProc);
                    if(ret == -1)
                    {
                        MessageBox(hwnd, TEXT("Dialog failed!"), TEXT("Error"),
                            MB_OK | MB_ICONINFORMATION);
                    }
                }
                break;
            }
        break;
        case WM_NOTIFY:
        {
            // get the tab message from lParam
            LPNMHDR lpnmhdr = (LPNMHDR)lParam;

            // if we received the TCN_SELCHANGE message, process it
            // (TCN_SELCHANGE is when the selection changes from
            // one tab item to another)
            if (lpnmhdr->code == TCN_SELCHANGE)
            {
                // get the newly selected tab item
                INT nTabItem = TabCtrl_GetCurSel(hTabCntrl);

                // hide and show the appropriate tab view
                // based on which tab item was clicked
                switch (nTabItem)
                {
                    case 0:
                    {
                        int gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0); //get selected General ID

                        ShowWindow(hTabMisc, SW_HIDE);
                        ShowWindow(hTabItemInv, SW_HIDE);
                        ShowWindow(hTabMassEdit, SW_HIDE);
                        ShowWindow(hTabDivisions, SW_HIDE);
                        ShowWindow(hTabCastles, SW_HIDE);
                        ShowWindow(hTabGenerals, SW_SHOW);

                        if(alreadyOpened)
                            updateGeneralsTab(gen);

                        SetFocus(hTabCntrl);
                        return 0;
                    }
                    break;
                    case 1:
                    {
                        int cas = SendMessage(CasTabCtrls.cb_CasNameList, CB_GETCURSEL, 0, 0); //get selected castle ID

                        ShowWindow(hTabMisc, SW_HIDE);
                        ShowWindow(hTabItemInv, SW_HIDE);
                        ShowWindow(hTabMassEdit, SW_HIDE);
                        ShowWindow(hTabDivisions, SW_HIDE);
                        ShowWindow(hTabGenerals, SW_HIDE);
                        ShowWindow(hTabCastles, SW_SHOW);

                        if(alreadyOpened)
                            updateCastlesTab(cas);

                        SetFocus(hTabCntrl);
                        return 0;
                    }
                    break;
                    case 2:
                    {
                        int div = SendMessage(DivTabCtrls.cb_DivNameList, CB_GETCURSEL, 0, 0);

                        ShowWindow(hTabMisc, SW_HIDE);
                        ShowWindow(hTabItemInv, SW_HIDE);
                        ShowWindow(hTabMassEdit, SW_HIDE);
                        ShowWindow(hTabCastles, SW_HIDE);
                        ShowWindow(hTabGenerals, SW_HIDE);
                        ShowWindow(hTabDivisions, SW_SHOW);

                        if(alreadyOpened)
                            updateDivisionsTab(div);

                        SetFocus(hTabCntrl);
                        return 0;
                    }
                    break;
                    case 3:
                    {
                        ShowWindow(hTabMisc, SW_HIDE);
                        ShowWindow(hTabItemInv, SW_HIDE);
                        ShowWindow(hTabDivisions, SW_HIDE);
                        ShowWindow(hTabCastles, SW_HIDE);
                        ShowWindow(hTabGenerals, SW_HIDE);
                        ShowWindow(hTabMassEdit, SW_SHOW);

                        SetFocus(hTabCntrl);
                        return 0;
                    }
                    break;
                    default:
                        // don't do anything if the tab item isn't 0 through 3
                        break;
                }
            }
            return 0;
        }
        break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

void InitComCtls(void)
{
    INITCOMMONCONTROLSEX icce;

    icce.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icce.dwICC = ICC_TAB_CLASSES;
    InitCommonControlsEx(&icce);

    return;
}

void SetDefaultFont (HWND hwnd)
{
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), (LPARAM)true);
}

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) //for the About box
{
    switch(msg)
    {
        case WM_INITDIALOG:

        return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                break;
                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                break;
            }
        break;
        default:
            return FALSE;
    }

    return TRUE;
}
