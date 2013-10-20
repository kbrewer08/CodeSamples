#include "DFGui.h"

HWND hTabCntrl = NULL;   // The main tab control

HWND hTabGenerals = NULL;
GENERALS_TAB GenTabCtrls; //struct to contain all the controls for Generals tab

HWND hTabCastles   = NULL;
CASTLES_TAB CasTabCtrls; //struct to contain all the controls for Castles tab

HWND hTabDivisions = NULL;
DIVISIONS_TAB DivTabCtrls; //struct to contain all the controls for Divisions tab

HWND hTabMassEdit  = NULL;
MASSEDIT_TAB MassEditTabCtrls;

HWND hTabItemInv   = NULL;
HWND hTabMisc      = NULL;

void CreateTabControl(void)
{
    TCITEM tie;  // tab item structure

    /* create tab control */
    hTabCntrl = CreateWindowEx(
        0,                    // extended style
        WC_TABCONTROL,                       // tab control constant
        "",                                  // text/caption
        WS_CHILD | WS_VISIBLE | WS_TABSTOP,  // is a child control, and visible
        0,                                   // X position - device units from left
        0,                                   // Y position - device units from top
        1018,                                // Width - in device units
        720,                                 // Height - in device units
        hMainWindow,                         // parent window
        (HMENU)101,                          // no menu
        hThisInst,                           // instance
        NULL                                 // no extra junk
    );

    if (hTabCntrl == NULL)
    {
        MessageBox(NULL, TEXT("Tab creation failed"), TEXT("Tab Creation"), MB_OK | MB_ICONERROR);
        return;
    }

    SetDefaultFont(hTabCntrl);

    /* start adding items to our tab control */
    // set up tab item structure for Tab1
    tie.mask = TCIF_TEXT;  // we're only displaying text in the tabs
    TCHAR pszTab1 [] = TEXT("Generals");  // tab1's text  (2-step process necessary to avoid compiler warnings)
    tie.pszText = pszTab1;  // the tab's text/caption

    // attempt to insert Tab1
    if (TabCtrl_InsertItem(hTabCntrl, 0, &tie) == -1)
    {
        // couldn't insert tab item
        DestroyWindow(hTabCntrl);
        MessageBox(NULL, TEXT("Couldn't add Generals tab"), TEXT("Tab Creation"), MB_OK | MB_ICONERROR);
        return;
    }

    // set up tab item structure for Tab2
    // (reusing same structure, just changing the text)
    TCHAR pszTab2 [] = TEXT("Castles");  // tab2's text  (2-step process necessary to avoid compiler warnings)
    tie.pszText = pszTab2;  // the tab's text/caption

    // attempt to insert Tab2
    if (TabCtrl_InsertItem(hTabCntrl, 1, &tie) == -1)
    {
        // couldn't insert tab item
        DestroyWindow(hTabCntrl);
        MessageBox(NULL, TEXT("Couldn't add Castles tab"), TEXT("Tab Creation"), MB_OK | MB_ICONERROR);
        return;
    }

    // set up tab item structure for Tab3
    // (reusing same structure, just changing the text)
    TCHAR pszTab3 [] = TEXT("Divisions");  // Tab3's text  (2-step process necessary to avoid compiler warnings)
    tie.pszText = pszTab3;  // the tab's text/caption

    // attempt to insert Tab3
    if (TabCtrl_InsertItem(hTabCntrl, 2, &tie) == -1)
    {
        // couldn't insert tab item
        DestroyWindow(hTabCntrl);
        MessageBox(NULL, TEXT("Couldn't add Divisions tab"), TEXT("Tab Creation"), MB_OK | MB_ICONERROR);
        return;
    }

    // set up tab item structure for Tab4
    // (reusing same structure, just changing the text)
    TCHAR pszTab4 [] = TEXT("Mass Editing");  // tab4's text  (2-step process necessary to avoid compiler warnings)
    tie.pszText = pszTab4;  // the tab's text/caption

    // attempt to insert Tab4
    if (TabCtrl_InsertItem(hTabCntrl, 3, &tie) == -1)
    {
        // couldn't insert tab item
        DestroyWindow(hTabCntrl);
        MessageBox(NULL, TEXT("Couldn't add Mass Editing tab"), TEXT("Tab Creation"), MB_OK | MB_ICONERROR);
        return;
    }
/*
    // set up tab item structure for Tab5
    // (reusing same structure, just changing the text)
    CHAR pszTab5 [] = "Items";  // tab5's text  (2-step process necessary to avoid compiler warnings)
    tie.pszText = pszTab5;  // the tab's text/caption

    // attempt to insert Tab5
    if (TabCtrl_InsertItem(hTabCntrl, 4, &tie) == -1)
    {
        // couldn't insert tab item
        DestroyWindow(hTabCntrl);
        MessageBox(NULL, "Couldn't add Item tab", "Tab Creation", MB_OK | MB_ICONERROR);
        return;
    }

    // set up tab item structure for Tab6
    // (reusing same structure, just changing the text)
    CHAR pszTab6 [] = "Misc";  // tab6's text  (2-step process necessary to avoid compiler warnings)
    tie.pszText = pszTab6;  // the tab's text/caption

    // attempt to insert Tab6
    if (TabCtrl_InsertItem(hTabCntrl, 5, &tie) == -1)
    {
        // couldn't insert tab item
        DestroyWindow(hTabCntrl);
        MessageBox(NULL, "Couldn't add Misc tab", "Tab Creation", MB_OK | MB_ICONERROR);
        return;
    }
*/
    return;
}
