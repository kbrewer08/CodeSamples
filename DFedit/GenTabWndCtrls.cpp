#include <windows.h>
#include <commctrl.h>
#include <cmath>

#include "DFGui.h"

WNDPROC g_MainWndProc;
                                      //Add checkbox for hospital? 
HWND sc_GenStrVal;
HWND sc_GenCmdVal;
HWND sc_GenIntVal;

HWND sc_GenDivStatusVal;
HWND sc_GenDivLeaderVal;
HWND sc_GenDivKingVal;
HWND sc_GenDivOriginVal;
HWND sc_GenDivGoalVal;
HWND sc_GenDivPrevVal;
HWND sc_GenDivNextVal;
HWND sc_GenDivXCoordVal;
HWND sc_GenDivYCoordVal;
HWND sc_GenDivNumVal;
HWND sc_GenDivTroopsVal;
HWND sc_GenDivMembersVal;
HWND sc_GenDivCaptivesVal;

HWND sc_GenDivisionTag;
HWND sc_GenDivStatusTag;
HWND sc_GenDivLeaderTag;
HWND sc_GenDivKingTag;
HWND sc_GenDivOriginTag;
HWND sc_GenDivGoalTag;
HWND sc_GenDivPrevTag;
HWND sc_GenDivNextTag;
HWND sc_GenDivXCoordTag;
HWND sc_GenDivYCoordTag;
HWND sc_GenDivNumTag;
HWND sc_GenDivTroopsTag;
HWND sc_GenDivMembersTag;
HWND sc_GenDivCaptivesTag;

HWND sc_GenIDNumVal;
HWND sc_GenIDNumTag;
HWND sc_GenPortraitVal;
HWND sc_GenPortraitTag;
HWND sc_GenClassVal;
HWND sc_GenClassTag;
HWND sc_GenStatusVal;
HWND sc_GenStatusTag;
HWND sc_GenHospitalVal;
HWND sc_GenHospitalTag;

void CreateGeneralsTab(void)
{
    HWND cb_GenNameTag;
    HWND cb_GenOwnerTag;
    HWND eb_GenLevelTag;
    HWND eb_GenExpTag;
    HWND eb_GenCurHP;
    HWND eb_GenCurMP;
    HWND eb_GenHpSlash;
    HWND eb_GenMpSlash;
    HWND eb_GenStrTag;
    HWND eb_GenComTag;
    HWND eb_GenIntTag;
    HWND cb_GenTrpTypeTag;
    HWND eb_GenTrpCntTag;

    HWND MedalsStaticGroup;
    HWND cb_GenSoldierTag;
    HWND cb_GenCavalryTag;
    HWND cb_GenMageTag;
    HWND cb_GenSamuraiTag;
    HWND cb_GenArcherTag;
    HWND cb_GenMonkTag;
    HWND cb_GenBeastTag;
    HWND cb_GenHarpyTag;
    HWND cb_GenDragonTag;
    HWND cb_GenZombieTag;

    HWND lineDownMiddle1;
    
    HWND eb_GenWinsTag;
    HWND eb_GenLossesTag;
    HWND eb_GenMeritsTag;
    HWND eb_GenLivesTag;
    HWND eb_GenLoyaltyTag;
    HWND eb_GenDefpTag;
    HWND eb_GenEscapeTag;
    HWND cb_GenSpellTierTag;
    HWND cb_GenItemTag;

    HWND LocationStaticGroup;
    HWND cb_GenLocationTag;
    HWND cb_GenHiddenTag;

    HWND WeaknessStaticGroup;
    HWND eb_GenDefVsSwordTag;
    HWND eb_GenDefVsIceTag;
    HWND eb_GenDefVsFireTag;
    HWND eb_GenDefVsLightTag;
    HWND eb_GenDefVsDarkTag;

    HWND StatusStaticGroup;

    HWND UnknownInfoGroup;
    HWND eb_GenNActionTag;
    HWND eb_GenBActionTag;
    HWND eb_GenBtlActionTag;
    HWND eb_GenMoralTag;
    HWND eb_GenWarlikeTag;
    HWND eb_GenNegoTag;
    HWND eb_GenAtkPlusTag;
    HWND eb_GenDefPlusTag;

    // create a Static control for our view window
    hTabGenerals = CreateWindowEx(
        0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
        0, 22, 1009, 688,
        hTabCntrl, NULL, hThisInst, NULL);

    g_MainWndProc = (WNDPROC)SetWindowLongPtr(hTabGenerals, GWL_WNDPROC, (LONG)GenTabWndProc);

    cb_GenNameTag = CreateWindowEx( //General text tag
        0, "STATIC", "General:", WS_CHILD | WS_VISIBLE,
        10, 28, 43, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.cb_GenNameList = CreateWindowEx( //names list combobox
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 28, 100, 500,
        hTabGenerals, (HMENU)ID_CB_GENNAME, hThisInst, NULL);

    cb_GenOwnerTag = CreateWindowEx( //owner text tag
        0, "STATIC", "Owner:", WS_CHILD | WS_VISIBLE,
        10, 53, 43, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.cb_GenOwnerList = CreateWindowEx( //owner name list combobox
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 53, 100, 500,
        hTabGenerals, (HMENU)ID_CB_GENOWNER, hThisInst, NULL);

    GenTabCtrls.but_SetGenOwner = CreateWindowEx(   //owner set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 53, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENOWNER, hThisInst, NULL);

    eb_GenLevelTag = CreateWindowEx(                //level edit tag
        0, "STATIC", "Level:", WS_CHILD | WS_VISIBLE,
        10, 78, 43, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenLevel = CreateWindowEx( //level edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        55, 78, 50, 20,
        hTabGenerals, (HMENU)ID_EB_GENLEVEL, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenLevel = CreateWindowEx(   //level set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 78, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENLEVEL, hThisInst, NULL);

    eb_GenExpTag = CreateWindowEx(                //curr exp edit tag
        0, "STATIC", "Exp:", WS_CHILD | WS_VISIBLE,
        10, 103, 43, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenExp = CreateWindowEx( //curr exp edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        55, 103, 50, 20,
        hTabGenerals, (HMENU)ID_EB_GENEXP, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenExp = CreateWindowEx(   //curr exp set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 103, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENEXP, hThisInst, NULL);

    eb_GenCurHP = CreateWindowEx(                //hp edit tag
        0, "STATIC", "HP:", WS_CHILD | WS_VISIBLE,
        10, 128, 43, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    eb_GenHpSlash = CreateWindowEx(                //hp slash
        0, "STATIC", "/", WS_CHILD | WS_VISIBLE,
        87, 128, 5, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenCurHP = CreateWindowEx( //cur hp edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        55, 128, 30, 20,
        hTabGenerals, (HMENU)ID_EB_GENCURHP, hThisInst, NULL);
        
    GenTabCtrls.eb_GenMaxHP = CreateWindowEx( //max hp edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        95, 128, 30, 20,
        hTabGenerals, (HMENU)ID_EB_GENMAXHP, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenHP = CreateWindowEx(   //hp set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 128, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENHP, hThisInst, NULL);

    eb_GenCurMP = CreateWindowEx(                //mp edit tag
        0, "STATIC", "MP:", WS_CHILD | WS_VISIBLE,
        10, 153, 43, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    eb_GenMpSlash = CreateWindowEx(                //mp slash
        0, "STATIC", "/", WS_CHILD | WS_VISIBLE,
        87, 153, 5, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenCurMP = CreateWindowEx( //cur mp edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        55, 153, 30, 20,
        hTabGenerals, (HMENU)ID_EB_GENCURMP, hThisInst, NULL);
        
    GenTabCtrls.eb_GenMaxMP = CreateWindowEx( //max mp edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        95, 153, 30, 20,
        hTabGenerals, (HMENU)ID_EB_GENMAXMP, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenMP = CreateWindowEx(   //mp set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 153, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENMP, hThisInst, NULL);

    eb_GenStrTag = CreateWindowEx(                //str edit tag
        0, "STATIC", "Strength:", WS_CHILD | WS_VISIBLE,
        10, 178, 43, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenStr = CreateWindowEx( //str edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        55, 178, 50, 20,
        hTabGenerals, (HMENU)ID_EB_GENSTR, hThisInst, NULL);
        
    sc_GenStrVal = CreateWindowEx(                //static str value
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        115, 182, 25, 20,
        hTabGenerals, (HMENU)ID_STATIC_STR_VAL, hThisInst, NULL);

    GenTabCtrls.but_SetGenStr = CreateWindowEx(   //str set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 178, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENSTR, hThisInst, NULL);

    eb_GenComTag = CreateWindowEx(                //com edit tag
        0, "STATIC", "Com:", WS_CHILD | WS_VISIBLE,
        10, 203, 43, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenCom = CreateWindowEx( //com edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        55, 203, 50, 20,
        hTabGenerals, (HMENU)ID_EB_GENCOM, hThisInst, NULL);
        
    sc_GenCmdVal = CreateWindowEx(                //static cmd value
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        115, 208, 25, 20,
        hTabGenerals, (HMENU)ID_STATIC_CMD_VAL, hThisInst, NULL);

    GenTabCtrls.but_SetGenCom = CreateWindowEx(   //com set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 203, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENCOM, hThisInst, NULL);

    eb_GenIntTag = CreateWindowEx(                //int edit tag
        0, "STATIC", "Int:", WS_CHILD | WS_VISIBLE,
        10, 228, 43, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenInt = CreateWindowEx( //int edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        55, 228, 50, 20,
        hTabGenerals, (HMENU)ID_EB_GENINT, hThisInst, NULL);
        
    sc_GenIntVal = CreateWindowEx(                //static int value
        0, "STATIC", "", WS_CHILD | WS_VISIBLE,
        115, 233, 25, 20,
        hTabGenerals, (HMENU)ID_STATIC_INT_VAL, hThisInst, NULL);

    GenTabCtrls.but_SetGenInt = CreateWindowEx(   //int set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 228, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENINT, hThisInst, NULL);

    eb_GenLivesTag = CreateWindowEx(                //lives edit tag
        0, "STATIC", "Lives:", WS_CHILD | WS_VISIBLE,
        10, 253, 60, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenLives = CreateWindowEx( //lives edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        55, 253, 50, 20,
        hTabGenerals, (HMENU)ID_EB_GENLIVES, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenLives = CreateWindowEx(   //lives set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 253, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENLIVES, hThisInst, NULL);

    eb_GenLoyaltyTag = CreateWindowEx(                //loyalty edit tag
        0, "STATIC", "Loyalty:", WS_CHILD | WS_VISIBLE,
        10, 278, 60, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenLoyalty = CreateWindowEx( //loyalty edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        55, 278, 50, 20,
        hTabGenerals, (HMENU)ID_EB_GENLOYALTY, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenLoyalty = CreateWindowEx(   //loyalty set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 278, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENLOYALTY, hThisInst, NULL);

    cb_GenTrpTypeTag = CreateWindowEx(                //troop type edit tag
        0, "STATIC", "Troops:", WS_CHILD | WS_VISIBLE,
        10, 343, 43, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.cb_GenTrpType = CreateWindowEx( //troop type combobox
        WS_EX_CLIENTEDGE, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 343, 100, 170,
        hTabGenerals, (HMENU)ID_CB_GENTRPTYPE, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenTrpType = CreateWindowEx(   //troop type set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 343, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENTRPTYPE, hThisInst, NULL);

    eb_GenTrpCntTag = CreateWindowEx(                //troop count edit tag
        0, "STATIC", "#Troops:", WS_CHILD | WS_VISIBLE,
        10, 368, 43, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenTrpCnt = CreateWindowEx( //troop count edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL,
        WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        55, 368, 50, 20,
        hTabGenerals, (HMENU)ID_EB_GENTRPCNT, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenTrpCnt = CreateWindowEx(   //troop count set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 368, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENTRPCNT, hThisInst, NULL);

////////////////////////////////////////////////////////////////////////////////
//
// MEDALS
//

    MedalsStaticGroup = CreateWindowEx(              //frame surrounding medals
        0, "BUTTON", "Medal Counts", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        5, 393, 200, 275, 
        hTabGenerals, NULL, hThisInst, NULL);

    cb_GenSoldierTag = CreateWindowEx(              //soldier medals tag
        0, "STATIC", "Soldier:", WS_CHILD | WS_VISIBLE,
        10, 413, 43, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    GenTabCtrls.cb_GenSoldier = CreateWindowEx( //soldier medals combobox
        0, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 413, 50, 170,
        hTabGenerals, (HMENU)ID_CB_GENSOLDIER, hThisInst, NULL);

    GenTabCtrls.but_SetGenSoldier = CreateWindowEx( //soldier medals set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 413, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENSOLDIER, hThisInst, NULL);

    cb_GenCavalryTag = CreateWindowEx(              //cavalry medals tag
        0, "STATIC", "Cavalry:", WS_CHILD | WS_VISIBLE,
        10, 438, 43, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    GenTabCtrls.cb_GenCavalry = CreateWindowEx( //cavalry medals combobox
        0, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 438, 50, 170,
        hTabGenerals, (HMENU)ID_CB_GENCAVALRY, hThisInst, NULL);

    GenTabCtrls.but_SetGenCavalry = CreateWindowEx( //cavalry medals set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 438, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENCAVALRY, hThisInst, NULL);

    cb_GenMageTag = CreateWindowEx(              //mage medals tag
        0, "STATIC", "Mage:", WS_CHILD | WS_VISIBLE,
        10, 463, 43, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    GenTabCtrls.cb_GenMage = CreateWindowEx( //mage medals combobox
        0, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 463, 50, 170,
        hTabGenerals, (HMENU)ID_CB_GENMAGE, hThisInst, NULL);

    GenTabCtrls.but_SetGenMage = CreateWindowEx( //mage medals set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 463, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENMAGE, hThisInst, NULL);

    cb_GenSamuraiTag = CreateWindowEx(              //samurai medals tag
        0, "STATIC", "Samurai:", WS_CHILD | WS_VISIBLE,
        10, 488, 43, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    GenTabCtrls.cb_GenSamurai = CreateWindowEx( //samurai medals combobox
        0, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 488, 50, 170,
        hTabGenerals, (HMENU)ID_CB_GENSAMURAI, hThisInst, NULL);

    GenTabCtrls.but_SetGenSamurai = CreateWindowEx( //samurai medals set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 488, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENSAMURAI, hThisInst, NULL);

    cb_GenArcherTag = CreateWindowEx(              //archer medals tag
        0, "STATIC", "Archer:", WS_CHILD | WS_VISIBLE,
        10, 513, 43, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    GenTabCtrls.cb_GenArcher = CreateWindowEx( //archer medals combobox
        0, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 513, 50, 170,
        hTabGenerals, (HMENU)ID_CB_GENARCHER, hThisInst, NULL);

    GenTabCtrls.but_SetGenArcher = CreateWindowEx( //archer medals set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 513, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENARCHER, hThisInst, NULL);

    cb_GenMonkTag = CreateWindowEx(              //monk medals tag
        0, "STATIC", "Monk:", WS_CHILD | WS_VISIBLE,
        10, 538, 43, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    GenTabCtrls.cb_GenMonk = CreateWindowEx( //monk medals combobox
        0, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 538, 50, 170,
        hTabGenerals, (HMENU)ID_CB_GENMONK, hThisInst, NULL);

    GenTabCtrls.but_SetGenMonk = CreateWindowEx( //monk medals set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 538, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENMONK, hThisInst, NULL);

    cb_GenHarpyTag = CreateWindowEx(              //Harpy medals tag
        0, "STATIC", "Harpy:", WS_CHILD | WS_VISIBLE,
        10, 563, 43, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    GenTabCtrls.cb_GenHarpy = CreateWindowEx( //harpy medals combobox
        0, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 563, 50, 170,
        hTabGenerals, (HMENU)ID_CB_GENHARPY, hThisInst, NULL);

    GenTabCtrls.but_SetGenHarpy = CreateWindowEx( //harpy medals set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 563, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENHARPY, hThisInst, NULL);

    cb_GenBeastTag = CreateWindowEx(              //beast medals tag
        0, "STATIC", "Beast:", WS_CHILD | WS_VISIBLE,
        10, 588, 43, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    GenTabCtrls.cb_GenBeast = CreateWindowEx( //beast medals combobox
        0, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 588, 50, 170,
        hTabGenerals, (HMENU)ID_CB_GENBEAST, hThisInst, NULL);

    GenTabCtrls.but_SetGenBeast = CreateWindowEx( //beast medals set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 588, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENBEAST, hThisInst, NULL);

    cb_GenDragonTag = CreateWindowEx(              //Dragon medals tag
        0, "STATIC", "Dragon:", WS_CHILD | WS_VISIBLE,
        10, 613, 43, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    GenTabCtrls.cb_GenDragon = CreateWindowEx( //dragon medals combobox
        0, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 613, 50, 170,
        hTabGenerals, (HMENU)ID_CB_GENDRAGON, hThisInst, NULL);

    GenTabCtrls.but_SetGenDragon = CreateWindowEx( //dragon medals set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 613, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENDRAGON, hThisInst, NULL);

    cb_GenZombieTag = CreateWindowEx(              //Zombie medals tag
        0, "STATIC", "Zombie:", WS_CHILD | WS_VISIBLE,
        10, 638, 43, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    GenTabCtrls.cb_GenZombie = CreateWindowEx( //zombie medals combobox
        0, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        55, 638, 50, 170,
        hTabGenerals, (HMENU)ID_CB_GENZOMBIE, hThisInst, NULL);

    GenTabCtrls.but_SetGenZombie = CreateWindowEx( //zombie medals set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        155, 638, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENZOMBIE, hThisInst, NULL);

////////////////////////////////////////////////////////////////////////////////
//
// Lines that splits interface
//
    lineDownMiddle1 = CreateWindowEx( //line to split interface
        WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        225, 45, 1, 260,
        hTabGenerals, NULL, hThisInst, NULL);

////////////////////////////////////////////////////////////////////////////////
//
// Second portion of interface
//
    eb_GenWinsTag = CreateWindowEx(                //wins edit tag
        0, "STATIC", "Wins:", WS_CHILD | WS_VISIBLE,
        235, 53, 60, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenWins = CreateWindowEx( //wins edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        315, 53, 50, 20,
        hTabGenerals, (HMENU)ID_EB_GENWINS, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenWins = CreateWindowEx(   //wins set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        427, 53, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENWINS, hThisInst, NULL);

    eb_GenLossesTag = CreateWindowEx(                //losses edit tag
        0, "STATIC", "Losses:", WS_CHILD | WS_VISIBLE,
        235, 78, 60, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenLosses = CreateWindowEx( //losses edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        315, 78, 50, 20,
        hTabGenerals, (HMENU)ID_EB_GENLOSSES, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenLosses = CreateWindowEx(   //losses set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        427, 78, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENLOSSES, hThisInst, NULL);

    eb_GenMeritsTag = CreateWindowEx(                //merits edit tag
        0, "STATIC", "Merits:", WS_CHILD | WS_VISIBLE,
        235, 103, 60, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenMerits = CreateWindowEx( //merits edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        315, 103, 50, 20,
        hTabGenerals, (HMENU)ID_EB_GENMERITS, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenMerits = CreateWindowEx(   //merits set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        427, 103, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENLOSSES, hThisInst, NULL);

    eb_GenEscapeTag = CreateWindowEx(                //escape edit tag
        0, "STATIC", "Escape:", WS_CHILD | WS_VISIBLE,
        235, 128, 60, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenEscape = CreateWindowEx( //escape edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        315, 128, 50, 20,
        hTabGenerals, (HMENU)ID_EB_GENESCAPE, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenEscape = CreateWindowEx(   //escape set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        427, 128, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENESCAPE, hThisInst, NULL);

    cb_GenSpellTierTag = CreateWindowEx( //spell tier edit tag
        0, "STATIC", "Spell Tier:", WS_CHILD | WS_VISIBLE,
        235, 153, 60, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.cb_GenSpellTier = CreateWindowEx( //spell tier combobox
        WS_EX_CLIENTEDGE, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        315, 153, 50, 80,
        hTabGenerals, (HMENU)ID_CB_GENSPELLTIER, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenSpellTier = CreateWindowEx(   //spell tier set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        427, 153, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENSPELLTIER, hThisInst, NULL);

    cb_GenItemTag = CreateWindowEx(              //Generals' items tag
        0, "STATIC", "Equipped Item:", WS_CHILD | WS_VISIBLE,
        235, 178, 80, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    GenTabCtrls.cb_GenItem = CreateWindowEx( //items combobox
        0, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        315, 178, 110, 500,
        hTabGenerals, (HMENU)ID_CB_GENITEM, hThisInst, NULL);

    GenTabCtrls.but_SetGenItem = CreateWindowEx( //items set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        427, 178, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENITEM, hThisInst, NULL);

    GenTabCtrls.ckbox_GenSearchFortify = CreateWindowEx( //search/fortify checkbox
        0, "BUTTON", "Already did Search/Fortify this week",
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED | BS_CHECKBOX,
        235, 203, 190, 20,
        hTabGenerals, (HMENU)ID_CKBX_SEARCH_FORT, hThisInst, NULL);

    GenTabCtrls.but_setGenSearchFortify = CreateWindowEx( //search/fortify set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        427, 203, 40, 20,
        hTabGenerals, (HMENU)ID_SET_SEARCH_FORT, hThisInst, NULL);

////////////////////////////////////////////////////////////////////////////////
//
// Location Editing
//
        LocationStaticGroup = CreateWindowEx( //frame surrounding location edit
        0, "BUTTON", "Location Editing", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        230, 333, 282, 275, 
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.rb_GenCastleLocation = CreateWindowEx( //General castle loc radio
        0, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | BS_RADIOBUTTON,
        235, 353, 20, 20, 
        hTabGenerals, (HMENU)ID_RB_GEN_CAS_LOC, hThisInst, NULL); 

    cb_GenLocationTag = CreateWindowEx(              //Generals' location tag
        0, "STATIC", "Castle:", WS_CHILD | WS_VISIBLE,
        257, 355, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    GenTabCtrls.cb_GenLocation = CreateWindowEx( //location combobox
        0, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        300, 353, 160, 500,
        hTabGenerals, (HMENU)ID_CB_GENLOCATION, hThisInst, NULL);

    GenTabCtrls.but_SetGenLocation = CreateWindowEx( //location set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        462, 353, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENLOCATION, hThisInst, NULL);

    GenTabCtrls.rb_GenHiddenLocation = CreateWindowEx( //General hidden loc radio
        0, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | BS_RADIOBUTTON,
        235, 378, 20, 20, 
        hTabGenerals, (HMENU)ID_RB_GEN_HIDE_LOC, hThisInst, NULL); 

    cb_GenHiddenTag = CreateWindowEx(              //Generals' Hidden loc tag
        0, "STATIC", "Hidden:", WS_CHILD | WS_VISIBLE,
        257, 380, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    GenTabCtrls.cb_GenHidden = CreateWindowEx( //hidden location combobox
        0, "COMBOBOX", NULL,
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        300, 378, 160, 80,
        hTabGenerals, (HMENU)ID_CB_GENHIDDEN, hThisInst, NULL);

    GenTabCtrls.but_SetGenHidden = CreateWindowEx( //hidden location set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        462, 378, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENHIDDEN, hThisInst, NULL);

    sc_GenDivisionTag = CreateWindowEx(              //Generals' Division tag
        0, "STATIC", "Division:", WS_CHILD,
        257, 405, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    GenTabCtrls.rb_GenDivision = CreateWindowEx( //General division radio
        0, "BUTTON", NULL, WS_CHILD | WS_DISABLED | BS_RADIOBUTTON,
        235, 403, 20, 20, 
        hTabGenerals, (HMENU)ID_RB_GEN_DIV_LOC, hThisInst, NULL); 

    sc_GenDivKingTag = CreateWindowEx(              //Generals' Division ruler tag
        0, "STATIC", "Ruler:", WS_CHILD,
        267, 425, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenDivKingVal = CreateWindowEx(              //Generals' Division ruler value
        0, "STATIC", "", WS_CHILD,
        312, 425, 60, 20, 
        hTabGenerals, (HMENU)ID_STATIC_DIV_KING, hThisInst, NULL); 

    sc_GenDivLeaderTag = CreateWindowEx(              //Generals' Division leader tag
        0, "STATIC", "Leader:", WS_CHILD,
        267, 440, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenDivLeaderVal = CreateWindowEx(              //Generals' Division leader value
        0, "STATIC", "", WS_CHILD,
        312, 440, 60, 20, 
        hTabGenerals, (HMENU)ID_STATIC_DIV_LEAD, hThisInst, NULL); 

    sc_GenDivNumTag = CreateWindowEx(              //Generals' Division number tag
        0, "STATIC", "Number:", WS_CHILD,
        400, 425, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenDivNumVal = CreateWindowEx(              //Generals' Division number value
        0, "STATIC", "", WS_CHILD,
        445, 425, 65, 20, 
        hTabGenerals, (HMENU)ID_STATIC_DIV_NUM, hThisInst, NULL); 

    sc_GenDivStatusTag = CreateWindowEx(              //Generals' Division status tag
        0, "STATIC", "Status:", WS_CHILD,
        400, 440, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenDivStatusVal = CreateWindowEx(              //Generals' Division status value
        0, "STATIC", "", WS_CHILD,
        445, 440, 65, 20, 
        hTabGenerals, (HMENU)ID_STATIC_DIV_STAT, hThisInst, NULL); 

    sc_GenDivXCoordTag = CreateWindowEx(              //Generals' Division x coordinate tag
        0, "STATIC", "X:", WS_CHILD,
        267, 470, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenDivXCoordVal = CreateWindowEx(              //Generals' Division x coordinate value
        0, "STATIC", "", WS_CHILD,
        312, 470, 60, 20, 
        hTabGenerals, (HMENU)ID_STATIC_DIV_X, hThisInst, NULL); 

    sc_GenDivYCoordTag = CreateWindowEx(              //Generals' Division y coordinate tag
        0, "STATIC", "Y:", WS_CHILD,
        267, 485, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenDivYCoordVal = CreateWindowEx(              //Generals' Division y coordinate value
        0, "STATIC", "", WS_CHILD,
        312, 485, 60, 20, 
        hTabGenerals, (HMENU)ID_STATIC_DIV_Y, hThisInst, NULL); 

    sc_GenDivOriginTag = CreateWindowEx(              //Generals' Division origin tag
        0, "STATIC", "Origin:", WS_CHILD,
        267, 515, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenDivOriginVal = CreateWindowEx(              //Generals' Division origin value
        0, "STATIC", "", WS_CHILD,
        312, 515, 120, 20, 
        hTabGenerals, (HMENU)ID_STATIC_DIV_ORIG, hThisInst, NULL); 

    sc_GenDivGoalTag = CreateWindowEx(              //Generals' Division goal tag
        0, "STATIC", "Goal:", WS_CHILD,
        267, 530, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenDivGoalVal = CreateWindowEx(              //Generals' Division goal value
        0, "STATIC", "", WS_CHILD,
        312, 530, 120, 20, 
        hTabGenerals, (HMENU)ID_STATIC_DIV_GOAL, hThisInst, NULL); 

    sc_GenDivPrevTag = CreateWindowEx(              //Generals' Division prev tag
        0, "STATIC", "Prev:", WS_CHILD,
        267, 550, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenDivPrevVal = CreateWindowEx(              //Generals' Division prev value
        0, "STATIC", "", WS_CHILD,
        312, 550, 120, 20, 
        hTabGenerals, (HMENU)ID_STATIC_DIV_PREV, hThisInst, NULL); 

    sc_GenDivNextTag = CreateWindowEx(              //Generals' Division next tag
        0, "STATIC", "Next:", WS_CHILD,
        267, 565, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenDivNextVal = CreateWindowEx(              //Generals' Division next value
        0, "STATIC", "", WS_CHILD,
        312, 565, 120, 20, 
        hTabGenerals, (HMENU)ID_STATIC_DIV_NEXT, hThisInst, NULL);

    sc_GenDivTroopsTag = CreateWindowEx(              //Generals' Division troop count tag
        0, "STATIC", "Troops:", WS_CHILD,
        400, 470, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenDivTroopsVal = CreateWindowEx(              //Generals' Division troop count value
        0, "STATIC", "", WS_CHILD,
        455, 470, 30, 20, 
        hTabGenerals, (HMENU)ID_STATIC_DIV_TROOP, hThisInst, NULL); 

    sc_GenDivMembersTag = CreateWindowEx(              //Generals' Division members tag
        0, "STATIC", "Members:", WS_CHILD,
        400, 485, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenDivMembersVal = CreateWindowEx(              //Generals' Division members value
        0, "STATIC", "", WS_CHILD,
        455, 485, 30, 20, 
        hTabGenerals, (HMENU)ID_STATIC_DIV_MEMBR, hThisInst, NULL); 

    sc_GenDivCaptivesTag = CreateWindowEx(              //Generals' Division captives tag
        0, "STATIC", "Captives:", WS_CHILD,
        400, 500, 60, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenDivCaptivesVal = CreateWindowEx(              //Generals' Division captives value
        0, "STATIC", "", WS_CHILD,
        455, 500, 30, 20, 
        hTabGenerals, (HMENU)ID_STATIC_DIV_CAPTV, hThisInst, NULL); 

////////////////////////////////////////////////////////////////////////////////
//
// Weakness Editing
//
        WeaknessStaticGroup = CreateWindowEx( //frame surrounding weakness edit
        0, "BUTTON", "Weakness Against: ", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        502, 45, 193, 175, 
        hTabGenerals, NULL, hThisInst, NULL);

    eb_GenDefpTag = CreateWindowEx(                //defp edit tag
        0, "STATIC", "Troop Attacks:", WS_CHILD | WS_VISIBLE,
        507, 65, 80, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenDefp = CreateWindowEx( //defp edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        585, 65, 50, 20,
        hTabGenerals, (HMENU)ID_EB_GENDEFP, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenDefp = CreateWindowEx(   //defp set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        645, 65, 40, 20,
        hTabGenerals, (HMENU)ID_SET_GENDEFP, hThisInst, NULL);

    eb_GenDefVsSwordTag = CreateWindowEx(                //def vs sword edit tag
        0, "STATIC", "Sword Magic:", WS_CHILD | WS_VISIBLE,
        507, 90, 80, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenDefVsSword = CreateWindowEx( //def vs sword edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        585, 90, 50, 20,
        hTabGenerals, (HMENU)ID_EB_DEF_VS_SWORD, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenDefVsSword = CreateWindowEx(   //def vs sword set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        645, 90, 40, 20,
        hTabGenerals, (HMENU)ID_SET_DEF_VS_SWORD, hThisInst, NULL);

    eb_GenDefVsIceTag = CreateWindowEx(                //def vs ice edit tag
        0, "STATIC", "Ice Magic:", WS_CHILD | WS_VISIBLE,
        507, 115, 80, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenDefVsIce = CreateWindowEx( //def vs ice edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        585, 115, 50, 20,
        hTabGenerals, (HMENU)ID_EB_DEF_VS_ICE, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenDefVsIce = CreateWindowEx(   //def vs ice set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        645, 115, 40, 20,
        hTabGenerals, (HMENU)ID_SET_DEF_VS_ICE, hThisInst, NULL);

    eb_GenDefVsFireTag = CreateWindowEx(                //def vs fire edit tag
        0, "STATIC", "Fire Magic:", WS_CHILD | WS_VISIBLE,
        507, 140, 80, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenDefVsFire = CreateWindowEx( //def vs fire edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        585, 140, 50, 20,
        hTabGenerals, (HMENU)ID_EB_DEF_VS_FIRE, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenDefVsFire = CreateWindowEx(   //def vs fire set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        645, 140, 40, 20,
        hTabGenerals, (HMENU)ID_SET_DEF_VS_FIRE, hThisInst, NULL);

    eb_GenDefVsLightTag = CreateWindowEx(                //def vs light edit tag
        0, "STATIC", "Light Magic:", WS_CHILD | WS_VISIBLE,
        507, 165, 80, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenDefVsLight= CreateWindowEx( //def vs light edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        585, 165, 50, 20,
        hTabGenerals, (HMENU)ID_EB_DEF_VS_LIGHT, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenDefVsLight = CreateWindowEx(   //def vs light set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        645, 165, 40, 20,
        hTabGenerals, (HMENU)ID_SET_DEF_VS_LIGHT, hThisInst, NULL);

    eb_GenDefVsDarkTag = CreateWindowEx(                //def vs dark edit tag
        0, "STATIC", "Dark Magic:", WS_CHILD | WS_VISIBLE,
        507, 190, 80, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenDefVsDark = CreateWindowEx( //def vs dark edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        585, 190, 50, 20,
        hTabGenerals, (HMENU)ID_EB_DEF_VS_DARK, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenDefVsDark = CreateWindowEx(   //def vs dark set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        645, 190, 40, 20,
        hTabGenerals, (HMENU)ID_SET_DEF_VS_DARK, hThisInst, NULL);

////////////////////////////////////////////////////////////////////////////////
//
// Status Info Display
//
        StatusStaticGroup = CreateWindowEx( //frame surrounding status information
        0, "BUTTON", "Status Information", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        720, 45, 180, 175, 
        hTabGenerals, NULL, hThisInst, NULL);

    sc_GenIDNumTag = CreateWindowEx(              //Generals' id# tag
        0, "STATIC", "Index:", WS_CHILD | WS_VISIBLE,
        725, 65, 45, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenIDNumVal = CreateWindowEx(              //Generals' id# value
        0, "STATIC", "", WS_CHILD,
        775, 65, 80, 20, 
        hTabGenerals, (HMENU)ID_STATIC_IDNUM, hThisInst, NULL); 

    sc_GenPortraitTag = CreateWindowEx(              //Generals' portrait tag
        0, "STATIC", "Portrait:", WS_CHILD | WS_VISIBLE,
        725, 80, 45, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenPortraitVal = CreateWindowEx(              //Generals' portrait value
        0, "STATIC", "", WS_CHILD,
        775, 80, 80, 20, 
        hTabGenerals, (HMENU)ID_STATIC_PORTRAIT, hThisInst, NULL); 

    sc_GenClassTag = CreateWindowEx(              //Generals' class tag
        0, "STATIC", "Class:", WS_CHILD | WS_VISIBLE,
        725, 95, 45, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenClassVal = CreateWindowEx(              //Generals' class value
        0, "STATIC", "", WS_CHILD,
        775, 95, 80, 20, 
        hTabGenerals, (HMENU)ID_STATIC_CLASS, hThisInst, NULL); 

    sc_GenStatusTag = CreateWindowEx(              //Generals' status tag
        0, "STATIC", "Status:", WS_CHILD | WS_VISIBLE,
        725, 110, 45, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenStatusVal = CreateWindowEx(              //Generals' status value
        0, "STATIC", "", WS_CHILD,
        775, 110, 80, 20, 
        hTabGenerals, (HMENU)ID_STATIC_STATUSSTR, hThisInst, NULL); 

    sc_GenHospitalTag = CreateWindowEx(              //Generals' hospital tag
        0, "STATIC", "Hospital:", WS_CHILD | WS_VISIBLE,
        725, 125, 45, 20, 
        hTabGenerals, NULL, hThisInst, NULL); 

    sc_GenHospitalVal = CreateWindowEx(              //Generals' hospital value
        0, "STATIC", "", WS_CHILD,
        775, 125, 80, 20, 
        hTabGenerals, (HMENU)ID_STATIC_HOSPITAL, hThisInst, NULL); 

////////////////////////////////////////////////////////////////////////////////
//
// Status Info Display
//
        UnknownInfoGroup = CreateWindowEx( //frame surrounding unknown effects
        0, "BUTTON", "Unknown Effects", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        542, 333, 193, 235, 
        hTabGenerals, NULL, hThisInst, NULL);

    eb_GenNActionTag = CreateWindowEx(                //n_action edit tag
        0, "STATIC", "n_action:", WS_CHILD | WS_VISIBLE,
        547, 353, 80, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenNAction = CreateWindowEx( //  n_action edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        620, 353, 50, 20,
        hTabGenerals, (HMENU)ID_EB_NACTION, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenNAction = CreateWindowEx(   //n_action set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        680, 353, 40, 20,
        hTabGenerals, (HMENU)ID_SET_NACTION, hThisInst, NULL);

    eb_GenBActionTag = CreateWindowEx(                //b_action edit tag
        0, "STATIC", "b_action:", WS_CHILD | WS_VISIBLE,
        547, 378, 80, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenBAction = CreateWindowEx( //  b_action edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        620, 378, 50, 20,
        hTabGenerals, (HMENU)ID_EB_BACTION, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenBAction = CreateWindowEx(   //b_action set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        680, 378, 40, 20,
        hTabGenerals, (HMENU)ID_SET_BACTION, hThisInst, NULL);

    eb_GenBtlActionTag = CreateWindowEx(                //btl_action edit tag
        0, "STATIC", "btl_action:", WS_CHILD | WS_VISIBLE,
        547, 403, 80, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenBtlAction = CreateWindowEx( //  btl_action edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        620, 403, 50, 20,
        hTabGenerals, (HMENU)ID_EB_BTL_ACTION, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenBtlAction = CreateWindowEx(   //btl_action set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        680, 403, 40, 20,
        hTabGenerals, (HMENU)ID_SET_BTL_ACTION, hThisInst, NULL);

    eb_GenMoralTag = CreateWindowEx(                //moral edit tag
        0, "STATIC", "moral:", WS_CHILD | WS_VISIBLE,
        547, 428, 80, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenMoral = CreateWindowEx( //  moral edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        620, 428, 50, 20,
        hTabGenerals, (HMENU)ID_EB_MORAL, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenMoral = CreateWindowEx(   //moral set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        680, 428, 40, 20,
        hTabGenerals, (HMENU)ID_SET_MORAL, hThisInst, NULL);

    eb_GenWarlikeTag = CreateWindowEx(                //warlike edit tag
        0, "STATIC", "warlike:", WS_CHILD | WS_VISIBLE,
        547, 453, 80, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenWarlike = CreateWindowEx( //  warlike edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        620, 453, 50, 20,
        hTabGenerals, (HMENU)ID_EB_WARLIKE, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenWarlike = CreateWindowEx(   //warlike set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        680, 453, 40, 20,
        hTabGenerals, (HMENU)ID_SET_WARLIKE, hThisInst, NULL);

    eb_GenNegoTag = CreateWindowEx(                //nego edit tag
        0, "STATIC", "nego:", WS_CHILD | WS_VISIBLE,
        547, 478, 80, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenNego = CreateWindowEx( //  nego edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        620, 478, 50, 20,
        hTabGenerals, (HMENU)ID_EB_NEGO, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenNego = CreateWindowEx(   //nego set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        680, 478, 40, 20,
        hTabGenerals, (HMENU)ID_SET_NEGO, hThisInst, NULL);

    eb_GenAtkPlusTag = CreateWindowEx(                //atkplus edit tag
        0, "STATIC", "atkplus:", WS_CHILD | WS_VISIBLE,
        547, 503, 80, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenAtkPlus = CreateWindowEx( //  atkplus edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        620, 503, 50, 20,
        hTabGenerals, (HMENU)ID_EB_ATKPLUS, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenAtkPlus = CreateWindowEx(   //atkplus set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        680, 503, 40, 20,
        hTabGenerals, (HMENU)ID_SET_ATKPLUS, hThisInst, NULL);

    eb_GenDefPlusTag = CreateWindowEx(                //defplus edit tag
        0, "STATIC", "defplus:", WS_CHILD | WS_VISIBLE,
        547, 528, 80, 20,
        hTabGenerals, NULL, hThisInst, NULL);

    GenTabCtrls.eb_GenDefPlus = CreateWindowEx( //  defplus edit field
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        620, 528, 50, 20,
        hTabGenerals, (HMENU)ID_EB_DEFPLUS, hThisInst, NULL);
        
    GenTabCtrls.but_SetGenDefPlus = CreateWindowEx(   //defplus set button
        0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
        680, 528, 40, 20,
        hTabGenerals, (HMENU)ID_SET_DEFPLUS, hThisInst, NULL);

    // Set this controls' font
    SetDefaultFont(hTabGenerals);
    SetDefaultFont(cb_GenNameTag);
    SetDefaultFont(cb_GenOwnerTag);
    SetDefaultFont(eb_GenLevelTag);
    SetDefaultFont(eb_GenExpTag);
    SetDefaultFont(eb_GenCurHP);
    SetDefaultFont(eb_GenCurMP);
    SetDefaultFont(eb_GenHpSlash);
    SetDefaultFont(eb_GenMpSlash);
    SetDefaultFont(eb_GenStrTag);
    SetDefaultFont(sc_GenStrVal);
    SetDefaultFont(eb_GenComTag);
    SetDefaultFont(sc_GenCmdVal);
    SetDefaultFont(eb_GenIntTag);
    SetDefaultFont(sc_GenIntVal);
    SetDefaultFont(cb_GenTrpTypeTag);
    SetDefaultFont(eb_GenTrpCntTag);

    SetDefaultFont(MedalsStaticGroup);
    SetDefaultFont(cb_GenSoldierTag);
    SetDefaultFont(cb_GenCavalryTag);
    SetDefaultFont(cb_GenMageTag);
    SetDefaultFont(cb_GenSamuraiTag);
    SetDefaultFont(cb_GenArcherTag);
    SetDefaultFont(cb_GenMonkTag);
    SetDefaultFont(cb_GenBeastTag);
    SetDefaultFont(cb_GenHarpyTag);
    SetDefaultFont(cb_GenDragonTag);
    SetDefaultFont(cb_GenZombieTag);
    SetDefaultFont(lineDownMiddle1);

    SetDefaultFont(eb_GenWinsTag);
    SetDefaultFont(eb_GenLossesTag);
    SetDefaultFont(eb_GenMeritsTag);
    SetDefaultFont(eb_GenLivesTag);
    SetDefaultFont(eb_GenLoyaltyTag);
    SetDefaultFont(eb_GenEscapeTag);
    SetDefaultFont(cb_GenSpellTierTag);
    SetDefaultFont(cb_GenItemTag);

    SetDefaultFont(cb_GenLocationTag);
    SetDefaultFont(cb_GenHiddenTag);
    SetDefaultFont(sc_GenDivisionTag);
    SetDefaultFont(sc_GenDivNumTag);
    SetDefaultFont(sc_GenDivNumVal);
    SetDefaultFont(sc_GenDivStatusTag);
    SetDefaultFont(sc_GenDivStatusVal);
    SetDefaultFont(sc_GenDivKingTag);
    SetDefaultFont(sc_GenDivKingVal);
    SetDefaultFont(sc_GenDivLeaderTag);
    SetDefaultFont(sc_GenDivLeaderVal);
    SetDefaultFont(sc_GenDivXCoordTag);
    SetDefaultFont(sc_GenDivXCoordVal);
    SetDefaultFont(sc_GenDivYCoordTag);
    SetDefaultFont(sc_GenDivYCoordVal);
    SetDefaultFont(sc_GenDivOriginTag);
    SetDefaultFont(sc_GenDivOriginVal);
    SetDefaultFont(sc_GenDivGoalTag);
    SetDefaultFont(sc_GenDivGoalVal);
    SetDefaultFont(sc_GenDivPrevTag);
    SetDefaultFont(sc_GenDivPrevVal);
    SetDefaultFont(sc_GenDivNextTag);
    SetDefaultFont(sc_GenDivNextVal);
    SetDefaultFont(sc_GenDivTroopsTag);
    SetDefaultFont(sc_GenDivTroopsVal);
    SetDefaultFont(sc_GenDivMembersTag);
    SetDefaultFont(sc_GenDivMembersVal);
    SetDefaultFont(sc_GenDivCaptivesTag);
    SetDefaultFont(sc_GenDivCaptivesVal);

    SetDefaultFont(eb_GenDefpTag);
    SetDefaultFont(eb_GenDefVsSwordTag);
    SetDefaultFont(eb_GenDefVsIceTag);
    SetDefaultFont(eb_GenDefVsFireTag);
    SetDefaultFont(eb_GenDefVsLightTag);
    SetDefaultFont(eb_GenDefVsDarkTag);

    SetDefaultFont(sc_GenIDNumTag);
    SetDefaultFont(sc_GenIDNumVal);
    SetDefaultFont(sc_GenPortraitTag);
    SetDefaultFont(sc_GenPortraitVal);
    SetDefaultFont(sc_GenClassTag);
    SetDefaultFont(sc_GenClassVal);
    SetDefaultFont(sc_GenStatusTag);
    SetDefaultFont(sc_GenStatusVal);
    SetDefaultFont(sc_GenHospitalTag);
    SetDefaultFont(sc_GenHospitalVal);

    SetDefaultFont(eb_GenNActionTag);
    SetDefaultFont(eb_GenBActionTag);
    SetDefaultFont(eb_GenBtlActionTag);
    SetDefaultFont(eb_GenMoralTag);
    SetDefaultFont(eb_GenWarlikeTag);
    SetDefaultFont(eb_GenNegoTag);
    SetDefaultFont(eb_GenAtkPlusTag);
    SetDefaultFont(eb_GenDefPlusTag);

    SetDefaultFont(GenTabCtrls.cb_GenNameList);
    SetDefaultFont(GenTabCtrls.cb_GenOwnerList);
    SetDefaultFont(GenTabCtrls.but_SetGenOwner);
    SetDefaultFont(GenTabCtrls.eb_GenLevel);
    SetDefaultFont(GenTabCtrls.but_SetGenLevel);
    SetDefaultFont(GenTabCtrls.eb_GenExp);
    SetDefaultFont(GenTabCtrls.but_SetGenExp);
    SetDefaultFont(GenTabCtrls.eb_GenCurHP);
    SetDefaultFont(GenTabCtrls.eb_GenMaxHP);
    SetDefaultFont(GenTabCtrls.but_SetGenHP);
    SetDefaultFont(GenTabCtrls.eb_GenCurMP);
    SetDefaultFont(GenTabCtrls.eb_GenMaxMP);
    SetDefaultFont(GenTabCtrls.but_SetGenMP);
    SetDefaultFont(GenTabCtrls.eb_GenStr);
    SetDefaultFont(GenTabCtrls.but_SetGenStr);
    SetDefaultFont(GenTabCtrls.eb_GenCom);
    SetDefaultFont(GenTabCtrls.but_SetGenCom);
    SetDefaultFont(GenTabCtrls.eb_GenInt);
    SetDefaultFont(GenTabCtrls.but_SetGenInt);
    SetDefaultFont(GenTabCtrls.cb_GenTrpType);
    SetDefaultFont(GenTabCtrls.but_SetGenTrpType);
    SetDefaultFont(GenTabCtrls.eb_GenTrpCnt);
    SetDefaultFont(GenTabCtrls.but_SetGenTrpCnt);
    SetDefaultFont(GenTabCtrls.cb_GenSoldier);
    SetDefaultFont(GenTabCtrls.but_SetGenSoldier);
    SetDefaultFont(GenTabCtrls.cb_GenCavalry);
    SetDefaultFont(GenTabCtrls.but_SetGenCavalry);
    SetDefaultFont(GenTabCtrls.cb_GenMage);
    SetDefaultFont(GenTabCtrls.but_SetGenMage);
    SetDefaultFont(GenTabCtrls.cb_GenSamurai);
    SetDefaultFont(GenTabCtrls.but_SetGenSamurai);
    SetDefaultFont(GenTabCtrls.cb_GenArcher);
    SetDefaultFont(GenTabCtrls.but_SetGenArcher);
    SetDefaultFont(GenTabCtrls.cb_GenMonk);
    SetDefaultFont(GenTabCtrls.but_SetGenMonk);
    SetDefaultFont(GenTabCtrls.cb_GenBeast);
    SetDefaultFont(GenTabCtrls.but_SetGenBeast);
    SetDefaultFont(GenTabCtrls.cb_GenHarpy);
    SetDefaultFont(GenTabCtrls.but_SetGenHarpy);
    SetDefaultFont(GenTabCtrls.cb_GenDragon);
    SetDefaultFont(GenTabCtrls.but_SetGenDragon);
    SetDefaultFont(GenTabCtrls.cb_GenZombie);
    SetDefaultFont(GenTabCtrls.but_SetGenZombie);

    SetDefaultFont(GenTabCtrls.eb_GenWins);
    SetDefaultFont(GenTabCtrls.but_SetGenWins);
    SetDefaultFont(GenTabCtrls.eb_GenLosses);
    SetDefaultFont(GenTabCtrls.but_SetGenLosses);
    SetDefaultFont(GenTabCtrls.eb_GenMerits);
    SetDefaultFont(GenTabCtrls.but_SetGenMerits);
    SetDefaultFont(GenTabCtrls.eb_GenLives);
    SetDefaultFont(GenTabCtrls.but_SetGenLives);
    SetDefaultFont(GenTabCtrls.eb_GenLoyalty);
    SetDefaultFont(GenTabCtrls.but_SetGenLoyalty);
    SetDefaultFont(GenTabCtrls.eb_GenEscape);
    SetDefaultFont(GenTabCtrls.but_SetGenEscape);
    SetDefaultFont(GenTabCtrls.cb_GenSpellTier);
    SetDefaultFont(GenTabCtrls.but_SetGenSpellTier);
    SetDefaultFont(GenTabCtrls.cb_GenItem);
    SetDefaultFont(GenTabCtrls.but_SetGenItem);
    SetDefaultFont(GenTabCtrls.ckbox_GenSearchFortify);
    SetDefaultFont(GenTabCtrls.but_setGenSearchFortify);
    

    SetDefaultFont(LocationStaticGroup);
    SetDefaultFont(GenTabCtrls.cb_GenLocation);
    SetDefaultFont(GenTabCtrls.but_SetGenLocation);
    SetDefaultFont(GenTabCtrls.cb_GenHidden);
    SetDefaultFont(GenTabCtrls.but_SetGenHidden);

    SetDefaultFont(WeaknessStaticGroup);
    SetDefaultFont(GenTabCtrls.eb_GenDefp);
    SetDefaultFont(GenTabCtrls.but_SetGenDefp);
    SetDefaultFont(GenTabCtrls.eb_GenDefVsSword);
    SetDefaultFont(GenTabCtrls.but_SetGenDefVsSword);
    SetDefaultFont(GenTabCtrls.eb_GenDefVsIce);
    SetDefaultFont(GenTabCtrls.but_SetGenDefVsIce);
    SetDefaultFont(GenTabCtrls.eb_GenDefVsFire);
    SetDefaultFont(GenTabCtrls.but_SetGenDefVsFire);
    SetDefaultFont(GenTabCtrls.eb_GenDefVsLight);
    SetDefaultFont(GenTabCtrls.but_SetGenDefVsLight);
    SetDefaultFont(GenTabCtrls.eb_GenDefVsDark);
    SetDefaultFont(GenTabCtrls.but_SetGenDefVsDark);

    SetDefaultFont(StatusStaticGroup);

    SetDefaultFont(UnknownInfoGroup);
    SetDefaultFont(GenTabCtrls.eb_GenNAction);
    SetDefaultFont(GenTabCtrls.but_SetGenNAction);
    SetDefaultFont(GenTabCtrls.eb_GenBAction);
    SetDefaultFont(GenTabCtrls.but_SetGenBAction);
    SetDefaultFont(GenTabCtrls.eb_GenBtlAction);
    SetDefaultFont(GenTabCtrls.but_SetGenBtlAction);
    SetDefaultFont(GenTabCtrls.eb_GenMoral);
    SetDefaultFont(GenTabCtrls.but_SetGenMoral);
    SetDefaultFont(GenTabCtrls.eb_GenWarlike);
    SetDefaultFont(GenTabCtrls.but_SetGenWarlike);
    SetDefaultFont(GenTabCtrls.eb_GenNego);
    SetDefaultFont(GenTabCtrls.but_SetGenNego);
    SetDefaultFont(GenTabCtrls.eb_GenAtkPlus);
    SetDefaultFont(GenTabCtrls.but_SetGenAtkPlus);
    SetDefaultFont(GenTabCtrls.eb_GenDefPlus);
    SetDefaultFont(GenTabCtrls.but_SetGenDefPlus);

    return;
}

void PopulateGeneralsTab(void)
{
    int gen = 0;
    char itoaArr[5] = {'\0'};

    dr.fr.readFile();   //read the save file
    dr.initGenerals();  //create the generals array
    dr.setMonarch();    //find who the player's monarch is
    dr.initCastles();   //create the castles array
    dr.initDivisions(); //create the divisions array
    dr.initItemInv();   //create the item inventory from domestic affairs
    dr.initKingdoms();  //fill in the status of each kingdom

    EnableWindow(GenTabCtrls.cb_GenNameList, TRUE); //turn on names list combobox
    EnableWindow(GenTabCtrls.cb_GenOwnerList, TRUE); //turn on owner's list combobox
    EnableWindow(GenTabCtrls.but_SetGenOwner, TRUE); //turn on the set owner button
    EnableWindow(GenTabCtrls.eb_GenLevel, TRUE); //turn on the edit level field
    EnableWindow(GenTabCtrls.but_SetGenLevel, TRUE); //turn on set level button
    EnableWindow(GenTabCtrls.eb_GenExp, TRUE); //turn on the edit exp field
    EnableWindow(GenTabCtrls.but_SetGenExp, TRUE); //turn on set exp button
    EnableWindow(GenTabCtrls.eb_GenCurHP, TRUE); //turn on the edit cur hp field
    EnableWindow(GenTabCtrls.eb_GenMaxHP, TRUE); //turn on the edit max hp field
    EnableWindow(GenTabCtrls.but_SetGenHP, TRUE); //turn on set hp button
    EnableWindow(GenTabCtrls.eb_GenCurMP, TRUE); //turn on the edit cur mp field
    EnableWindow(GenTabCtrls.eb_GenMaxMP, TRUE); //turn on the edit max mp field
    EnableWindow(GenTabCtrls.but_SetGenMP, TRUE); //turn on set mp button
    EnableWindow(GenTabCtrls.eb_GenStr, TRUE); //turn on the edit str field
    EnableWindow(GenTabCtrls.but_SetGenStr, TRUE); //turn on set str button
    EnableWindow(GenTabCtrls.eb_GenCom, TRUE); //turn on the edit com field
    EnableWindow(GenTabCtrls.but_SetGenCom, TRUE); //turn on set com button
    EnableWindow(GenTabCtrls.eb_GenInt, TRUE); //turn on the edit int field
    EnableWindow(GenTabCtrls.but_SetGenInt, TRUE); //turn on set int button
    EnableWindow(GenTabCtrls.cb_GenTrpType, TRUE); //turn on the edit troop type combobox
    EnableWindow(GenTabCtrls.but_SetGenTrpType, TRUE); //turn on set troop type button
    EnableWindow(GenTabCtrls.eb_GenTrpCnt, TRUE); //turn on the edit troop count field
    EnableWindow(GenTabCtrls.but_SetGenTrpCnt, TRUE); //turn on set troop count button

    EnableWindow(GenTabCtrls.cb_GenSoldier, TRUE); //turn on soldier medals combobox
    EnableWindow(GenTabCtrls.but_SetGenSoldier, TRUE); //turn on set soldier medals button
    EnableWindow(GenTabCtrls.cb_GenCavalry, TRUE); //turn on cavalry medals combobox
    EnableWindow(GenTabCtrls.but_SetGenCavalry, TRUE); //turn on set cavalry medals button
    EnableWindow(GenTabCtrls.cb_GenMage, TRUE); //turn on mage medals combobox
    EnableWindow(GenTabCtrls.but_SetGenMage, TRUE); //turn on set mage medals button
    EnableWindow(GenTabCtrls.cb_GenSamurai, TRUE); //turn on samurai medals combobox
    EnableWindow(GenTabCtrls.but_SetGenSamurai, TRUE); //turn on set samurai medals button
    EnableWindow(GenTabCtrls.cb_GenArcher, TRUE); //turn on archer medals combobox
    EnableWindow(GenTabCtrls.but_SetGenArcher, TRUE); //turn on set archer medals button
    EnableWindow(GenTabCtrls.cb_GenMonk, TRUE); //turn on monk medals combobox
    EnableWindow(GenTabCtrls.but_SetGenMonk, TRUE); //turn on set monk medals button
    EnableWindow(GenTabCtrls.cb_GenBeast, TRUE); //turn on beast medals combobox
    EnableWindow(GenTabCtrls.but_SetGenBeast, TRUE); //turn on set beast medals button
    EnableWindow(GenTabCtrls.cb_GenHarpy, TRUE); //turn on harpy medals combobox
    EnableWindow(GenTabCtrls.but_SetGenHarpy, TRUE); //turn on set harpy medals button
    EnableWindow(GenTabCtrls.cb_GenDragon, TRUE); //turn on dragon medals combobox
    EnableWindow(GenTabCtrls.but_SetGenDragon, TRUE); //turn on set dragon medals button
    EnableWindow(GenTabCtrls.cb_GenZombie, TRUE); //turn on zombie medals combobox
    EnableWindow(GenTabCtrls.but_SetGenZombie, TRUE); //turn on set zombie medals button

    EnableWindow(GenTabCtrls.eb_GenWins, TRUE); //turn on edit wins field
    EnableWindow(GenTabCtrls.but_SetGenWins, TRUE); //turn on set wins button
    EnableWindow(GenTabCtrls.eb_GenLosses, TRUE); //turn on edit losses field
    EnableWindow(GenTabCtrls.but_SetGenLosses, TRUE); //turn on set losses button
    EnableWindow(GenTabCtrls.eb_GenMerits, TRUE); //turn on edit merits field
    EnableWindow(GenTabCtrls.but_SetGenMerits, TRUE); //turn on set merits button
    EnableWindow(GenTabCtrls.eb_GenLives, TRUE); //turn on edit lives field
    EnableWindow(GenTabCtrls.but_SetGenLives, TRUE); //turn on set lives button
    EnableWindow(GenTabCtrls.eb_GenLoyalty, TRUE); //turn on edit loyalty field
    EnableWindow(GenTabCtrls.but_SetGenLoyalty, TRUE); //turn on set loyalty button
    EnableWindow(GenTabCtrls.eb_GenEscape, TRUE); //turn on edit escape field
    EnableWindow(GenTabCtrls.but_SetGenEscape, TRUE); //turn on set escape button
    EnableWindow(GenTabCtrls.cb_GenSpellTier, TRUE); //turn on edit spell tier combobox
    EnableWindow(GenTabCtrls.but_SetGenSpellTier, TRUE); //turn on set spell tier button
    EnableWindow(GenTabCtrls.cb_GenItem, TRUE); //turn on item combobox
    EnableWindow(GenTabCtrls.but_SetGenItem, TRUE); //turn on set item button
    EnableWindow(GenTabCtrls.ckbox_GenSearchFortify, TRUE); //turn on search/fortify check box
    EnableWindow(GenTabCtrls.but_setGenSearchFortify, TRUE); //turn on set search/fortify button

    EnableWindow(GenTabCtrls.rb_GenCastleLocation, TRUE); //turn location radio button on
    EnableWindow(GenTabCtrls.cb_GenLocation, TRUE); //turn on location combobox
    EnableWindow(GenTabCtrls.but_SetGenLocation, TRUE); //turn on set location button
    EnableWindow(GenTabCtrls.rb_GenHiddenLocation, TRUE); //turn hidden location radio button on
    EnableWindow(GenTabCtrls.cb_GenHidden, TRUE); //turn on hidden location combobox
    EnableWindow(GenTabCtrls.but_SetGenHidden, TRUE); //turn on set hidden location button
    EnableWindow(GenTabCtrls.rb_GenDivision, TRUE); //turn division radio button on

    EnableWindow(GenTabCtrls.eb_GenDefp, TRUE); //turn on edit defp field
    EnableWindow(GenTabCtrls.but_SetGenDefp, TRUE); //turn on set defp button
    EnableWindow(GenTabCtrls.eb_GenDefVsSword, TRUE); //turn on edit def vs sword field
    EnableWindow(GenTabCtrls.but_SetGenDefVsSword, TRUE); //turn on set def vs sword button
    EnableWindow(GenTabCtrls.eb_GenDefVsIce, TRUE); //turn on edit def vs ice field
    EnableWindow(GenTabCtrls.but_SetGenDefVsIce, TRUE); //turn on set def vs ice button
    EnableWindow(GenTabCtrls.eb_GenDefVsFire, TRUE); //turn on edit def vs fire field
    EnableWindow(GenTabCtrls.but_SetGenDefVsFire, TRUE); //turn on set def vs fire button
    EnableWindow(GenTabCtrls.eb_GenDefVsLight, TRUE); //turn on edit def vs light field
    EnableWindow(GenTabCtrls.but_SetGenDefVsLight, TRUE); //turn on set def vs light button
    EnableWindow(GenTabCtrls.eb_GenDefVsDark, TRUE); //turn on edit def vs dark field
    EnableWindow(GenTabCtrls.but_SetGenDefVsDark, TRUE); //turn on set def vs dark button

    EnableWindow(GenTabCtrls.eb_GenNAction, TRUE); //turn on edit n_action field
    EnableWindow(GenTabCtrls.but_SetGenNAction, TRUE); //turn on set n_action button
    EnableWindow(GenTabCtrls.eb_GenBAction, TRUE); //turn on edit b_action field
    EnableWindow(GenTabCtrls.but_SetGenBAction, TRUE); //turn on set b_action button
    EnableWindow(GenTabCtrls.eb_GenBtlAction, TRUE); //turn on edit btl_action field
    EnableWindow(GenTabCtrls.but_SetGenBtlAction, TRUE); //turn on set btl_action button
    EnableWindow(GenTabCtrls.eb_GenMoral, TRUE); //turn on edit moral field
    EnableWindow(GenTabCtrls.but_SetGenMoral, TRUE); //turn on set moral button
    EnableWindow(GenTabCtrls.eb_GenWarlike, TRUE); //turn on edit warlike field
    EnableWindow(GenTabCtrls.but_SetGenWarlike, TRUE); //turn on set warlike button
    EnableWindow(GenTabCtrls.eb_GenNego, TRUE); //turn on edit nego field
    EnableWindow(GenTabCtrls.but_SetGenNego, TRUE); //turn on set nego button
    EnableWindow(GenTabCtrls.eb_GenAtkPlus, TRUE); //turn on edit atkplus field
    EnableWindow(GenTabCtrls.but_SetGenAtkPlus, TRUE); //turn on set atkplus button
    EnableWindow(GenTabCtrls.eb_GenDefPlus, TRUE); //turn on edit defplus field
    EnableWindow(GenTabCtrls.but_SetGenDefPlus, TRUE); //turn on set defplus button

    if(!alreadyOpened) //only need to initialize contents of comboboxes once
    {
        for(int i = 0; i < 171; i++) //setting up Generals Names List combobox
            SendMessage(GenTabCtrls.cb_GenNameList, CB_ADDSTRING, 0, LPARAM(generalsNameList[i]));
        SendMessage(GenTabCtrls.cb_GenNameList, CB_SETCURSEL, 0, 0);

        for(int i = 0; i < 171; i++) //setting up Generals Owners List combobox
            SendMessage(GenTabCtrls.cb_GenOwnerList, CB_ADDSTRING, 0, LPARAM(generalsNameList[i]));
        SendMessage(GenTabCtrls.cb_GenOwnerList, CB_SETCURSEL, 0, 0);

        for(int i = 0; i < 11; i++) //setting up Generals troop type combobox
            SendMessage(GenTabCtrls.cb_GenTrpType, CB_ADDSTRING, 0, LPARAM(troopType[i]));
        SendMessage(GenTabCtrls.cb_GenTrpType, CB_SETCURSEL, dr.genArr[gen].troopIndex, 0);

        for(int i = 0; i < 11; i++) //setting up Generals soldier medals combobox
            SendMessage(GenTabCtrls.cb_GenSoldier, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
        SendMessage(GenTabCtrls.cb_GenSoldier, CB_SETCURSEL, dr.genArr[gen].troopMedals[1], 0);

        for(int i = 0; i < 11; i++) //setting up Generals cavalry medals combobox
            SendMessage(GenTabCtrls.cb_GenCavalry, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
        SendMessage(GenTabCtrls.cb_GenCavalry, CB_SETCURSEL, dr.genArr[gen].troopMedals[2], 0);

        for(int i = 0; i < 11; i++) //setting up Generals mage medals combobox
            SendMessage(GenTabCtrls.cb_GenMage, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
        SendMessage(GenTabCtrls.cb_GenMage, CB_SETCURSEL, dr.genArr[gen].troopMedals[3], 0);

        for(int i = 0; i < 11; i++) //setting up Generals samurai medals combobox
            SendMessage(GenTabCtrls.cb_GenSamurai, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
        SendMessage(GenTabCtrls.cb_GenSamurai, CB_SETCURSEL, dr.genArr[gen].troopMedals[4], 0);

        for(int i = 0; i < 11; i++) //setting up Generals archer medals combobox
            SendMessage(GenTabCtrls.cb_GenArcher, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
        SendMessage(GenTabCtrls.cb_GenArcher, CB_SETCURSEL, dr.genArr[gen].troopMedals[5], 0);

        for(int i = 0; i < 11; i++) //setting up Generals monk medals combobox
            SendMessage(GenTabCtrls.cb_GenMonk, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
        SendMessage(GenTabCtrls.cb_GenMonk, CB_SETCURSEL, dr.genArr[gen].troopMedals[6], 0);

        for(int i = 0; i < 11; i++) //setting up Generals harpy medals combobox
            SendMessage(GenTabCtrls.cb_GenHarpy, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
        SendMessage(GenTabCtrls.cb_GenHarpy, CB_SETCURSEL, dr.genArr[gen].troopMedals[7], 0);

        for(int i = 0; i < 11; i++) //setting up Generals beast medals combobox
            SendMessage(GenTabCtrls.cb_GenBeast, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
        SendMessage(GenTabCtrls.cb_GenBeast, CB_SETCURSEL, dr.genArr[gen].troopMedals[8], 0);

        for(int i = 0; i < 11; i++) //setting up Generals dragon medals combobox
            SendMessage(GenTabCtrls.cb_GenDragon, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
        SendMessage(GenTabCtrls.cb_GenDragon, CB_SETCURSEL, dr.genArr[gen].troopMedals[9], 0);

        for(int i = 0; i < 11; i++) //setting up Generals zombie medals combobox
            SendMessage(GenTabCtrls.cb_GenZombie, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
        SendMessage(GenTabCtrls.cb_GenZombie, CB_SETCURSEL, dr.genArr[gen].troopMedals[10], 0);

        for(int i = 0; i < 48; i++) //setting up Generals item combobox
            SendMessage(GenTabCtrls.cb_GenItem, CB_ADDSTRING, 0, LPARAM(itemList[i]));
        SendMessage(GenTabCtrls.cb_GenItem, CB_SETCURSEL, dr.genArr[gen].equippedItem, 0);

        for(int i = 0; i < 4; i++) //setting up Generals spell tier combobox
            SendMessage(GenTabCtrls.cb_GenSpellTier, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
        SendMessage(GenTabCtrls.cb_GenSpellTier, CB_SETCURSEL, dr.genArr[gen].spellTier, 0);

        for(int i = 0; i < 35; i++) //setting up Generals location combobox
            SendMessage(GenTabCtrls.cb_GenLocation, CB_ADDSTRING, 0, LPARAM(castlesNameList[i]));

        SendMessage(GenTabCtrls.cb_GenHidden, CB_ADDSTRING, 0, LPARAM("No"));
        SendMessage(GenTabCtrls.cb_GenHidden, CB_ADDSTRING, 0, LPARAM("Site 62"));
        SendMessage(GenTabCtrls.cb_GenHidden, CB_ADDSTRING, 0, LPARAM("Site 127"));
    } // if(!alreadyOpened)

    SendMessage(GenTabCtrls.cb_GenLocation, CB_SETCURSEL, (dr.genArr[gen].location < 34) ? dr.genArr[gen].location : 35, 0);

    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0); //get selected general ID
    SendMessage(GenTabCtrls.cb_GenOwnerList, CB_SETCURSEL, officerOwner[gen], 0); //select owner

    SetDlgItemInt(hTabGenerals, ID_EB_GENLEVEL, dr.genArr[gen].level, FALSE); //fill level field
    SetDlgItemInt(hTabGenerals, ID_EB_GENEXP, dr.genArr[gen].currentExp, FALSE); //fill curr exp field

    SetDlgItemInt(hTabGenerals, ID_EB_GENCURHP, dr.genArr[gen].currentHP, FALSE); //fill cur hp field
    SetDlgItemInt(hTabGenerals, ID_EB_GENMAXHP, dr.genArr[gen].maxHP, FALSE);     //fill max hp field

    SetDlgItemInt(hTabGenerals, ID_EB_GENCURMP, dr.genArr[gen].currentMP, FALSE); //fill cur mp field
    SetDlgItemInt(hTabGenerals, ID_EB_GENMAXMP, dr.genArr[gen].maxMP, FALSE);     //fill max mp field

    SetDlgItemInt(hTabGenerals, ID_EB_GENSTR, dr.genArr[gen].strength, FALSE);     //fill str field
    SetWindowText(sc_GenStrVal, itoa((int)ceil((dr.genArr[gen].strength * 0.6)), itoaArr, 10)); //fill str static control
    SetDlgItemInt(hTabGenerals, ID_EB_GENCOM, dr.genArr[gen].command, FALSE);      //fill com field
    SetWindowText(sc_GenCmdVal, itoa((int)ceil((dr.genArr[gen].command * 0.6)), itoaArr, 10)); //fill cmd static control
    SetDlgItemInt(hTabGenerals, ID_EB_GENINT, dr.genArr[gen].intelligence, FALSE); //fill int field
    SetWindowText(sc_GenIntVal, itoa((int)ceil(((dr.genArr[gen].intelligence * 6) + 10)), itoaArr, 10)); //fill int static control

    SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE); //fill troop count field
    
    SetDlgItemInt(hTabGenerals, ID_EB_GENWINS, dr.genArr[gen].newWins, FALSE); //fill wins field
    SetDlgItemInt(hTabGenerals, ID_EB_GENLOSSES, dr.genArr[gen].newLosses, FALSE); //fill losses field
    SetDlgItemInt(hTabGenerals, ID_EB_GENMERITS, dr.genArr[gen].newMerits, FALSE); //fill merits field
    SetDlgItemInt(hTabGenerals, ID_EB_GENLIVES, dr.genArr[gen].livesLeft, FALSE); //fill lives field
    SetDlgItemInt(hTabGenerals, ID_EB_GENLOYALTY, dr.genArr[gen].loyalty, FALSE); //fill loyalty field
    SetDlgItemInt(hTabGenerals, ID_EB_GENESCAPE, dr.genArr[gen].escapeChance, FALSE); //fill escape field

    SetDlgItemInt(hTabGenerals, ID_EB_GENDEFP, dr.genArr[gen].defp, FALSE); //fill defp field
    SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_SWORD, dr.genArr[gen].defSword, FALSE); //fill defSword field
    SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_ICE, dr.genArr[gen].defIce, FALSE); //fill defIcefield
    SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_FIRE, dr.genArr[gen].defFire, FALSE); //fill defFire field
    SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_LIGHT, dr.genArr[gen].defLight, FALSE); //fill defLight field
    SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_DARK, dr.genArr[gen].defDark, FALSE); //fill defDark field

    SetDlgItemInt(hTabGenerals, ID_EB_NACTION, dr.genArr[gen].nAction, FALSE); //fill n_action field
    SetDlgItemInt(hTabGenerals, ID_EB_BACTION, dr.genArr[gen].bAction, FALSE); //fill b_action field
    SetDlgItemInt(hTabGenerals, ID_EB_BTL_ACTION, dr.genArr[gen].btlAction, FALSE); //fill btl_action field
    SetDlgItemInt(hTabGenerals, ID_EB_MORAL, dr.genArr[gen].moral, FALSE); //fill moral field
    SetDlgItemInt(hTabGenerals, ID_EB_WARLIKE, dr.genArr[gen].warlike, FALSE); //fill warlike field
    SetDlgItemInt(hTabGenerals, ID_EB_NEGO, dr.genArr[gen].nego, FALSE); //fill nego field
    SetDlgItemInt(hTabGenerals, ID_EB_ATKPLUS, dr.genArr[gen].atkPlus, FALSE); //fill atkplus field
    SetDlgItemInt(hTabGenerals, ID_EB_DEFPLUS, dr.genArr[gen].defPlus, FALSE); //fill defplus field

    ShowWindow(sc_GenIDNumVal, TRUE);
    SetWindowText(sc_GenIDNumVal, itoa(dr.genArr[gen].listIndex, itoaArr, 10));
    ShowWindow(sc_GenPortraitVal, TRUE);
    SetWindowText(sc_GenPortraitVal, itoa(dr.genArr[gen].portrait, itoaArr, 10));
    ShowWindow(sc_GenClassVal, TRUE);
    SetWindowText(sc_GenClassVal, classType[dr.genArr[gen].classType]);
    ShowWindow(sc_GenStatusVal, TRUE);
    SetWindowText(sc_GenStatusVal, genStatusArray[dr.genArr[gen].fieldStatus1][dr.genArr[gen].fieldStatus2]);

    ShowWindow(sc_GenHospitalVal, TRUE);
    if(dr.genArr[gen].hospital)
        SetWindowText(sc_GenHospitalVal, "Yes");
    else
        SetWindowText(sc_GenHospitalVal, "No");

    if(!dr.genArr[gen].domesticsSF)
        CheckDlgButton(hTabGenerals, ID_CKBX_SEARCH_FORT, BST_CHECKED);
    else
        CheckDlgButton(hTabGenerals, ID_CKBX_SEARCH_FORT, BST_UNCHECKED);

    if(dr.genArr[gen].fixedLocation && (dr.genArr[gen].location < 34))
    {
        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_CAS_LOC, BM_SETCHECK, 1, 0);
        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_HIDE_LOC, BM_SETCHECK, 0, 0);
        SendMessage(GenTabCtrls.cb_GenHidden, CB_SETCURSEL, 0, 0); //select owner
        EnableWindow(GenTabCtrls.but_SetGenLocation, TRUE); //turn on set location button
        EnableWindow(GenTabCtrls.but_SetGenHidden, FALSE); //turn off set hidden location button
        EnableWindow(GenTabCtrls.cb_GenLocation, TRUE); //turn on location combobox
        EnableWindow(GenTabCtrls.cb_GenHidden, FALSE); //turn off hidden location combobox
    }
    if(dr.genArr[gen].fixedLocation && (dr.genArr[gen].location > 34))
    {
        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_HIDE_LOC, BM_SETCHECK, 1, 0);
        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_CAS_LOC, BM_SETCHECK, 0, 0);
        EnableWindow(GenTabCtrls.cb_GenHidden, TRUE); //turn on hidden location combobox
        EnableWindow(GenTabCtrls.but_SetGenHidden, TRUE); //turn on set hidden location button
        EnableWindow(GenTabCtrls.cb_GenLocation, FALSE); //turn off set location combobox
        EnableWindow(GenTabCtrls.but_SetGenLocation, FALSE); //turn off set location button
    }
    if(!dr.genArr[gen].fixedLocation)
    {
        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_HIDE_LOC, BM_SETCHECK, 0, 0);
        EnableWindow(GenTabCtrls.cb_GenHidden, FALSE); //turn off hidden location combobox
        EnableWindow(GenTabCtrls.but_SetGenHidden, FALSE); //turn off set hidden location button

        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_CAS_LOC, BM_SETCHECK, 0, 0);
        EnableWindow(GenTabCtrls.cb_GenLocation, FALSE); //turn off set location combobox
        EnableWindow(GenTabCtrls.but_SetGenLocation, FALSE); //turn off set location button
        ShowGenTabDivisionInfo(gen, true);
    }

    return;
}

void ShowGenTabDivisionInfo(const int gen, const bool show)
{
    char itoaArr[5] = {'\0'};

    if(show)
    {
        ShowWindow(GenTabCtrls.rb_GenDivision, TRUE);
        ShowWindow(sc_GenDivisionTag, TRUE);
        ShowWindow(sc_GenDivKingTag, TRUE);
        ShowWindow(sc_GenDivLeaderTag, TRUE);
        ShowWindow(sc_GenDivStatusTag, TRUE);
        ShowWindow(sc_GenDivNumTag, TRUE);
        ShowWindow(sc_GenDivXCoordTag, TRUE);
        ShowWindow(sc_GenDivYCoordTag, TRUE);
        ShowWindow(sc_GenDivOriginTag, TRUE);
        ShowWindow(sc_GenDivGoalTag, TRUE);
        ShowWindow(sc_GenDivPrevTag, TRUE);
        ShowWindow(sc_GenDivNextTag, TRUE);
        ShowWindow(sc_GenDivTroopsTag, TRUE);
        ShowWindow(sc_GenDivMembersTag, TRUE);
        ShowWindow(sc_GenDivCaptivesTag, TRUE);

        ShowWindow(sc_GenDivKingVal, TRUE);
        ShowWindow(sc_GenDivLeaderVal, TRUE);
        ShowWindow(sc_GenDivStatusVal, TRUE);
        ShowWindow(sc_GenDivNumVal, TRUE);
        ShowWindow(sc_GenDivXCoordVal, TRUE);
        ShowWindow(sc_GenDivYCoordVal, TRUE);
        ShowWindow(sc_GenDivOriginVal, TRUE);
        ShowWindow(sc_GenDivGoalVal, TRUE);
        ShowWindow(sc_GenDivPrevVal, TRUE);
        ShowWindow(sc_GenDivNextVal, TRUE);
        ShowWindow(sc_GenDivTroopsVal, TRUE);
        ShowWindow(sc_GenDivMembersVal, TRUE);
        ShowWindow(sc_GenDivCaptivesVal, TRUE);

        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_DIV_LOC, BM_SETCHECK, 1, 0);
        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_CAS_LOC, BM_SETCHECK, 0, 0);
        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_HIDE_LOC, BM_SETCHECK, 0, 0);
        SetWindowText(sc_GenDivKingVal, dr.genArr[gen].owner.c_str());
        SetWindowText(sc_GenDivLeaderVal, generalsNameList[dr.divArr[dr.genArr[gen].location].leader]);
        SetWindowText(sc_GenDivStatusVal, shidanStatus[dr.divArr[dr.genArr[gen].location].status]);
        SetWindowText(sc_GenDivOriginVal, locationList[dr.divArr[dr.genArr[gen].location].origin]);
        
        if(dr.divArr[dr.genArr[gen].location].goal == 255) //needed for Paine/Agonni's goal being out of bounds because of monarch targeting
            SetWindowText(sc_GenDivGoalVal, generalsNameList[dr.playingAs]);
        else
            SetWindowText(sc_GenDivGoalVal, locationList[dr.divArr[dr.genArr[gen].location].goal]);
        
        SetWindowText(sc_GenDivPrevVal, locationList[dr.divArr[dr.genArr[gen].location].prev]);
        SetWindowText(sc_GenDivNextVal, locationList[dr.divArr[dr.genArr[gen].location].next]);
        SetWindowText(sc_GenDivNumVal, itoa(dr.genArr[gen].location, itoaArr, 10));
        SetWindowText(sc_GenDivXCoordVal, itoa(dr.divArr[dr.genArr[gen].location].xCoordinate, itoaArr, 10));
        SetWindowText(sc_GenDivYCoordVal, itoa(dr.divArr[dr.genArr[gen].location].yCoordinate, itoaArr, 10));
        SetWindowText(sc_GenDivTroopsVal, itoa(dr.divArr[dr.genArr[gen].location].troopCount, itoaArr, 10));
        SetWindowText(sc_GenDivMembersVal, itoa(dr.divArr[dr.genArr[gen].location].numMembers, itoaArr, 10));
        SetWindowText(sc_GenDivCaptivesVal, itoa(dr.divArr[dr.genArr[gen].location].numCaptives, itoaArr, 10));
    }
    else
    {
        ShowWindow(GenTabCtrls.rb_GenDivision, FALSE);
        ShowWindow(sc_GenDivisionTag, FALSE);
        ShowWindow(sc_GenDivKingTag, FALSE);
        ShowWindow(sc_GenDivLeaderTag, FALSE);
        ShowWindow(sc_GenDivStatusTag, FALSE);
        ShowWindow(sc_GenDivNumTag, FALSE);
        ShowWindow(sc_GenDivXCoordTag, FALSE);
        ShowWindow(sc_GenDivYCoordTag, FALSE);
        ShowWindow(sc_GenDivOriginTag, FALSE);
        ShowWindow(sc_GenDivGoalTag, FALSE);
        ShowWindow(sc_GenDivPrevTag, FALSE);
        ShowWindow(sc_GenDivNextTag, FALSE);
        ShowWindow(sc_GenDivTroopsTag, FALSE);
        ShowWindow(sc_GenDivMembersTag, FALSE);
        ShowWindow(sc_GenDivCaptivesTag, FALSE);

        ShowWindow(sc_GenDivKingVal, FALSE);
        ShowWindow(sc_GenDivLeaderVal, FALSE);
        ShowWindow(sc_GenDivStatusVal, FALSE);
        ShowWindow(sc_GenDivNumVal, FALSE);
        ShowWindow(sc_GenDivXCoordVal, FALSE);
        ShowWindow(sc_GenDivYCoordVal, FALSE);
        ShowWindow(sc_GenDivOriginVal, FALSE);
        ShowWindow(sc_GenDivGoalVal, FALSE);
        ShowWindow(sc_GenDivPrevVal, FALSE);
        ShowWindow(sc_GenDivNextVal, FALSE);
        ShowWindow(sc_GenDivTroopsVal, FALSE);
        ShowWindow(sc_GenDivMembersVal, FALSE);
        ShowWindow(sc_GenDivCaptivesVal, FALSE);

        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_DIV_LOC, BM_SETCHECK, 0, 0);
    }

    return;
}

void setGenLocationControls(const int gen)
{
    if(dr.genArr[gen].fixedLocation && (dr.genArr[gen].location < 34)) //enable castle line, disable rest
    {
        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_CAS_LOC, BM_SETCHECK, 1, 0);
        EnableWindow(GenTabCtrls.cb_GenLocation, TRUE); //turn on location combobox
        EnableWindow(GenTabCtrls.but_SetGenLocation, TRUE); //turn on set location button

        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_HIDE_LOC, BM_SETCHECK, 0, 0);
        EnableWindow(GenTabCtrls.cb_GenHidden, FALSE); //turn off hidden location combobox
        EnableWindow(GenTabCtrls.but_SetGenHidden, FALSE); //turn off set hidden location button
        ShowGenTabDivisionInfo(gen, false);
    }
    if(dr.genArr[gen].fixedLocation && (dr.genArr[gen].location > 33)) //enable hidden loc line, disable rest
    {
        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_HIDE_LOC, BM_SETCHECK, 1, 0);
        EnableWindow(GenTabCtrls.cb_GenHidden, TRUE); //turn on hidden location combobox
        if(dr.genArr[gen].location == 62)
            SendMessage(GenTabCtrls.cb_GenHidden, CB_SETCURSEL, 1, 0);
        if(dr.genArr[gen].location == 127)
            SendMessage(GenTabCtrls.cb_GenHidden, CB_SETCURSEL, 2, 0);
        EnableWindow(GenTabCtrls.but_SetGenHidden, TRUE); //turn on set hidden location button

        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_CAS_LOC, BM_SETCHECK, 0, 0);
        EnableWindow(GenTabCtrls.cb_GenLocation, FALSE); //turn off set location button
        EnableWindow(GenTabCtrls.but_SetGenLocation, FALSE); //turn off set location button
        ShowGenTabDivisionInfo(gen, false);
    }
    if(!dr.genArr[gen].fixedLocation) //enable division area, disable rest
    {
        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_HIDE_LOC, BM_SETCHECK, 0, 0);
        SendMessage(GenTabCtrls.cb_GenHidden, CB_SETCURSEL, 0, 0);
        EnableWindow(GenTabCtrls.cb_GenHidden, FALSE); //turn off hidden location combobox
        EnableWindow(GenTabCtrls.but_SetGenHidden, FALSE); //turn off set hidden location button

        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_CAS_LOC, BM_SETCHECK, 0, 0);
        SendMessage(GenTabCtrls.cb_GenLocation, CB_SETCURSEL, 34, 0);
        EnableWindow(GenTabCtrls.cb_GenLocation, FALSE); //turn off set location button
        EnableWindow(GenTabCtrls.but_SetGenLocation, FALSE); //turn off set location button
        ShowGenTabDivisionInfo(gen, true);
    }

    return;
}

/*
   RETURN: -1 == multiple generals in castle; trying to give one general different owner
            0 == nothing happened
            1 == one general in castle, had to fix castle ownership
*/
int compareOwnerGenVsCastle(const int gen)
{
    int loc;
    int locNumGens;
    int genRuler;
    int locRuler;

    loc        = dr.genArr[gen].location;
    locNumGens = dr.casArr[loc].numGenerals;
    genRuler   = officerOwner[gen];
    locRuler   = dr.casArr[loc].ruler;
    
    if(genRuler != locRuler)
    {
        if(locNumGens == 1) //if they are the only general in the castle, just change it's ruler to the general's ruler
        {
            dr.casArr[loc].changeRuler(genRuler);
            return 1;
        }
        else
            if(locNumGens > 1)
            {
                dr.genArr[gen].changeGenOwner(locRuler);
                return -1;
            }
    }

    return 0;
}

LRESULT CALLBACK GenTabWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int gen     = -1;
    int success = 0;
    char itoaArr[5] = {'\0'};

    switch(msg)
    {
        case WM_ACTIVATE:         //not sure if this is needed yet
            if(wParam == 0)
                hDlgCurrent = NULL;
            else
                hDlgCurrent = hwnd;
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_CB_GENNAME:
                    switch(HIWORD(wParam))
                    {
                        case CBN_SELCHANGE:
                        {
                            gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0); //find who is selected
                            updateGeneralsTab(gen);
                        }
                        break;
                    }
                break;//ID_CB_GENNAME
                case ID_SET_GENOWNER:
                {
                    int newOwner;
                    int compareSuccess;
                    gen      = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    newOwner = SendMessage(GenTabCtrls.cb_GenOwnerList, CB_GETCURSEL, 0, 0);
                    if(!(success = dr.genArr[gen].changeGenOwner(newOwner)))
                        MessageBox(hwnd, "Failed to write new owner to file.", "Error", MB_OK | MB_ICONERROR);
                    if(success == -1)
                    {
                        SendMessage(GenTabCtrls.cb_GenOwnerList, CB_SETCURSEL, officerOwner[gen], 0);
                        MessageBox(hwnd, "You can't change your monarch's owner.", "Error", MB_OK | MB_ICONERROR);
                    }
                    compareSuccess = compareOwnerGenVsCastle(gen);
                    if(compareSuccess == -1)
                    {
                        MessageBox(hwnd, "The general's owner must be the same as the castle's owner.", "Error", MB_OK | MB_ICONERROR);
                        dr.genArr[gen].changeGenOwner(dr.casArr[dr.genArr[gen].location].ruler);
                        SendMessage(GenTabCtrls.cb_GenOwnerList, CB_SETCURSEL, officerOwner[gen], 0);
                    }
                        
                }
                break; //ID_SET_GENOWNER
                case ID_SET_GENLEVEL:
                {
                    int level;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    level = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENLEVEL, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(0, 49, level - 1, GEN_LEVEL, &(dr.genArr[gen].level), levelBuffer);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENLEVEL, dr.genArr[gen].level, FALSE);
                        MessageBox(hwnd, "The level is out of range (1 to 50).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write level to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENLEVEL
                case ID_SET_GENEXP:
                {
                    int exp;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    exp = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENEXP, NULL, FALSE);
                    success = dr.genArr[gen].editTwoByteStat(0, 65535, exp, GEN_CURR_EXP, &(dr.genArr[gen].currentExp), currExpBuffer);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENEXP, dr.genArr[gen].currentExp, FALSE);
                        MessageBox(hwnd, "The experience is out of range (0 to 65535).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write experience to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENEXP
                case ID_SET_GENHP:
                {
                    int curHP;
                    int maxHP;
                    int success2 = 0;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    curHP = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENCURHP, NULL, FALSE);
                    maxHP = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENMAXHP, NULL, FALSE);
                    success  = dr.genArr[gen].editOneByteStat(1, 127, curHP, GEN_CURRENT_HP, &(dr.genArr[gen].currentHP), currentHpBuffer);
                    success2 = dr.genArr[gen].editOneByteStat(1, 127, maxHP, GEN_MAX_HP, &(dr.genArr[gen].maxHP), maxHpBuffer);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENCURHP, dr.genArr[gen].currentHP, FALSE);
                        MessageBox(hwnd, "The current hit points are out of range (1 to 127).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write current hit points to file.", "Error", MB_OK | MB_ICONERROR);
                    if(success2 == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENMAXHP, dr.genArr[gen].maxHP, FALSE);
                        MessageBox(hwnd, "The maximum hit points are out of range (1 to 127).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success2 == -2)
                        MessageBox(hwnd, "Failed to write maximum hit points to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENHP
                case ID_SET_GENMP:
                {
                    int curMP;
                    int maxMP;
                    int success2 = 0;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    curMP = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENCURMP, NULL, FALSE);
                    maxMP = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENMAXMP, NULL, FALSE);
                    success  = dr.genArr[gen].editOneByteStat(1, 99, curMP, GEN_CURRENT_MP, &(dr.genArr[gen].currentMP), currentMpBuffer);
                    success2 = dr.genArr[gen].editOneByteStat(1, 99, maxMP, GEN_MAX_MP, &(dr.genArr[gen].maxMP), maxMpBuffer);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENCURMP, dr.genArr[gen].currentMP, FALSE);
                        MessageBox(hwnd, "The current magic points are out of range (1 to 99).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write current magic points to file.", "Error", MB_OK | MB_ICONERROR);
                    if(success2 == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENMAXMP, dr.genArr[gen].maxMP, FALSE);
                        MessageBox(hwnd, "The maximum magic points are out of range (1 to 99).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success2 == -2)
                        MessageBox(hwnd, "Failed to write maximum magic points to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENMP
                case ID_SET_GENSTR:
                {
                    int str;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    str = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENSTR, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(1, 255, str, GEN_STRENGTH, &(dr.genArr[gen].strength), strengthBuffer);
                    if(success == 1)
                        SetWindowText(sc_GenStrVal, itoa((int)ceil((dr.genArr[gen].strength * 0.6)), itoaArr, 10)); //set str static control
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENSTR, dr.genArr[gen].strength, FALSE);
                        MessageBox(hwnd, "The strength is out of range (1 to 255).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write strength to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENSTR
                case ID_SET_GENCOM:
                {
                    int com;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    com = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENCOM, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(1, 255, com, GEN_COMMAND, &(dr.genArr[gen].command), commandBuffer);
                    if(success == 1)
                        SetWindowText(sc_GenCmdVal, itoa((int)ceil((dr.genArr[gen].command * 0.6)), itoaArr, 10)); //fill cmd static control
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENCOM, dr.genArr[gen].command, FALSE);
                        MessageBox(hwnd, "The command is out of range (1 to 255).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write command to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENCOM
                case ID_SET_GENINT:
                {
                    int intell;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    intell = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENINT, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(1, 255, intell, GEN_INTELLIGENCE, &(dr.genArr[gen].intelligence), intellBuffer);
                    if(success == 1)
                        SetWindowText(sc_GenIntVal, itoa((int)ceil(((dr.genArr[gen].intelligence * 6) + 10)), itoaArr, 10)); //fill int static control
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENINT, dr.genArr[gen].intelligence, FALSE);
                        MessageBox(hwnd, "The intelligence is out of range (1 to 255).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write intelligence to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENINT
                case ID_SET_GENTRPCNT:
                {
                    int troopCount;
                    int maxTroops;
                    
                    gen        = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    troopCount = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, NULL, FALSE);
                    maxTroops  = dr.genArr[gen].troopMedals[dr.genArr[gen].troopIndex] * 10;
                    success    = dr.genArr[gen].editOneByteStat(0, maxTroops, troopCount, GEN_CURR_TROOP_COUNT, &(dr.genArr[gen].currentTroopCount), currTroopCountBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE);
                        MessageBox(hwnd, "The troop count is out of range (0 to (medals x 10)).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write troop count to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENTRPCNT
                case ID_SET_GENTRPTYPE:
                {
                    int troopCount;
                    int maxTroops;
                    int newTroopType;

                    gen          = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    newTroopType = SendMessage(GenTabCtrls.cb_GenTrpType, CB_GETCURSEL, 0, 0);
                    troopCount   = dr.genArr[gen].currentTroopCount;
                    success      = dr.genArr[gen].changeGenTroopType(newTroopType);
                    maxTroops    = dr.genArr[gen].troopMedals[dr.genArr[gen].troopIndex] * 10;
                    if(success == -1)
                    {
                        SendMessage(GenTabCtrls.cb_GenTrpType, CB_SETCURSEL, dr.genArr[gen].troopIndex, 0); //set their troop type
                        MessageBox(hwnd, "The General does not have any medals for that troop type.", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == 1)
                    {
                        if(troopCount > maxTroops)
                        {
                            troopCount = maxTroops;
                            dr.genArr[gen].editOneByteStat(0, maxTroops, troopCount, GEN_CURR_TROOP_COUNT, &(dr.genArr[gen].currentTroopCount), currTroopCountBuff);
                            SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE);
                        }
                        if(dr.genArr[gen].troopIndex == 0)
                        {
                            dr.genArr[gen].editOneByteStat(0, 0, 0, GEN_CURR_TROOP_COUNT, &(dr.genArr[gen].currentTroopCount), currTroopCountBuff);
                            SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE);
                        }
                    }
                }
                break;//ID_SET_GENTRPTYPE
                case ID_SET_GENWINS:
                {
                    int wins;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    wins = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENWINS, NULL, FALSE);
                    success = dr.genArr[gen].editTwoByteStat(0, 9999, wins, GEN_TOTAL_WINS, &(dr.genArr[gen].newWins), totalWinBuffer);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENWINS, dr.genArr[gen].newWins, FALSE);
                        MessageBox(hwnd, "The wins are out of range (0 to 9999).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write wins to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENWINS
                case ID_SET_GENLOSSES:
                {
                    int losses;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    losses = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENLOSSES, NULL, FALSE);
                    success = dr.genArr[gen].editTwoByteStat(0, 9999, losses, GEN_TOTAL_LOSSES, &(dr.genArr[gen].newLosses), totalLossBuffer);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENLOSSES, dr.genArr[gen].newLosses, FALSE);
                        MessageBox(hwnd, "The losses are out of range (0 to 9999).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write losses to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENLOSSES
                case ID_SET_GENMERITS:
                {
                    int merits;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    merits = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENMERITS, NULL, FALSE);
                    success = dr.genArr[gen].editTwoByteStat(0, 9999, merits, GEN_NEW_MERITS, &(dr.genArr[gen].newMerits), newMeritsBuffer);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENMERITS, dr.genArr[gen].newMerits, FALSE);
                        MessageBox(hwnd, "The merits are out of range (0 to 9999).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write merits to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENMERITS
                case ID_SET_GENLIVES:
                {
                    int lives;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    lives = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENLIVES, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(1, 255, lives, GEN_LIVES_BEF_SLAIN, &(dr.genArr[gen].livesLeft), livesBefSlainBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENLIVES, dr.genArr[gen].livesLeft, FALSE);
                        MessageBox(hwnd, "The lives are out of range (1 to 255).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write lives to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENLIVES
                case ID_SET_GENLOYALTY:
                {
                    int loyal;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    loyal = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENLOYALTY, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(0, 255, loyal, GEN_LOYALTY, &(dr.genArr[gen].loyalty), loyaltyBuffer);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENLOYALTY, dr.genArr[gen].loyalty, FALSE);
                        MessageBox(hwnd, "The loyalty is out of range (0 to 255).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write loyalty to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENLOYALTY
                case ID_SET_GENDEFP:
                {
                    int defp;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    defp = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENDEFP, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(0, 255, defp, GEN_DEFP, &(dr.genArr[gen].defp), defpBuffer);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENDEFP, dr.genArr[gen].defp, FALSE);
                        MessageBox(hwnd, "The defp is out of range (0 to 255).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write defp to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENDEFP
                case ID_SET_GENESCAPE:
                {
                    int escape;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    escape = (int)GetDlgItemInt(hTabGenerals, ID_EB_GENESCAPE, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(0, 255, escape, GEN_ESCAPE_CHANCE, &(dr.genArr[gen].escapeChance), escChanceBuffer);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_GENESCAPE, dr.genArr[gen].escapeChance, FALSE);
                        MessageBox(hwnd, "The escape chance is out of range (0 to 255).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write escape chance to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENESCAPE
                case ID_SET_GENSPELLTIER:
                {
                    int spelltier;
                    gen       = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    spelltier = SendMessage(GenTabCtrls.cb_GenSpellTier, CB_GETCURSEL, 0, 0);
                    if(!(success = dr.genArr[gen].editOneByteStat(0, 3, spelltier, GEN_SPELL_TIER, &(dr.genArr[gen].spellTier), spellTierBuffer)))
                        MessageBox(hwnd, "Failed to write spell tier to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENSPELLTIER
                case ID_SET_GENITEM:
                {
                    int item;
                    gen   = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    item  = SendMessage(GenTabCtrls.cb_GenItem, CB_GETCURSEL, 0, 0);
                    if(!(success = dr.genArr[gen].editOneByteStat(0, 47, item, GEN_EQUIPPED_ITEM, &(dr.genArr[gen].equippedItem), equippedItemBuffer)))
                        MessageBox(hwnd, "Failed to write equipped item to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_GENITEM
                case ID_RB_GEN_CAS_LOC: 
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                            SendDlgItemMessage(hTabGenerals, ID_RB_GEN_CAS_LOC, BM_SETCHECK, 1, 0);
                            EnableWindow(GenTabCtrls.cb_GenLocation, TRUE); //turn on location combobox
                            EnableWindow(GenTabCtrls.but_SetGenLocation, TRUE); //turn on set location button

                            SendDlgItemMessage(hTabGenerals, ID_RB_GEN_HIDE_LOC, BM_SETCHECK, 0, 0);
                            EnableWindow(GenTabCtrls.cb_GenHidden, FALSE); //turn off hidden location combobox
                            EnableWindow(GenTabCtrls.but_SetGenHidden, FALSE); //turn off set hidden location button
                            SendDlgItemMessage(hTabGenerals, ID_RB_GEN_DIV_LOC, BM_SETCHECK, 0, 0);
                            if(dr.genArr[gen].fixedLocation)
                                ShowGenTabDivisionInfo(gen, false);
                        }
                        break;
                    }
                }
                break; //ID_RB_GEN_CAS_LOC
                case ID_RB_GEN_HIDE_LOC: 
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                            SendDlgItemMessage(hTabGenerals, ID_RB_GEN_HIDE_LOC, BM_SETCHECK, 1, 0);
                            EnableWindow(GenTabCtrls.cb_GenHidden, TRUE); //turn on hidden location combobox
                            EnableWindow(GenTabCtrls.but_SetGenHidden, TRUE); //turn on set hidden location button

                            SendDlgItemMessage(hTabGenerals, ID_RB_GEN_CAS_LOC, BM_SETCHECK, 0, 0);
                            EnableWindow(GenTabCtrls.cb_GenLocation, FALSE); //turn off set location button
                            EnableWindow(GenTabCtrls.but_SetGenLocation, FALSE); //turn off set location button
                            SendDlgItemMessage(hTabGenerals, ID_RB_GEN_DIV_LOC, BM_SETCHECK, 0, 0);
                            if(dr.genArr[gen].fixedLocation)
                                ShowGenTabDivisionInfo(gen, false);
                        }
                        break;
                    }
                }
                break; //ID_RB_GEN_HIDE_LOC
                case ID_RB_GEN_DIV_LOC: 
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                            SendDlgItemMessage(hTabGenerals, ID_RB_GEN_HIDE_LOC, BM_SETCHECK, 0, 0);
                            EnableWindow(GenTabCtrls.cb_GenHidden, FALSE); //turn off hidden location combobox
                            EnableWindow(GenTabCtrls.but_SetGenHidden, FALSE); //turn off set hidden location button

                            SendDlgItemMessage(hTabGenerals, ID_RB_GEN_CAS_LOC, BM_SETCHECK, 0, 0);
                            EnableWindow(GenTabCtrls.cb_GenLocation, FALSE); //turn off set location button
                            EnableWindow(GenTabCtrls.but_SetGenLocation, FALSE); //turn off set location button
                            ShowGenTabDivisionInfo(gen, true);
                        }
                        break;
                    }
                }
                break; //ID_RB_GEN_DIV_LOC
                case ID_SET_GENLOCATION:
                {
                    int location;
                    
                    gen      = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    location = SendMessage(GenTabCtrls.cb_GenLocation, CB_GETCURSEL, 0, 0);
                    success  = dr.genArr[gen].changeLocation(1, 3, location);
                    if(success == 1)
                    {
                        SendMessage(GenTabCtrls.cb_GenOwnerList, CB_SETCURSEL, officerOwner[gen], 0);
                        SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE);
                        SetWindowText(sc_GenStatusVal, genStatusArray[dr.genArr[gen].fieldStatus1][dr.genArr[gen].fieldStatus2]);
                    }
                    if(success == -1)
                        MessageBox(hwnd, "The destination castle is already full", "Error", MB_OK | MB_ICONERROR);
                    if(success == -2)
                        MessageBox(hwnd, "You can't hide your monarch.", "Error", MB_OK | MB_ICONERROR);
                    updateGeneralsTab(gen);
                }
                break; //ID_SET_GENLOCATION
                case ID_SET_GENHIDDEN:
                {
                    int location;
                    
                    gen      = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    location = SendMessage(GenTabCtrls.cb_GenHidden, CB_GETCURSEL, 0, 0);
                    if(location == 0)
                    {
                        MessageBox(hwnd, "You need to choose either 62 or 127.", "Error", MB_OK | MB_ICONERROR);
                        setGenLocationControls(gen);
                        break;
                    }
                    success  = dr.genArr[gen].changeLocation(1, 3, 62);
                    if(success == 1)
                    {
                        SendMessage(GenTabCtrls.cb_GenOwnerList, CB_SETCURSEL, officerOwner[gen], 0);
                        SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "You can't hide your monarch.", "Error", MB_OK | MB_ICONERROR);
                    setGenLocationControls(gen);
                }
                break; //ID_SET_GENHIDDEN
                case ID_SET_GENSOLDIER:
                {
                    int medals;

                    gen    = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    medals = SendMessage(GenTabCtrls.cb_GenSoldier, CB_GETCURSEL, 0, 0);
                    dr.genArr[gen].editMedals(medals, 1, &dr.genArr[gen].soldierCavalry, 2, dr.genArr[gen].troopMedals[1], dr.genArr[gen].troopMedals[2], GEN_SOLD_AND_CAVA);
                    SendMessage(GenTabCtrls.cb_GenTrpType, CB_SETCURSEL, troopTypeBuff[gen], 0); //set their troop type
                    SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE); //set troop count
                }
                break; //ID_SET_GENSOLDIER
                case ID_SET_GENCAVALRY:
                {
                    int medals;

                    gen    = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    medals = SendMessage(GenTabCtrls.cb_GenCavalry, CB_GETCURSEL, 0, 0);
                    dr.genArr[gen].editMedals(medals, 2, &dr.genArr[gen].soldierCavalry, 1, dr.genArr[gen].troopMedals[1], dr.genArr[gen].troopMedals[2], GEN_SOLD_AND_CAVA);
                    SendMessage(GenTabCtrls.cb_GenTrpType, CB_SETCURSEL, troopTypeBuff[gen], 0); //set their troop type
                    SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE); //set troop count
                }
                break; //ID_SET_GENCAVALRY
                case ID_SET_GENMAGE:
                {
                    int medals;

                    gen    = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    medals = SendMessage(GenTabCtrls.cb_GenMage, CB_GETCURSEL, 0, 0);
                    dr.genArr[gen].editMedals(medals, 3, &dr.genArr[gen].mageSamurai, 2, dr.genArr[gen].troopMedals[3], dr.genArr[gen].troopMedals[4], GEN_MAGE_AND_SAMU);
                    SendMessage(GenTabCtrls.cb_GenTrpType, CB_SETCURSEL, troopTypeBuff[gen], 0); //set their troop type
                    SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE); //set troop count
                }
                break; //ID_SET_GENMAGE
                case ID_SET_GENSAMURAI:
                {
                    int medals;

                    gen    = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    medals = SendMessage(GenTabCtrls.cb_GenSamurai, CB_GETCURSEL, 0, 0);
                    dr.genArr[gen].editMedals(medals, 4, &dr.genArr[gen].mageSamurai, 1, dr.genArr[gen].troopMedals[3], dr.genArr[gen].troopMedals[4], GEN_MAGE_AND_SAMU);
                    SendMessage(GenTabCtrls.cb_GenTrpType, CB_SETCURSEL, troopTypeBuff[gen], 0); //set their troop type
                    SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE); //set troop count
                }
                break; //ID_SET_GENSAMURAI
                case ID_SET_GENARCHER:
                {
                    int medals;

                    gen    = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    medals = SendMessage(GenTabCtrls.cb_GenArcher, CB_GETCURSEL, 0, 0);
                    dr.genArr[gen].editMedals(medals, 5, &dr.genArr[gen].archerMonk, 2, dr.genArr[gen].troopMedals[5], dr.genArr[gen].troopMedals[6], GEN_ARCH_AND_MONK);
                    SendMessage(GenTabCtrls.cb_GenTrpType, CB_SETCURSEL, troopTypeBuff[gen], 0); //set their troop type
                    SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE); //set troop count
                }
                break; //ID_SET_GENARCHER
                case ID_SET_GENMONK:
                {
                    int medals;

                    gen    = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    medals = SendMessage(GenTabCtrls.cb_GenMonk, CB_GETCURSEL, 0, 0);
                    dr.genArr[gen].editMedals(medals, 6, &dr.genArr[gen].archerMonk, 1, dr.genArr[gen].troopMedals[5], dr.genArr[gen].troopMedals[6], GEN_ARCH_AND_MONK);
                    SendMessage(GenTabCtrls.cb_GenTrpType, CB_SETCURSEL, troopTypeBuff[gen], 0); //set their troop type
                    SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE); //set troop count
                }
                break; //ID_SET_GENMONK
                case ID_SET_GENHARPY:
                {
                    int medals;

                    gen    = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    medals = SendMessage(GenTabCtrls.cb_GenHarpy, CB_GETCURSEL, 0, 0);
                    dr.genArr[gen].editMedals(medals, 7, &dr.genArr[gen].harpyBeast, 2, dr.genArr[gen].troopMedals[7], dr.genArr[gen].troopMedals[8], GEN_HARP_AND_BEAS);
                    SendMessage(GenTabCtrls.cb_GenTrpType, CB_SETCURSEL, troopTypeBuff[gen], 0); //set their troop type
                    SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE); //set troop count
                }
                break; //ID_SET_GENHARPY
                case ID_SET_GENBEAST:
                {
                    int medals;

                    gen    = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    medals = SendMessage(GenTabCtrls.cb_GenBeast, CB_GETCURSEL, 0, 0);
                    dr.genArr[gen].editMedals(medals, 8, &dr.genArr[gen].harpyBeast, 1, dr.genArr[gen].troopMedals[7], dr.genArr[gen].troopMedals[8], GEN_HARP_AND_BEAS);
                    SendMessage(GenTabCtrls.cb_GenTrpType, CB_SETCURSEL, troopTypeBuff[gen], 0); //set their troop type
                    SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE); //set troop count
                }
                break; //ID_SET_GENBEAST
                case ID_SET_GENDRAGON:
                {
                    int medals;

                    gen    = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    medals = SendMessage(GenTabCtrls.cb_GenDragon, CB_GETCURSEL, 0, 0);
                    dr.genArr[gen].editMedals(medals, 9, &dr.genArr[gen].dragonZombie, 2, dr.genArr[gen].troopMedals[9], dr.genArr[gen].troopMedals[10], GEN_DRAG_AND_ZOMB);
                    SendMessage(GenTabCtrls.cb_GenTrpType, CB_SETCURSEL, troopTypeBuff[gen], 0); //set their troop type
                    SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE); //set troop count
                }
                break; //ID_SET_GENDRAGON
                case ID_SET_GENZOMBIE:
                {
                    int medals;

                    gen    = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    medals = SendMessage(GenTabCtrls.cb_GenZombie, CB_GETCURSEL, 0, 0);
                    dr.genArr[gen].editMedals(medals, 10, &dr.genArr[gen].dragonZombie, 1, dr.genArr[gen].troopMedals[9], dr.genArr[gen].troopMedals[10], GEN_DRAG_AND_ZOMB);
                    SendMessage(GenTabCtrls.cb_GenTrpType, CB_SETCURSEL, troopTypeBuff[gen], 0); //set their troop type
                    SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE); //set troop count
                }
                break; //ID_SET_GENZOMBIE
                case ID_CKBX_SEARCH_FORT:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            int checkState;

                            checkState = SendMessage(GenTabCtrls.ckbox_GenSearchFortify, BM_GETCHECK, 0, 0);

                            if(checkState == BST_CHECKED)
                                CheckDlgButton(hTabGenerals, ID_CKBX_SEARCH_FORT, BST_UNCHECKED);
                            if(checkState == BST_UNCHECKED)
                                CheckDlgButton(hTabGenerals, ID_CKBX_SEARCH_FORT, BST_CHECKED);
                        }
                        break;
                    }
                }
                break; //ID_CKBX_SEARCH_FORT
                case ID_SET_SEARCH_FORT:
                {
                    int checkState;

                    checkState = SendMessage(GenTabCtrls.ckbox_GenSearchFortify, BM_GETCHECK, 0, 0);
                    gen        = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    
                    if(checkState == BST_CHECKED)
                        dr.genArr[gen].setSearchFortifyStatus(false);
                    if(checkState == BST_UNCHECKED)
                        dr.genArr[gen].setSearchFortifyStatus(true);
                }
                break; //ID_SET_SEARCH_FORT
                case ID_SET_DEF_VS_SWORD:
                {
                    int defSword;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    defSword = (int)GetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_SWORD, NULL, FALSE);
                    success = dr.genArr[gen].editTwoByteStat(0, 65535, defSword, GEN_DEF_SWORD, &(dr.genArr[gen].defSword), defSwordBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_SWORD, dr.genArr[gen].defSword, FALSE);
                        MessageBox(hwnd, "The weakness vs troops is out of range (0 to 65535).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write weakness vs troops to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_EB_DEF_VS_SWORD
                case ID_SET_DEF_VS_ICE:
                {
                    int defIce;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    defIce = (int)GetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_ICE, NULL, FALSE);
                    success = dr.genArr[gen].editTwoByteStat(0, 65535, defIce, GEN_DEF_ICE, &(dr.genArr[gen].defIce), defIceBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_ICE, dr.genArr[gen].defIce, FALSE);
                        MessageBox(hwnd, "The weakness vs water/wind is out of range (0 to 65535).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write weakness vs water/wind to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_EB_DEF_VS_ICE
                case ID_SET_DEF_VS_FIRE:
                {
                    int defFire;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    defFire = (int)GetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_FIRE, NULL, FALSE);
                    success = dr.genArr[gen].editTwoByteStat(0, 65535, defFire, GEN_DEF_FIRE, &(dr.genArr[gen].defFire), defFireBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_FIRE, dr.genArr[gen].defFire, FALSE);
                        MessageBox(hwnd, "The weakness vs fire is out of range (0 to 65535).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write weakness vs fire to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_EB_DEF_VS_FIRE
                case ID_SET_DEF_VS_LIGHT:
                {
                    int defLight;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    defLight = (int)GetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_LIGHT, NULL, FALSE);
                    success = dr.genArr[gen].editTwoByteStat(0, 65535, defLight, GEN_DEF_LIGHT, &(dr.genArr[gen].defLight), defLightBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_LIGHT, dr.genArr[gen].defLight, FALSE);
                        MessageBox(hwnd, "The weakness vs light is out of range (0 to 65535).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write weakness vs light to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_EB_DEF_VS_LIGHT
                case ID_SET_DEF_VS_DARK:
                {
                    int defDark;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    defDark = (int)GetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_DARK, NULL, FALSE);
                    success = dr.genArr[gen].editTwoByteStat(0, 65535, defDark, GEN_DEF_DARK, &(dr.genArr[gen].defDark), defDarkBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_DARK, dr.genArr[gen].defDark, FALSE);
                        MessageBox(hwnd, "The weakness vs dark is out of range (0 to 65535).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write weakness vs dark to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_EB_DEF_VS_DARK
                case ID_SET_NACTION:
                {
                    int nAction;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    nAction = (int)GetDlgItemInt(hTabGenerals, ID_EB_NACTION, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(0, 255, nAction, GEN_N_ACTION, &(dr.genArr[gen].nAction), nActionBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_NACTION, dr.genArr[gen].nAction, FALSE);
                        MessageBox(hwnd, "The n_action is out of range (0 to 255).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write n_action to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_NACTION
                case ID_SET_BACTION:
                {
                    int bAction;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    bAction = (int)GetDlgItemInt(hTabGenerals, ID_EB_BACTION, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(0, 255, bAction, GEN_B_ACTION, &(dr.genArr[gen].bAction), bActionBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_BACTION, dr.genArr[gen].bAction, FALSE);
                        MessageBox(hwnd, "The b_action is out of range (0 to 255).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write b_action to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_BACTION
                case ID_SET_BTL_ACTION:
                {
                    int btlAction;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    btlAction = (int)GetDlgItemInt(hTabGenerals, ID_EB_BTL_ACTION, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(0, 255, btlAction, GEN_BTL_ACTION, &(dr.genArr[gen].btlAction), btlActionBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_BTL_ACTION, dr.genArr[gen].btlAction, FALSE);
                        MessageBox(hwnd, "The btl_action is out of range (0 to 255).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write btl_action to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_BTL_ACTION
                case ID_SET_MORAL:
                {
                    int moral;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    moral = (int)GetDlgItemInt(hTabGenerals, ID_EB_MORAL, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(0, 255, moral, GEN_MORAL, &(dr.genArr[gen].moral), moralBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_MORAL, dr.genArr[gen].moral, FALSE);
                        MessageBox(hwnd, "The moral is out of range (0 to 255).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write moral to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_MORAL
                case ID_SET_WARLIKE:
                {
                    int warlike;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    warlike = (int)GetDlgItemInt(hTabGenerals, ID_EB_WARLIKE, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(0, 255, warlike, GEN_WARLIKE, &(dr.genArr[gen].warlike), warlikeBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_WARLIKE, dr.genArr[gen].warlike, FALSE);
                        MessageBox(hwnd, "The warlike is out of range (0 to 255).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write warlike to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_WARLIKE
                case ID_SET_NEGO:
                {
                    int nego;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    nego = (int)GetDlgItemInt(hTabGenerals, ID_EB_NEGO, NULL, FALSE);
                    success = dr.genArr[gen].editTwoByteStat(0, 65535, nego, GEN_NEGO, &(dr.genArr[gen].nego), negoBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_NEGO, dr.genArr[gen].nego, FALSE);
                        MessageBox(hwnd, "The nego is out of range (0 to 65535).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write nego to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_NEGO
                case ID_SET_ATKPLUS:
                {
                    int atkPlus;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    atkPlus = (int)GetDlgItemInt(hTabGenerals, ID_EB_ATKPLUS, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(0, 170, atkPlus, GEN_ATK_PLUS, &(dr.genArr[gen].atkPlus), atkPlusBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_ATKPLUS, dr.genArr[gen].atkPlus, FALSE);
                        MessageBox(hwnd, "The atkPlus is out of range (0 to 179).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write atkPlus to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_ATKPLUS
                case ID_SET_DEFPLUS:
                {
                    int defPlus;
                    gen = SendMessage(GenTabCtrls.cb_GenNameList, CB_GETCURSEL, 0, 0);
                    defPlus = (int)GetDlgItemInt(hTabGenerals, ID_EB_DEFPLUS, NULL, FALSE);
                    success = dr.genArr[gen].editOneByteStat(0, 255, defPlus, GEN_DEF_PLUS, &(dr.genArr[gen].defPlus), defPlusBuff);
                    if(success == -1)
                    {
                        SetDlgItemInt(hTabGenerals, ID_EB_DEFPLUS, dr.genArr[gen].defPlus, FALSE);
                        MessageBox(hwnd, "The defPlus is out of range (0 to 255).", "Error", MB_OK | MB_ICONERROR);
                    }
                    if(success == -2)
                        MessageBox(hwnd, "Failed to write defPlus to file.", "Error", MB_OK | MB_ICONERROR);
                }
                break; //ID_SET_DEFPLUS
            }
        break;
        default:
            return CallWindowProc(g_MainWndProc, hwnd, msg, wParam, lParam);
    }

    return 0;
}

void updateGeneralsTab(const int gen)
{
    char itoaArr[5] = {'\0'};

    dr.genArr[gen].needsUpdate = false;

    SendMessage(GenTabCtrls.cb_GenOwnerList, CB_SETCURSEL, officerOwner[gen], 0); //set their owner
    SetDlgItemInt(hTabGenerals, ID_EB_GENLEVEL, dr.genArr[gen].level, FALSE); //set their level
    SetDlgItemInt(hTabGenerals, ID_EB_GENEXP, dr.genArr[gen].currentExp, FALSE); //set their exp
    SetDlgItemInt(hTabGenerals, ID_EB_GENCURHP, dr.genArr[gen].currentHP, FALSE); //set cur hp
    SetDlgItemInt(hTabGenerals, ID_EB_GENMAXHP, dr.genArr[gen].maxHP, FALSE);     //set max hp
    SetDlgItemInt(hTabGenerals, ID_EB_GENCURMP, dr.genArr[gen].currentMP, FALSE); //set cur hp
    SetDlgItemInt(hTabGenerals, ID_EB_GENMAXMP, dr.genArr[gen].maxMP, FALSE);     //set max hp
    SetDlgItemInt(hTabGenerals, ID_EB_GENSTR, dr.genArr[gen].strength, FALSE);    //fill str field
    SetWindowText(sc_GenStrVal, itoa((int)ceil((dr.genArr[gen].strength * 0.6)), itoaArr, 10)); //set str static control
    SetDlgItemInt(hTabGenerals, ID_EB_GENCOM, dr.genArr[gen].command, FALSE);      //fill com field
    SetWindowText(sc_GenCmdVal, itoa((int)ceil((dr.genArr[gen].command * 0.6)), itoaArr, 10)); //fill cmd static control
    SetDlgItemInt(hTabGenerals, ID_EB_GENINT, dr.genArr[gen].intelligence, FALSE); //fill int field
    SetWindowText(sc_GenIntVal, itoa((int)ceil(((dr.genArr[gen].intelligence * 6) + 10)), itoaArr, 10)); //fill int static control

    SendMessage(GenTabCtrls.cb_GenTrpType, CB_SETCURSEL, dr.genArr[gen].troopIndex, 0); //set their troop type
    SetDlgItemInt(hTabGenerals, ID_EB_GENTRPCNT, dr.genArr[gen].currentTroopCount, FALSE); //set troop count
    SendMessage(GenTabCtrls.cb_GenSoldier, CB_SETCURSEL, dr.genArr[gen].troopMedals[1], 0); //set soldier medals
    SendMessage(GenTabCtrls.cb_GenCavalry, CB_SETCURSEL, dr.genArr[gen].troopMedals[2], 0); //set cavalry medals
    SendMessage(GenTabCtrls.cb_GenMage, CB_SETCURSEL, dr.genArr[gen].troopMedals[3], 0); //set mage medals
    SendMessage(GenTabCtrls.cb_GenSamurai, CB_SETCURSEL, dr.genArr[gen].troopMedals[4], 0); //set samurai medals
    SendMessage(GenTabCtrls.cb_GenArcher, CB_SETCURSEL, dr.genArr[gen].troopMedals[5], 0); //set archer medals
    SendMessage(GenTabCtrls.cb_GenMonk, CB_SETCURSEL, dr.genArr[gen].troopMedals[6], 0); //set monk medals
    SendMessage(GenTabCtrls.cb_GenHarpy, CB_SETCURSEL, dr.genArr[gen].troopMedals[7], 0); //set beast medals
    SendMessage(GenTabCtrls.cb_GenBeast, CB_SETCURSEL, dr.genArr[gen].troopMedals[8], 0); //set harpy medals
    SendMessage(GenTabCtrls.cb_GenDragon, CB_SETCURSEL, dr.genArr[gen].troopMedals[9], 0); //set dragon medals
    SendMessage(GenTabCtrls.cb_GenZombie, CB_SETCURSEL, dr.genArr[gen].troopMedals[10], 0); //set zombie medals

    SetDlgItemInt(hTabGenerals, ID_EB_GENWINS, dr.genArr[gen].newWins, FALSE); //set wins field
    SetDlgItemInt(hTabGenerals, ID_EB_GENLOSSES, dr.genArr[gen].newLosses, FALSE); //set losses field
    SetDlgItemInt(hTabGenerals, ID_EB_GENMERITS, dr.genArr[gen].newMerits, FALSE); //fill merits field
    SetDlgItemInt(hTabGenerals, ID_EB_GENLIVES, dr.genArr[gen].livesLeft, FALSE); //fill lives field
    SetDlgItemInt(hTabGenerals, ID_EB_GENLOYALTY, dr.genArr[gen].loyalty, FALSE); //fill loyalty field
    SetDlgItemInt(hTabGenerals, ID_EB_GENESCAPE, dr.genArr[gen].escapeChance, FALSE); //fill escape field
    SendMessage(GenTabCtrls.cb_GenSpellTier, CB_SETCURSEL, dr.genArr[gen].spellTier, 0); //set spell tier
    SendMessage(GenTabCtrls.cb_GenItem, CB_SETCURSEL, dr.genArr[gen].equippedItem, 0); //set equipped item

    SetDlgItemInt(hTabGenerals, ID_EB_GENDEFP, dr.genArr[gen].defp, FALSE); //fill defp field
    SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_SWORD, dr.genArr[gen].defSword, FALSE); //fill defSword field
    SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_ICE, dr.genArr[gen].defIce, FALSE); //fill defIcefield
    SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_FIRE, dr.genArr[gen].defFire, FALSE); //fill defFire field
    SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_LIGHT, dr.genArr[gen].defLight, FALSE); //fill defLight field
    SetDlgItemInt(hTabGenerals, ID_EB_DEF_VS_DARK, dr.genArr[gen].defDark, FALSE); //fill defDark field

    SetWindowText(sc_GenIDNumVal, itoa(dr.genArr[gen].listIndex, itoaArr, 10));
    SetWindowText(sc_GenPortraitVal, itoa(dr.genArr[gen].portrait, itoaArr, 10));
    SetWindowText(sc_GenClassVal, classType[dr.genArr[gen].classType]);
    SetWindowText(sc_GenStatusVal, genStatusArray[dr.genArr[gen].fieldStatus1][dr.genArr[gen].fieldStatus2]);

    if(dr.genArr[gen].hospital)
        SetWindowText(sc_GenHospitalVal, "Yes");
    else
        SetWindowText(sc_GenHospitalVal, "No");


    SetDlgItemInt(hTabGenerals, ID_EB_NACTION, dr.genArr[gen].nAction, FALSE); //fill n_action field
    SetDlgItemInt(hTabGenerals, ID_EB_BACTION, dr.genArr[gen].bAction, FALSE); //fill b_action field
    SetDlgItemInt(hTabGenerals, ID_EB_BTL_ACTION, dr.genArr[gen].btlAction, FALSE); //fill btl_action field
    SetDlgItemInt(hTabGenerals, ID_EB_MORAL, dr.genArr[gen].moral, FALSE); //fill moral field
    SetDlgItemInt(hTabGenerals, ID_EB_WARLIKE, dr.genArr[gen].warlike, FALSE); //fill warlike field
    SetDlgItemInt(hTabGenerals, ID_EB_NEGO, dr.genArr[gen].nego, FALSE); //fill nego field
    SetDlgItemInt(hTabGenerals, ID_EB_ATKPLUS, dr.genArr[gen].atkPlus, FALSE); //fill atkplus field
    SetDlgItemInt(hTabGenerals, ID_EB_DEFPLUS, dr.genArr[gen].defPlus, FALSE); //fill defplus field

    if(!dr.genArr[gen].domesticsSF)
        CheckDlgButton(hTabGenerals, ID_CKBX_SEARCH_FORT, BST_CHECKED);
    else
        CheckDlgButton(hTabGenerals, ID_CKBX_SEARCH_FORT, BST_UNCHECKED);
                            
    if((dr.genArr[gen].fixedLocation == 1) && (dr.genArr[gen].location < 34)) //set castle location
    {
        SendMessage(GenTabCtrls.cb_GenLocation, CB_SETCURSEL, dr.genArr[gen].location, 0); //set location
        SendMessage(GenTabCtrls.cb_GenHidden, CB_SETCURSEL, 0, 0); //set hidden location
    }
    if((dr.genArr[gen].fixedLocation == 1) && (dr.genArr[gen].location == 62))  //set location for site 62
    {
        SendMessage(GenTabCtrls.cb_GenLocation, CB_SETCURSEL, 34, 0); //set location
        SendMessage(GenTabCtrls.cb_GenHidden, CB_SETCURSEL, 1, 0); //set hidden location
    }
    if((dr.genArr[gen].fixedLocation == 1) && (dr.genArr[gen].location == 127))  //set location for site 127
    {
        SendMessage(GenTabCtrls.cb_GenLocation, CB_SETCURSEL, 34, 0); //set location
        SendMessage(GenTabCtrls.cb_GenHidden, CB_SETCURSEL, 2, 0); //set hidden location
    }
    if(!dr.genArr[gen].fixedLocation)
    {
        SendMessage(GenTabCtrls.cb_GenLocation, CB_SETCURSEL, 34, 0); //set location
        SendMessage(GenTabCtrls.cb_GenHidden, CB_SETCURSEL, 0, 0); //set hidden location
    }

    if(dr.genArr[gen].fixedLocation && (dr.genArr[gen].location < 34)) //enable castle line, disable rest
    {
        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_CAS_LOC, BM_SETCHECK, 1, 0);
        EnableWindow(GenTabCtrls.cb_GenLocation, TRUE); //turn on location combobox
        EnableWindow(GenTabCtrls.but_SetGenLocation, TRUE); //turn on set location button

        SendDlgItemMessage(hTabGenerals, ID_RB_GEN_HIDE_LOC, BM_SETCHECK, 0, 0);
        EnableWindow(GenTabCtrls.cb_GenHidden, FALSE); //turn off hidden location combobox
        EnableWindow(GenTabCtrls.but_SetGenHidden, FALSE); //turn off set hidden location button
        ShowGenTabDivisionInfo(gen, false);
    }
        if(dr.genArr[gen].fixedLocation && (dr.genArr[gen].location > 33)) //enable hidden loc line, disable rest
        {
            SendDlgItemMessage(hTabGenerals, ID_RB_GEN_HIDE_LOC, BM_SETCHECK, 1, 0);
            EnableWindow(GenTabCtrls.cb_GenHidden, TRUE); //turn on hidden location combobox
            if(dr.genArr[gen].location == 62)
                SendMessage(GenTabCtrls.cb_GenHidden, CB_SETCURSEL, 1, 0);
            if(dr.genArr[gen].location == 127)
                SendMessage(GenTabCtrls.cb_GenHidden, CB_SETCURSEL, 2, 0);
            EnableWindow(GenTabCtrls.but_SetGenHidden, TRUE); //turn on set hidden location button

            SendDlgItemMessage(hTabGenerals, ID_RB_GEN_CAS_LOC, BM_SETCHECK, 0, 0);
            EnableWindow(GenTabCtrls.cb_GenLocation, FALSE); //turn off set location button
            EnableWindow(GenTabCtrls.but_SetGenLocation, FALSE); //turn off set location button
            ShowGenTabDivisionInfo(gen, false);
        }
        if(!dr.genArr[gen].fixedLocation) //enable division area, disable rest
        {
            SendDlgItemMessage(hTabGenerals, ID_RB_GEN_HIDE_LOC, BM_SETCHECK, 0, 0);
            EnableWindow(GenTabCtrls.cb_GenHidden, FALSE); //turn off hidden location combobox
            EnableWindow(GenTabCtrls.but_SetGenHidden, FALSE); //turn off set hidden location button

            SendDlgItemMessage(hTabGenerals, ID_RB_GEN_CAS_LOC, BM_SETCHECK, 0, 0);
            EnableWindow(GenTabCtrls.cb_GenLocation, FALSE); //turn off set location button
            EnableWindow(GenTabCtrls.but_SetGenLocation, FALSE); //turn off set location button
            ShowGenTabDivisionInfo(gen, true);
        }

    return;
}
