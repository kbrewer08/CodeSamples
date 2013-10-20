#include <windows.h>
#include <commctrl.h>
#include <cmath>

#include "DFGui.h"

    HWND sc_CasMaxTroopsVal;

    HWND sc_CasNumGenTag;
    HWND sc_CasNumGenVal;
    HWND sc_CasNumCapTag;
    HWND sc_CasNumCapVal;
    HWND sc_CasXCoordTag;
    HWND sc_CasXCoordVal;
    HWND sc_CasYCoordTag;
    HWND sc_CasYCoordVal;
    HWND sc_HasPlayerMonarchTag;
    HWND sc_HasPlayerMonarchVal;
    HWND sc_CasExpCurrTag;
    HWND sc_CasExpCurrVal;
    HWND sc_CasExpNextTag;
    HWND sc_CasExpNextVal;

void CreateCastlesTab(void)
{
    HWND cb_CasNameTag;
    HWND cb_CasRulerTag;
    HWND cb_CasLeaderTag;
    HWND cb_CasLevelTag;
    HWND eb_CasTroopCountTag;
    HWND eb_CasTroopSlash;
    HWND lb_CasGeneralsTag;
    HWND lb_CasCaptivesTag;
    HWND lb_CasGenListTag;
    
    HWND CasInfoStaticGroup;

    // create a Static control for our view window
    hTabCastles = CreateWindowEx(
        0, "STATIC", NULL, WS_CHILD | WS_TABSTOP,
        0, 22, 1009, 688,
        hTabCntrl, NULL, hThisInst, NULL);

    g_MainWndProc = (WNDPROC)SetWindowLongPtr(hTabCastles, GWL_WNDPROC, (LONG)CasTabWndProc);

    cb_CasNameTag = CreateWindowEx( //Castle name text tag
        0, "STATIC", "Castle:", WS_CHILD | WS_VISIBLE,
        10, 28, 43, 20,
        hTabCastles, NULL, hThisInst, NULL);

    CasTabCtrls.cb_CasNameList = CreateWindowEx( //names list combobox
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 28, 100, 500,
        hTabCastles, (HMENU)ID_CB_CASNAME, hThisInst, NULL);

    cb_CasRulerTag = CreateWindowEx( //Castle ruler text tag
        0, "STATIC", "Ruler:", WS_CHILD | WS_VISIBLE,
        10, 53, 43, 20,
        hTabCastles, NULL, hThisInst, NULL);

    CasTabCtrls.cb_CasRulerList = CreateWindowEx( //rulers list combobox
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 53, 100, 500,
        hTabCastles, (HMENU)ID_CB_CAS_RULER, hThisInst, NULL);

    CasTabCtrls.but_SetCasRuler = CreateWindowEx(   //ruler set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 53, 40, 20,
        hTabCastles, (HMENU)ID_SET_CAS_RULER, hThisInst, NULL);

    cb_CasLeaderTag = CreateWindowEx( //Castle leader text tag
        0, "STATIC", "Leader:", WS_CHILD | WS_VISIBLE,
        10, 78, 43, 20,
        hTabCastles, NULL, hThisInst, NULL);

    CasTabCtrls.cb_CasLeaderList = CreateWindowEx( //leader list combobox
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 78, 100, 500,
        hTabCastles, (HMENU)ID_CB_CAS_LEADER, hThisInst, NULL);

    CasTabCtrls.but_SetCasLeader = CreateWindowEx(   //leader set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 78, 40, 20,
        hTabCastles, (HMENU)ID_SET_CAS_LEADER, hThisInst, NULL);

    cb_CasLevelTag = CreateWindowEx( //Castle level text tag
        0, "STATIC", "Level:", WS_CHILD | WS_VISIBLE,
        10, 103, 43, 20,
        hTabCastles, NULL, hThisInst, NULL);

    CasTabCtrls.cb_CasLevel = CreateWindowEx( //castle level combobox
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 103, 100, 500,
        hTabCastles, (HMENU)ID_CB_CAS_LEVEL, hThisInst, NULL);

    CasTabCtrls.but_SetCasLevel = CreateWindowEx(   //level set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 103, 40, 20,
        hTabCastles, (HMENU)ID_SET_CAS_LEVEL, hThisInst, NULL);

    eb_CasTroopCountTag = CreateWindowEx( //Castle troop count text tag
        0, "STATIC", "Troops:", WS_CHILD | WS_VISIBLE,
        10, 128, 43, 20,
        hTabCastles, NULL, hThisInst, NULL);

    CasTabCtrls.eb_CasTroopCount = CreateWindowEx( //castle troop count edit box
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        55, 128, 30, 20,
        hTabCastles, (HMENU)ID_EB_CAS_TRP_CNT, hThisInst, NULL);

    eb_CasTroopSlash = CreateWindowEx(                //troop count slash
        0, "STATIC", "/", WS_CHILD | WS_VISIBLE,
        87, 131, 5, 20,
        hTabCastles, NULL, hThisInst, NULL);

    sc_CasMaxTroopsVal = CreateWindowEx(              //castle max troop count value
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        95, 131, 30, 20, 
        hTabCastles, (HMENU)ID_STATIC_CASTRPCNT, hThisInst, NULL); 

    CasTabCtrls.but_SetCasTroopCount = CreateWindowEx(   //castle troop count set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 128, 40, 20,
        hTabCastles, (HMENU)ID_SET_CAS_TRP_CNT, hThisInst, NULL);

    CasInfoStaticGroup = CreateWindowEx( //frame surrounding status information
        0, "BUTTON", "Status Information", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        10, 183, 180, 175, 
        hTabCastles, NULL, hThisInst, NULL);

    sc_CasNumGenTag = CreateWindowEx(              //number of generals tag
        0, "STATIC", "Generals:", WS_CHILD | WS_VISIBLE,
        15, 203, 60, 20, 
        hTabCastles, NULL, hThisInst, NULL); 

    sc_CasNumGenVal = CreateWindowEx(              //number of generals value
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 203, 60, 20, 
        hTabCastles, (HMENU)ID_STATIC_CASNUMGEN, hThisInst, NULL); 

    sc_CasNumCapTag = CreateWindowEx(              //number of captives tag
        0, "STATIC", "Captives:", WS_CHILD | WS_VISIBLE,
        15, 218, 60, 20, 
        hTabCastles, NULL, hThisInst, NULL); 

    sc_CasNumCapVal = CreateWindowEx(              //number of captives value
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 218, 80, 20, 
        hTabCastles, (HMENU)ID_STATIC_CASNUMCAP, hThisInst, NULL); 

    sc_CasXCoordTag = CreateWindowEx(              //castle x coordinate tag
        0, "STATIC", "X Pos:", WS_CHILD | WS_VISIBLE,
        15, 233, 60, 20, 
        hTabCastles, NULL, hThisInst, NULL); 

    sc_CasXCoordVal = CreateWindowEx(              //castle x coordinate val
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 233, 80, 20, 
        hTabCastles, (HMENU)ID_STATIC_CAS_X, hThisInst, NULL); 

    sc_CasYCoordTag = CreateWindowEx(              //castle y coordinate tag
        0, "STATIC", "Y Pos:", WS_CHILD | WS_VISIBLE,
        15, 248, 60, 20, 
        hTabCastles, NULL, hThisInst, NULL); 

    sc_CasYCoordVal = CreateWindowEx(              //castle y coordinate val
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 248, 80, 20, 
        hTabCastles, (HMENU)ID_STATIC_CAS_Y, hThisInst, NULL); 

    sc_HasPlayerMonarchTag = CreateWindowEx(              //castle has monarch tag
        0, "STATIC", "Player King:", WS_CHILD | WS_VISIBLE,
        15, 263, 60, 20, 
        hTabCastles, NULL, hThisInst, NULL); 

    sc_HasPlayerMonarchVal = CreateWindowEx(              //castle has monarch val
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 263, 80, 20, 
        hTabCastles, (HMENU)ID_STATIC_CASHASMON, hThisInst, NULL); 

    sc_CasExpCurrTag = CreateWindowEx(              //castle curr exp tag
        0, "STATIC", "Curr Exp:", WS_CHILD | WS_VISIBLE,
        15, 278, 60, 20, 
        hTabCastles, NULL, hThisInst, NULL); 

    sc_CasExpCurrVal = CreateWindowEx(              //castle curr exp val
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 278, 80, 20, 
        hTabCastles, (HMENU)ID_STATIC_CASEXPCUR, hThisInst, NULL); 

    sc_CasExpNextTag = CreateWindowEx(              //castle next exp tag
        0, "STATIC", "Next Level:", WS_CHILD | WS_VISIBLE,
        15, 293, 60, 20, 
        hTabCastles, NULL, hThisInst, NULL); 

    sc_CasExpNextVal = CreateWindowEx(              //castle next exp val
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 293, 80, 20, 
        hTabCastles, (HMENU)ID_STATIC_CASEXPNXT, hThisInst, NULL);

////////////////////////////////////////////////////////////////////////////////
///
/// Second portion of interface
///
////////////////////////////////////////////////////////////////////////////////

    lb_CasGeneralsTag = CreateWindowEx(              //castle generals listbox tag
        0, "STATIC", "Generals:", WS_CHILD | WS_VISIBLE,
        235, 28, 60, 20, 
        hTabCastles, NULL, hThisInst, NULL); 

    CasTabCtrls.lb_casGenerals = CreateWindowEx( //castle generals listbox
        WS_EX_CLIENTEDGE, "LISTBOX", NULL, WS_CHILD | WS_VISIBLE | 
        WS_TABSTOP | WS_DISABLED | LBS_EXTENDEDSEL | LBS_NOTIFY,
        235, 53, 100, 150,
        hTabCastles, (HMENU)ID_LB_CAS_GENERALS, hThisInst, NULL);

    lb_CasCaptivesTag = CreateWindowEx(              //castle captives listbox tag
        0, "STATIC", "Captives:", WS_CHILD | WS_VISIBLE,
        235, 218, 60, 20,
        hTabCastles, NULL, hThisInst, NULL); 

    CasTabCtrls.lb_casCaptives = CreateWindowEx( //castle captives listbox
        WS_EX_CLIENTEDGE, "LISTBOX", NULL, WS_VSCROLL | WS_CHILD | WS_VISIBLE | 
        WS_TABSTOP | WS_DISABLED | LBS_EXTENDEDSEL | LBS_NOTIFY,
        235, 243, 100, 150,
        hTabCastles, (HMENU)ID_LB_CAS_CAPTIVES, hThisInst, NULL);

    lb_CasGenListTag = CreateWindowEx(              //castle generals name list listbox tag
        0, "STATIC", "Generals List:", WS_CHILD | WS_VISIBLE,
        400, 28, 80, 20,
        hTabCastles, NULL, hThisInst, NULL); 

    CasTabCtrls.lb_casGenList = CreateWindowEx( //castle generals name list listbox
        WS_EX_CLIENTEDGE, "LISTBOX", NULL, WS_VSCROLL | WS_CHILD | WS_VISIBLE | 
        WS_TABSTOP | WS_DISABLED | LBS_EXTENDEDSEL | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
        400, 53, 100, 343,
        hTabCastles, (HMENU)ID_LB_CAS_GEN_LIST, hThisInst, NULL);

    CasTabCtrls.but_CasAddGenerals = CreateWindowEx(   //castle add generals button
        0, "BUTTON", "<<", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        347, 98, 40, 20,
        hTabCastles, (HMENU)ID_SET_CAS_ADDGEN, hThisInst, NULL);

    CasTabCtrls.but_CasDelGenerals = CreateWindowEx(   //castle remove generals button
        0, "BUTTON", ">>", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        347, 128, 40, 20,
        hTabCastles, (HMENU)ID_SET_CAS_DELGEN, hThisInst, NULL);

    CasTabCtrls.but_CasAddCaptives = CreateWindowEx(   //castle add captives button
        0, "BUTTON", "<<", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        347, 288, 40, 20,
        hTabCastles, (HMENU)ID_SET_CAS_ADDCAP, hThisInst, NULL);

    CasTabCtrls.but_CasDelCaptives = CreateWindowEx(   //castle remove captives button
        0, "BUTTON", ">>", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        347, 318, 40, 20,
        hTabCastles, (HMENU)ID_SET_CAS_DELCAP, hThisInst, NULL);

    CasTabCtrls.but_CasGeneralToCaptive = CreateWindowEx(   //castle move general to captive
        0, "BUTTON", "V", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        285, 210, 20, 20,
        hTabCastles, (HMENU)ID_SET_CAS_GENTOCAP, hThisInst, NULL);

    CasTabCtrls.but_CasCaptiveToGeneral = CreateWindowEx(   //castle move captive to general
        0, "BUTTON", "^", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        315, 210, 20, 20,
        hTabCastles, (HMENU)ID_SET_CAS_CAPTOGEN, hThisInst, NULL);

    SetDefaultFont(hTabCastles);
    SetDefaultFont(cb_CasNameTag);
    SetDefaultFont(cb_CasRulerTag);
    SetDefaultFont(cb_CasLeaderTag);
    SetDefaultFont(cb_CasLevelTag);
    SetDefaultFont(eb_CasTroopCountTag);
    SetDefaultFont(eb_CasTroopSlash);
    SetDefaultFont(sc_CasMaxTroopsVal);
    SetDefaultFont(lb_CasGeneralsTag);
    SetDefaultFont(lb_CasCaptivesTag);
    SetDefaultFont(lb_CasGenListTag);

    SetDefaultFont(CasInfoStaticGroup);
    SetDefaultFont(sc_CasNumGenTag);
    SetDefaultFont(sc_CasNumGenVal);
    SetDefaultFont(sc_CasNumCapTag);
    SetDefaultFont(sc_CasNumCapVal);
    SetDefaultFont(sc_CasXCoordTag);
    SetDefaultFont(sc_CasXCoordVal);
    SetDefaultFont(sc_CasYCoordTag);
    SetDefaultFont(sc_CasYCoordVal);
    SetDefaultFont(sc_HasPlayerMonarchTag);
    SetDefaultFont(sc_HasPlayerMonarchVal);
    SetDefaultFont(sc_CasExpCurrTag);
    SetDefaultFont(sc_CasExpCurrVal);
    SetDefaultFont(sc_CasExpNextTag);
    SetDefaultFont(sc_CasExpNextVal);

    SetDefaultFont(CasTabCtrls.cb_CasNameList);
    SetDefaultFont(CasTabCtrls.cb_CasRulerList);
    SetDefaultFont(CasTabCtrls.but_SetCasRuler);
    SetDefaultFont(CasTabCtrls.cb_CasLeaderList);
    SetDefaultFont(CasTabCtrls.but_SetCasLeader);
    SetDefaultFont(CasTabCtrls.cb_CasLevel);
    SetDefaultFont(CasTabCtrls.but_SetCasLevel);
    SetDefaultFont(CasTabCtrls.eb_CasTroopCount);
    SetDefaultFont(CasTabCtrls.but_SetCasTroopCount);
    SetDefaultFont(CasTabCtrls.lb_casGenerals);
    SetDefaultFont(CasTabCtrls.lb_casCaptives);
    SetDefaultFont(CasTabCtrls.lb_casGenList);
    SetDefaultFont(CasTabCtrls.but_CasAddGenerals);
    SetDefaultFont(CasTabCtrls.but_CasDelGenerals);
    SetDefaultFont(CasTabCtrls.but_CasAddCaptives);
    SetDefaultFont(CasTabCtrls.but_CasDelCaptives);
    SetDefaultFont(CasTabCtrls.but_CasGeneralToCaptive);
    SetDefaultFont(CasTabCtrls.but_CasCaptiveToGeneral);

    return;
}

void PopulateCastlesTab(void)
{
    int cas = 0;
    char itoaArr[5] = {'\0'};
/*
    Copied here from PopulateGeneralsTab as reminder that this stuff has been set up already
    dr.fr.readFile();   //read the save file
    dr.initGenerals();  //create the generals array
    dr.setMonarch();    //find who the player's monarch is
    dr.initCastles();   //create the castles array
    dr.initDivisions(); //create the divisions array
*/
    EnableWindow(CasTabCtrls.cb_CasNameList, TRUE); //turn on names list combobox
    EnableWindow(CasTabCtrls.cb_CasRulerList, TRUE); //turn on ruler list combobox
    EnableWindow(CasTabCtrls.cb_CasLeaderList, TRUE); //turn on castle leader combobox
    EnableWindow(CasTabCtrls.cb_CasLevel, TRUE); //turn on castle level combobox
    EnableWindow(CasTabCtrls.but_SetCasLevel, TRUE); //turn on castle level set button
    EnableWindow(CasTabCtrls.eb_CasTroopCount, TRUE); //turn on castle troop count edit box
    EnableWindow(CasTabCtrls.but_SetCasTroopCount, TRUE); //turn on castle troop count set button
    EnableWindow(CasTabCtrls.lb_casGenerals, TRUE); //turn on castle generals list box
    EnableWindow(CasTabCtrls.lb_casCaptives, TRUE); //turn on castle captives list box
    EnableWindow(CasTabCtrls.lb_casGenList, TRUE); //turn on castle generals name list listbox
    EnableWindow(CasTabCtrls.but_CasAddGenerals, TRUE); //turn on castle add generals button
    EnableWindow(CasTabCtrls.but_CasDelGenerals, TRUE); //turn on castle remove generals button
    EnableWindow(CasTabCtrls.but_CasAddCaptives, TRUE); //turn on castle add captives button
    EnableWindow(CasTabCtrls.but_CasDelCaptives, TRUE); //turn on castle remove captives button
    EnableWindow(CasTabCtrls.but_CasGeneralToCaptive, TRUE); //turn on castle move generals to captive
    EnableWindow(CasTabCtrls.but_CasCaptiveToGeneral, TRUE); //turn on castle move captives to generals

    if(!alreadyOpened) //only need to initialize contents of the following items once
    {
        for(int i = 0; i < 34; i++) //setting up Castles Names List combobox
            SendMessage(CasTabCtrls.cb_CasNameList, CB_ADDSTRING, 0, LPARAM(castlesNameList[i]));
        SendMessage(CasTabCtrls.cb_CasNameList, CB_SETCURSEL, 0, 0);

        for(int i = 0; i < 51; i++) //setting up castle levels combobox
            SendMessage(CasTabCtrls.cb_CasLevel, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));

        for(int i = 0; i < 171; i++) //setting up master Generals Names List listbox
            SendMessage(CasTabCtrls.lb_casGenList, LB_ADDSTRING, 0, LPARAM(generalsNameList[i]));
    }

    cas = SendMessage(CasTabCtrls.cb_CasNameList, CB_GETCURSEL, 0, 0); //get selected castle ID

    if(dr.casArr[cas].isCastleEmpty()) //if castle is empty, put a "none" for ruler
    {
        SendMessage(CasTabCtrls.cb_CasRulerList, CB_RESETCONTENT, 0, 0); //redo the ruler combobox if castle empty
        SendMessage(CasTabCtrls.cb_CasRulerList, CB_ADDSTRING, 0, LPARAM("None"));
        SendMessage(CasTabCtrls.cb_CasRulerList, CB_SETCURSEL, 0, 0);
        EnableWindow(CasTabCtrls.but_SetCasRuler, FALSE); //turn on ruler set button
    }
    else
    {
        for(int i = 0; i < 171; i++) //setting up Rulers Names List combobox
            SendMessage(CasTabCtrls.cb_CasRulerList, CB_ADDSTRING, 0, LPARAM(generalsNameList[i]));
        SendMessage(CasTabCtrls.cb_CasRulerList, CB_SETCURSEL, dr.casArr[cas].ruler, 0);
        EnableWindow(CasTabCtrls.but_SetCasRuler, TRUE); //turn on ruler set button
    }

    SendMessage(CasTabCtrls.cb_CasLeaderList, CB_RESETCONTENT, 0, 0); //redo the leader combobox for current castle
    if(dr.casArr[cas].isCastleEmpty()) //if castle is empty, put a "none" for leader
    {
        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_ADDSTRING, 0, LPARAM("None"));
        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_SETCURSEL, 0, 0);
        EnableWindow(CasTabCtrls.but_SetCasLeader, FALSE); //turn on castle leader set button

    }
    else
    {
        for(int i = 0; i < dr.casArr[cas].numGenerals; i++) //setting up Leaders Names List combobox
            SendMessage(CasTabCtrls.cb_CasLeaderList, CB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].generals[i]]));
        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_SETCURSEL, findLeaderCasIndex(cas), 0);
        EnableWindow(CasTabCtrls.but_SetCasLeader, TRUE); //turn on castle leader set button
    }

    SendMessage(CasTabCtrls.lb_casGenerals, LB_RESETCONTENT, 0, 0); //redo the castle generals listbox for current castle
    for(int i = 0; i < dr.casArr[cas].numGenerals; i++) //setting up generals Names List listbox
        SendMessage(CasTabCtrls.lb_casGenerals, LB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].generals[i]]));

    SendMessage(CasTabCtrls.lb_casCaptives, LB_RESETCONTENT, 0, 0); //redo the castle captives listbox for current castle
    for(int i = 0; i < dr.casArr[cas].numCaptives; i++) //setting up generals Names List listbox
        SendMessage(CasTabCtrls.lb_casCaptives, LB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].captives[i]]));

    SendMessage(CasTabCtrls.cb_CasLevel, CB_SETCURSEL, dr.casArr[cas].level, 0);

    SetDlgItemInt(hTabCastles, ID_EB_CAS_TRP_CNT, dr.casArr[cas].troopCount, FALSE); //fill troop count field
    SetWindowText(sc_CasMaxTroopsVal, itoa((dr.casArr[cas].level + 5) * 10, itoaArr, 10)); //fill max troop static
    SetWindowText(sc_CasNumGenVal, itoa(dr.casArr[cas].numGenerals, itoaArr, 10));  //fill number of generals static
    SetWindowText(sc_CasNumCapVal, itoa(dr.casArr[cas].numCaptives, itoaArr, 10));  //fill number of captives static
    SetWindowText(sc_CasXCoordVal, itoa(dr.casArr[cas].xCoordinate, itoaArr, 10));  //fill x coordinate static
    SetWindowText(sc_CasYCoordVal, itoa(dr.casArr[cas].yCoordinate, itoaArr, 10));  //fill y coordinate static
    
    if(dr.casArr[cas].hasPlayerRuler)
        SetWindowText(sc_HasPlayerMonarchVal, "Yes");  //fill has player monarch static
    else
        SetWindowText(sc_HasPlayerMonarchVal, "No");  //fill has player monarch static

    SetWindowText(sc_CasExpCurrVal, itoa(dr.casArr[cas].experience, itoaArr, 10));  //fill curr exp static
    SetWindowText(sc_CasExpNextVal, itoa(dr.casArr[cas].expNext, itoaArr, 10));  //fill next exp static

    return;
}

LRESULT CALLBACK CasTabWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int  cas      = -1;
    int  count    = 0;
    int  success  = 0;
    bool newRuler = false;
    int* genBuff  = NULL;
    char itoaArr[5] = {'\0'};

    switch(msg)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_CB_CASNAME:
                    switch(HIWORD(wParam))
                    {
                        case CBN_SELCHANGE:
                        {
                            cas = SendMessage(CasTabCtrls.cb_CasNameList, CB_GETCURSEL, 0, 0); //get selected castle ID
                            updateCastlesTab(cas);
                        }
                        break;//CBN_SELCHANGE
                    }
                break;//ID_CB_CASNAME
                case ID_SET_CAS_RULER:
                {
                    int newRuler;
                    cas      = SendMessage(CasTabCtrls.cb_CasNameList, CB_GETCURSEL, 0, 0); //get selected castle ID
                    newRuler = SendMessage(CasTabCtrls.cb_CasRulerList, CB_GETCURSEL, 0, 0);
                    success  = dr.casArr[cas].changeRuler(newRuler);
                    if(!success)
                    {
                        MessageBox(hwnd, "The ruler can't be changed because your monarch is located here.", "Error", MB_OK | MB_ICONERROR);
                        SendMessage(CasTabCtrls.cb_CasRulerList, CB_SETCURSEL, dr.casArr[cas].ruler, 0);
                    }
                    if(success == 2)
                        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_SETCURSEL, dr.casArr[cas].findRulerIndex(), 0);
                }
                break;
                case ID_SET_CAS_LEADER:
                {
                    int newLeader;
                    cas       = SendMessage(CasTabCtrls.cb_CasNameList, CB_GETCURSEL, 0, 0); //get selected castle ID
                    newLeader = SendMessage(CasTabCtrls.cb_CasLeaderList, CB_GETCURSEL, 0, 0); //get selected leader
                    success   = dr.casArr[cas].changeLeader(newLeader);
                    if(!success)
                    {
                        MessageBox(hwnd, "The leader can't be changed because the castle's ruler is present.", "Error", MB_OK | MB_ICONERROR);
                        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_SETCURSEL, findLeaderCasIndex(cas), 0);
                    }
                }
                break;
                case ID_SET_CAS_LEVEL:
                {
                    int newLevel;
                    cas      = SendMessage(CasTabCtrls.cb_CasNameList, CB_GETCURSEL, 0, 0); //get selected castle ID
                    newLevel = SendMessage(CasTabCtrls.cb_CasLevel, CB_GETCURSEL, 0, 0);
                    success  = dr.casArr[cas].adjustLevel(newLevel);
                    if(!success)
                    {
                        MessageBox(hwnd, "A castle's level can't be set to 0.", "Error", MB_OK | MB_ICONERROR);
                        SendMessage(CasTabCtrls.cb_CasLevel, CB_SETCURSEL, dr.casArr[cas].level, 0);
                    }
                    else
                    {
                        SetWindowText(sc_CasExpCurrVal, itoa(dr.casArr[cas].experience, itoaArr, 10));  //fill curr exp static
                        SetWindowText(sc_CasExpNextVal, itoa(dr.casArr[cas].expNext, itoaArr, 10));  //fill next exp static
                        SetDlgItemInt(hTabCastles, ID_EB_CAS_TRP_CNT, dr.casArr[cas].troopCount, FALSE); //fill troop count field
                        SetWindowText(sc_CasMaxTroopsVal, itoa(dr.casArr[cas].maxTroops, itoaArr, 10)); //fill in max troop value static
                    }
                }
                break;
                case ID_SET_CAS_TRP_CNT:
                {
                    int newTroops;
                    cas       = SendMessage(CasTabCtrls.cb_CasNameList, CB_GETCURSEL, 0, 0); //get selected castle ID
                    newTroops = (int)GetDlgItemInt(hTabCastles, ID_EB_CAS_TRP_CNT, NULL, FALSE);
                    success   = dr.casArr[cas].adjustTroops(newTroops);
                    if(!success)
                    {
                        MessageBox(hwnd, "The troops can't be set to higher than the maximum.", "Error", MB_OK | MB_ICONERROR);
                        SetDlgItemInt(hTabCastles, ID_EB_CAS_TRP_CNT, dr.casArr[cas].troopCount, FALSE); //fill troop count field
                    }
                }
                break;
                case ID_SET_CAS_ADDGEN:
                {
                    
                    cas     = SendMessage(CasTabCtrls.cb_CasNameList, CB_GETCURSEL, 0, 0); //get selected castle ID
                    count   = SendMessage(CasTabCtrls.lb_casGenList, LB_GETSELCOUNT, 0, 0);
                    genBuff = (int*)malloc(sizeof(int) * count);
                    SendMessage(CasTabCtrls.lb_casGenList, LB_GETSELITEMS, WPARAM(count), LPARAM(genBuff));

                    if(dr.casArr[cas].numGenerals == 0)
                        newRuler = true;

                    if(dr.casArr[cas].addMultiGenFromList(genBuff, count)) //if generals were added, update appropriate combo/list boxes
                    {
                        //redo the listbox for this castle's occupying generals
                        SendMessage(CasTabCtrls.lb_casGenerals, LB_RESETCONTENT, 0, 0); //redo the castle generals listbox for current castle
                        for(int i = 0; i < dr.casArr[cas].numGenerals; i++) //setting up Generals List combobox
                            SendMessage(CasTabCtrls.lb_casGenerals, LB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].generals[i]]));

                        //redo the listbox for this castle's captives
                        SendMessage(CasTabCtrls.lb_casCaptives, LB_RESETCONTENT, 0, 0); //redo the castle captives listbox for current castle
                        for(int i = 0; i < dr.casArr[cas].numCaptives; i++) //setting up Captives List combobox
                            SendMessage(CasTabCtrls.lb_casCaptives, LB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].captives[i]]));

                        //redo leader combobox because generals were added
                        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_RESETCONTENT, 0, 0); //clear the leader combobox for current castle
                        EnableWindow(CasTabCtrls.but_SetCasLeader, TRUE); //turn on castle set leader button if castle occupied
                        for(int i = 0; i < dr.casArr[cas].numGenerals; i++) //setting up Leaders Names List combobox
                            SendMessage(CasTabCtrls.cb_CasLeaderList, CB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].generals[i]]));
                        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_SETCURSEL, findLeaderCasIndex(cas), 0);

                        if(newRuler)
                        {
                            SendMessage(CasTabCtrls.cb_CasRulerList, CB_RESETCONTENT, 0, 0); //redo Ruler combobox
                            for(int i = 0; i < 171; i++)
                                SendMessage(CasTabCtrls.cb_CasRulerList, CB_ADDSTRING, 0, LPARAM(generalsNameList[i]));
                            SendMessage(CasTabCtrls.cb_CasRulerList, CB_SETCURSEL, dr.casArr[cas].ruler, 0);
                            EnableWindow(CasTabCtrls.but_SetCasRuler, TRUE); //turn on castle set ruler button if castle occupied
                        }

                        SetWindowText(sc_CasNumGenVal, itoa(dr.casArr[cas].numGenerals, itoaArr, 10)); //fill in number of generals static
                        SetWindowText(sc_CasNumCapVal, itoa(dr.casArr[cas].numCaptives, itoaArr, 10)); //fill in number of captives static
                    }

                    free(genBuff);
                }
                break;
                case ID_SET_CAS_DELGEN:
                {
                    cas     = SendMessage(CasTabCtrls.cb_CasNameList, CB_GETCURSEL, 0, 0); //get selected castle ID
                    count   = SendMessage(CasTabCtrls.lb_casGenerals, LB_GETSELCOUNT, 0, 0);
                    genBuff = (int*)malloc(sizeof(int) * count);
                    SendMessage(CasTabCtrls.lb_casGenerals, LB_GETSELITEMS, WPARAM(count), LPARAM(genBuff));

                    if(dr.casArr[cas].delMultiGenFromList(genBuff, count)) //if generals were deleted, update appropriate combo/list boxes
                    {
                        //redo the listbox for this castle's occupying generals
                        SendMessage(CasTabCtrls.lb_casGenerals, LB_RESETCONTENT, 0, 0); //redo the castle generals listbox for current castle
                        for(int i = 0; i < dr.casArr[cas].numGenerals; i++) //setting up Leaders Names List combobox
                            SendMessage(CasTabCtrls.lb_casGenerals, LB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].generals[i]]));

                        //redo leader combobox because generals were added
                        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_RESETCONTENT, 0, 0); //clear the leader combobox for current castle
                        EnableWindow(CasTabCtrls.but_SetCasLeader, TRUE); //turn on castle set leader button if castle occupied
                        for(int i = 0; i < dr.casArr[cas].numGenerals; i++) //setting up Leaders Names List combobox
                            SendMessage(CasTabCtrls.cb_CasLeaderList, CB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].generals[i]]));
                        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_SETCURSEL, findLeaderCasIndex(cas), 0);

                        SendMessage(CasTabCtrls.cb_CasRulerList, CB_SETCURSEL, dr.casArr[cas].ruler, 0); //make sure right ruler is set

                        SetWindowText(sc_CasNumGenVal, itoa(dr.casArr[cas].numGenerals, itoaArr, 10)); //fill in number of generals static
                    }
                    free(genBuff);

                    //if castle is empty, update various on-screen information
                    if(!dr.casArr[cas].numGenerals) //if castle is empty, put a "none" for ruler
                    {
                        SendMessage(CasTabCtrls.cb_CasRulerList, CB_RESETCONTENT, 0, 0); //clear the ruler combobox if castle empty
                        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_RESETCONTENT, 0, 0); //clear the leader combobox if castle empty
                        SendMessage(CasTabCtrls.lb_casCaptives, LB_RESETCONTENT, 0, 0); //empty out the captives box
                        
                        SendMessage(CasTabCtrls.cb_CasRulerList, CB_ADDSTRING, 0, LPARAM("None")); //only add a 'none' option
                        SendMessage(CasTabCtrls.cb_CasRulerList, CB_SETCURSEL, 0, 0); //select the 'none' option
                        EnableWindow(CasTabCtrls.but_SetCasRuler, FALSE); //turn off castle set ruler button if castle empty

                        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_ADDSTRING, 0, LPARAM("None")); //add 'none' option
                        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_SETCURSEL, 0, 0); //choose the 'none' option
                        EnableWindow(CasTabCtrls.but_SetCasLeader, FALSE); //turn off castle set leader button if castle empty

                        dr.casArr[cas].adjustTroops(0);
                        SetDlgItemInt(hTabCastles, ID_EB_CAS_TRP_CNT, 0, FALSE); //fill troop count field

                        SetWindowText(sc_CasNumCapVal, itoa(dr.casArr[cas].numCaptives, itoaArr, 10)); //set number of captives to 0
                    }
                }
                break;
                case ID_SET_CAS_ADDCAP:
                {
                    cas     = SendMessage(CasTabCtrls.cb_CasNameList, CB_GETCURSEL, 0, 0); //get selected castle ID
                    count   = SendMessage(CasTabCtrls.lb_casGenList, LB_GETSELCOUNT, 0, 0);
                    genBuff = (int*)malloc(sizeof(int) * count);
                    SendMessage(CasTabCtrls.lb_casGenList, LB_GETSELITEMS, WPARAM(count), LPARAM(genBuff));

                    if(dr.casArr[cas].addMultiCapFromList(genBuff, count)) //if captives were added, update appropriate combo/list boxes
                    {
                        SendMessage(CasTabCtrls.lb_casCaptives, LB_RESETCONTENT, 0, 0); //redo the castle captives listbox for current castle
                        for(int i = 0; i < dr.casArr[cas].numCaptives; i++) //setting up Captives List combobox
                            SendMessage(CasTabCtrls.lb_casCaptives, LB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].captives[i]]));
                        SetWindowText(sc_CasNumCapVal, itoa(dr.casArr[cas].numCaptives, itoaArr, 10)); //fill in number of captives static
                    }
                }
                break;
                case ID_SET_CAS_DELCAP:
                {
                    cas     = SendMessage(CasTabCtrls.cb_CasNameList, CB_GETCURSEL, 0, 0); //get selected castle ID
                    count   = SendMessage(CasTabCtrls.lb_casCaptives, LB_GETSELCOUNT, 0, 0);
                    genBuff = (int*)malloc(sizeof(int) * count);
                    SendMessage(CasTabCtrls.lb_casCaptives, LB_GETSELITEMS, WPARAM(count), LPARAM(genBuff));

                    if(dr.casArr[cas].delMultiCapFromList(genBuff, count)) //if captives were deleted, update appropriate combo/list boxes
                    {
                        SendMessage(CasTabCtrls.lb_casCaptives, LB_RESETCONTENT, 0, 0); //redo the castle captives listbox for current castle
                        for(int i = 0; i < dr.casArr[cas].numCaptives; i++) //setting up Captives List combobox
                            SendMessage(CasTabCtrls.lb_casCaptives, LB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].captives[i]]));
                        SetWindowText(sc_CasNumCapVal, itoa(dr.casArr[cas].numCaptives, itoaArr, 10)); //fill in number of captives static
                    }
                    free(genBuff);
                }
                break;
                case ID_SET_CAS_GENTOCAP:
                {
                    cas     = SendMessage(CasTabCtrls.cb_CasNameList, CB_GETCURSEL, 0, 0); //get selected castle ID
                    count   = SendMessage(CasTabCtrls.lb_casGenerals, LB_GETSELCOUNT, 0, 0);
                    genBuff = (int*)malloc(sizeof(int) * count);
                    SendMessage(CasTabCtrls.lb_casGenerals, LB_GETSELITEMS, WPARAM(count), LPARAM(genBuff));

                    success = dr.casArr[cas].fromGenToCap(genBuff, count);

                    if(success == -1)
                        MessageBox(hwnd, "If there are going to be captives, you need at least one general here.", "Error", MB_OK | MB_ICONERROR);
                    
                    if(success == 1)
                    {
                        //redo the listbox for this castle's occupying generals
                        SendMessage(CasTabCtrls.lb_casGenerals, LB_RESETCONTENT, 0, 0); //redo the castle generals listbox for current castle
                        for(int i = 0; i < dr.casArr[cas].numGenerals; i++) //setting up Leaders Names List combobox
                            SendMessage(CasTabCtrls.lb_casGenerals, LB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].generals[i]]));
                        SetWindowText(sc_CasNumGenVal, itoa(dr.casArr[cas].numGenerals, itoaArr, 10)); //fill in number of generals static

                        //redo the castle captives listbox for current castle
                        SendMessage(CasTabCtrls.lb_casCaptives, LB_RESETCONTENT, 0, 0);
                        for(int i = 0; i < dr.casArr[cas].numCaptives; i++) //setting up Captives List combobox
                            SendMessage(CasTabCtrls.lb_casCaptives, LB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].captives[i]]));
                        SetWindowText(sc_CasNumCapVal, itoa(dr.casArr[cas].numCaptives, itoaArr, 10)); //fill in number of captives static

                        //redo leader combobox because generals were deleted
                        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_RESETCONTENT, 0, 0); //clear the leader combobox for current castle
                        EnableWindow(CasTabCtrls.but_SetCasLeader, TRUE); //turn on castle set leader button if castle occupied
                        for(int i = 0; i < dr.casArr[cas].numGenerals; i++) //setting up Leaders Names List combobox
                            SendMessage(CasTabCtrls.cb_CasLeaderList, CB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].generals[i]]));
                        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_SETCURSEL, findLeaderCasIndex(cas), 0);

                        SendMessage(CasTabCtrls.cb_CasRulerList, CB_SETCURSEL, dr.casArr[cas].ruler, 0); //make sure right ruler is set
                    }
                    free(genBuff);
                }
                break;
                case ID_SET_CAS_CAPTOGEN:
                {
                    cas     = SendMessage(CasTabCtrls.cb_CasNameList, CB_GETCURSEL, 0, 0); //get selected castle ID
                    count   = SendMessage(CasTabCtrls.lb_casCaptives, LB_GETSELCOUNT, 0, 0);
                    genBuff = (int*)malloc(sizeof(int) * count);
                    SendMessage(CasTabCtrls.lb_casCaptives, LB_GETSELITEMS, WPARAM(count), LPARAM(genBuff));

                    if(dr.casArr[cas].fromCapToGen(genBuff, count)) //if captives were deleted, update appropriate combo/list boxes
                    {
                        //redo the listbox for this castle's occupying generals
                        SendMessage(CasTabCtrls.lb_casGenerals, LB_RESETCONTENT, 0, 0); //redo the castle generals listbox for current castle
                        for(int i = 0; i < dr.casArr[cas].numGenerals; i++) //setting up Leaders Names List combobox
                            SendMessage(CasTabCtrls.lb_casGenerals, LB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].generals[i]]));
                        SetWindowText(sc_CasNumGenVal, itoa(dr.casArr[cas].numGenerals, itoaArr, 10)); //fill in number of generals static

                        //redo the castle captives listbox for current castle
                        SendMessage(CasTabCtrls.lb_casCaptives, LB_RESETCONTENT, 0, 0);
                        for(int i = 0; i < dr.casArr[cas].numCaptives; i++) //setting up Captives List combobox
                            SendMessage(CasTabCtrls.lb_casCaptives, LB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].captives[i]]));
                        SetWindowText(sc_CasNumCapVal, itoa(dr.casArr[cas].numCaptives, itoaArr, 10)); //fill in number of captives static

                        //redo leader combobox because generals were added
                        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_RESETCONTENT, 0, 0); //clear the leader combobox for current castle
                        EnableWindow(CasTabCtrls.but_SetCasLeader, TRUE); //turn on castle set leader button if castle occupied
                        for(int i = 0; i < dr.casArr[cas].numGenerals; i++) //setting up Leaders Names List combobox
                            SendMessage(CasTabCtrls.cb_CasLeaderList, CB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].generals[i]]));
                        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_SETCURSEL, findLeaderCasIndex(cas), 0);
                    }
                    free(genBuff);
                }
                break;
            }
        break;//WM_COMMAND
        default:
            return CallWindowProc(g_MainWndProc, hwnd, msg, wParam, lParam);
    }

    return 0;
}

int findLeaderCasIndex(const int castle)
{
    int i = 0;


    if(!(dr.casArr[castle].isCastleEmpty()))
        while(dr.casArr[castle].generals[i] != dr.casArr[castle].leader)
            i++;

    return i;
}

void updateCastlesTab(const int cas)
{
    char itoaArr[5] = {'\0'};

    dr.casArr[cas].needsUpdate = false;
    
    for(int i = 0; i < 171; i++) //clear any selections in the generals names listbox
        SendMessage(CasTabCtrls.lb_casGenList, LB_SETSEL, FALSE, i);

//set up the combobox and button for castle ruler
    SendMessage(CasTabCtrls.cb_CasRulerList, CB_RESETCONTENT, 0, 0); //clear the ruler combobox if castle empty
    if(!dr.casArr[cas].numGenerals) //if castle is empty, put a "none" for ruler
    {
        SendMessage(CasTabCtrls.cb_CasRulerList, CB_ADDSTRING, 0, LPARAM("None")); //only add a 'none' option
        SendMessage(CasTabCtrls.cb_CasRulerList, CB_SETCURSEL, 0, 0); //select the 'none' option
        EnableWindow(CasTabCtrls.but_SetCasRuler, FALSE); //turn off castle set ruler button if castle empty
    }
    else //if the castle is occupied, set the rulers name list combobox
        for(int i = 0; i < 171; i++) //setting up Rulers Names List combobox
        {
            SendMessage(CasTabCtrls.cb_CasRulerList, CB_ADDSTRING, 0, LPARAM(generalsNameList[i]));
            SendMessage(CasTabCtrls.cb_CasRulerList, CB_SETCURSEL, dr.casArr[cas].ruler, 0);
            EnableWindow(CasTabCtrls.but_SetCasRuler, TRUE); //turn on castle set ruler button if castle occupied
        }

//set up leader combobox and button
    SendMessage(CasTabCtrls.cb_CasLeaderList, CB_RESETCONTENT, 0, 0); //clear the leader combobox for current castle
    if(!dr.casArr[cas].numGenerals) //if castle empty, turn off SET button and select 'none' in leader list
    {
        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_ADDSTRING, 0, LPARAM("None")); //add 'none' option
        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_SETCURSEL, 0, 0); //choose the 'none' option
        EnableWindow(CasTabCtrls.but_SetCasLeader, FALSE); //turn off castle set leader button if castle empty
    }
    else //if castle occupied, set leader combobox up and enable SET button
    {
        EnableWindow(CasTabCtrls.but_SetCasLeader, TRUE); //turn on castle set leader button if castle occupied
        for(int i = 0; i < dr.casArr[cas].numGenerals; i++) //setting up Leaders Names List combobox
            SendMessage(CasTabCtrls.cb_CasLeaderList, CB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].generals[i]]));
        SendMessage(CasTabCtrls.cb_CasLeaderList, CB_SETCURSEL, findLeaderCasIndex(cas), 0);
    }

//set up the listbox for this castles occupying generals
    SendMessage(CasTabCtrls.lb_casGenerals, LB_RESETCONTENT, 0, 0); //redo the castle generals listbox for current castle
    for(int i = 0; i < dr.casArr[cas].numGenerals; i++) //setting up Leaders Names List combobox
        SendMessage(CasTabCtrls.lb_casGenerals, LB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].generals[i]]));

//set up the listbox for this castles current captives
    SendMessage(CasTabCtrls.lb_casCaptives, LB_RESETCONTENT, 0, 0); //redo the castle captives listbox for current castle
    for(int i = 0; i < dr.casArr[cas].numCaptives; i++) //setting up generals Names List listbox
        SendMessage(CasTabCtrls.lb_casCaptives, LB_ADDSTRING, 0, LPARAM(generalsNameList[dr.casArr[cas].captives[i]]));

    SendMessage(CasTabCtrls.cb_CasLevel, CB_SETCURSEL, dr.casArr[cas].level, 0); //set castle level

//if castle is empty, disable button to set troop reserves
    if(!dr.casArr[cas].numGenerals) //if castle empty, turn off SET button for troop count
        EnableWindow(CasTabCtrls.but_SetCasTroopCount, FALSE);
    else    //otherwise, turn the button back on
        EnableWindow(CasTabCtrls.but_SetCasTroopCount, TRUE);
        
    SetDlgItemInt(hTabCastles, ID_EB_CAS_TRP_CNT, dr.casArr[cas].troopCount, FALSE); //fill troop count field
    SetWindowText(sc_CasMaxTroopsVal, itoa(dr.casArr[cas].maxTroops, itoaArr, 10)); //fill in max troop value static
    SetWindowText(sc_CasNumGenVal, itoa(dr.casArr[cas].numGenerals, itoaArr, 10)); //fill in number of generals static
    SetWindowText(sc_CasNumCapVal, itoa(dr.casArr[cas].numCaptives, itoaArr, 10));  //fill number of captives static
    SetWindowText(sc_CasXCoordVal, itoa(dr.casArr[cas].xCoordinate, itoaArr, 10));  //fill x coordinate static
    SetWindowText(sc_CasYCoordVal, itoa(dr.casArr[cas].yCoordinate, itoaArr, 10));  //fill y coordinate static

    if(dr.casArr[cas].hasPlayerRuler)
        SetWindowText(sc_HasPlayerMonarchVal, "Yes");  //fill has player monarch static
    else
        SetWindowText(sc_HasPlayerMonarchVal, "No");  //fill has player monarch static

    SetWindowText(sc_CasExpCurrVal, itoa(dr.casArr[cas].experience, itoaArr, 10));  //fill curr exp static
    SetWindowText(sc_CasExpNextVal, itoa(dr.casArr[cas].expNext, itoaArr, 10));  //fill next exp static


    return;
}
