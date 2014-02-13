#include <windows.h>
#include <commctrl.h>
#include <sstream>

#include "DFGui.h"

HWND staticRulerNames[8]   = {NULL};
HWND staticKingdomNames[8] = {NULL};
HWND staticCasCountTag[8]  = {NULL};
HWND staticGenCountTag[8]  = {NULL};
HWND staticCapCountTag[8]  = {NULL};
HWND staticWinCountTag[8]  = {NULL};
HWND staticLossCountTag[8] = {NULL};

HWND staticCasCountVal[8]  = {NULL};
HWND staticGenCountVal[8]  = {NULL};
HWND staticCapCountVal[8]  = {NULL};
HWND staticWinCountVal[8]  = {NULL};
HWND staticLossCountVal[8] = {NULL};

HWND staticGenOwnedList[8] = {NULL};
HWND staticCapOwnedList[8] = {NULL};
HWND staticCasOwnedList[8] = {NULL};

HWND ks_rbGeneralsList;
HWND ks_rbCaptivesList;
HWND ks_rbCastlesList;

static int ks_maxTagLength = 0;

void createStaticKingdomControls(void)
{
    int headerX = 10;
    for(int i = 0; i < 8; i++, headerX += 125)
    {
        RECT rect = {0};
        const char* name    = generalsNameList[i];
        const char* kingdom = castlesNameList[i];
        //controls created with zero size because this will be set later
        staticRulerNames[i] = CreateWindowEx(0, "STATIC", TEXT(name), WS_CHILD | WS_VISIBLE,
                                             headerX, 28, 0, 0,
                                             hTabKingdoms, NULL, hThisInst, NULL);
                                             
        staticKingdomNames[i] = CreateWindowEx(0, "STATIC", TEXT(kingdom), WS_CHILD | WS_VISIBLE,
                                               headerX, 43, 0, 0,
                                               hTabKingdoms, NULL, hThisInst, NULL);

        staticCasCountTag[i] = CreateWindowEx(0, "STATIC", TEXT("Castles: "), WS_CHILD | WS_VISIBLE,
                                               headerX + 10, 63, 0, 0,
                                               hTabKingdoms, NULL, hThisInst, NULL);

        staticGenCountTag[i] = CreateWindowEx(0, "STATIC", TEXT("Generals: "), WS_CHILD | WS_VISIBLE,
                                               headerX + 10, 78, 0, 0,
                                               hTabKingdoms, NULL, hThisInst, NULL);

        staticCapCountTag[i] = CreateWindowEx(0, "STATIC", TEXT("Captives: "), WS_CHILD | WS_VISIBLE,
                                               headerX + 10, 93, 0, 0,
                                               hTabKingdoms, NULL, hThisInst, NULL);

        staticWinCountTag[i] = CreateWindowEx(0, "STATIC", TEXT("Wins: "), WS_CHILD | WS_VISIBLE,
                                               headerX + 10, 108, 0, 0,
                                               hTabKingdoms, NULL, hThisInst, NULL);

        staticLossCountTag[i] = CreateWindowEx(0, "STATIC", TEXT("Losses: "), WS_CHILD | WS_VISIBLE,
                                               headerX + 10, 123, 0, 0,
                                               hTabKingdoms, NULL, hThisInst, NULL);

        //Here is where we find and set the size of the controls based
        //upon the text that is displayed in them
        getKingdomsStaticTextSize(staticRulerNames[i], generalsNameList[i], &rect);
        SetWindowPos(staticRulerNames[i], 0, headerX, 28, rect.right, rect.bottom, 0);

        getKingdomsStaticTextSize(staticKingdomNames[i], castlesNameList[i], &rect);
        SetWindowPos(staticKingdomNames[i], 0, headerX, 43, rect.right, rect.bottom, 0);

        getKingdomsStaticTextSize(staticCasCountTag[i], "Castles: ", &rect);
        SetWindowPos(staticCasCountTag[i], 0, headerX + 10, 63, rect.right, rect.bottom, 0);

        getKingdomsStaticTextSize(staticGenCountTag[i], "Generals: ", &rect);
        SetWindowPos(staticGenCountTag[i], 0, headerX + 10, 78, rect.right, rect.bottom, 0);

        getKingdomsStaticTextSize(staticCapCountTag[i], "Captives: ", &rect);
        SetWindowPos(staticCapCountTag[i], 0, headerX + 10, 93, rect.right, rect.bottom, 0);

        getKingdomsStaticTextSize(staticWinCountTag[i], "Wins: ", &rect);
        SetWindowPos(staticWinCountTag[i], 0, headerX + 10, 108, rect.right, rect.bottom, 0);

        getKingdomsStaticTextSize(staticLossCountTag[i], "Losses: ", &rect);
        SetWindowPos(staticLossCountTag[i], 0, headerX + 10, 123, rect.right, rect.bottom, 0);

//windows for actual values of each kingdom
        staticCasCountVal[i] = CreateWindowEx(0, "STATIC", TEXT(""), WS_CHILD | WS_VISIBLE,
                                               headerX + 10 + ks_maxTagLength + 5, 63, 0, 0,
                                               hTabKingdoms, NULL, hThisInst, NULL);

        staticGenCountVal[i] = CreateWindowEx(0, "STATIC", TEXT(""), WS_CHILD | WS_VISIBLE,
                                               headerX + 10 + ks_maxTagLength + 5, 78, 0, 0,
                                               hTabKingdoms, NULL, hThisInst, NULL);

        staticCapCountVal[i] = CreateWindowEx(0, "STATIC", TEXT(""), WS_CHILD | WS_VISIBLE,
                                               headerX + 10 + ks_maxTagLength + 5, 93, 0, 0,
                                               hTabKingdoms, NULL, hThisInst, NULL);

        staticWinCountVal[i] = CreateWindowEx(0, "STATIC", TEXT(""), WS_CHILD | WS_VISIBLE,
                                               headerX + 10 + ks_maxTagLength + 5, 108, 0, 0,
                                               hTabKingdoms, NULL, hThisInst, NULL);

        staticLossCountVal[i] = CreateWindowEx(0, "STATIC", TEXT(""), WS_CHILD | WS_VISIBLE,
                                               headerX + 10 + ks_maxTagLength + 5, 123, 0, 0,
                                               hTabKingdoms, NULL, hThisInst, NULL);

//non-editable edit boxes to list generals, captives, and castles
        staticGenOwnedList[i] = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_VSCROLL | WS_CHILD |
        ES_READONLY| ES_MULTILINE,
        headerX, 223, 100, 325,
        hTabKingdoms, NULL, hThisInst, NULL);

        staticCapOwnedList[i] = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_VSCROLL | WS_CHILD |
        ES_READONLY| ES_MULTILINE,
        headerX, 223, 100, 325,
        hTabKingdoms, NULL, hThisInst, NULL);

        staticCasOwnedList[i] = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_VSCROLL | WS_CHILD |
        ES_READONLY| ES_MULTILINE,
        headerX, 223, 100, 325,
        hTabKingdoms, NULL, hThisInst, NULL);

        SetDefaultFont(staticRulerNames[i]);
        SetDefaultFont(staticKingdomNames[i]);
        SetDefaultFont(staticCasCountTag[i]);
        SetDefaultFont(staticGenCountTag[i]);
        SetDefaultFont(staticCapCountTag[i]);
        SetDefaultFont(staticWinCountTag[i]);
        SetDefaultFont(staticLossCountTag[i]);

        SetDefaultFont(staticCasCountVal[i]);
        SetDefaultFont(staticGenCountVal[i]);
        SetDefaultFont(staticCapCountVal[i]);
        SetDefaultFont(staticWinCountVal[i]);
        SetDefaultFont(staticLossCountVal[i]);

        SetDefaultFont(staticGenOwnedList[i]);
        SetDefaultFont(staticCapOwnedList[i]);
        SetDefaultFont(staticCasOwnedList[i]);
    }
    
//Radio Buttons

    ks_rbGeneralsList = CreateWindowEx(
        0, "BUTTON", TEXT("Generals"), WS_CHILD | WS_VISIBLE | WS_DISABLED | BS_AUTORADIOBUTTON | WS_GROUP,
        395, 163, 73, 13,
        hTabKingdoms, (HMENU)ID_KS_RB_GENS, hThisInst, NULL); 

    ks_rbCaptivesList = CreateWindowEx(
        0, "BUTTON", TEXT("Captives"), WS_CHILD | WS_VISIBLE | WS_DISABLED | BS_AUTORADIOBUTTON,
        395, 178, 73, 13,
        hTabKingdoms, (HMENU)ID_KS_RB_CAPS, hThisInst, NULL); 

    ks_rbCastlesList = CreateWindowEx(
        0, "BUTTON", TEXT("Castles"), WS_CHILD | WS_VISIBLE | WS_DISABLED | BS_AUTORADIOBUTTON,
        395, 193, 73, 13,
        hTabKingdoms, (HMENU)ID_KS_RB_CASTLES, hThisInst, NULL);

    SetDefaultFont(ks_rbGeneralsList);
    SetDefaultFont(ks_rbCaptivesList);
    SetDefaultFont(ks_rbCastlesList);

    return;
}

void getKingdomsStaticTextSize(const HWND hwnd, const char* str, RECT* rect)
{
    LOGFONT lf;
    HFONT   hfont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

    GetObject(hfont, sizeof(LOGFONT), &lf);
    SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, LPARAM(TRUE));

    HDC hdc = GetDC(hwnd);

    HFONT hfOld = reinterpret_cast<HFONT>(SelectObject(hdc, hfont));
    DeleteObject(hfOld);

    DrawText(hdc, str, -1, rect, DT_CALCRECT | DT_SINGLELINE);
    ReleaseDC(hwnd, hdc);

    if(ks_maxTagLength < rect->right)
        ks_maxTagLength = rect->right;

    return;
}

void CreateKingdomsTab(void)
{
    hTabKingdoms = CreateWindowEx(
        0, "STATIC", NULL, WS_CHILD | WS_TABSTOP,
        0, 22, 1009, 688,
        hTabCntrl, NULL, hThisInst, NULL);

    g_MainWndProc = (WNDPROC)SetWindowLongPtr(hTabKingdoms, GWL_WNDPROC, (LONG)KingdomTabWndProc);

    createStaticKingdomControls();

    return;
}

void updateKingdomsTab(void)
{
    char itoaArr[7] = {'\0'};
    RECT rect       = {0};

    if(alreadyOpened)
        for(int i = 0; i < 8; i++)
        {
            SetWindowText(staticCasCountVal[i], itoaArr);
            SetWindowText(staticGenCountVal[i], itoaArr);
            SetWindowText(staticCapCountVal[i], itoaArr);
            SetWindowText(staticWinCountVal[i], itoaArr);
            SetWindowText(staticLossCountVal[i], itoaArr);
            SetWindowText(staticGenOwnedList[i], itoaArr);
            SetWindowText(staticCapOwnedList[i], itoaArr);
            SetWindowText(staticCasOwnedList[i], itoaArr);

            SendDlgItemMessage(hTabKingdoms, ID_KS_RB_GENS, BM_SETCHECK, 0, 0);
            SendDlgItemMessage(hTabKingdoms, ID_KS_RB_CAPS, BM_SETCHECK, 0, 0);
            SendDlgItemMessage(hTabKingdoms, ID_KS_RB_CASTLES, BM_SETCHECK, 0, 0);
        }

    int  headerX = 10;
    for(int i = 0; i < 8; i++, headerX += 125)
    {
        itoa(dr.kingdoms[i].numCastles, itoaArr, 10);
        getKingdomsStaticTextSize(staticCasCountVal[i], itoaArr, &rect);
        SetWindowText(staticCasCountVal[i], itoaArr);
        SetWindowPos(staticCasCountVal[i], 0, headerX + 10 + ks_maxTagLength + 5, 63, rect.right, rect.bottom, 0);

        itoa(dr.kingdoms[i].numGenerals, itoaArr, 10);
        getKingdomsStaticTextSize(staticGenCountVal[i], itoaArr, &rect);
        SetWindowText(staticGenCountVal[i], itoaArr);
        SetWindowPos(staticGenCountVal[i], 0, headerX + 10 + ks_maxTagLength + 5, 78, rect.right, rect.bottom, 0);

        itoa(dr.kingdoms[i].numCaptives, itoaArr, 10);
        getKingdomsStaticTextSize(staticCapCountVal[i], itoaArr, &rect);
        SetWindowText(staticCapCountVal[i], itoaArr);
        SetWindowPos(staticCapCountVal[i], 0, headerX + 10 + ks_maxTagLength + 5, 93, rect.right, rect.bottom, 0);

        itoa(dr.kingdoms[i].kingdomWins, itoaArr, 10);
        getKingdomsStaticTextSize(staticWinCountVal[i], itoaArr, &rect);
        SetWindowText(staticWinCountVal[i], itoaArr);
        SetWindowPos(staticWinCountVal[i], 0, headerX + 10 + ks_maxTagLength + 5, 108, rect.right, rect.bottom, 0);

        itoa(dr.kingdoms[i].kingdomLosses, itoaArr, 10);
        getKingdomsStaticTextSize(staticLossCountVal[i], itoaArr, &rect);
        SetWindowText(staticLossCountVal[i], itoaArr);
        SetWindowPos(staticLossCountVal[i], 0, headerX + 10 + ks_maxTagLength + 5, 123, rect.right, rect.bottom, 0);
    }

    //Need this, otherwise when opening the very first file after program start,
    //Wein's castle count will say 34...
    if(!alreadyOpened)
        SetWindowText(staticCasCountVal[0], "0");

    return;
}

void enableKingdomRadioControls(void)
{
    EnableWindow(ks_rbGeneralsList, TRUE);
    EnableWindow(ks_rbCaptivesList, TRUE);
    EnableWindow(ks_rbCastlesList, TRUE);

    return;
}

void showKingdomOwnedResources(const int listToShow)
{
    if(listToShow == GENERALS_LIST)
    {
        for(int i = 0; i < 8; i++)
        {
            ShowWindow(staticGenOwnedList[i], TRUE);
            ShowWindow(staticCapOwnedList[i], FALSE);
            ShowWindow(staticCasOwnedList[i], FALSE);
        }

        for(int i = 0; i < 8; i++)
        {
            stringstream ss;
            for(int j = 0; j < dr.kingdoms[i].numGenerals; j++)
                ss << generalsNameList[dr.kingdoms[i].ownedGenerals[j]] << "\r\n";
            SendMessage(staticGenOwnedList[i], WM_SETTEXT, 0, LPARAM(ss.str().c_str()));
        }
    }

    if(listToShow == CAPTIVES_LIST)
    {
        for(int i = 0; i < 8; i++)
        {
            ShowWindow(staticGenOwnedList[i], FALSE);
            ShowWindow(staticCapOwnedList[i], TRUE);
            ShowWindow(staticCasOwnedList[i], FALSE);
        }

        for(int i = 0; i < 8; i++)
        {
            stringstream ss;
            for(int j = 0; j < dr.kingdoms[i].numCaptives; j++)
                ss << generalsNameList[dr.kingdoms[i].ownedCaptives[j]] << "\r\n";
            SendMessage(staticCapOwnedList[i], WM_SETTEXT, 0, LPARAM(ss.str().c_str()));
        }
    }

    if(listToShow == CASTLES_LIST)
    {
        for(int i = 0; i < 8; i++)
        {
            ShowWindow(staticGenOwnedList[i], FALSE);
            ShowWindow(staticCapOwnedList[i], FALSE);
            ShowWindow(staticCasOwnedList[i], TRUE);
        }

        for(int i = 0; i < 8; i++)
        {
            stringstream ss;
            for(int j = 0; j < dr.kingdoms[i].numCastles; j++)
                ss << castlesNameList[dr.kingdoms[i].ownedCastles[j]] << "\r\n";
            SendMessage(staticCasOwnedList[i], WM_SETTEXT, 0, LPARAM(ss.str().c_str()));
        }
    }

    return;
}

LRESULT CALLBACK KingdomTabWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch(msg)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_KS_RB_GENS:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            showKingdomOwnedResources(GENERALS_LIST);
                        }
                        break;
                    }
                }
                break;
                case ID_KS_RB_CAPS:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            showKingdomOwnedResources(CAPTIVES_LIST);
                        }
                        break;
                    }
                }
                break;
                case ID_KS_RB_CASTLES:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            showKingdomOwnedResources(CASTLES_LIST);
                        }
                        break;
                    }
                }
                break;
            }
        break;//WM_COMMAND
        default:
            return CallWindowProc(g_MainWndProc, hwnd, msg, wParam, lParam);
    }

    return 0;
}
