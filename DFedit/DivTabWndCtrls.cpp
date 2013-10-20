#include <windows.h>
#include <commctrl.h>
#include <cmath>

#include "DFGui.h"

    static Division localDivArr[171];
    int numArmies = 0;

    HWND sc_DivCurrTroopTag;
    HWND sc_DivCurrTroopVal;

    HWND sc_DivNumTag;
    HWND sc_DivNumVal;
    HWND sc_DivNumGenTag;
    HWND sc_DivNumGenVal;
    HWND sc_DivNumCapTag;
    HWND sc_DivNumCapVal;
    HWND sc_DivXCoordTag;
    HWND sc_DivXCoordVal;
    HWND sc_DivYCoordTag;
    HWND sc_DivYCoordVal;
    HWND sc_DivOriginTag;
    HWND sc_DivOriginVal;
    HWND sc_DivGoalTag;
    HWND sc_DivGoalVal;
    HWND sc_DivPreviousTag;
    HWND sc_DivPreviousVal;
    HWND sc_DivNextTag;
    HWND sc_DivNextVal;
    HWND sc_DivHasPlayerKingTag;
    HWND sc_DivHasPlayerKingVal;

void CreateDivisionsTab(void)
{
    HWND cb_DivNameTag;
    HWND cb_DivRulerTag;
    HWND cb_DivLeaderTag;
    HWND cb_DivGoalTag;
    HWND cb_DivLocTag;
    HWND cb_DivStatusTag;
    HWND lb_DivGeneralsTag;
    HWND lb_DivCaptivesTag;
    HWND lb_DivGenListTag;
    
    HWND DivInfoStaticGroup;

    // create a Static control for our view window
    hTabDivisions = CreateWindowEx(
        0, "STATIC", NULL, WS_CHILD | WS_TABSTOP,
        0, 22, 1009, 688,
        hTabCntrl, NULL, hThisInst, NULL);

    g_MainWndProc = (WNDPROC)SetWindowLongPtr(hTabDivisions, GWL_WNDPROC, (LONG)DivTabWndProc);

    cb_DivNameTag = CreateWindowEx( //Castle name text tag
        0, "STATIC", "Division:", WS_CHILD | WS_VISIBLE,
        10, 28, 43, 20,
        hTabDivisions, NULL, hThisInst, NULL);

    DivTabCtrls.cb_DivNameList = CreateWindowEx( //names list combobox
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 28, 100, 500,
        hTabDivisions, (HMENU)ID_CB_DIVNAME, hThisInst, NULL);

    cb_DivRulerTag = CreateWindowEx( //Castle ruler text tag
        0, "STATIC", "Ruler:", WS_CHILD | WS_VISIBLE,
        10, 53, 43, 20,
        hTabDivisions, NULL, hThisInst, NULL);

    DivTabCtrls.cb_DivRulerList = CreateWindowEx( //rulers list combobox
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 53, 100, 500,
        hTabDivisions, (HMENU)ID_CB_DIV_RULER, hThisInst, NULL);

    DivTabCtrls.but_SetDivRuler = CreateWindowEx(   //ruler set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        215, 53, 40, 20,
        hTabDivisions, (HMENU)ID_SET_DIV_RULER, hThisInst, NULL);

    cb_DivLeaderTag = CreateWindowEx( //Castle leader text tag
        0, "STATIC", "Leader:", WS_CHILD | WS_VISIBLE,
        10, 78, 43, 20,
        hTabDivisions, NULL, hThisInst, NULL);

    DivTabCtrls.cb_DivLeaderList = CreateWindowEx( //leader list combobox
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 78, 100, 500,
        hTabDivisions, (HMENU)ID_CB_DIV_LEADER, hThisInst, NULL);

    DivTabCtrls.but_SetDivLeader = CreateWindowEx(   //leader set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        215, 78, 40, 20,
        hTabDivisions, (HMENU)ID_SET_DIV_LEADER, hThisInst, NULL);

    cb_DivStatusTag = CreateWindowEx( //Division status text tag
        0, "STATIC", "Status:", WS_CHILD | WS_VISIBLE,
        10, 103, 43, 20,
        hTabDivisions, NULL, hThisInst, NULL);

    DivTabCtrls.cb_DivStatusList = CreateWindowEx( //Division current status list
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 103, 100, 500,
        hTabDivisions, (HMENU)ID_CB_DIV_STATUS, hThisInst, NULL);

    DivTabCtrls.but_SetDivStatus = CreateWindowEx(   //current status set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        215, 103, 40, 20,
        hTabDivisions, (HMENU)ID_SET_DIV_STATUS, hThisInst, NULL);

    cb_DivGoalTag = CreateWindowEx( //Division goal text tag
        0, "STATIC", "Goal:", WS_CHILD | WS_VISIBLE,
        10, 128, 43, 20,
        hTabDivisions, NULL, hThisInst, NULL);

    DivTabCtrls.cb_DivGoalList = CreateWindowEx( //Division goal location list
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 128, 160, 500,
        hTabDivisions, (HMENU)ID_CB_DIV_GOAL, hThisInst, NULL);

    DivTabCtrls.but_SetDivGoal = CreateWindowEx(   //goal set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        215, 128, 40, 20,
        hTabDivisions, (HMENU)ID_SET_DIV_GOAL, hThisInst, NULL);

    cb_DivLocTag = CreateWindowEx( //Division location text tag
        0, "STATIC", "Location:", WS_CHILD | WS_VISIBLE,
        10, 153, 43, 20,
        hTabDivisions, NULL, hThisInst, NULL);

    DivTabCtrls.cb_DivLocList = CreateWindowEx( //Division current location list
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 153, 160, 500,
        hTabDivisions, (HMENU)ID_CB_DIV_LOC, hThisInst, NULL);

    DivTabCtrls.but_SetDivLoc = CreateWindowEx(   //current location set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        215, 153, 40, 20,
        hTabDivisions, (HMENU)ID_SET_DIV_LOC, hThisInst, NULL);

    DivInfoStaticGroup = CreateWindowEx( //frame surrounding status information
        0, "BUTTON", "Status Information", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        10, 183, 210, 225, 
        hTabDivisions, NULL, hThisInst, NULL);

    sc_DivNumTag = CreateWindowEx( //division number text tag
        0, "STATIC", "Division #:", WS_CHILD | WS_VISIBLE,
        15, 203, 60, 20, 
        hTabDivisions, NULL, hThisInst, NULL); 

    sc_DivNumVal = CreateWindowEx( //division number value
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 203, 60, 20, 
        hTabDivisions, (HMENU)ID_STATIC_DVT_NUM, hThisInst, NULL); 

    sc_DivNumGenTag = CreateWindowEx(              //number of generals tag
        0, "STATIC", "Generals:", WS_CHILD | WS_VISIBLE,
        15, 233, 60, 20, 
        hTabDivisions, NULL, hThisInst, NULL); 

    sc_DivNumGenVal = CreateWindowEx(              //number of generals value
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 233, 60, 20, 
        hTabDivisions, (HMENU)ID_STATIC_DVTNUMGEN, hThisInst, NULL); 

    sc_DivNumCapTag = CreateWindowEx(              //number of captives tag
        0, "STATIC", "Captives:", WS_CHILD | WS_VISIBLE,
        15, 248, 60, 20, 
        hTabDivisions, NULL, hThisInst, NULL); 

    sc_DivNumCapVal = CreateWindowEx(              //number of captives value
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 248, 80, 20, 
        hTabDivisions, (HMENU)ID_STATIC_DVTNUMCAP, hThisInst, NULL); 

    sc_DivXCoordTag = CreateWindowEx(              //division x coordinate tag
        0, "STATIC", "X Pos:", WS_CHILD | WS_VISIBLE,
        15, 263, 60, 20, 
        hTabDivisions, NULL, hThisInst, NULL); 

    sc_DivXCoordVal = CreateWindowEx(              //division x coordinate val
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 263, 80, 20, 
        hTabDivisions, (HMENU)ID_STATIC_DVT_X, hThisInst, NULL); 

    sc_DivYCoordTag = CreateWindowEx(              //division y coordinate tag
        0, "STATIC", "Y Pos:", WS_CHILD | WS_VISIBLE,
        15, 278, 60, 20, 
        hTabDivisions, NULL, hThisInst, NULL); 

    sc_DivYCoordVal = CreateWindowEx(              //division y coordinate val
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 278, 80, 20, 
        hTabDivisions, (HMENU)ID_STATIC_DVT_Y, hThisInst, NULL); 

    sc_DivHasPlayerKingTag = CreateWindowEx(              //division has monarch tag
        0, "STATIC", "Player King:", WS_CHILD | WS_VISIBLE,
        15, 293, 60, 20, 
        hTabDivisions, NULL, hThisInst, NULL); 

    sc_DivHasPlayerKingVal = CreateWindowEx(              //division has monarch val
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 293, 80, 20, 
        hTabDivisions, (HMENU)ID_STATIC_DVTHASMON, hThisInst, NULL); 

    sc_DivCurrTroopTag = CreateWindowEx(              //current number of troops tag
        0, "STATIC", "Curr Troops:", WS_CHILD | WS_VISIBLE,
        15, 308, 60, 20, 
        hTabDivisions, NULL, hThisInst, NULL); 

    sc_DivCurrTroopVal = CreateWindowEx(              //current number of troops val
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 308, 80, 20, 
        hTabDivisions, (HMENU)ID_STATIC_DVTTRPCNT, hThisInst, NULL); 

    sc_DivOriginTag = CreateWindowEx(              //division origin tag
        0, "STATIC", "Origin:", WS_CHILD | WS_VISIBLE,
        15, 338, 60, 20, 
        hTabDivisions, NULL, hThisInst, NULL); 

    sc_DivOriginVal = CreateWindowEx(              //division origin val
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 338, 120, 20, 
        hTabDivisions, (HMENU)ID_STATIC_DVT_BEG, hThisInst, NULL); 

    sc_DivGoalTag = CreateWindowEx(              //division goal tag
        0, "STATIC", "Goal:", WS_CHILD | WS_VISIBLE,
        15, 353, 60, 20, 
        hTabDivisions, NULL, hThisInst, NULL); 

    sc_DivGoalVal = CreateWindowEx(              //division goal val
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 353, 120, 20, 
        hTabDivisions, (HMENU)ID_STATIC_DVT_GOAL, hThisInst, NULL); 

    sc_DivPreviousTag = CreateWindowEx(              //division previous tag
        0, "STATIC", "Previous:", WS_CHILD | WS_VISIBLE,
        15, 368, 60, 20, 
        hTabDivisions, NULL, hThisInst, NULL); 

    sc_DivPreviousVal = CreateWindowEx(              //division previous val
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 368, 120, 20, 
        hTabDivisions, (HMENU)ID_STATIC_DVT_PREV, hThisInst, NULL); 

    sc_DivNextTag = CreateWindowEx(              //division next tag
        0, "STATIC", "Next:", WS_CHILD | WS_VISIBLE,
        15, 383, 60, 20, 
        hTabDivisions, NULL, hThisInst, NULL); 

    sc_DivNextVal = CreateWindowEx(              //division next val
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        80, 383, 120, 20, 
        hTabDivisions, (HMENU)ID_STATIC_DVT_NEXT, hThisInst, NULL); 

////////////////////////////////////////////////////////////////////////////////
///
/// Second portion of interface
///
////////////////////////////////////////////////////////////////////////////////

    lb_DivGeneralsTag = CreateWindowEx(              //division generals listbox tag
        0, "STATIC", "Generals:", WS_CHILD | WS_VISIBLE,
        295, 28, 60, 20, 
        hTabDivisions, NULL, hThisInst, NULL); 

    DivTabCtrls.lb_DivGenerals = CreateWindowEx( //division generals listbox
        WS_EX_CLIENTEDGE, "LISTBOX", NULL, WS_CHILD | WS_VISIBLE | 
        WS_TABSTOP | WS_DISABLED | LBS_EXTENDEDSEL | LBS_NOTIFY,
        295, 53, 100, 150,
        hTabDivisions, (HMENU)ID_LB_DIV_GENERALS, hThisInst, NULL);

    lb_DivCaptivesTag = CreateWindowEx(              //division captives listbox tag
        0, "STATIC", "Captives:", WS_CHILD | WS_VISIBLE,
        295, 218, 60, 20,
        hTabDivisions, NULL, hThisInst, NULL); 

    DivTabCtrls.lb_DivCaptives = CreateWindowEx( //division captives listbox
        WS_EX_CLIENTEDGE, "LISTBOX", NULL, WS_VSCROLL | WS_CHILD | WS_VISIBLE | 
        WS_TABSTOP | WS_DISABLED | LBS_EXTENDEDSEL | LBS_NOTIFY,
        295, 243, 100, 150,
        hTabDivisions, (HMENU)ID_LB_DIV_CAPTIVES, hThisInst, NULL);

    lb_DivGenListTag = CreateWindowEx(              //division generals name list listbox tag
        0, "STATIC", "Generals List:", WS_CHILD | WS_VISIBLE,
        460, 28, 80, 20,
        hTabDivisions, NULL, hThisInst, NULL); 

    DivTabCtrls.lb_DivGenList = CreateWindowEx( //division generals name list listbox
        WS_EX_CLIENTEDGE, "LISTBOX", NULL, WS_VSCROLL | WS_CHILD | WS_VISIBLE | 
        WS_TABSTOP | WS_DISABLED | LBS_EXTENDEDSEL | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
        460, 53, 100, 343,
        hTabDivisions, (HMENU)ID_LB_DIV_GEN_LIST, hThisInst, NULL);

    DivTabCtrls.but_DivAddGenerals = CreateWindowEx(   //division add generals button
        0, "BUTTON", "<<", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        407, 98, 40, 20,
        hTabDivisions, (HMENU)ID_SET_DIV_ADDGEN, hThisInst, NULL);

    DivTabCtrls.but_DivDelGenerals = CreateWindowEx(   //division remove generals button
        0, "BUTTON", ">>", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        407, 128, 40, 20,
        hTabDivisions, (HMENU)ID_SET_DIV_DELGEN, hThisInst, NULL);

    DivTabCtrls.but_DivAddCaptives = CreateWindowEx(   //division add captives button
        0, "BUTTON", "<<", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        407, 288, 40, 20,
        hTabDivisions, (HMENU)ID_SET_DIV_ADDCAP, hThisInst, NULL);

    DivTabCtrls.but_DivDelCaptives = CreateWindowEx(   //division remove captives button
        0, "BUTTON", ">>", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        407, 318, 40, 20,
        hTabDivisions, (HMENU)ID_SET_DIV_DELCAP, hThisInst, NULL);

    DivTabCtrls.but_DivGeneralToCaptive = CreateWindowEx(   //division move general to captive
        0, "BUTTON", "V", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        345, 210, 20, 20,
        hTabDivisions, (HMENU)ID_SET_DIV_GENTOCAP, hThisInst, NULL);

    DivTabCtrls.but_DivCaptiveToGeneral = CreateWindowEx(   //division move captive to general
        0, "BUTTON", "^", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        375, 210, 20, 20,
        hTabDivisions, (HMENU)ID_SET_DIV_CAPTOGEN, hThisInst, NULL);

    SetDefaultFont(hTabDivisions);
    SetDefaultFont(cb_DivNameTag);
    SetDefaultFont(cb_DivRulerTag);
    SetDefaultFont(cb_DivLeaderTag);
    SetDefaultFont(cb_DivGoalTag);
    SetDefaultFont(cb_DivLocTag);
    SetDefaultFont(cb_DivStatusTag);
    SetDefaultFont(sc_DivCurrTroopTag);
    SetDefaultFont(sc_DivCurrTroopVal);
    SetDefaultFont(lb_DivGeneralsTag);
    SetDefaultFont(lb_DivCaptivesTag);
    SetDefaultFont(lb_DivGenListTag);

    SetDefaultFont(DivInfoStaticGroup);
    SetDefaultFont(sc_DivNumTag);
    SetDefaultFont(sc_DivNumVal);
    SetDefaultFont(sc_DivNumGenTag);
    SetDefaultFont(sc_DivNumGenVal);
    SetDefaultFont(sc_DivNumCapTag);
    SetDefaultFont(sc_DivNumCapVal);
    SetDefaultFont(sc_DivXCoordTag);
    SetDefaultFont(sc_DivXCoordVal);
    SetDefaultFont(sc_DivYCoordTag);
    SetDefaultFont(sc_DivYCoordVal);
    SetDefaultFont(sc_DivHasPlayerKingTag);
    SetDefaultFont(sc_DivHasPlayerKingVal);
    SetDefaultFont(sc_DivOriginTag);
    SetDefaultFont(sc_DivOriginVal);
    SetDefaultFont(sc_DivGoalTag);
    SetDefaultFont(sc_DivGoalVal);
    SetDefaultFont(sc_DivPreviousTag);
    SetDefaultFont(sc_DivPreviousVal);
    SetDefaultFont(sc_DivNextTag);
    SetDefaultFont(sc_DivNextVal);

    SetDefaultFont(DivTabCtrls.cb_DivNameList);
    SetDefaultFont(DivTabCtrls.cb_DivRulerList);
    SetDefaultFont(DivTabCtrls.but_SetDivRuler);
    SetDefaultFont(DivTabCtrls.cb_DivLeaderList);
    SetDefaultFont(DivTabCtrls.but_SetDivLeader);
    SetDefaultFont(DivTabCtrls.cb_DivGoalList);
    SetDefaultFont(DivTabCtrls.but_SetDivGoal);
    SetDefaultFont(DivTabCtrls.cb_DivLocList);
    SetDefaultFont(DivTabCtrls.but_SetDivLoc);
    SetDefaultFont(DivTabCtrls.cb_DivStatusList);
    SetDefaultFont(DivTabCtrls.but_SetDivStatus);
    SetDefaultFont(DivTabCtrls.lb_DivGenerals);
    SetDefaultFont(DivTabCtrls.lb_DivCaptives);
    SetDefaultFont(DivTabCtrls.lb_DivGenList);
    SetDefaultFont(DivTabCtrls.but_DivAddGenerals);
    SetDefaultFont(DivTabCtrls.but_DivDelGenerals);
    SetDefaultFont(DivTabCtrls.but_DivAddCaptives);
    SetDefaultFont(DivTabCtrls.but_DivDelCaptives);
    SetDefaultFont(DivTabCtrls.but_DivGeneralToCaptive);
    SetDefaultFont(DivTabCtrls.but_DivCaptiveToGeneral);

    return;
}

void PopulateDivisionsTab(void)
{
    char itoaArr[5] = {'\0'};

/*
    Copied here from PopulateGeneralsTab as reminder that this stuff has been set up already
    dr.fr.readFile();   //read the save file
    dr.initGenerals();  //create the generals array
    dr.setMonarch();    //find who the player's monarch is
    dr.initCastles();   //create the castles array
    dr.initDivisions(); //create the divisions array
*/

    updateLocalDivArr();

    if(numArmies)
    {
        EnableWindow(DivTabCtrls.cb_DivNameList, TRUE); //turn on names list combobox
        EnableWindow(DivTabCtrls.cb_DivRulerList, TRUE); //turn on ruler list combobox
        EnableWindow(DivTabCtrls.but_SetDivRuler, TRUE); //turn on ruler set button
        EnableWindow(DivTabCtrls.cb_DivLeaderList, TRUE); //turn on division leader combobox
        EnableWindow(DivTabCtrls.but_SetDivLeader, TRUE); //turn on division leader set button
        EnableWindow(DivTabCtrls.cb_DivGoalList, TRUE); //turn on division goal combobox
        EnableWindow(DivTabCtrls.but_SetDivGoal, TRUE); //turn on division goal set button
        EnableWindow(DivTabCtrls.cb_DivLocList, TRUE); //turn on division location combobox
        EnableWindow(DivTabCtrls.but_SetDivLoc, TRUE); //turn on division location set button
        EnableWindow(DivTabCtrls.cb_DivStatusList, TRUE); //turn on division status combobox
        EnableWindow(DivTabCtrls.but_SetDivStatus, TRUE); //turn on division status set button
        EnableWindow(DivTabCtrls.lb_DivGenerals, TRUE); //turn on division generals list box
        EnableWindow(DivTabCtrls.lb_DivCaptives, TRUE); //turn on division captives list box
        EnableWindow(DivTabCtrls.lb_DivGenList, TRUE); //turn on division generals name list listbox
        EnableWindow(DivTabCtrls.but_DivAddGenerals, TRUE); //turn on division add generals button
        EnableWindow(DivTabCtrls.but_DivDelGenerals, TRUE); //turn on division remove generals button
        EnableWindow(DivTabCtrls.but_DivAddCaptives, TRUE); //turn on division add captives button
        EnableWindow(DivTabCtrls.but_DivDelCaptives, TRUE); //turn on division remove captives button
        EnableWindow(DivTabCtrls.but_DivGeneralToCaptive, TRUE); //turn on division move generals to captive
        EnableWindow(DivTabCtrls.but_DivCaptiveToGeneral, TRUE); //turn on division move captives to generals

        SendMessage(DivTabCtrls.cb_DivNameList, CB_RESETCONTENT, 0, 0); //make sure to reset division names combobox
        SendMessage(DivTabCtrls.cb_DivRulerList, CB_RESETCONTENT, 0, 0); //make sure to reset division ruler combobox
        SendMessage(DivTabCtrls.cb_DivLeaderList, CB_RESETCONTENT, 0, 0); //make sure to reset possible-leader combobox
        SendMessage(DivTabCtrls.cb_DivGoalList, CB_RESETCONTENT, 0, 0); //make sure to reset division goal list combobox
        SendMessage(DivTabCtrls.cb_DivLocList, CB_RESETCONTENT, 0, 0); //make sure to reset division location list combobox
        SendMessage(DivTabCtrls.cb_DivStatusList, CB_RESETCONTENT, 0, 0); //make sure to reset division status combobox

        SendMessage(DivTabCtrls.lb_DivGenerals, LB_RESETCONTENT, 0, 0); //make sure to reset division members listbox
        SendMessage(DivTabCtrls.lb_DivCaptives, LB_RESETCONTENT, 0, 0); //make sure to reset division captives listbox
        SendMessage(DivTabCtrls.lb_DivGenList, LB_RESETCONTENT, 0, 0); //make sure to reset master generals listbox

        SendMessage(DivTabCtrls.lb_DivGenList, LB_RESETCONTENT, 0, 0); //make sure to reset master generals listbox
        for(int i = 0; i < 171; i++) //setting up master Generals Names List listbox
            SendMessage(DivTabCtrls.lb_DivGenList, LB_ADDSTRING, 0, LPARAM(generalsNameList[i]));

        for(int i = 0; i < 171; i++) //setting up Rulers Names List combobox
            SendMessage(DivTabCtrls.cb_DivRulerList, CB_ADDSTRING, 0, LPARAM(generalsNameList[i]));
        SendMessage(DivTabCtrls.cb_DivRulerList, CB_SETCURSEL, localDivArr[0].ruler, 0);

        for(int i = 0; i < numArmies; i++) //set up the list of division names
            SendMessage(DivTabCtrls.cb_DivNameList, CB_ADDSTRING, 0, LPARAM(generalsNameList[localDivArr[i].leader])); //division name combobox
        SendMessage(DivTabCtrls.cb_DivNameList, CB_SETCURSEL, 0, 0); //select first division
        
        for(int i = 0; i < localDivArr[0].numMembers; i++)
        {
            SendMessage(DivTabCtrls.cb_DivLeaderList, CB_ADDSTRING, 0, LPARAM(generalsNameList[localDivArr[0].members[i]])); //division leader combobox
            SendMessage(DivTabCtrls.lb_DivGenerals, LB_ADDSTRING, 0, LPARAM(generalsNameList[localDivArr[0].members[i]])); //division members listbox
        }
        SendMessage(DivTabCtrls.cb_DivLeaderList, CB_SETCURSEL, findLeaderDivIndex(0), 0); //select current leader

        for(int i = 0; i < localDivArr[0].numCaptives; i++)
            SendMessage(DivTabCtrls.lb_DivCaptives, LB_ADDSTRING, 0, LPARAM(generalsNameList[localDivArr[0].captives[i]])); //division captives listbox

         for(int i = 0; i < 114; i++) //setting up goal list combobox and location list combobox
         {
            SendMessage(DivTabCtrls.cb_DivGoalList, CB_ADDSTRING, 0, LPARAM(locationList[i]));
            SendMessage(DivTabCtrls.cb_DivLocList, CB_ADDSTRING, 0, LPARAM(locationList[i]));
         }
         SendMessage(DivTabCtrls.cb_DivLocList, CB_DELETESTRING, 113, 0);
         SendMessage(DivTabCtrls.cb_DivGoalList, CB_SETCURSEL, localDivArr[0].goal, 0); //select goal
         SendMessage(DivTabCtrls.cb_DivLocList, CB_SETCURSEL, localDivArr[0].prev, 0);  //select "previous location" to use for location changing box

        for(int i = 0; i < 28; i++) //setting up division status combobox
            SendMessage(DivTabCtrls.cb_DivStatusList, CB_ADDSTRING, 0, LPARAM(shidanStatus[i]));
        SendMessage(DivTabCtrls.cb_DivStatusList, CB_SETCURSEL, localDivArr[0].status, 0); //select division status

        SetWindowText(sc_DivNumVal, itoa(localDivArr[0].divNum, itoaArr, 10));  //fill division number static
        SetWindowText(sc_DivNumGenVal, itoa(localDivArr[0].numMembers, itoaArr, 10));  //fill division members static
        SetWindowText(sc_DivNumCapVal, itoa(localDivArr[0].numCaptives, itoaArr, 10));  //fill division captives static
        SetWindowText(sc_DivXCoordVal, itoa(localDivArr[0].xCoordinate, itoaArr, 10));  //fill division x coord static
        SetWindowText(sc_DivYCoordVal, itoa(localDivArr[0].yCoordinate, itoaArr, 10));  //fill division y coord static

        if(localDivArr[0].hasPlayerRuler)
            SetWindowText(sc_DivHasPlayerKingVal, "Yes");  //fill has player monarch static
        else
            SetWindowText(sc_DivHasPlayerKingVal, "No");  //fill has player monarch static

        SetWindowText(sc_DivCurrTroopVal, itoa(localDivArr[0].troopCount, itoaArr, 10));  //fill division troop count static

        SetWindowText(sc_DivOriginVal, locationList[localDivArr[0].origin]);
        if(localDivArr[0].goal == 255)
            SetWindowText(sc_DivGoalVal, locationList[113]);
        else
            SetWindowText(sc_DivGoalVal, locationList[localDivArr[0].goal]);
        SetWindowText(sc_DivPreviousVal, locationList[localDivArr[0].prev]);
        SetWindowText(sc_DivNextVal, locationList[localDivArr[0].next]);
    }
    else
    {
        SendMessage(DivTabCtrls.cb_DivNameList, CB_RESETCONTENT, 0, 0);
        SendMessage(DivTabCtrls.cb_DivRulerList, CB_RESETCONTENT, 0, 0);
        SendMessage(DivTabCtrls.cb_DivLeaderList, CB_RESETCONTENT, 0, 0);
        SendMessage(DivTabCtrls.cb_DivGoalList, CB_RESETCONTENT, 0, 0);
        SendMessage(DivTabCtrls.cb_DivLocList, CB_RESETCONTENT, 0, 0);
        SendMessage(DivTabCtrls.cb_DivStatusList, CB_RESETCONTENT, 0, 0);
        SendMessage(DivTabCtrls.lb_DivGenList, LB_RESETCONTENT, 0, 0);
        SendMessage(DivTabCtrls.lb_DivCaptives, LB_RESETCONTENT, 0, 0);
        SendMessage(DivTabCtrls.lb_DivGenerals, LB_RESETCONTENT, 0, 0);

        EnableWindow(DivTabCtrls.cb_DivNameList, FALSE); //turn off names list combobox
        EnableWindow(DivTabCtrls.cb_DivRulerList, FALSE); //turn off ruler list combobox
        EnableWindow(DivTabCtrls.but_SetDivRuler, FALSE); //turn off ruler set button
        EnableWindow(DivTabCtrls.cb_DivLeaderList, FALSE); //turn off division leader combobox
        EnableWindow(DivTabCtrls.but_SetDivLeader, FALSE); //turn off division leader set button
        EnableWindow(DivTabCtrls.cb_DivGoalList, FALSE); //turn off division goal combobox
        EnableWindow(DivTabCtrls.but_SetDivGoal, FALSE); //turn off division goal set button
        EnableWindow(DivTabCtrls.cb_DivLocList, FALSE); //turn off division location combobox
        EnableWindow(DivTabCtrls.but_SetDivLoc, FALSE); //turn off division location set button
        EnableWindow(DivTabCtrls.cb_DivStatusList, FALSE); //turn off division status combobox
        EnableWindow(DivTabCtrls.but_SetDivStatus, FALSE); //turn off division status set button
        EnableWindow(DivTabCtrls.lb_DivGenerals, FALSE); //turn off division generals list box
        EnableWindow(DivTabCtrls.lb_DivCaptives, FALSE); //turn off division captives list box
        EnableWindow(DivTabCtrls.lb_DivGenList, FALSE); //turn off division generals name list listbox
        EnableWindow(DivTabCtrls.but_DivAddGenerals, FALSE); //turn off division add generals button
        EnableWindow(DivTabCtrls.but_DivDelGenerals, FALSE); //turn off division remove generals button
        EnableWindow(DivTabCtrls.but_DivAddCaptives, FALSE); //turn off division add captives button
        EnableWindow(DivTabCtrls.but_DivDelCaptives, FALSE); //turn off division remove captives button
        EnableWindow(DivTabCtrls.but_DivGeneralToCaptive, FALSE); //turn off division move generals to captive
        EnableWindow(DivTabCtrls.but_DivCaptiveToGeneral, FALSE); //turn off division move captives to generals

        SetWindowText(sc_DivNumVal, "");  //fill division number static
        SetWindowText(sc_DivNumGenVal, "");  //fill division members static
        SetWindowText(sc_DivNumCapVal, "");  //fill division captives static
        SetWindowText(sc_DivXCoordVal, "");  //fill division x coord static
        SetWindowText(sc_DivYCoordVal, "");  //fill division y coord static
        SetWindowText(sc_DivHasPlayerKingVal, "");  //fill has player monarch static
        SetWindowText(sc_DivCurrTroopVal, "");  //fill division troop count static
        SetWindowText(sc_DivOriginVal, "");
        SetWindowText(sc_DivGoalVal, "");
        SetWindowText(sc_DivPreviousVal, "");
        SetWindowText(sc_DivNextVal, "");
    }

    return;
}

LRESULT CALLBACK DivTabWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int  div          = -1;
    int  drDivNum     = -1;
    int  numArmiesOld = 0;
    int  count        = 0;
    int  success      = 0;
    int* genBuff      = NULL;
    char itoaArr[5]   = {'\0'};

    switch(msg)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_CB_DIVNAME:
                    switch(HIWORD(wParam))
                    {
                        case CBN_SELCHANGE:
                        {
                            div = SendMessage(DivTabCtrls.cb_DivNameList, CB_GETCURSEL, 0, 0);
                            updateDivisionsTab(div);
                        }
                        break; //CBN_SELCHANGE
                    }
                break;
                case ID_SET_DIV_RULER:
                {
                    int newRuler;
                    div      = SendMessage(DivTabCtrls.cb_DivNameList, CB_GETCURSEL, 0, 0); //get selected division ID
                    drDivNum = localDivArr[div].divNum;
                    newRuler = SendMessage(DivTabCtrls.cb_DivRulerList, CB_GETCURSEL, 0, 0);
                    success  = dr.divArr[drDivNum].changeRuler(newRuler); //only changes the local division array
                    if(!success)
                    {
                        MessageBox(hwnd, "The ruler can't be changed because your monarch is located here.", "Error", MB_OK | MB_ICONERROR);
                        SendMessage(DivTabCtrls.cb_DivRulerList, CB_SETCURSEL, localDivArr[div].ruler, 0);
                    }
                    updateLocalDivArr();
                    if(success == 2)
                        SendMessage(DivTabCtrls.cb_DivLeaderList, CB_SETCURSEL, localDivArr[div].findRulerIndex(), 0);
                }
                break; //ID_SET_DIV_RULER
                case ID_SET_DIV_LEADER:
                {
                    int newLeader;
                    div       = SendMessage(DivTabCtrls.cb_DivNameList, CB_GETCURSEL, 0, 0); //get selected division ID
                    drDivNum  = localDivArr[div].divNum;
                    newLeader = SendMessage(DivTabCtrls.cb_DivLeaderList, CB_GETCURSEL, 0, 0); //get selected leader
                    success   = dr.divArr[drDivNum].changeLeader(newLeader);
                    if(!success)
                    {
                        MessageBox(hwnd, "The leader can't be changed because the division's ruler is present.", "Error", MB_OK | MB_ICONERROR);
                        SendMessage(DivTabCtrls.cb_DivLeaderList, CB_SETCURSEL, findLeaderDivIndex(div), 0);
                    }
                    if(success == 1)
                    {
                        updateLocalDivArr();
                        //redo division names combobox because leader was changed
                        SendMessage(DivTabCtrls.cb_DivNameList, CB_RESETCONTENT, 0, 0); //clear the division names combobox
                        for(int i = 0; i < numArmies; i++)
                            SendMessage(DivTabCtrls.cb_DivNameList, CB_ADDSTRING, 0, LPARAM(generalsNameList[localDivArr[i].leader])); //division name combobox
                        SendMessage(DivTabCtrls.cb_DivNameList, CB_SETCURSEL, div, 0); //select first division

                        //redo leader combobox because leader was changed
                        SendMessage(DivTabCtrls.cb_DivLeaderList, CB_RESETCONTENT, 0, 0); //clear the leader combobox for current division
                        for(int i = 0; i < localDivArr[div].numMembers; i++) //setting up Leaders Names List combobox
                            SendMessage(DivTabCtrls.cb_DivLeaderList, CB_ADDSTRING, 0, LPARAM(generalsNameList[localDivArr[div].members[i]]));
                        SendMessage(DivTabCtrls.cb_DivLeaderList, CB_SETCURSEL, findLeaderDivIndex(div), 0);
                    }
                }
                break; //ID_SET_DIV_LEADER
                case ID_SET_DIV_STATUS:
                {
                    int newStatus;
                    numArmiesOld = numArmies;
                    div          = SendMessage(DivTabCtrls.cb_DivNameList, CB_GETCURSEL, 0, 0); //get selected division ID
                    drDivNum     = localDivArr[div].divNum;
                    newStatus    = SendMessage(DivTabCtrls.cb_DivStatusList, CB_GETCURSEL, 0, 0); //get selected division status
                    dr.divArr[drDivNum].changeStatus(newStatus);

                    PopulateDivisionsTab(); //redo the divisions tab information
                    if(numArmiesOld == numArmies)
                        updateDivisionsTab(div);
                    else
                        if(numArmies)
                            updateDivisionsTab(0); //don't know how divisions have changed, so just select the first one
                }
                break; //ID_SET_DIV_STATUS
                case ID_SET_DIV_GOAL:
                {
                    int newGoal;
                    div      = SendMessage(DivTabCtrls.cb_DivNameList, CB_GETCURSEL, 0, 0); //get selected division ID
                    drDivNum = localDivArr[div].divNum;
                    newGoal  = SendMessage(DivTabCtrls.cb_DivGoalList, CB_GETCURSEL, 0, 0); //get selected division goal
                    dr.divArr[drDivNum].changeGoal(newGoal);
                    updateLocalDivArr();
                    SetWindowText(sc_DivGoalVal, locationList[newGoal]);
                }
                break; //ID_SET_DIV_GOAL
                case ID_SET_DIV_LOC:
                {
                    int newLoc;
                    div      = SendMessage(DivTabCtrls.cb_DivNameList, CB_GETCURSEL, 0, 0); //get selected division ID
                    drDivNum = localDivArr[div].divNum;
                    newLoc   = SendMessage(DivTabCtrls.cb_DivLocList, CB_GETCURSEL, 0, 0); //get selected division goal
                    dr.divArr[drDivNum].setDivisionCoords(newLoc);

                    updateLocalDivArr();
                    SetWindowText(sc_DivXCoordVal, itoa(localDivArr[div].xCoordinate, itoaArr, 10));  //fill division x coord static
                    SetWindowText(sc_DivYCoordVal, itoa(localDivArr[div].yCoordinate, itoaArr, 10));  //fill division y coord static
                    SetWindowText(sc_DivPreviousVal, locationList[localDivArr[div].prev]);
                    SetWindowText(sc_DivNextVal, locationList[localDivArr[div].next]);
                    SendMessage(DivTabCtrls.cb_DivStatusList, CB_SETCURSEL, localDivArr[div].status, 0); //set division status
                }
                break; //ID_SET_DIV_LOC
                case ID_SET_DIV_ADDGEN:
                {
                    numArmiesOld = numArmies;
                    div          = SendMessage(DivTabCtrls.cb_DivNameList, CB_GETCURSEL, 0, 0); //get selected division ID
                    drDivNum     = localDivArr[div].divNum;
                    count        = SendMessage(DivTabCtrls.lb_DivGenList, LB_GETSELCOUNT, 0, 0);
                    genBuff      = (int*)malloc(sizeof(int) * count);
                    SendMessage(DivTabCtrls.lb_DivGenList, LB_GETSELITEMS, WPARAM(count), LPARAM(genBuff));

                    if(dr.divArr[drDivNum].addMultiGenFromList(genBuff, count)) //if generals were added, update the tab
                    {
                        PopulateDivisionsTab(); //redo the divisions tab information

                        if(numArmiesOld == numArmies)
                            updateDivisionsTab(div);
                        else
                            if(numArmies)
                                updateDivisionsTab(0); //don't know how divisions have changed, so just select the first one
                    }
                    free(genBuff);
                }
                break; //ID_SET_DIV_ADDGEN
                case ID_SET_DIV_DELGEN:
                {
                    numArmiesOld = numArmies;
                    div          = SendMessage(DivTabCtrls.cb_DivNameList, CB_GETCURSEL, 0, 0); //get selected division ID
                    drDivNum     = localDivArr[div].divNum;
                    count        = SendMessage(DivTabCtrls.lb_DivGenerals, LB_GETSELCOUNT, 0, 0);
                    genBuff      = (int*)malloc(sizeof(int) * count);
                    SendMessage(DivTabCtrls.lb_DivGenerals, LB_GETSELITEMS, WPARAM(count), LPARAM(genBuff));

                    if(dr.divArr[drDivNum].delMultiGenFromList(genBuff, count)) //if generals were deleted, update the tab
                    {
                        PopulateDivisionsTab(); //redo the divisions tab information

                        if(numArmiesOld == numArmies)
                            updateDivisionsTab(div);
                        else
                            if(numArmies)
                                updateDivisionsTab(0); //don't know how divisions have changed, so just select the first one
                    }
                    free(genBuff);
                }
                break; //ID_SET_DIV_DELGEN
                case ID_SET_DIV_ADDCAP:
                {
                    numArmiesOld = numArmies;
                    div          = SendMessage(DivTabCtrls.cb_DivNameList, CB_GETCURSEL, 0, 0); //get selected division ID
                    drDivNum     = localDivArr[div].divNum;
                    count        = SendMessage(DivTabCtrls.lb_DivGenList, LB_GETSELCOUNT, 0, 0);
                    genBuff      = (int*)malloc(sizeof(int) * count);
                    SendMessage(DivTabCtrls.lb_DivGenList, LB_GETSELITEMS, WPARAM(count), LPARAM(genBuff));

                    if(dr.divArr[drDivNum].addMultiCapFromList(genBuff, count)) //if captives were added, update the tab
                    {
                        PopulateDivisionsTab(); //redo the divisions tab information

                        if(numArmiesOld == numArmies)
                            updateDivisionsTab(div);
                        else
                            if(numArmies)
                                updateDivisionsTab(0); //don't know how divisions have changed, so just select the first one
                    }
                    free(genBuff);
                }
                break; //ID_SET_DIV_ADDCAP
                case ID_SET_DIV_DELCAP:
                {
                    numArmiesOld = numArmies;
                    div          = SendMessage(DivTabCtrls.cb_DivNameList, CB_GETCURSEL, 0, 0); //get selected division ID
                    drDivNum     = localDivArr[div].divNum;
                    count        = SendMessage(DivTabCtrls.lb_DivCaptives, LB_GETSELCOUNT, 0, 0);
                    genBuff      = (int*)malloc(sizeof(int) * count);
                    SendMessage(DivTabCtrls.lb_DivCaptives, LB_GETSELITEMS, WPARAM(count), LPARAM(genBuff));

                    if(dr.divArr[drDivNum].delMultiCapFromList(genBuff, count)) //if captives were deleted, update the tab
                    {
                        PopulateDivisionsTab(); //redo the divisions tab information

                        if(numArmiesOld == numArmies)
                            updateDivisionsTab(div);
                        else
                            if(numArmies)
                                updateDivisionsTab(0); //don't know how divisions have changed, so just select the first one
                    }
                    free(genBuff);
                }
                break; //ID_SET_DIV_DELCAP
                case ID_SET_DIV_GENTOCAP:
                {
                    numArmiesOld = numArmies;
                    div          = SendMessage(DivTabCtrls.cb_DivNameList, CB_GETCURSEL, 0, 0); //get selected division ID
                    drDivNum     = localDivArr[div].divNum;
                    count        = SendMessage(DivTabCtrls.lb_DivGenerals, LB_GETSELCOUNT, 0, 0);
                    genBuff      = (int*)malloc(sizeof(int) * count);
                    SendMessage(DivTabCtrls.lb_DivGenerals, LB_GETSELITEMS, WPARAM(count), LPARAM(genBuff));

                    if(dr.divArr[drDivNum].fromGenToCap(genBuff, count)) //if generals were demoted to captives, update the tab
                    {
                        PopulateDivisionsTab(); //redo the divisions tab information

                        if(numArmiesOld == numArmies)
                            updateDivisionsTab(div);
                        else
                            if(numArmies)
                                updateDivisionsTab(0); //don't know how divisions have changed, so just select the first one
                    }
                    free(genBuff);
                }
                break; //ID_SET_DIV_GENTOCAP
                case ID_SET_DIV_CAPTOGEN:
                {
                    numArmiesOld = numArmies;
                    div          = SendMessage(DivTabCtrls.cb_DivNameList, CB_GETCURSEL, 0, 0); //get selected division ID
                    drDivNum     = localDivArr[div].divNum;
                    count        = SendMessage(DivTabCtrls.lb_DivCaptives, LB_GETSELCOUNT, 0, 0);
                    genBuff      = (int*)malloc(sizeof(int) * count);
                    SendMessage(DivTabCtrls.lb_DivCaptives, LB_GETSELITEMS, WPARAM(count), LPARAM(genBuff));

                    if(dr.divArr[drDivNum].fromCapToGen(genBuff, count)) //if captives were promoted to generals, update the tab
                    {
                        PopulateDivisionsTab(); //redo the divisions tab information

                        if(numArmiesOld == numArmies)
                            updateDivisionsTab(div);
                        else
                            if(numArmies)
                                updateDivisionsTab(0); //don't know how divisions have changed, so just select the first one
                    }
                    free(genBuff);
                }
                break; //ID_SET_DIV_CAPTOGEN
            }
        break;
        default:
            return CallWindowProc(g_MainWndProc, hwnd, msg, wParam, lParam);
    }

    return 0;
}

int findLeaderDivIndex(const int div)
{
    int i = 0;

    while(localDivArr[div].members[i] != localDivArr[div].leader)
        i++;

    return i;
}

void updateDivisionsTab(const int div)
{
    char itoaArr[5] = {'\0'};

    if(!numArmies)
    {
        PopulateDivisionsTab();
        return;
    }

    SendMessage(DivTabCtrls.cb_DivNameList, CB_SETCURSEL, div, 0);
    SendMessage(DivTabCtrls.cb_DivRulerList, CB_SETCURSEL, localDivArr[div].ruler, 0); //set division's ruler

    SendMessage(DivTabCtrls.cb_DivLeaderList, CB_RESETCONTENT, 0, 0); //prepare to redo possible-leader combobox
    SendMessage(DivTabCtrls.lb_DivGenerals, LB_RESETCONTENT, 0, 0); //prepare to redo division members listbox
    for(int i = 0; i < localDivArr[div].numMembers; i++)
    {
        SendMessage(DivTabCtrls.cb_DivLeaderList, CB_ADDSTRING, 0, LPARAM(generalsNameList[localDivArr[div].members[i]])); //division leader combobox
        SendMessage(DivTabCtrls.lb_DivGenerals, LB_ADDSTRING, 0, LPARAM(generalsNameList[localDivArr[div].members[i]])); //division members listbox
    }
    SendMessage(DivTabCtrls.cb_DivLeaderList, CB_SETCURSEL, findLeaderDivIndex(div), 0); //select current leader

    SendMessage(DivTabCtrls.lb_DivCaptives, LB_RESETCONTENT, 0, 0); //prepare to redo division captives listbox
    for(int i = 0; i < localDivArr[div].numCaptives; i++)
        SendMessage(DivTabCtrls.lb_DivCaptives, LB_ADDSTRING, 0, LPARAM(generalsNameList[localDivArr[div].captives[i]])); //division captives listbox

    if(localDivArr[div].goal == 255)
        SendMessage(DivTabCtrls.cb_DivGoalList, CB_SETCURSEL, 113, 0); //select item 113 in location list if the goal is player's monarch
    else
        SendMessage(DivTabCtrls.cb_DivGoalList, CB_SETCURSEL, localDivArr[div].goal, 0); //select goal
    SendMessage(DivTabCtrls.cb_DivLocList, CB_SETCURSEL, localDivArr[div].prev, 0);  //select "previous location" to use for location changing box
    SendMessage(DivTabCtrls.cb_DivStatusList, CB_SETCURSEL, localDivArr[div].status, 0); //select division status

    SetWindowText(sc_DivNumVal, itoa(localDivArr[div].divNum, itoaArr, 10));  //fill division number static
    SetWindowText(sc_DivNumGenVal, itoa(localDivArr[div].numMembers, itoaArr, 10));  //fill division members static
    SetWindowText(sc_DivNumCapVal, itoa(localDivArr[div].numCaptives, itoaArr, 10));  //fill division captives static
    SetWindowText(sc_DivXCoordVal, itoa(localDivArr[div].xCoordinate, itoaArr, 10));  //fill division x coord static
    SetWindowText(sc_DivYCoordVal, itoa(localDivArr[div].yCoordinate, itoaArr, 10));  //fill division y coord static

    if(localDivArr[div].hasPlayerRuler)
        SetWindowText(sc_DivHasPlayerKingVal, "Yes");  //fill has player monarch static
    else
        SetWindowText(sc_DivHasPlayerKingVal, "No");  //fill has player monarch static

    SetWindowText(sc_DivCurrTroopVal, itoa(localDivArr[div].troopCount, itoaArr, 10));  //fill division troop count static

    SetWindowText(sc_DivOriginVal, locationList[localDivArr[div].origin]);
    if(localDivArr[div].goal == 255)
        SetWindowText(sc_DivGoalVal, locationList[113]);
    else
        SetWindowText(sc_DivGoalVal, locationList[localDivArr[div].goal]);
    SetWindowText(sc_DivPreviousVal, locationList[localDivArr[div].prev]);
    SetWindowText(sc_DivNextVal, locationList[localDivArr[div].next]);

    return;
}

void updateLocalDivArr(void)
{
    numArmies = 0;
    for(int i = 0, j = 0; i < 171; i++)
    {
        if(divisionStatus[i])
        {
            localDivArr[j] = dr.divArr[i];
            j++;
            numArmies++;
        }
        else
            localDivArr[i] = Division(); //make sure to zero out a division no longer active
    }

    return;
}
