#include <windows.h>
#include <commctrl.h>
#include <cmath>
#include <sstream>

#include "DFGui.h"

static int castleOwners[171] = {-1};
static int castleOwnerCount  = 0;

HWND MassEditTypeGroupBox;
HWND MassEditGenSelGroupBox;
HWND MassEditCasSelGroupBox;
HWND SelectedGensGroupBox;
HWND SelectedCasGroupBox;

HWND rb_MassEditGenTag;
HWND rb_MassEditCasTag;
//HWND rb_MassEditDivTag;

HWND MassEditGenStatsGroupBox;

HWND cb_MassEditGenOwnerTag;
HWND eb_MassEditGenLevelTag;
HWND eb_MassEditGenExpTag;
HWND eb_MassEditGenHpTag;
HWND eb_MassEditGenMpTag;
HWND eb_MassEditGenStrTag;
HWND eb_MassEditGenComTag;
HWND eb_MassEditGenIntTag;
HWND eb_MassEditGenLivesTag;
HWND eb_MassEditGenLoyaltyTag;
HWND cb_MassEditGenTrpTypeTag;
HWND eb_MassEditGenTrpCntTag;
HWND cb_MassEditGenSoldierTag;
HWND cb_MassEditGenCavalryTag;
HWND cb_MassEditGenMageTag;
HWND cb_MassEditGenSamuraiTag;
HWND cb_MassEditGenArcherTag;
HWND cb_MassEditGenMonkTag;
HWND cb_MassEditGenHarpyTag;
HWND cb_MassEditGenBeastTag;
HWND cb_MassEditGenDragonTag;
HWND cb_MassEditGenZombieTag;
HWND eb_MassEditGenWinsTag;
HWND eb_MassEditGenLossTag;
HWND eb_MassEditGenMeritsTag;
HWND eb_MassEditGenEscapeTag;
HWND cb_MassEditGenSpellTierTag;
HWND cb_MassEditGenItemTag;
HWND eb_MassEditGenDefTrpsTag;
HWND eb_MassEditGenDefSwdTag;
HWND eb_MassEditGenDefIceTag;
HWND eb_MassEditGenDefFireTag;
HWND eb_MassEditGenDefLightTag;
HWND eb_MassEditGenDefDarkTag;
HWND eb_MassEditGenNAactionTag;
HWND eb_MassEditGenBActionTag;
HWND eb_MassEditGenBtlActionTag;
HWND eb_MassEditGenWarlikeTag;
HWND eb_MassEditGenNegoTag;
HWND eb_MassEditGenAtkPlusTag;
HWND eb_MassEditGenDefPlusTag;

HWND ME_lineDownMiddle;

HWND ME_WeaknessGroupBox;
HWND ME_UnknownsGroupBox;

HWND cb_MassEditCasOwnerTag;
HWND cb_MassEditCasLevelTag;
HWND eb_MassEditCasTrpCntTag;

void CreateMassEditTab(void)
{
    hTabMassEdit = CreateWindowEx(
        0, "STATIC", NULL, WS_CHILD | WS_TABSTOP,
        0, 22, 1009, 688,
        hTabCntrl, NULL, hThisInst, NULL);

    g_MainWndProc = (WNDPROC)SetWindowLongPtr(hTabMassEdit, GWL_WNDPROC, (LONG)MassEditTabWndProc);

    MassEditTypeGroupBox = CreateWindowEx( //frame surrounding struct type radio buttons
        0, "BUTTON", TEXT("Edit What"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        10, 28, 115, 60, //was 165 when including division editing
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.rb_MassEditGen = CreateWindowEx( //Generals radio button
        0, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | BS_RADIOBUTTON,
        35, 43, 15, 15, 
        hTabMassEdit, (HMENU)ID_RB_ME_GEN, hThisInst, NULL); 

    rb_MassEditGenTag = CreateWindowEx( //Generals radio button text tag
        0, "STATIC", TEXT("Generals"), WS_CHILD | WS_VISIBLE,
        20, 58, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.rb_MassEditCas = CreateWindowEx( //Castles radio button
        0, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | BS_RADIOBUTTON,
        85, 43, 15, 15, 
        hTabMassEdit, (HMENU)ID_RB_ME_CAS, hThisInst, NULL); 

    rb_MassEditCasTag = CreateWindowEx( //Castles radio button text tag
        0, "STATIC", TEXT("Castles"), WS_CHILD | WS_VISIBLE,
        75, 58, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);
/*
    MassEditTabCtrls.rb_MassEditDiv = CreateWindowEx( //Divisions radio button       *********************** CHANGE TO VISIBLE AFTER IMPLEMENTING
        0, "BUTTON", NULL, WS_CHILD | WS_DISABLED | BS_RADIOBUTTON,
        135, 43, 15, 15, 
        hTabMassEdit, (HMENU)ID_RB_ME_DIV, hThisInst, NULL); 

    rb_MassEditDivTag = CreateWindowEx( //Divisions radio button text tag            *********************** CHANGE TO VISIBLE AFTER IMPLEMENTING
        0, "STATIC", TEXT("Divisions"), WS_CHILD,
        122, 58, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);
*/
    MassEditGenSelGroupBox = CreateWindowEx( //frame surrounding Generals selection area
        0, "BUTTON", TEXT("Edit Who"), WS_CHILD | BS_GROUPBOX,
        10, 98, 250, 590, 
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.rb_MassEditGenList = CreateWindowEx( //Generals list radio button
        0, "BUTTON", TEXT("All Generals"), WS_CHILD | WS_DISABLED | BS_RADIOBUTTON,
        20, 123, 74, 15, 
        hTabMassEdit, (HMENU)ID_ME_RB_GENLIST, hThisInst, NULL); 

    MassEditTabCtrls.lb_MassEditGenList = CreateWindowEx( //All Generals listbox
        WS_EX_CLIENTEDGE, "LISTBOX", NULL, WS_VSCROLL | WS_CHILD | 
        WS_TABSTOP | WS_DISABLED | LBS_EXTENDEDSEL | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
        20, 148, 100, 525,
        hTabMassEdit, (HMENU)ID_ME_LB_GENLIST, hThisInst, NULL);

    MassEditTabCtrls.rb_MassEditClassList = CreateWindowEx( //class type radio button
        0, "BUTTON", TEXT("Specific Class"), WS_CHILD | WS_DISABLED | BS_RADIOBUTTON,
        150, 123, 84, 15, 
        hTabMassEdit, (HMENU)ID_ME_RB_CLASS_CB, hThisInst, NULL); 

    MassEditTabCtrls.cb_MassEditClassList = CreateWindowEx( //class type combobox
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        150, 171, 100, 210,
        hTabMassEdit, (HMENU)ID_ME_CB_CLASSLIST, hThisInst, NULL);

    MassEditTabCtrls.ckbox_MonarchsWithClass = CreateWindowEx( //tag for check box to include monarchs in class type selection
        0, "BUTTON", TEXT("Include monarchs"),
        WS_CHILD | WS_TABSTOP | WS_DISABLED | BS_CHECKBOX,
        150, 148, 105, 15,
        hTabMassEdit, (HMENU)ID_ME_XB_INC_KINGS, hThisInst, NULL);

    SelectedGensGroupBox = CreateWindowEx( //frame surrounding selected Generals output area
        0, "BUTTON", TEXT("Generals affected"), WS_CHILD | BS_GROUPBOX,
        280, 98, 140, 590,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_selectedGens = CreateWindowEx( //Selected Generals non-editable editbox
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_VSCROLL | WS_CHILD |
        ES_READONLY | WS_TABSTOP | WS_DISABLED | ES_MULTILINE,
        300, 123, 100, 550,
        hTabMassEdit, (HMENU)ID_ME_EB_SEL_GENS, hThisInst, NULL);

    MassEditGenStatsGroupBox = CreateWindowEx( //frame surrounding editing methods radio buttons
        0, "BUTTON", TEXT("Editing Method"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        440, 28, 127, 85, 
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.rb_MassEditGenByValue = CreateWindowEx( //edit by values radio button
        0, "BUTTON", TEXT("Use Values"), WS_CHILD | WS_VISIBLE | WS_DISABLED | BS_RADIOBUTTON | BS_TEXT,
        450, 43, 73, 15, 
        hTabMassEdit, (HMENU)ID_ME_RB_GEN_VAL, hThisInst, NULL); 

    MassEditTabCtrls.rb_MassEditGenByPercent = CreateWindowEx( //edit by percentages radio button
        0, "BUTTON", TEXT("Use Percentages"), WS_CHILD | WS_VISIBLE | WS_DISABLED | BS_RADIOBUTTON | BS_TEXT,
        450, 58, 102, 15, 
        hTabMassEdit, (HMENU)ID_ME_RB_GEN_PERC, hThisInst, NULL); 

    MassEditTabCtrls.rb_MassEditGenOfCurrent = CreateWindowEx( //edit by percentage of current radio button
        0, "BUTTON", TEXT("Use Current"), WS_CHILD | WS_VISIBLE | WS_DISABLED | BS_RADIOBUTTON | BS_TEXT,
        470, 73, 73, 15, 
        hTabMassEdit, (HMENU)ID_ME_RB_GEN_PC_CUR, hThisInst, NULL); 

    MassEditTabCtrls.rb_MassEditGenOfMax = CreateWindowEx( //edit by percentage of max radio button
        0, "BUTTON", TEXT("Use Maximum"), WS_CHILD | WS_VISIBLE | WS_DISABLED | BS_RADIOBUTTON | BS_TEXT,
        470, 88, 83, 15, 
        hTabMassEdit, (HMENU)ID_ME_RB_GEN_PC_MAX, hThisInst, NULL); 

    cb_MassEditGenOwnerTag = CreateWindowEx( //owner text tag
        0, "STATIC", TEXT("Owner:"), WS_CHILD,
        440, 132, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_GenOwnerList = CreateWindowEx( //owner name list combobox
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        485, 132, 100, 500,
        hTabMassEdit, (HMENU)ID_ME_CB_GENOWNER, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenOwner = CreateWindowEx(   //owner set button
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 132, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENOWNER, hThisInst, NULL);

    eb_MassEditGenLevelTag = CreateWindowEx( //general level text tag
        0, "STATIC", TEXT("Level:"), WS_CHILD,
        440, 157, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenLevel = CreateWindowEx( //general level edit box
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        485, 157, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENLEVEL, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenLevel = CreateWindowEx(   //level set button
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 157, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENLEVEL, hThisInst, NULL);

    eb_MassEditGenExpTag = CreateWindowEx(
        0, "STATIC", TEXT("Exp:"), WS_CHILD,
        440, 182, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenExp = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        485, 182, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENEXP, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenExp = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 182, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENEXP, hThisInst, NULL);

    eb_MassEditGenHpTag = CreateWindowEx(
        0, "STATIC", TEXT("HP:"), WS_CHILD,
        440, 207, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenHP = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        485, 207, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENHP, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenHP = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 207, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENHP, hThisInst, NULL);

    eb_MassEditGenMpTag = CreateWindowEx(
        0, "STATIC", TEXT("MP:"), WS_CHILD,
        440, 232, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenMP = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        485, 232, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENMP, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenMP = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 232, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENMP, hThisInst, NULL);

    eb_MassEditGenStrTag = CreateWindowEx(
        0, "STATIC", TEXT("Strength:"), WS_CHILD,
        440, 257, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenStr = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        485, 257, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENSTR, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenStr = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 257, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENSTR, hThisInst, NULL);

    eb_MassEditGenComTag = CreateWindowEx(
        0, "STATIC", TEXT("Com:"), WS_CHILD,
        440, 282, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenCom = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        485, 282, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENCOM, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenCom = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 282, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENCOM, hThisInst, NULL);

    eb_MassEditGenIntTag = CreateWindowEx(
        0, "STATIC", TEXT("Int:"), WS_CHILD,
        440, 307, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenInt = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        485, 307, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENINT, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenInt = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 307, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENINT, hThisInst, NULL);

    eb_MassEditGenLivesTag = CreateWindowEx(
        0, "STATIC", TEXT("Lives:"), WS_CHILD,
        440, 332, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenLives = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        485, 332, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENLIVES, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenLives = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 332, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENLIVES, hThisInst, NULL);

    eb_MassEditGenLoyaltyTag = CreateWindowEx(
        0, "STATIC", TEXT("Loyalty:"), WS_CHILD,
        440, 357, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenLoyalty = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        485, 357, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENLOYAL, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenLoyalty = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 357, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENLOYAL, hThisInst, NULL);

    cb_MassEditGenTrpTypeTag = CreateWindowEx(
        0, "STATIC", TEXT("Troops:"), WS_CHILD,
        440, 382, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_GenTroopType = CreateWindowEx(
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        485, 382, 100, 170,
        hTabMassEdit, (HMENU)ID_ME_CB_GENTRPS, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenTroopType = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 382, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENTRPS, hThisInst, NULL);

    eb_MassEditGenTrpCntTag = CreateWindowEx(
        0, "STATIC", TEXT("#Troops:"), WS_CHILD,
        440, 407, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenTroopCnt = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        485, 407, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENTRPCNT, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenTrpCnt = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 407, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENTRPCNT, hThisInst, NULL);

    cb_MassEditGenSoldierTag = CreateWindowEx(
        0, "STATIC", TEXT("Soldier:"), WS_CHILD,
        440, 432, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_GenSoldier = CreateWindowEx(
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        485, 432, 50, 170,
        hTabMassEdit, (HMENU)ID_ME_CB_GENSOLD, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenSoldier = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 432, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENSOLD, hThisInst, NULL);

    cb_MassEditGenCavalryTag = CreateWindowEx(
        0, "STATIC", TEXT("Cavalry:"), WS_CHILD,
        440, 457, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_GenCavalry = CreateWindowEx(
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        485, 457, 50, 170,
        hTabMassEdit, (HMENU)ID_ME_CB_GENCAV, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenCavalry = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 457, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENCAV, hThisInst, NULL);

    cb_MassEditGenMageTag = CreateWindowEx(
        0, "STATIC", TEXT("Mage:"), WS_CHILD,
        440, 482, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_GenMage = CreateWindowEx(
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        485, 482, 50, 170,
        hTabMassEdit, (HMENU)ID_ME_CB_GENMAGE, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenMage = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 482, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENMAGE, hThisInst, NULL);

    cb_MassEditGenSamuraiTag = CreateWindowEx(
        0, "STATIC", TEXT("Samurai:"), WS_CHILD,
        440, 507, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_GenSamurai = CreateWindowEx(
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        485, 507, 50, 170,
        hTabMassEdit, (HMENU)ID_ME_CB_GENSAMU, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenSamurai = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 507, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENSAMU, hThisInst, NULL);

    cb_MassEditGenArcherTag = CreateWindowEx(
        0, "STATIC", TEXT("Archer:"), WS_CHILD,
        440, 532, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_GenArcher = CreateWindowEx(
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        485, 532, 50, 170,
        hTabMassEdit, (HMENU)ID_ME_CB_GENARCH, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenArcher = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 532, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENARCH, hThisInst, NULL);

    cb_MassEditGenMonkTag = CreateWindowEx(
        0, "STATIC", TEXT("Monk:"), WS_CHILD,
        440, 557, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_GenMonk = CreateWindowEx(
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        485, 557, 50, 170,
        hTabMassEdit, (HMENU)ID_ME_CB_GENMONK, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenMonk = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 557, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENMONK, hThisInst, NULL);

    cb_MassEditGenHarpyTag = CreateWindowEx(
        0, "STATIC", TEXT("Harpy:"), WS_CHILD,
        440, 582, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_GenHarpy = CreateWindowEx(
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        485, 582, 50, 170,
        hTabMassEdit, (HMENU)ID_ME_CB_GENHARP, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenHarpy = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 582, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENHARP, hThisInst, NULL);

    cb_MassEditGenBeastTag = CreateWindowEx(
        0, "STATIC", TEXT("Beast:"), WS_CHILD,
        440, 607, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_GenBeast = CreateWindowEx(
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        485, 607, 50, 170,
        hTabMassEdit, (HMENU)ID_ME_CB_GENBEAST, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenBeast = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 607, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENBEAST, hThisInst, NULL);

    cb_MassEditGenDragonTag = CreateWindowEx(
        0, "STATIC", TEXT("Dragon:"), WS_CHILD,
        440, 632, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_GenDragon = CreateWindowEx(
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        485, 632, 50, 170,
        hTabMassEdit, (HMENU)ID_ME_CB_GENDRAG, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenDragon = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 632, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENDRAG, hThisInst, NULL);

    cb_MassEditGenZombieTag = CreateWindowEx(
        0, "STATIC", TEXT("Zombie:"), WS_CHILD,
        440, 657, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_GenZombie = CreateWindowEx(
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        485, 657, 50, 170,
        hTabMassEdit, (HMENU)ID_ME_CB_GENZOMB, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenZombie = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 657, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENZOMB, hThisInst, NULL);

    ME_lineDownMiddle = CreateWindowEx(                //line to split interface
        WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | BS_GROUPBOX,
        655, 124, 2, 553,
        hTabMassEdit, NULL, hThisInst, NULL);

    eb_MassEditGenWinsTag = CreateWindowEx(
        0, "STATIC", TEXT("Wins:"), WS_CHILD,
        675, 132, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenWins = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 132, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENWINS, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenWins = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 132, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENWINS, hThisInst, NULL);

    eb_MassEditGenLossTag = CreateWindowEx(
        0, "STATIC", TEXT("Losses:"), WS_CHILD,
        675, 157, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenLoss = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 157, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENLOSS, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenLoss = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 157, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENLOSS, hThisInst, NULL);

    eb_MassEditGenMeritsTag = CreateWindowEx(
        0, "STATIC", TEXT("Merits:"), WS_CHILD,
        675, 182, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenMerits = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 182, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENMERIT, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenMerits = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 182, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENMERIT, hThisInst, NULL);

    eb_MassEditGenEscapeTag = CreateWindowEx(
        0, "STATIC", TEXT("Escape:"), WS_CHILD,
        675, 207, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenEscape = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 207, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENESCAPE, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenEscape = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 207, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENESCAPE, hThisInst, NULL);

    cb_MassEditGenSpellTierTag = CreateWindowEx(
        0, "STATIC", TEXT("Spell Tier:"), WS_CHILD,
        675, 232, 47, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_GenSpellTier = CreateWindowEx(
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        755, 232, 50, 80,
        hTabMassEdit, (HMENU)ID_ME_CB_GENSPELL, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenSpellTier = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 232, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENSPELL, hThisInst, NULL);

    cb_MassEditGenItemTag = CreateWindowEx(
        0, "STATIC", TEXT("Equipped Item:"), WS_CHILD,
        675, 257, 71, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_GenItem = CreateWindowEx(
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        755, 257, 110, 500,
        hTabMassEdit, (HMENU)ID_ME_CB_GENITEM, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenItem = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 257, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENITEM, hThisInst, NULL);

    MassEditTabCtrls.xb_ME_GenNaisei = CreateWindowEx(
        0, "BUTTON", "Already did Search/Fortify this week",
        WS_CHILD | WS_TABSTOP | WS_DISABLED | BS_CHECKBOX,
        675, 282, 190, 20,
        hTabMassEdit, (HMENU)ID_ME_XB_GENNAISEI, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenNaisei = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 282, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENNAISEI, hThisInst, NULL);

    ME_WeaknessGroupBox = CreateWindowEx( //frame surrounding weaknesses
        0, "BUTTON", TEXT("Weakness Against:"), WS_CHILD | BS_GROUPBOX,
        665, 307, 257, 175, 
        hTabMassEdit, NULL, hThisInst, NULL);

    eb_MassEditGenDefTrpsTag = CreateWindowEx(
        0, "STATIC", TEXT("Troop Attacks:"), WS_CHILD,
        675, 327, 71, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenDefTrps = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 327, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENDEFTRP, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenDefTrps = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 327, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENDEFTRP, hThisInst, NULL);

    eb_MassEditGenDefSwdTag = CreateWindowEx(
        0, "STATIC", TEXT("Sword Magic:"), WS_CHILD,
        675, 352, 71, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenDefSwd = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 352, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENDEFSWD, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenDefSwd = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 352, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENDEFSWD, hThisInst, NULL);

    eb_MassEditGenDefIceTag = CreateWindowEx(
        0, "STATIC", TEXT("Ice Magic:"), WS_CHILD,
        675, 377, 71, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenDefIce = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 377, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENDEFICE, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenDefIce = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 377, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENDEFICE, hThisInst, NULL);

    eb_MassEditGenDefFireTag = CreateWindowEx(
        0, "STATIC", TEXT("Fire Magic:"), WS_CHILD,
        675, 402, 71, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenDefFire = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 402, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENDEFFRE, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenDefFire = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 402, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENDEFFRE, hThisInst, NULL);

    eb_MassEditGenDefLightTag = CreateWindowEx(
        0, "STATIC", TEXT("Light Magic:"), WS_CHILD,
        675, 427, 71, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenDefLight = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 427, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENDEFLGT, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenDefLight = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 427, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENDEFLGT, hThisInst, NULL);

    eb_MassEditGenDefDarkTag = CreateWindowEx(
        0, "STATIC", TEXT("Dark Magic:"), WS_CHILD,
        675, 452, 71, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenDefDark = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 452, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENDEFDRK, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenDefDark = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 452, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENDEFDRK, hThisInst, NULL);

    ME_UnknownsGroupBox = CreateWindowEx( //frame surrounding unknown effects
        0, "BUTTON", TEXT("Unknown Effects:"), WS_CHILD | BS_GROUPBOX,
        665, 487, 257, 200, 
        hTabMassEdit, NULL, hThisInst, NULL);

    eb_MassEditGenNAactionTag = CreateWindowEx(
        0, "STATIC", TEXT("n_action:"), WS_CHILD,
        675, 507, 71, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenNAction = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 507, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENNACT, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenNaction = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 507, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENNACT, hThisInst, NULL);

    eb_MassEditGenBActionTag = CreateWindowEx(
        0, "STATIC", TEXT("b_action:"), WS_CHILD,
        675, 532, 71, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenBAction = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 532, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENBACT, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenBAction = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 532, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENBACT, hThisInst, NULL);

    eb_MassEditGenBtlActionTag = CreateWindowEx(
        0, "STATIC", TEXT("btl_action:"), WS_CHILD,
        675, 557, 71, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenBtlAction = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 557, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENBTLACT, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenBtlAction = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 557, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENBTLACT, hThisInst, NULL);

    eb_MassEditGenWarlikeTag = CreateWindowEx(
        0, "STATIC", TEXT("warlike:"), WS_CHILD,
        675, 582, 71, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenWarlike = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 582, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENWARLK, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenWarlike = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 582, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENWARLK, hThisInst, NULL);

    eb_MassEditGenNegoTag = CreateWindowEx(
        0, "STATIC", TEXT("nego:"), WS_CHILD,
        675, 607, 71, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenNego = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 607, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENNEGO, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenNego = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 607, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENNEGO, hThisInst, NULL);

    eb_MassEditGenAtkPlusTag = CreateWindowEx(
        0, "STATIC", TEXT("atk_plus:"), WS_CHILD,
        675, 632, 71, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenAtkPlus = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 632, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENATKPLS, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenAtkPlus = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 632, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENATKPLS, hThisInst, NULL);

    eb_MassEditGenDefPlusTag = CreateWindowEx(
        0, "STATIC", TEXT("def_plus:"), WS_CHILD,
        675, 657, 71, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_GenDefPlus = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        755, 657, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_GENDEFPLS, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetGenDefPlus = CreateWindowEx(
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        867, 657, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_GENDEFPLS, hThisInst, NULL);

// *****************************************************************************
//
// END GENERALS
//
// BEGIN CASTLES
//
// *****************************************************************************

    MassEditTabCtrls.rb_MassEditCasList = CreateWindowEx( //Castles list radio button
        0, "BUTTON", TEXT("All Castles"), WS_CHILD | WS_DISABLED | BS_RADIOBUTTON,
        20, 123, 74, 15, 
        hTabMassEdit, (HMENU)ID_ME_RB_CASLIST, hThisInst, NULL); 

    MassEditTabCtrls.lb_MassEditCasList = CreateWindowEx( //All Castles listbox
        WS_EX_CLIENTEDGE, "LISTBOX", NULL, WS_VSCROLL | WS_CHILD | 
        WS_TABSTOP | WS_DISABLED | LBS_EXTENDEDSEL | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
        20, 148, 100, 450,
        hTabMassEdit, (HMENU)ID_ME_LB_CASLIST, hThisInst, NULL);

    MassEditCasSelGroupBox = CreateWindowEx( //frame surrounding Castles selection area
        0, "BUTTON", TEXT("Edit Which Castles"), WS_CHILD | BS_GROUPBOX,
        10, 98, 250, 590, 
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.rb_MassEditCasOwnerList = CreateWindowEx( //castle owner radio button
        0, "BUTTON", TEXT("Castles Owned By"), WS_CHILD | WS_DISABLED | BS_RADIOBUTTON,
        150, 123, 104, 15, 
        hTabMassEdit, (HMENU)ID_ME_RB_CASOWN_CB, hThisInst, NULL); 

    MassEditTabCtrls.cb_MassEditCasOwnerList = CreateWindowEx( //castle owner combobox
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        150, 148, 100, 210,
        hTabMassEdit, (HMENU)ID_ME_CB_CAS_OWNER, hThisInst, NULL);

    SelectedCasGroupBox = CreateWindowEx( //frame surrounding selected Castles output area
        0, "BUTTON", TEXT("Castles affected"), WS_CHILD | BS_GROUPBOX,
        280, 98, 140, 590,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_selectedCas = CreateWindowEx( //Selected Castles non-editable editbox
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_VSCROLL | WS_CHILD |
        ES_READONLY | WS_TABSTOP | WS_DISABLED | ES_MULTILINE,
        300, 123, 100, 550,
        hTabMassEdit, (HMENU)ID_ME_EB_SEL_CAS, hThisInst, NULL);

    cb_MassEditCasOwnerTag = CreateWindowEx( //castle owner text tag
        0, "STATIC", TEXT("Ruler:"), WS_CHILD,
        440, 132, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_CasOwnerList = CreateWindowEx( //castle owner name list combobox
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        485, 132, 100, 500,
        hTabMassEdit, (HMENU)ID_ME_CB_CASOWNER, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetCasOwner = CreateWindowEx(   //castle owner set button
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 132, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_CASOWNER, hThisInst, NULL);

    cb_MassEditCasLevelTag = CreateWindowEx( //castle level text tag
        0, "STATIC", TEXT("Level:"), WS_CHILD,
        440, 157, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.cb_ME_CasLevel = CreateWindowEx( //castle level combobox
        0, "COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP | WS_DISABLED,
        485, 157, 100, 500,
        hTabMassEdit, (HMENU)ID_ME_CB_CASLEVEL, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetCasLevel = CreateWindowEx(   //castle set button
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 157, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_CASLEVEL, hThisInst, NULL);

    eb_MassEditCasTrpCntTag = CreateWindowEx( //castle troop count text tag
        0, "STATIC", TEXT("Troops:"), WS_CHILD,
        440, 182, 43, 15,
        hTabMassEdit, NULL, hThisInst, NULL);

    MassEditTabCtrls.eb_ME_CasTrpCnt = CreateWindowEx( //castle troop count edit box
        WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_TABSTOP | ES_NUMBER,
        485, 182, 50, 20,
        hTabMassEdit, (HMENU)ID_ME_EB_CASTROOPS, hThisInst, NULL);

    MassEditTabCtrls.but_ME_SetCasTrpCnt = CreateWindowEx(   //castle troop count set button
        0, "BUTTON", TEXT("Set"), WS_CHILD | WS_TABSTOP | WS_DISABLED,
        585, 182, 40, 20,
        hTabMassEdit, (HMENU)ID_ME_SET_CASTROOPS, hThisInst, NULL);

    SetDefaultFont(hTabMassEdit);

    SetDefaultFont(MassEditTypeGroupBox);
    SetDefaultFont(rb_MassEditGenTag);
    SetDefaultFont(rb_MassEditCasTag);
//    SetDefaultFont(rb_MassEditDivTag);

    SetDefaultFont(MassEditGenSelGroupBox);
    SetDefaultFont(MassEditTabCtrls.rb_MassEditGenList);
    SetDefaultFont(MassEditTabCtrls.lb_MassEditGenList);
    SetDefaultFont(MassEditTabCtrls.rb_MassEditClassList);
    SetDefaultFont(MassEditTabCtrls.cb_MassEditClassList);
    SetDefaultFont(MassEditTabCtrls.ckbox_MonarchsWithClass);

    SetDefaultFont(SelectedGensGroupBox);
    SetDefaultFont(MassEditTabCtrls.eb_selectedGens);

    SetDefaultFont(MassEditGenStatsGroupBox);
    SetDefaultFont(MassEditTabCtrls.rb_MassEditGenByValue);
    SetDefaultFont(MassEditTabCtrls.rb_MassEditGenByPercent);
    SetDefaultFont(MassEditTabCtrls.rb_MassEditGenOfCurrent);
    SetDefaultFont(MassEditTabCtrls.rb_MassEditGenOfMax);

    SetDefaultFont(cb_MassEditGenOwnerTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_GenOwnerList);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenOwner);
    SetDefaultFont(eb_MassEditGenLevelTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenLevel);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenLevel);
    SetDefaultFont(eb_MassEditGenExpTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenExp);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenExp);
    SetDefaultFont(eb_MassEditGenHpTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenHP);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenHP);
    SetDefaultFont(eb_MassEditGenMpTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenMP);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenMP);
    SetDefaultFont(eb_MassEditGenStrTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenStr);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenStr);
    SetDefaultFont(eb_MassEditGenComTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenCom);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenCom);
    SetDefaultFont(eb_MassEditGenIntTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenInt);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenInt);
    SetDefaultFont(eb_MassEditGenLivesTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenLives);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenLives);
    SetDefaultFont(eb_MassEditGenLoyaltyTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenLoyalty);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenLoyalty);
    SetDefaultFont(cb_MassEditGenTrpTypeTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_GenTroopType);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenTroopType);
    SetDefaultFont(eb_MassEditGenTrpCntTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenTroopCnt);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenTrpCnt);
    SetDefaultFont(cb_MassEditGenSoldierTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_GenSoldier);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenSoldier);
    SetDefaultFont(cb_MassEditGenCavalryTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_GenCavalry);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenCavalry);
    SetDefaultFont(cb_MassEditGenMageTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_GenMage);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenMage);
    SetDefaultFont(cb_MassEditGenSamuraiTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_GenSamurai);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenSamurai);
    SetDefaultFont(cb_MassEditGenArcherTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_GenArcher);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenArcher);
    SetDefaultFont(cb_MassEditGenMonkTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_GenMonk);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenMonk);
    SetDefaultFont(cb_MassEditGenHarpyTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_GenHarpy);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenHarpy);
    SetDefaultFont(cb_MassEditGenBeastTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_GenBeast);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenBeast);
    SetDefaultFont(cb_MassEditGenDragonTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_GenDragon);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenDragon);
    SetDefaultFont(cb_MassEditGenZombieTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_GenZombie);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenZombie);

    SetDefaultFont(eb_MassEditGenWinsTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenWins);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenWins);
    SetDefaultFont(eb_MassEditGenLossTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenLoss);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenLoss);
    SetDefaultFont(eb_MassEditGenMeritsTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenMerits);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenMerits);
    SetDefaultFont(eb_MassEditGenEscapeTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenEscape);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenEscape);
    SetDefaultFont(cb_MassEditGenSpellTierTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_GenSpellTier);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenSpellTier);
    SetDefaultFont(cb_MassEditGenItemTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_GenItem);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenItem);
    SetDefaultFont(MassEditTabCtrls.xb_ME_GenNaisei);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenNaisei);
    SetDefaultFont(eb_MassEditGenDefTrpsTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenDefTrps);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenDefTrps);
    SetDefaultFont(eb_MassEditGenDefSwdTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenDefSwd);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenDefSwd);
    SetDefaultFont(eb_MassEditGenDefIceTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenDefIce);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenDefIce);
    SetDefaultFont(eb_MassEditGenDefFireTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenDefFire);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenDefFire);
    SetDefaultFont(eb_MassEditGenDefLightTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenDefLight);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenDefLight);
    SetDefaultFont(eb_MassEditGenDefDarkTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenDefDark);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenDefDark);
    SetDefaultFont(eb_MassEditGenNAactionTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenNAction);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenNaction);
    SetDefaultFont(eb_MassEditGenBActionTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenBAction);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenBAction);
    SetDefaultFont(eb_MassEditGenBtlActionTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenBtlAction);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenBtlAction);
    SetDefaultFont(eb_MassEditGenWarlikeTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenWarlike);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenWarlike);
    SetDefaultFont(eb_MassEditGenNegoTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenNego);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenNego);
    SetDefaultFont(eb_MassEditGenAtkPlusTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenAtkPlus);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenAtkPlus);
    SetDefaultFont(eb_MassEditGenDefPlusTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_GenDefPlus);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetGenDefPlus);
    
    SetDefaultFont(ME_WeaknessGroupBox);
    SetDefaultFont(ME_UnknownsGroupBox);

    SetDefaultFont(MassEditCasSelGroupBox);
    SetDefaultFont(MassEditTabCtrls.rb_MassEditCasList);
    SetDefaultFont(MassEditTabCtrls.lb_MassEditCasList);
    SetDefaultFont(MassEditTabCtrls.rb_MassEditCasOwnerList);
    SetDefaultFont(MassEditTabCtrls.cb_MassEditCasOwnerList);
    SetDefaultFont(SelectedCasGroupBox);
    SetDefaultFont(MassEditTabCtrls.eb_selectedCas);
    SetDefaultFont(cb_MassEditCasOwnerTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_CasOwnerList);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetCasOwner);
    SetDefaultFont(cb_MassEditCasLevelTag);
    SetDefaultFont(MassEditTabCtrls.cb_ME_CasLevel);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetCasLevel);
    SetDefaultFont(eb_MassEditCasTrpCntTag);
    SetDefaultFont(MassEditTabCtrls.eb_ME_CasTrpCnt);
    SetDefaultFont(MassEditTabCtrls.but_ME_SetCasTrpCnt);

    return;
}

void PopulateMassEditTab(void)
{
    char itoaArr[5] = {'\0'};

    stringstream ss;

    ShowWindow(MassEditTabCtrls.rb_MassEditGen, TRUE); //show radio button to select generals
    ShowWindow(MassEditTabCtrls.rb_MassEditCas, TRUE); //show radio button to select castles
    //ShowWindow(MassEditTabCtrls.rb_MassEditDiv, TRUE); //show radio button to select divisions

    EnableWindow(MassEditTabCtrls.rb_MassEditGen, TRUE); //turn on radio button to select generals
    EnableWindow(MassEditTabCtrls.rb_MassEditCas, TRUE); //turn on radio button to select castles
    //EnableWindow(MassEditTabCtrls.rb_MassEditDiv, TRUE); //turn on radio button to select divisions

    EnableWindow(MassEditGenStatsGroupBox, TRUE);
    EnableWindow(MassEditTabCtrls.rb_MassEditGenByValue, TRUE);
    EnableWindow(MassEditTabCtrls.rb_MassEditGenByPercent, TRUE);
    EnableWindow(MassEditTabCtrls.rb_MassEditGenOfCurrent, TRUE);
    EnableWindow(MassEditTabCtrls.rb_MassEditGenOfMax, TRUE);

    if(!alreadyOpened)
    {
        for(int i = 0; i < 171; i++)
        {
            SendMessage(MassEditTabCtrls.lb_MassEditGenList, LB_ADDSTRING, 0, LPARAM(generalsNameList[i]));
            SendMessage(MassEditTabCtrls.cb_ME_GenOwnerList, CB_ADDSTRING, 0, LPARAM(generalsNameList[i]));
            SendMessage(MassEditTabCtrls.cb_ME_CasOwnerList, CB_ADDSTRING, 0, LPARAM(generalsNameList[i]));
        }
        SendMessage(MassEditTabCtrls.cb_ME_GenOwnerList, CB_SETCURSEL, 0, 0);
        SendMessage(MassEditTabCtrls.cb_ME_CasOwnerList, CB_SETCURSEL, 0, 0);

        for(int i = 1; i < 15; i++)
            SendMessage(MassEditTabCtrls.cb_MassEditClassList, CB_ADDSTRING, 0, LPARAM(classType[i]));
        SendMessage(MassEditTabCtrls.cb_MassEditClassList, CB_SETCURSEL, 0, 0);

        for(int i = 0; i < 11; i++)
        {
            SendMessage(MassEditTabCtrls.cb_ME_GenTroopType, CB_ADDSTRING, 0, LPARAM(troopType[i]));
            SendMessage(MassEditTabCtrls.cb_ME_GenSoldier, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
            SendMessage(MassEditTabCtrls.cb_ME_GenCavalry, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
            SendMessage(MassEditTabCtrls.cb_ME_GenMage, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
            SendMessage(MassEditTabCtrls.cb_ME_GenSamurai, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
            SendMessage(MassEditTabCtrls.cb_ME_GenArcher, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
            SendMessage(MassEditTabCtrls.cb_ME_GenMonk, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
            SendMessage(MassEditTabCtrls.cb_ME_GenHarpy, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
            SendMessage(MassEditTabCtrls.cb_ME_GenBeast, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
            SendMessage(MassEditTabCtrls.cb_ME_GenDragon, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
            SendMessage(MassEditTabCtrls.cb_ME_GenZombie, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
        }
        SendMessage(MassEditTabCtrls.cb_ME_GenTroopType, CB_SETCURSEL, 0, 0);
        SendMessage(MassEditTabCtrls.cb_ME_GenSoldier, CB_SETCURSEL, 0, 0);
        SendMessage(MassEditTabCtrls.cb_ME_GenCavalry, CB_SETCURSEL, 0, 0);
        SendMessage(MassEditTabCtrls.cb_ME_GenMage, CB_SETCURSEL, 0, 0);
        SendMessage(MassEditTabCtrls.cb_ME_GenSamurai, CB_SETCURSEL, 0, 0);
        SendMessage(MassEditTabCtrls.cb_ME_GenArcher, CB_SETCURSEL, 0, 0);
        SendMessage(MassEditTabCtrls.cb_ME_GenMonk, CB_SETCURSEL, 0, 0);
        SendMessage(MassEditTabCtrls.cb_ME_GenHarpy, CB_SETCURSEL, 0, 0);
        SendMessage(MassEditTabCtrls.cb_ME_GenBeast, CB_SETCURSEL, 0, 0);
        SendMessage(MassEditTabCtrls.cb_ME_GenDragon, CB_SETCURSEL, 0, 0);
        SendMessage(MassEditTabCtrls.cb_ME_GenZombie, CB_SETCURSEL, 0, 0);

        SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_VAL, BM_SETCHECK, 1, 0);

        for(int i = 0; i < 48; i++) //setting up Generals item combobox
            SendMessage(MassEditTabCtrls.cb_ME_GenItem, CB_ADDSTRING, 0, LPARAM(itemList[i]));
        SendMessage(MassEditTabCtrls.cb_ME_GenItem, CB_SETCURSEL, 0, 0);

        for(int i = 0; i < 4; i++) //setting up Generals spell tier combobox
            SendMessage(MassEditTabCtrls.cb_ME_GenSpellTier, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
        SendMessage(MassEditTabCtrls.cb_ME_GenSpellTier, CB_SETCURSEL, 0, 0);

        for(int i = 0; i < 34; i++)
            SendMessage(MassEditTabCtrls.lb_MassEditCasList, LB_ADDSTRING, 0, LPARAM(castlesNameList[i]));

        for(int i = 1; i < 51; i++) //setting up castle levels combobox
            SendMessage(MassEditTabCtrls.cb_ME_CasLevel, CB_ADDSTRING, 0, LPARAM(itoa(i, itoaArr, 10)));
        SendMessage(MassEditTabCtrls.cb_ME_CasLevel, CB_SETCURSEL, 0, 0);
    }
/* commented out because not needed when opening first file after program start, but may be useful later
    for(int i = 0; i < 34; i++)
        castleOwners[i] = -1;
    castleOwnerCount = 0;
*/
    PopulateCastleOwners();
    if(SendMessage(MassEditTabCtrls.rb_MassEditCasOwnerList, BM_GETCHECK, 0, 0) == BST_CHECKED)
        MassEditShowCasByOwner();
    if(SendMessage(MassEditTabCtrls.rb_MassEditCasList, BM_GETCHECK, 0, 0) == BST_CHECKED)
    {
        SendMessage(MassEditTabCtrls.eb_selectedCas, WM_SETTEXT, 0, LPARAM(""));
        SendMessage(MassEditTabCtrls.lb_MassEditCasList, LB_SETSEL, FALSE, -1); //clears all selections from a listbox
    }
    
    return;
}

void MassEditShowGenerals(const bool show)
{
    if(show)
    {
        ShowWindow(MassEditGenSelGroupBox, TRUE);
        ShowWindow(SelectedGensGroupBox, TRUE);
        ShowWindow(MassEditTabCtrls.rb_MassEditGenList, TRUE); //show radio button for Generals list
        ShowWindow(MassEditTabCtrls.lb_MassEditGenList, TRUE); //show listbox for Generals list
        ShowWindow(MassEditTabCtrls.rb_MassEditClassList, TRUE); //show radio button for class list
        ShowWindow(MassEditTabCtrls.cb_MassEditClassList, TRUE); //show combobox for class list
        ShowWindow(MassEditTabCtrls.ckbox_MonarchsWithClass, TRUE); //show checkbox for including monarchs with class
        ShowWindow(MassEditTabCtrls.eb_selectedGens, TRUE); //show selected Generals listbox
        ShowWindow(cb_MassEditGenOwnerTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenOwnerList, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenOwner, TRUE);
        ShowWindow(eb_MassEditGenLevelTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenLevel, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenLevel, TRUE);
        ShowWindow(eb_MassEditGenExpTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenExp, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenExp, TRUE);
        ShowWindow(eb_MassEditGenHpTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenHP, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenHP, TRUE);
        ShowWindow(eb_MassEditGenMpTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenMP, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenMP, TRUE);
        ShowWindow(eb_MassEditGenStrTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenStr, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenStr, TRUE);
        ShowWindow(eb_MassEditGenComTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenCom, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenCom, TRUE);
        ShowWindow(eb_MassEditGenIntTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenInt, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenInt, TRUE);
        ShowWindow(eb_MassEditGenLivesTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenLives, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenLives, TRUE);
        ShowWindow(eb_MassEditGenLoyaltyTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenLoyalty, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenLoyalty, TRUE);
        ShowWindow(cb_MassEditGenTrpTypeTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenTroopType, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenTroopType, TRUE);
        ShowWindow(eb_MassEditGenTrpCntTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenTroopCnt, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenTrpCnt, TRUE);
        ShowWindow(cb_MassEditGenSoldierTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenSoldier, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenSoldier, TRUE);
        ShowWindow(cb_MassEditGenCavalryTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenCavalry, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenCavalry, TRUE);
        ShowWindow(cb_MassEditGenMageTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenMage, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenMage, TRUE);
        ShowWindow(cb_MassEditGenSamuraiTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenSamurai, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenSamurai, TRUE);
        ShowWindow(cb_MassEditGenArcherTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenArcher, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenArcher, TRUE);
        ShowWindow(cb_MassEditGenMonkTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenMonk, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenMonk, TRUE);
        ShowWindow(cb_MassEditGenHarpyTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenHarpy, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenHarpy, TRUE);
        ShowWindow(cb_MassEditGenBeastTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenBeast, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenBeast, TRUE);
        ShowWindow(cb_MassEditGenDragonTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenDragon, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDragon, TRUE);
        ShowWindow(cb_MassEditGenZombieTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenZombie, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenZombie, TRUE);
        ShowWindow(ME_lineDownMiddle, TRUE);                  //line down middle
        ShowWindow(eb_MassEditGenWinsTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenWins, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenWins, TRUE);
        ShowWindow(eb_MassEditGenLossTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenLoss, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenLoss, TRUE);
        ShowWindow(eb_MassEditGenMeritsTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenMerits, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenMerits, TRUE);
        ShowWindow(eb_MassEditGenEscapeTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenEscape, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenEscape, TRUE);
        ShowWindow(cb_MassEditGenSpellTierTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenSpellTier, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenSpellTier, TRUE);
        ShowWindow(cb_MassEditGenItemTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenItem, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenItem, TRUE);
        ShowWindow(MassEditTabCtrls.xb_ME_GenNaisei, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenNaisei, TRUE);
        ShowWindow(ME_WeaknessGroupBox, TRUE);             //weaknesses groupbox
        ShowWindow(eb_MassEditGenDefTrpsTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenDefTrps, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDefTrps, TRUE);
        ShowWindow(eb_MassEditGenDefSwdTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenDefSwd, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDefSwd, TRUE);
        ShowWindow(eb_MassEditGenDefIceTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenDefIce, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDefIce, TRUE);
        ShowWindow(eb_MassEditGenDefFireTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenDefFire, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDefFire, TRUE);
        ShowWindow(eb_MassEditGenDefLightTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenDefLight, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDefLight, TRUE);
        ShowWindow(eb_MassEditGenDefDarkTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenDefDark, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDefDark, TRUE);
        ShowWindow(ME_UnknownsGroupBox, TRUE);             //unknowns groupbox
        ShowWindow(eb_MassEditGenNAactionTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenNAction, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenNaction, TRUE);
        ShowWindow(eb_MassEditGenBActionTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenBAction, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenBAction, TRUE);
        ShowWindow(eb_MassEditGenBtlActionTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenBtlAction, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenBtlAction, TRUE);
        ShowWindow(eb_MassEditGenWarlikeTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenWarlike, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenWarlike, TRUE);
        ShowWindow(eb_MassEditGenNegoTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenNego, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenNego, TRUE);
        ShowWindow(eb_MassEditGenAtkPlusTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenAtkPlus, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenAtkPlus, TRUE);
        ShowWindow(eb_MassEditGenDefPlusTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenDefPlus, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDefPlus, TRUE);

        EnableWindow(MassEditGenSelGroupBox, TRUE);
        EnableWindow(SelectedGensGroupBox, TRUE);
        EnableWindow(MassEditTabCtrls.rb_MassEditGenList, TRUE); //turn on radio button for Generals list
        EnableWindow(MassEditTabCtrls.lb_MassEditGenList, TRUE); //turn on listbox for Generals list
        EnableWindow(MassEditTabCtrls.rb_MassEditClassList, TRUE); //turn on radio button for class list
        EnableWindow(MassEditTabCtrls.eb_selectedGens, TRUE); //turn on non-editable Affected Generals editbox
        EnableWindow(cb_MassEditGenOwnerTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenOwnerList, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenOwner, TRUE);
        EnableWindow(eb_MassEditGenLevelTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenLevel, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenLevel, TRUE);
        EnableWindow(eb_MassEditGenExpTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenExp, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenExp, TRUE);
        EnableWindow(eb_MassEditGenHpTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenHP, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenHP, TRUE);
        EnableWindow(eb_MassEditGenMpTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenMP, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenMP, TRUE);
        EnableWindow(eb_MassEditGenStrTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenStr, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenStr, TRUE);
        EnableWindow(eb_MassEditGenComTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenCom, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenCom, TRUE);
        EnableWindow(eb_MassEditGenIntTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenInt, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenInt, TRUE);
        EnableWindow(eb_MassEditGenLivesTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenLives, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenLives, TRUE);
        EnableWindow(eb_MassEditGenLoyaltyTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenLoyalty, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenLoyalty, TRUE);
        EnableWindow(cb_MassEditGenTrpTypeTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenTroopType, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenTroopType, TRUE);
        EnableWindow(eb_MassEditGenTrpCntTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenTroopCnt, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenTrpCnt, TRUE);
        EnableWindow(cb_MassEditGenSoldierTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenSoldier, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenSoldier, TRUE);
        EnableWindow(cb_MassEditGenCavalryTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenCavalry, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenCavalry, TRUE);
        EnableWindow(cb_MassEditGenMageTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenMage, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenMage, TRUE);
        EnableWindow(cb_MassEditGenSamuraiTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenSamurai, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenSamurai, TRUE);
        EnableWindow(cb_MassEditGenArcherTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenArcher, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenArcher, TRUE);
        EnableWindow(cb_MassEditGenMonkTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenMonk, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenMonk, TRUE);
        EnableWindow(cb_MassEditGenHarpyTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenHarpy, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenHarpy, TRUE);
        EnableWindow(cb_MassEditGenBeastTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenBeast, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenBeast, TRUE);
        EnableWindow(cb_MassEditGenDragonTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenDragon, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDragon, TRUE);
        EnableWindow(cb_MassEditGenZombieTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenZombie, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenZombie, TRUE);
        EnableWindow(ME_lineDownMiddle, TRUE);                //line down middle
        EnableWindow(eb_MassEditGenWinsTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenWins, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenWins, TRUE);
        EnableWindow(eb_MassEditGenLossTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenLoss, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenLoss, TRUE);
        EnableWindow(eb_MassEditGenMeritsTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenMerits, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenMerits, TRUE);
        EnableWindow(eb_MassEditGenEscapeTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenEscape, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenEscape, TRUE);
        EnableWindow(cb_MassEditGenSpellTierTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenSpellTier, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenSpellTier, TRUE);
        EnableWindow(cb_MassEditGenItemTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenItem, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenItem, TRUE);
        EnableWindow(MassEditTabCtrls.xb_ME_GenNaisei, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenNaisei, TRUE);
        EnableWindow(ME_WeaknessGroupBox, TRUE);           //weaknesses groupbox
        EnableWindow(eb_MassEditGenDefTrpsTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenDefTrps, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDefTrps, TRUE);
        EnableWindow(eb_MassEditGenDefSwdTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenDefSwd, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDefSwd, TRUE);
        EnableWindow(eb_MassEditGenDefIceTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenDefIce, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDefIce, TRUE);
        EnableWindow(eb_MassEditGenDefFireTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenDefFire, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDefFire, TRUE);
        EnableWindow(eb_MassEditGenDefLightTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenDefLight, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDefLight, TRUE);
        EnableWindow(eb_MassEditGenDefDarkTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenDefDark, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDefDark, TRUE);
        EnableWindow(ME_UnknownsGroupBox, TRUE);             //unknowns groupbox
        EnableWindow(eb_MassEditGenNAactionTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenNAction, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenNaction, TRUE);
        EnableWindow(eb_MassEditGenBActionTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenBAction, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenBAction, TRUE);
        EnableWindow(eb_MassEditGenBtlActionTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenBtlAction, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenBtlAction, TRUE);
        EnableWindow(eb_MassEditGenWarlikeTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenWarlike, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenWarlike, TRUE);
        EnableWindow(eb_MassEditGenNegoTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenNego, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenNego, TRUE);
        EnableWindow(eb_MassEditGenAtkPlusTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenAtkPlus, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenAtkPlus, TRUE);
        EnableWindow(eb_MassEditGenDefPlusTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenDefPlus, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDefPlus, TRUE);

        SendDlgItemMessage(hTabMassEdit, ID_RB_ME_GEN, BM_SETCHECK, 1, 0);
        SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GENLIST, BM_SETCHECK, 1, 0);
        SendDlgItemMessage(hTabMassEdit, ID_ME_RB_CLASS_CB, BM_SETCHECK, 0, 0);
        EnableWindow(MassEditTabCtrls.cb_MassEditClassList, FALSE); //turn off combobox for class list
        EnableWindow(MassEditTabCtrls.ckbox_MonarchsWithClass, FALSE); //turn off checkbox for including monarchs with class

        EnableWindow(MassEditGenStatsGroupBox, TRUE);
    }
    else
    {
        ShowWindow(MassEditGenSelGroupBox, FALSE);
        ShowWindow(SelectedGensGroupBox, FALSE);
        ShowWindow(MassEditTabCtrls.rb_MassEditGenList, FALSE); //hide radio button for Generals list
        ShowWindow(MassEditTabCtrls.lb_MassEditGenList, FALSE); //hide listbox for Generals list
        ShowWindow(MassEditTabCtrls.rb_MassEditClassList, FALSE); //hide radio button for class list
        ShowWindow(MassEditTabCtrls.cb_MassEditClassList, FALSE); //hide combobox for class list
        ShowWindow(MassEditTabCtrls.ckbox_MonarchsWithClass, FALSE); //hide checkbox for including monarchs with class
        ShowWindow(MassEditTabCtrls.eb_selectedGens, FALSE); //hide selected Generals listbox
        ShowWindow(cb_MassEditGenOwnerTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenOwnerList, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenOwner, FALSE);
        ShowWindow(eb_MassEditGenLevelTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenLevel, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenLevel, FALSE);
        ShowWindow(eb_MassEditGenExpTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenExp, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenExp, FALSE);
        ShowWindow(eb_MassEditGenHpTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenHP, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenHP, FALSE);
        ShowWindow(eb_MassEditGenMpTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenMP, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenMP, FALSE);
        ShowWindow(eb_MassEditGenStrTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenStr, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenStr, FALSE);
        ShowWindow(eb_MassEditGenComTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenCom, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenCom, FALSE);
        ShowWindow(eb_MassEditGenIntTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenInt, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenInt, FALSE);
        ShowWindow(eb_MassEditGenLivesTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenLives, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenLives, FALSE);
        ShowWindow(eb_MassEditGenLoyaltyTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenLoyalty, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenLoyalty, FALSE);
        ShowWindow(cb_MassEditGenTrpTypeTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenTroopType, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenTroopType, FALSE);
        ShowWindow(eb_MassEditGenTrpCntTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenTroopCnt, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenTrpCnt, FALSE);
        ShowWindow(cb_MassEditGenSoldierTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenSoldier, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenSoldier, FALSE);
        ShowWindow(cb_MassEditGenCavalryTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenCavalry, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenCavalry, FALSE);
        ShowWindow(cb_MassEditGenMageTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenMage, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenMage, FALSE);
        ShowWindow(cb_MassEditGenSamuraiTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenSamurai, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenSamurai, FALSE);
        ShowWindow(cb_MassEditGenArcherTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenArcher, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenArcher, FALSE);
        ShowWindow(cb_MassEditGenMonkTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenMonk, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenMonk, FALSE);
        ShowWindow(cb_MassEditGenHarpyTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenHarpy, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenHarpy, FALSE);
        ShowWindow(cb_MassEditGenBeastTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenBeast, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenBeast, FALSE);
        ShowWindow(cb_MassEditGenDragonTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenDragon, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDragon, FALSE);
        ShowWindow(cb_MassEditGenZombieTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenZombie, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenZombie, FALSE);
        ShowWindow(ME_lineDownMiddle, FALSE);                 //line down middle
        ShowWindow(eb_MassEditGenWinsTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenWins, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenWins, FALSE);
        ShowWindow(eb_MassEditGenLossTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenLoss, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenLoss, FALSE);
        ShowWindow(eb_MassEditGenMeritsTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenMerits, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenMerits, FALSE);
        ShowWindow(eb_MassEditGenEscapeTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenEscape, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenEscape, FALSE);
        ShowWindow(cb_MassEditGenSpellTierTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenSpellTier, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenSpellTier, FALSE);
        ShowWindow(cb_MassEditGenItemTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_GenItem, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenItem, FALSE);
        ShowWindow(MassEditTabCtrls.xb_ME_GenNaisei, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenNaisei, FALSE);
        ShowWindow(ME_WeaknessGroupBox, FALSE);           //weaknesses groupbox
        ShowWindow(eb_MassEditGenDefTrpsTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenDefTrps, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDefTrps, FALSE);
        ShowWindow(eb_MassEditGenDefSwdTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenDefSwd, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDefSwd, FALSE);
        ShowWindow(eb_MassEditGenDefIceTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenDefIce, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDefIce, FALSE);
        ShowWindow(eb_MassEditGenDefFireTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenDefFire, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDefFire, FALSE);
        ShowWindow(eb_MassEditGenDefLightTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenDefLight, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDefLight, FALSE);
        ShowWindow(eb_MassEditGenDefDarkTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenDefDark, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDefDark, FALSE);
        ShowWindow(ME_UnknownsGroupBox, FALSE);             //unknowns groupbox
        ShowWindow(eb_MassEditGenNAactionTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenNAction, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenNaction, FALSE);
        ShowWindow(eb_MassEditGenBActionTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenBAction, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenBAction, FALSE);
        ShowWindow(eb_MassEditGenBtlActionTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenBtlAction, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenBtlAction, FALSE);
        ShowWindow(eb_MassEditGenWarlikeTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenWarlike, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenWarlike, FALSE);
        ShowWindow(eb_MassEditGenNegoTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenNego, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenNego, FALSE);
        ShowWindow(eb_MassEditGenAtkPlusTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenAtkPlus, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenAtkPlus, FALSE);
        ShowWindow(eb_MassEditGenDefPlusTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_GenDefPlus, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetGenDefPlus, FALSE);

        EnableWindow(MassEditGenSelGroupBox, FALSE);
        EnableWindow(SelectedGensGroupBox, FALSE);
        EnableWindow(MassEditTabCtrls.rb_MassEditGenList, FALSE); //turn off radio button for Generals list
        EnableWindow(MassEditTabCtrls.lb_MassEditGenList, FALSE); //turn off listbox for Generals list
        EnableWindow(MassEditTabCtrls.rb_MassEditClassList, FALSE); //turn off radio button for class list
        EnableWindow(MassEditTabCtrls.cb_MassEditClassList, FALSE); //turn off combobox for class list
        EnableWindow(MassEditTabCtrls.ckbox_MonarchsWithClass, FALSE); //turn off checkbox for including monarchs with class
        EnableWindow(MassEditTabCtrls.eb_selectedGens, FALSE); //turn off selected Generals listbox
        EnableWindow(MassEditTabCtrls.eb_selectedGens, FALSE); //turn off non-editable Affected Generals editbox
        EnableWindow(cb_MassEditGenOwnerTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenOwnerList, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenOwner, FALSE);
        EnableWindow(eb_MassEditGenLevelTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenLevel, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenLevel, FALSE);
        EnableWindow(eb_MassEditGenExpTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenExp, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenExp, FALSE);
        EnableWindow(eb_MassEditGenHpTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenHP, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenHP, FALSE);
        EnableWindow(eb_MassEditGenMpTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenMP, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenMP, FALSE);
        EnableWindow(eb_MassEditGenStrTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenStr, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenStr, FALSE);
        EnableWindow(eb_MassEditGenComTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenCom, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenCom, FALSE);
        EnableWindow(eb_MassEditGenIntTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenInt, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenInt, FALSE);
        EnableWindow(eb_MassEditGenLivesTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenLives, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenLives, FALSE);
        EnableWindow(eb_MassEditGenLoyaltyTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenLoyalty, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenLoyalty, FALSE);
        EnableWindow(cb_MassEditGenTrpTypeTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenTroopType, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenTroopType, FALSE);
        EnableWindow(eb_MassEditGenTrpCntTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenTroopCnt, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenTrpCnt, FALSE);
        EnableWindow(cb_MassEditGenSoldierTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenSoldier, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenSoldier, FALSE);
        EnableWindow(cb_MassEditGenCavalryTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenCavalry, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenCavalry, FALSE);
        EnableWindow(cb_MassEditGenMageTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenMage, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenMage, FALSE);
        EnableWindow(cb_MassEditGenSamuraiTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenSamurai, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenSamurai, FALSE);
        EnableWindow(cb_MassEditGenArcherTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenArcher, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenArcher, FALSE);
        EnableWindow(cb_MassEditGenMonkTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenMonk, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenMonk, FALSE);
        EnableWindow(cb_MassEditGenHarpyTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenHarpy, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenHarpy, FALSE);
        EnableWindow(cb_MassEditGenBeastTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenBeast, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenBeast, FALSE);
        EnableWindow(cb_MassEditGenDragonTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenDragon, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDragon, FALSE);
        EnableWindow(cb_MassEditGenZombieTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenZombie, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenZombie, FALSE);
        EnableWindow(ME_lineDownMiddle, FALSE);               //line down middle
        EnableWindow(eb_MassEditGenWinsTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenWins, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenWins, FALSE);
        EnableWindow(eb_MassEditGenLossTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenLoss, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenLoss, FALSE);
        EnableWindow(eb_MassEditGenMeritsTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenMerits, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenMerits, FALSE);
        EnableWindow(eb_MassEditGenEscapeTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenEscape, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenEscape, FALSE);
        EnableWindow(cb_MassEditGenSpellTierTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenSpellTier, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenSpellTier, FALSE);
        EnableWindow(cb_MassEditGenItemTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_GenItem, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenItem, FALSE);
        EnableWindow(MassEditTabCtrls.xb_ME_GenNaisei, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenNaisei, FALSE);
        EnableWindow(ME_WeaknessGroupBox, FALSE);          //weaknesses groupbox
        EnableWindow(eb_MassEditGenDefTrpsTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenDefTrps, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDefTrps, FALSE);
        EnableWindow(eb_MassEditGenDefSwdTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenDefSwd, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDefSwd, FALSE);
        EnableWindow(eb_MassEditGenDefIceTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenDefIce, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDefIce, FALSE);
        EnableWindow(eb_MassEditGenDefFireTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenDefFire, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDefFire, FALSE);
        EnableWindow(eb_MassEditGenDefLightTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenDefLight, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDefLight, FALSE);
        EnableWindow(eb_MassEditGenDefDarkTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenDefDark, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDefDark, FALSE);
        EnableWindow(ME_UnknownsGroupBox, FALSE);             //unknowns groupbox
        EnableWindow(eb_MassEditGenNAactionTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenNAction, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenNaction, FALSE);
        EnableWindow(eb_MassEditGenBActionTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenBAction, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenBAction, FALSE);
        EnableWindow(eb_MassEditGenBtlActionTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenBtlAction, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenBtlAction, FALSE);
        EnableWindow(eb_MassEditGenWarlikeTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenWarlike, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenWarlike, FALSE);
        EnableWindow(eb_MassEditGenNegoTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenNego, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenNego, FALSE);
        EnableWindow(eb_MassEditGenAtkPlusTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenAtkPlus, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenAtkPlus, FALSE);
        EnableWindow(eb_MassEditGenDefPlusTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_GenDefPlus, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetGenDefPlus, FALSE);

        SendDlgItemMessage(hTabMassEdit, ID_RB_ME_GEN, BM_SETCHECK, 0, 0);
        SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GENLIST, BM_SETCHECK, 0, 0);
    }

    return;
}

void MassEditShowGenByClass(void)
{
    int i        = 0;
    int genClass = -1;

    EnableWindow(MassEditTabCtrls.ckbox_MonarchsWithClass, TRUE);
    EnableWindow(MassEditTabCtrls.cb_MassEditClassList, TRUE);
    EnableWindow(MassEditTabCtrls.lb_MassEditGenList, FALSE); //turn off listbox for Generals list

    if(SendMessage(MassEditTabCtrls.rb_MassEditClassList, BM_GETCHECK, 0, 0) == BST_CHECKED)
    {
        genClass = SendMessage(MassEditTabCtrls.cb_MassEditClassList, CB_GETCURSEL, 0, 0);
        genClass++; //because we didn't include "none" in the combobox, so need to add one

        if(SendMessage(MassEditTabCtrls.ckbox_MonarchsWithClass, BM_GETCHECK, 0, 0) == BST_CHECKED)
            i = 0;
        else
            i = 8;
        MassEditUpdateGensAffected(genClass, i);
    }

    return;
}

void MassEditUpdateGensAffected(const int genClass, const int start)
{
    int i = start;
    stringstream ss;

    for(; i < 171; i++)
        if(dr.genArr[i].classType == genClass)
            ss << generalsNameList[i] << "\r\n";
    SendMessage(MassEditTabCtrls.eb_selectedGens, WM_SETTEXT, 0, LPARAM(ss.str().c_str()));

    return;
}

void MassEditUpdateGensAffected(int* const genBuff, const int count)
{
    stringstream ss;

    SendMessage(MassEditTabCtrls.eb_selectedGens, WM_SETTEXT, 0, LPARAM(""));

    if(genBuff)
    {
        for(int i = 0; i < count; i++)
            ss << generalsNameList[genBuff[i]] << "\r\n";
        SendMessage(MassEditTabCtrls.eb_selectedGens, WM_SETTEXT, 0, LPARAM(ss.str().c_str()));
    }

    return;
}

void prepareGenBuff(int** genBuff, int* count)
{
    int genClass;

    if(SendMessage(MassEditTabCtrls.rb_MassEditGenList, BM_GETCHECK, 0, 0) == BST_CHECKED)
    {
        *count = SendMessage(MassEditTabCtrls.lb_MassEditGenList, LB_GETSELCOUNT, 0, 0);;
        *genBuff = (int*)malloc(sizeof(int) * (*count));
        SendMessage(MassEditTabCtrls.lb_MassEditGenList, LB_GETSELITEMS, WPARAM(*count), LPARAM(*genBuff));

        return;
    }

    if(SendMessage(MassEditTabCtrls.rb_MassEditClassList, BM_GETCHECK, 0, 0) == BST_CHECKED)
    {
        genClass = SendMessage(MassEditTabCtrls.cb_MassEditClassList, CB_GETCURSEL, 0, 0);
        genClass++;

        *count = getCountForGenClass(genClass);
        *genBuff = (int*)malloc(sizeof(int) * (*count));
        fillGenClassBuff(*genBuff, *count, genClass);

        return;
    }

    return;
}

void fillGenClassBuff(int* const genClassBuff, const int count, const int genClass)
{
    int i = 0;
    int j = 0;

    if(SendMessage(MassEditTabCtrls.rb_MassEditClassList, BM_GETCHECK, 0, 0) == BST_CHECKED)
    {
        MassEditCheckBoxState() == 1 ? i = 0 : i = 8;
        for(; i < 171; i++)
            if(dr.genArr[i].classType == genClass)
            {
                genClassBuff[j] = dr.genArr[i].listIndex;
                j++;
            }
    }

    return;
}

int getCountForGenClass(const int genClass)
{
    int i     = 0;
    int count = 0;

    MassEditCheckBoxState() == 1 ? i = 0 : i = 8;

    for(; i < 171; i++)
        if(dr.genArr[i].classType == genClass)
            count++;

    return count;
}

int MassEditCheckBoxState(void)
{
    if(SendMessage(MassEditTabCtrls.ckbox_MonarchsWithClass, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
        return 0;
    else
        return 1; //if Include Monarchs checkbox is checked, return true

    return 0;
}

void MassEditShowCastles(const bool show)
{
    SendDlgItemMessage(hTabMassEdit, ID_RB_ME_CAS, BM_SETCHECK, 1, 0);

    PopulateCastleOwners();

    if(show)
    {
        ShowWindow(MassEditCasSelGroupBox, TRUE);
        ShowWindow(MassEditTabCtrls.rb_MassEditCasList, TRUE);
        ShowWindow(MassEditTabCtrls.lb_MassEditCasList, TRUE);
        ShowWindow(MassEditTabCtrls.rb_MassEditCasOwnerList, TRUE);
        ShowWindow(MassEditTabCtrls.cb_MassEditCasOwnerList, TRUE);
        ShowWindow(SelectedCasGroupBox, TRUE);
        ShowWindow(MassEditTabCtrls.eb_selectedCas, TRUE);
        ShowWindow(cb_MassEditCasOwnerTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_CasOwnerList, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetCasOwner, TRUE);
        ShowWindow(cb_MassEditCasLevelTag, TRUE);
        ShowWindow(MassEditTabCtrls.cb_ME_CasLevel, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetCasLevel, TRUE);
        ShowWindow(eb_MassEditCasTrpCntTag, TRUE);
        ShowWindow(MassEditTabCtrls.eb_ME_CasTrpCnt, TRUE);
        ShowWindow(MassEditTabCtrls.but_ME_SetCasTrpCnt, TRUE);

        EnableWindow(MassEditCasSelGroupBox, TRUE);
        EnableWindow(MassEditTabCtrls.rb_MassEditCasList, TRUE);
        EnableWindow(MassEditTabCtrls.lb_MassEditCasList, TRUE);
        EnableWindow(MassEditTabCtrls.rb_MassEditCasOwnerList, TRUE);
        EnableWindow(SelectedCasGroupBox, TRUE);
        EnableWindow(MassEditTabCtrls.eb_selectedCas, TRUE);
        EnableWindow(cb_MassEditCasOwnerTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_CasOwnerList, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetCasOwner, TRUE);
        EnableWindow(cb_MassEditCasLevelTag, TRUE);
        EnableWindow(MassEditTabCtrls.cb_ME_CasLevel, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetCasLevel, TRUE);
        EnableWindow(eb_MassEditCasTrpCntTag, TRUE);
        EnableWindow(MassEditTabCtrls.eb_ME_CasTrpCnt, TRUE);
        EnableWindow(MassEditTabCtrls.but_ME_SetCasTrpCnt, TRUE);

        SendDlgItemMessage(hTabMassEdit, ID_ME_RB_CASLIST, BM_SETCHECK, 1, 0);
        SendDlgItemMessage(hTabMassEdit, ID_ME_RB_CASOWN_CB, BM_SETCHECK, 0, 0);
    }
    else
    {
        ShowWindow(MassEditCasSelGroupBox, FALSE);
        ShowWindow(MassEditTabCtrls.rb_MassEditCasList, FALSE);
        ShowWindow(MassEditTabCtrls.lb_MassEditCasList, FALSE);
        ShowWindow(MassEditTabCtrls.rb_MassEditCasOwnerList, FALSE);
        ShowWindow(MassEditTabCtrls.cb_MassEditCasOwnerList, FALSE);
        ShowWindow(SelectedCasGroupBox, FALSE);
        ShowWindow(MassEditTabCtrls.eb_selectedCas, FALSE);
        ShowWindow(cb_MassEditCasOwnerTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_CasOwnerList, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetCasOwner, FALSE);
        ShowWindow(cb_MassEditCasLevelTag, FALSE);
        ShowWindow(MassEditTabCtrls.cb_ME_CasLevel, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetCasLevel, FALSE);
        ShowWindow(eb_MassEditCasTrpCntTag, FALSE);
        ShowWindow(MassEditTabCtrls.eb_ME_CasTrpCnt, FALSE);
        ShowWindow(MassEditTabCtrls.but_ME_SetCasTrpCnt, FALSE);

        EnableWindow(MassEditCasSelGroupBox, FALSE);
        EnableWindow(MassEditTabCtrls.rb_MassEditCasList, FALSE);
        EnableWindow(MassEditTabCtrls.lb_MassEditCasList, FALSE);
        EnableWindow(MassEditTabCtrls.rb_MassEditCasOwnerList, FALSE);
        EnableWindow(MassEditTabCtrls.cb_MassEditCasOwnerList, FALSE);
        EnableWindow(SelectedCasGroupBox, FALSE);
        EnableWindow(MassEditTabCtrls.eb_selectedCas, FALSE);
        EnableWindow(cb_MassEditCasOwnerTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_CasOwnerList, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetCasOwner, FALSE);
        EnableWindow(cb_MassEditCasLevelTag, FALSE);
        EnableWindow(MassEditTabCtrls.cb_ME_CasLevel, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetCasLevel, FALSE);
        EnableWindow(eb_MassEditCasTrpCntTag, FALSE);
        EnableWindow(MassEditTabCtrls.eb_ME_CasTrpCnt, FALSE);
        EnableWindow(MassEditTabCtrls.but_ME_SetCasTrpCnt, FALSE);
    }

    return;
}

void MassEditShowCasByOwner(void)
{
    int casOwner = -1;

    EnableWindow(MassEditTabCtrls.cb_MassEditCasOwnerList, TRUE);
    EnableWindow(MassEditTabCtrls.lb_MassEditCasList, FALSE); //turn off listbox for Castles list

    PopulateCastleOwners();

    casOwner = SendMessage(MassEditTabCtrls.cb_MassEditCasOwnerList, CB_GETCURSEL, 0, 0);

    MassEditUpdateCasAffected(castleOwners[casOwner]);

    return;
}

void MassEditUpdateCasAffected(int* const casBuff, const int count)
{
    stringstream ss;

    SendMessage(MassEditTabCtrls.eb_selectedCas, WM_SETTEXT, 0, LPARAM(""));

    if(casBuff)
    {
        for(int i = 0; i < count; i++)
            ss << castlesNameList[casBuff[i]] << "\r\n";
        SendMessage(MassEditTabCtrls.eb_selectedCas, WM_SETTEXT, 0, LPARAM(ss.str().c_str()));
    }

    return;
}

void MassEditUpdateCasAffected(const int casOwner)
{
    stringstream ss;

    SendMessage(MassEditTabCtrls.eb_selectedCas, WM_SETTEXT, 0, LPARAM(""));

    for(int i = 0; i < 34; i++)
        if(castleOwnership[i] == casOwner)
            ss << castlesNameList[i] << "\r\n";
    SendMessage(MassEditTabCtrls.eb_selectedCas, WM_SETTEXT, 0, LPARAM(ss.str().c_str()));

    return;
}

void PopulateCastleOwners(void)
{
    int j         = 0;
    int currOwner = 171; //used as invalid owner indicator; max is 170

    castleOwnerCount = 0;

    for(int i = 0; i < 34; i++)
    {
        currOwner = castleOwnership[i];
        for(j = 0; j < castleOwnerCount; j++)
        {
            if(castleOwners[j] == currOwner)
                j = 171;
        }
        if(j == castleOwnerCount)
        {
            castleOwners[j] = currOwner;
            castleOwnerCount++;
        }
    }

    if(castleOwnerCount)
        insertionSort(castleOwners, castleOwnerCount);

    SendMessage(MassEditTabCtrls.cb_MassEditCasOwnerList, CB_RESETCONTENT, 0, 0);
    for(int i = 0; i < castleOwnerCount; i++)
    {
        if(castleOwners[i] < 171)
            SendMessage(MassEditTabCtrls.cb_MassEditCasOwnerList, CB_ADDSTRING, 0, LPARAM(generalsNameList[castleOwners[i]]));
        if(castleOwners[i] >= 171)
            SendMessage(MassEditTabCtrls.cb_MassEditCasOwnerList, CB_ADDSTRING, 0, LPARAM(TEXT("None")));
    }
    
    SendMessage(MassEditTabCtrls.cb_MassEditCasOwnerList, CB_SETCURSEL, 0, 0);

    return;
}

void prepareCasBuff(int** casBuff, int* count)
{
    int j             = 0;
    int casOwner      = -1;
    int comboboxIndex = -1;

    if(SendMessage(MassEditTabCtrls.rb_MassEditCasList, BM_GETCHECK, 0, 0) == BST_CHECKED)
    {
        *count = SendMessage(MassEditTabCtrls.lb_MassEditCasList, LB_GETSELCOUNT, 0, 0);;
        *casBuff = (int*)malloc(sizeof(int) * (*count));
        SendMessage(MassEditTabCtrls.lb_MassEditCasList, LB_GETSELITEMS, WPARAM(*count), LPARAM(*casBuff));

        return;
    }

    if(SendMessage(MassEditTabCtrls.rb_MassEditCasOwnerList, BM_GETCHECK, 0, 0) == BST_CHECKED)
    {

        comboboxIndex = SendMessage(MassEditTabCtrls.cb_MassEditCasOwnerList, CB_GETCURSEL, 0, 0);
        casOwner      = castleOwners[comboboxIndex];

        *count = 0;
        for(int i = 0; i < 34; i++)
            if(castleOwnership[i] == casOwner)
                (*count)++;

        *casBuff = (int*)malloc(sizeof(int) * (*count));
        for(int i = 0; i < 34; i++)
        {
            if(castleOwnership[i] == casOwner)
            {
                (*casBuff)[j] = i;
                j++;
            }
        }

        return;
    }

    return;
}

//void MassEditShowDivisions(const bool show){return;}

int checkMassEditMethod(void)
{
    int methodNumber = 0;

    if(SendMessage(MassEditTabCtrls.rb_MassEditGenByValue, BM_GETCHECK, 0, 0) == BST_CHECKED)
        methodNumber = 1;

    if(SendMessage(MassEditTabCtrls.rb_MassEditGenOfCurrent, BM_GETCHECK, 0, 0) == BST_CHECKED)
        methodNumber = 2;

    if(SendMessage(MassEditTabCtrls.rb_MassEditGenOfMax, BM_GETCHECK, 0, 0) == BST_CHECKED)
        methodNumber = 3;

    return methodNumber;
}

int getValFromPerc(const int targetPerc, const int currValue, const int maxValue)
{
          int newValue = currValue;
    const int percType = checkMassEditMethod(); // 2 for "of current", 3 for "of max"

    if((percType != 2) && (percType != 3))
        return -1;

    if((targetPerc < 1) || (targetPerc > 100)) // *************************************** MAYBE REMOVE THIS, BUT CHECK TO MAKE SURE newValue DOESN'T FALL OUTSIDE MIN/MAX
        return -1;

    if(percType == 2)
        newValue = (int)floor((((double)targetPerc / 100) * (double)currValue) + 0.5);

    if(percType == 3)
        newValue = (int)floor((((double)targetPerc / 100) * (double)maxValue) + 0.5);

    return newValue;
}

LRESULT CALLBACK MassEditTabWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int currStat;
    int newStat;

    switch(msg)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_RB_ME_GEN:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            int* genBuff = NULL;

                            if(SendMessage(MassEditTabCtrls.rb_MassEditGen, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
                            {
                                MassEditShowGenerals(true);
                                MassEditShowCastles(false);
                                //MassEditShowDivisions(false);
                                SendDlgItemMessage(hTabMassEdit, ID_RB_ME_CAS, BM_SETCHECK, 0, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_RB_ME_DIV, BM_SETCHECK, 0, 0);

                                MassEditUpdateGensAffected(genBuff, 0);
                                SendMessage(MassEditTabCtrls.lb_MassEditGenList, LB_SETSEL, FALSE, -1); //clears all selections from a listbox
                            }
                        }
                        break;
                    }
                }
                break;
                case ID_RB_ME_CAS:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            int* casBuff = NULL;

                            if(SendMessage(MassEditTabCtrls.rb_MassEditCas, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
                            {
                                MassEditShowCastles(true);
                                MassEditShowGenerals(false);
                                //MassEditShowDivisions(false);
                                SendDlgItemMessage(hTabMassEdit, ID_RB_ME_GEN, BM_SETCHECK, 0, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_RB_ME_DIV, BM_SETCHECK, 0, 0);

                                MassEditUpdateCasAffected(casBuff, 0);
                                SendMessage(MassEditTabCtrls.lb_MassEditCasList, LB_SETSEL, FALSE, -1); //clears all selections from a listbox
                            }
                        }
                        break;
                    }
                }
                break;
/*                case ID_RB_ME_DIV:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            if(SendMessage(MassEditTabCtrls.rb_MassEditDiv, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
                            {
                                MassEditShowDivisions(true);
                                MassEditShowGenerals(false);
                                MassEditShowCastles(false);
                                SendDlgItemMessage(hTabMassEdit, ID_RB_ME_GEN, BM_SETCHECK, 0, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_RB_ME_CAS, BM_SETCHECK, 0, 0);
                            }
                        }
                        break;
                    }
                }
                break;  */
                case ID_ME_RB_GENLIST:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            if(SendMessage(MassEditTabCtrls.rb_MassEditGenList, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
                            {   
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_CLASS_CB, BM_SETCHECK, 0, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GENLIST, BM_SETCHECK, 1, 0);
                                EnableWindow(MassEditTabCtrls.ckbox_MonarchsWithClass, FALSE);
                                EnableWindow(MassEditTabCtrls.cb_MassEditClassList, FALSE);
                                EnableWindow(MassEditTabCtrls.lb_MassEditGenList, TRUE); //turn off listbox for Generals list
                                SendMessage(MassEditTabCtrls.eb_selectedGens, WM_SETTEXT, 0, LPARAM(""));
                            }

                        }
                         break;
                    }
                }
                break;
                case ID_ME_LB_GENLIST:
                {
                    switch(HIWORD(wParam))
                    {
                        case LBN_SELCHANGE:
                        {
                            int  count   = SendMessage(MassEditTabCtrls.lb_MassEditGenList, LB_GETSELCOUNT, 0, 0);;
                            int* genBuff = (int*)malloc(sizeof(int) * count);
                            SendMessage(MassEditTabCtrls.lb_MassEditGenList, LB_GETSELITEMS, WPARAM(count), LPARAM(genBuff));

                            MassEditUpdateGensAffected(genBuff, count);

                            free(genBuff);
                        }
                         break;
                    }
                }
                break;
                case ID_ME_RB_CLASS_CB:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            SendDlgItemMessage(hTabMassEdit, ID_ME_RB_CLASS_CB, BM_SETCHECK, 1, 0);
                            SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GENLIST, BM_SETCHECK, 0, 0);
                            SendMessage(MassEditTabCtrls.lb_MassEditGenList, LB_SETSEL, FALSE, -1); //clears all selections from a listbox
                            MassEditShowGenByClass();
                        }
                         break;
                    }
                }
                break;
                case ID_ME_XB_INC_KINGS:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            if(SendMessage(MassEditTabCtrls.ckbox_MonarchsWithClass, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
                            {
                                SendDlgItemMessage(hTabMassEdit, ID_ME_XB_INC_KINGS, BM_SETCHECK, 1, 0);
                                MassEditShowGenByClass();
                            }
                            else
                            {
                                SendDlgItemMessage(hTabMassEdit, ID_ME_XB_INC_KINGS, BM_SETCHECK, 0, 0);
                                MassEditShowGenByClass();
                            }
                        }
                         break;
                    }
                }
                break;
                case ID_ME_CB_CLASSLIST:
                {
                    switch(HIWORD(wParam))
                    {
                        case CBN_SELCHANGE:
                        {
                            int genClass;
                            int checkboxState;

                            genClass = SendMessage(MassEditTabCtrls.cb_MassEditClassList, CB_GETCURSEL, 0, 0);
                            genClass++;
                            MassEditCheckBoxState() == 1 ? checkboxState = 0 : checkboxState = 8;
                            MassEditUpdateGensAffected(genClass, checkboxState);
                        }
                        break;
                    }
                }
                break;
                case ID_ME_SET_GENOWNER:
                {
                    int  count;
                    int* genBuff;
                    int  owner = SendMessage(MassEditTabCtrls.cb_ME_GenOwnerList, CB_GETCURSEL, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                        if(genBuff[i] != dr.playingAs)
                            dr.genArr[genBuff[i]].setOwner(owner);
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENLEVEL:
                {
                    int  count;
                    int* genBuff;
                    int  level = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENLEVEL, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                            dr.genArr[genBuff[i]].editOneByteStat(0, 49, level - 1, GEN_LEVEL, &(dr.genArr[genBuff[i]].level), levelBuffer);

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].level;
                            newStat  = getValFromPerc(level, currStat, 50);
                            dr.genArr[genBuff[i]].editOneByteStat(0, 49, newStat - 1, GEN_LEVEL, &(dr.genArr[genBuff[i]].level), levelBuffer);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENEXP:
                {
                    int  count;
                    int* genBuff;
                    int  exp = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENEXP, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 65535, exp, GEN_CURR_EXP, &(dr.genArr[genBuff[i]].currentExp), currExpBuffer);

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].currentExp;
                            newStat  = getValFromPerc(exp, currStat, 65535);
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 65535, newStat, GEN_CURR_EXP, &(dr.genArr[genBuff[i]].currentExp), currExpBuffer);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENHP:
                {
                    int  count;
                    int* genBuff;
                    int  maxHP = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENHP, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(1, 127, maxHP, GEN_MAX_HP, &(dr.genArr[genBuff[i]].maxHP), maxHpBuffer);
                            dr.genArr[genBuff[i]].editOneByteStat(1, 127, maxHP, GEN_CURRENT_HP, &(dr.genArr[genBuff[i]].currentHP), currentHpBuffer);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].maxHP;
                            newStat  = getValFromPerc(maxHP, currStat, 127);
                            dr.genArr[genBuff[i]].editOneByteStat(1, 127, newStat, GEN_MAX_HP, &(dr.genArr[genBuff[i]].maxHP), maxHpBuffer);
                            dr.genArr[genBuff[i]].editOneByteStat(1, 127, newStat, GEN_CURRENT_HP, &(dr.genArr[genBuff[i]].currentHP), currentHpBuffer);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENMP:
                {
                    int  count;
                    int* genBuff;
                    int  maxMP = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENMP, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(1, 127, maxMP, GEN_MAX_MP, &(dr.genArr[genBuff[i]].maxMP), maxMpBuffer);
                            dr.genArr[genBuff[i]].editOneByteStat(1, 127, maxMP, GEN_CURRENT_MP, &(dr.genArr[genBuff[i]].currentMP), currentMpBuffer);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].maxMP;
                            newStat  = getValFromPerc(maxMP, currStat, 127);
                            dr.genArr[genBuff[i]].editOneByteStat(1, 127, newStat, GEN_MAX_MP, &(dr.genArr[genBuff[i]].maxMP), maxMpBuffer);
                            dr.genArr[genBuff[i]].editOneByteStat(1, 127, newStat, GEN_CURRENT_MP, &(dr.genArr[genBuff[i]].currentMP), currentMpBuffer);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENSTR:
                {
                    int  count;
                    int* genBuff;
                    int  strength = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENSTR, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(1, 255, strength, GEN_STRENGTH, &(dr.genArr[genBuff[i]].strength), strengthBuffer);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].strength;
                            newStat  = getValFromPerc(strength, currStat, 255);
                            dr.genArr[genBuff[i]].editOneByteStat(1, 255, newStat, GEN_STRENGTH, &(dr.genArr[genBuff[i]].strength), strengthBuffer);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENCOM:
                {
                    int  count;
                    int* genBuff;
                    int  command = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENCOM, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(1, 255, command, GEN_COMMAND, &(dr.genArr[genBuff[i]].command), commandBuffer);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].command;
                            newStat  = getValFromPerc(command, currStat, 255);
                            dr.genArr[genBuff[i]].editOneByteStat(1, 255, newStat, GEN_COMMAND, &(dr.genArr[genBuff[i]].command), commandBuffer);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENINT:
                {
                    int  count;
                    int* genBuff;
                    int  intel = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENINT, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(1, 255, intel, GEN_INTELLIGENCE, &(dr.genArr[genBuff[i]].intelligence), intellBuffer);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].intelligence;
                            newStat  = getValFromPerc(intel, currStat, 255);
                            dr.genArr[genBuff[i]].editOneByteStat(1, 255, newStat, GEN_INTELLIGENCE, &(dr.genArr[genBuff[i]].intelligence), intellBuffer);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENLIVES:
                {
                    int  count;
                    int* genBuff;
                    int  lives = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENLIVES, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(1, 255, lives, GEN_LIVES_BEF_SLAIN, &(dr.genArr[genBuff[i]].livesLeft), livesBefSlainBuff);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].livesLeft;
                            newStat  = getValFromPerc(lives, currStat, 255);
                            dr.genArr[genBuff[i]].editOneByteStat(1, 255, newStat, GEN_LIVES_BEF_SLAIN, &(dr.genArr[genBuff[i]].livesLeft), livesBefSlainBuff);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENLOYAL:
                {
                    int  count;
                    int* genBuff;
                    int  loyalty = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENLOYAL, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(1, 255, loyalty, GEN_LOYALTY, &(dr.genArr[genBuff[i]].loyalty), loyaltyBuffer);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].loyalty;
                            newStat  = getValFromPerc(loyalty, currStat, 255);
                            dr.genArr[genBuff[i]].editOneByteStat(1, 255, newStat, GEN_LOYALTY, &(dr.genArr[genBuff[i]].loyalty), loyaltyBuffer);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENTRPS:
                {
                    int  count;
                    int* genBuff;
                    int  troopType = SendMessage(MassEditTabCtrls.cb_ME_GenTroopType, CB_GETCURSEL, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                        dr.genArr[genBuff[i]].changeGenTroopType(troopType);
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENTRPCNT:
                {
                    int  count;
                    int* genBuff;
                    int  trpCnt = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENTRPCNT, NULL, FALSE);
                    int  maxTroops;
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        maxTroops = dr.genArr[genBuff[i]].troopMedals[dr.genArr[genBuff[i]].troopIndex] * 10;
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(0, maxTroops, trpCnt, GEN_CURR_TROOP_COUNT, &(dr.genArr[genBuff[i]].currentTroopCount), currTroopCountBuff);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].currentTroopCount;
                            newStat  = getValFromPerc(trpCnt, currStat, 100);
                            dr.genArr[genBuff[i]].editOneByteStat(0, maxTroops, newStat, GEN_CURR_TROOP_COUNT, &(dr.genArr[genBuff[i]].currentTroopCount), currTroopCountBuff);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENSOLD:
                {
                    int  count;
                    int* genBuff;
                    int  medals = SendMessage(MassEditTabCtrls.cb_ME_GenSoldier, CB_GETCURSEL, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                        dr.genArr[genBuff[i]].editMedals(medals, 1, &dr.genArr[genBuff[i]].soldierCavalry, 2,
                                                         dr.genArr[genBuff[i]].troopMedals[1],
                                                         dr.genArr[genBuff[i]].troopMedals[2], GEN_SOLD_AND_CAVA);
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENCAV:
                {
                    int  count;
                    int* genBuff;
                    int  medals = SendMessage(MassEditTabCtrls.cb_ME_GenCavalry, CB_GETCURSEL, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                        dr.genArr[genBuff[i]].editMedals(medals, 2, &dr.genArr[genBuff[i]].soldierCavalry, 1,
                                                         dr.genArr[genBuff[i]].troopMedals[1],
                                                         dr.genArr[genBuff[i]].troopMedals[2], GEN_SOLD_AND_CAVA);
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENMAGE:
                {
                    int  count;
                    int* genBuff;
                    int  medals = SendMessage(MassEditTabCtrls.cb_ME_GenMage, CB_GETCURSEL, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                        dr.genArr[genBuff[i]].editMedals(medals, 3, &dr.genArr[genBuff[i]].mageSamurai, 2,
                                                         dr.genArr[genBuff[i]].troopMedals[3],
                                                         dr.genArr[genBuff[i]].troopMedals[4], GEN_MAGE_AND_SAMU);
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENSAMU:
                {
                    int  count;
                    int* genBuff;
                    int  medals = SendMessage(MassEditTabCtrls.cb_ME_GenSamurai, CB_GETCURSEL, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                        dr.genArr[genBuff[i]].editMedals(medals, 4, &dr.genArr[genBuff[i]].mageSamurai, 1,
                                                         dr.genArr[genBuff[i]].troopMedals[3],
                                                         dr.genArr[genBuff[i]].troopMedals[4], GEN_MAGE_AND_SAMU);
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENARCH:
                {
                    int  count;
                    int* genBuff;
                    int  medals = SendMessage(MassEditTabCtrls.cb_ME_GenArcher, CB_GETCURSEL, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                        dr.genArr[genBuff[i]].editMedals(medals, 5, &dr.genArr[genBuff[i]].archerMonk, 2,
                                                         dr.genArr[genBuff[i]].troopMedals[5],
                                                         dr.genArr[genBuff[i]].troopMedals[6], GEN_ARCH_AND_MONK);
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENMONK:
                {
                    int  count;
                    int* genBuff;
                    int  medals = SendMessage(MassEditTabCtrls.cb_ME_GenMonk, CB_GETCURSEL, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                        dr.genArr[genBuff[i]].editMedals(medals, 6, &dr.genArr[genBuff[i]].archerMonk, 1,
                                                         dr.genArr[genBuff[i]].troopMedals[5],
                                                         dr.genArr[genBuff[i]].troopMedals[6], GEN_ARCH_AND_MONK);
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENHARP:
                {
                    int  count;
                    int* genBuff;
                    int  medals = SendMessage(MassEditTabCtrls.cb_ME_GenHarpy, CB_GETCURSEL, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                        dr.genArr[genBuff[i]].editMedals(medals, 7, &dr.genArr[genBuff[i]].harpyBeast, 2,
                                                         dr.genArr[genBuff[i]].troopMedals[7],
                                                         dr.genArr[genBuff[i]].troopMedals[8], GEN_HARP_AND_BEAS);
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENBEAST:
                {
                    int  count;
                    int* genBuff;
                    int  medals = SendMessage(MassEditTabCtrls.cb_ME_GenBeast, CB_GETCURSEL, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                        dr.genArr[genBuff[i]].editMedals(medals, 8, &dr.genArr[genBuff[i]].harpyBeast, 1,
                                                         dr.genArr[genBuff[i]].troopMedals[7],
                                                         dr.genArr[genBuff[i]].troopMedals[8], GEN_HARP_AND_BEAS);
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENDRAG:
                {
                    int  count;
                    int* genBuff;
                    int  medals = SendMessage(MassEditTabCtrls.cb_ME_GenDragon, CB_GETCURSEL, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                        dr.genArr[genBuff[i]].editMedals(medals, 9, &dr.genArr[genBuff[i]].dragonZombie, 2,
                                                         dr.genArr[genBuff[i]].troopMedals[9],
                                                         dr.genArr[genBuff[i]].troopMedals[10], GEN_DRAG_AND_ZOMB);
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENZOMB:
                {
                    int  count;
                    int* genBuff;
                    int  medals = SendMessage(MassEditTabCtrls.cb_ME_GenZombie, CB_GETCURSEL, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                        dr.genArr[genBuff[i]].editMedals(medals, 10, &dr.genArr[genBuff[i]].dragonZombie, 1,
                                                         dr.genArr[genBuff[i]].troopMedals[9],
                                                         dr.genArr[genBuff[i]].troopMedals[10], GEN_DRAG_AND_ZOMB);
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENWINS:
                {
                    int  count;
                    int* genBuff;
                    int  wins = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENWINS, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 9999, wins, GEN_TOTAL_WINS, &(dr.genArr[genBuff[i]].newWins), totalWinBuffer);

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].newWins;
                            newStat  = getValFromPerc(wins, currStat, 9999);
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 9999, newStat, GEN_TOTAL_WINS, &(dr.genArr[genBuff[i]].newWins), totalWinBuffer);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENLOSS:
                {
                    int  count;
                    int* genBuff;
                    int  losses = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENLOSS, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 9999, losses, GEN_TOTAL_LOSSES, &(dr.genArr[genBuff[i]].newLosses), totalLossBuffer);

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].newLosses;
                            newStat  = getValFromPerc(losses, currStat, 9999);
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 9999, newStat, GEN_TOTAL_LOSSES, &(dr.genArr[genBuff[i]].newLosses), totalLossBuffer);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENMERIT:
                {
                    int  count;
                    int* genBuff;
                    int  merits = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENMERIT, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 9999, merits, GEN_NEW_MERITS, &(dr.genArr[genBuff[i]].newMerits), newMeritsBuffer);

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].newMerits;
                            newStat  = getValFromPerc(merits, currStat, 9999);
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 9999, newStat, GEN_NEW_MERITS, &(dr.genArr[genBuff[i]].newMerits), newMeritsBuffer);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENESCAPE:
                {
                    int  count;
                    int* genBuff;
                    int  genEscape = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENESCAPE, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(0, 255, genEscape, GEN_ESCAPE_CHANCE, &(dr.genArr[genBuff[i]].escapeChance), escChanceBuffer);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].escapeChance;
                            newStat  = getValFromPerc(genEscape, currStat, 255);
                            dr.genArr[genBuff[i]].editOneByteStat(0, 255, newStat, GEN_ESCAPE_CHANCE, &(dr.genArr[genBuff[i]].escapeChance), escChanceBuffer);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENSPELL:
                {
                    int  count;
                    int* genBuff;
                    int  spellTier = SendMessage(MassEditTabCtrls.cb_ME_GenSpellTier, CB_GETCURSEL, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                        dr.genArr[genBuff[i]].editOneByteStat(0, 3, spellTier, GEN_SPELL_TIER, &(dr.genArr[genBuff[i]].spellTier), spellTierBuffer);
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENITEM:
                {
                    int  count;
                    int* genBuff;
                    int  equipItem = SendMessage(MassEditTabCtrls.cb_ME_GenItem, CB_GETCURSEL, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                        dr.genArr[genBuff[i]].editOneByteStat(0, 47, equipItem, GEN_EQUIPPED_ITEM, &(dr.genArr[genBuff[i]].equippedItem), equippedItemBuffer);
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENNAISEI:
                {
                    int  count;
                    int* genBuff;
                    int  checkState = SendMessage(MassEditTabCtrls.xb_ME_GenNaisei, BM_GETCHECK, 0, 0);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkState == BST_CHECKED)
                            dr.genArr[genBuff[i]].setSearchFortifyStatus(false);
                        if(checkState == BST_UNCHECKED)
                            dr.genArr[genBuff[i]].setSearchFortifyStatus(true);
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_XB_GENNAISEI:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            if(SendMessage(MassEditTabCtrls.xb_ME_GenNaisei, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
                                SendDlgItemMessage(hTabMassEdit, ID_ME_XB_GENNAISEI, BM_SETCHECK, 1, 0);
                            else
                                SendDlgItemMessage(hTabMassEdit, ID_ME_XB_GENNAISEI, BM_SETCHECK, 0, 0);
                        }
                         break;
                    }
                }
                break;
                case ID_ME_SET_GENDEFTRP:
                {
                    int  count;
                    int* genBuff;
                    int  defp = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENDEFTRP, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(0, 255, defp, GEN_DEFP, &(dr.genArr[genBuff[i]].defp), defpBuffer);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].defp;
                            newStat  = getValFromPerc(defp, currStat, 255);
                            dr.genArr[genBuff[i]].editOneByteStat(0, 255, newStat, GEN_DEFP, &(dr.genArr[genBuff[i]].defp), defpBuffer);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENDEFSWD:
                {
                    int  count;
                    int* genBuff;
                    int defSwd = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENDEFSWD, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 65535, defSwd, GEN_DEF_SWORD, &(dr.genArr[genBuff[i]].defSword), defSwordBuff);

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].defSword;
                            newStat  = getValFromPerc(defSwd, currStat, 65535);
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 65535, newStat, GEN_DEF_SWORD, &(dr.genArr[genBuff[i]].defSword), defSwordBuff);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENDEFICE:
                {
                    int  count;
                    int* genBuff;
                    int defIce = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENDEFICE, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 65535, defIce, GEN_DEF_ICE, &(dr.genArr[genBuff[i]].defIce), defIceBuff);

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].defIce;
                            newStat  = getValFromPerc(defIce, currStat, 65535);
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 65535, newStat, GEN_DEF_ICE, &(dr.genArr[genBuff[i]].defIce), defIceBuff);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENDEFFRE:
                {
                    int  count;
                    int* genBuff;
                    int defFire = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENDEFFRE, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 65535, defFire, GEN_DEF_FIRE, &(dr.genArr[genBuff[i]].defFire), defFireBuff);

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].defFire;
                            newStat  = getValFromPerc(defFire, currStat, 65535);
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 65535, newStat, GEN_DEF_FIRE, &(dr.genArr[genBuff[i]].defFire), defFireBuff);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENDEFLGT:
                {
                    int  count;
                    int* genBuff;
                    int defLight = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENDEFLGT, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 65535, defLight, GEN_DEF_LIGHT, &(dr.genArr[genBuff[i]].defLight), defLightBuff);

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].defLight;
                            newStat  = getValFromPerc(defLight, currStat, 65535);
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 65535, newStat, GEN_DEF_LIGHT, &(dr.genArr[genBuff[i]].defLight), defLightBuff);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENDEFDRK:
                {
                    int  count;
                    int* genBuff;
                    int defDark = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENDEFDRK, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 65535, defDark, GEN_DEF_DARK, &(dr.genArr[genBuff[i]].defDark), defDarkBuff);

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].defDark;
                            newStat  = getValFromPerc(defDark, currStat, 65535);
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 65535, newStat, GEN_DEF_DARK, &(dr.genArr[genBuff[i]].defDark), defDarkBuff);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENNACT:
                {
                    int  count;
                    int* genBuff;
                    int  naction = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENNACT, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(0, 255, naction, GEN_N_ACTION, &(dr.genArr[genBuff[i]].nAction), nActionBuff);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].nAction;
                            newStat  = getValFromPerc(naction, currStat, 255);
                            dr.genArr[genBuff[i]].editOneByteStat(0, 255, newStat, GEN_N_ACTION, &(dr.genArr[genBuff[i]].nAction), nActionBuff);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENBACT:
                {
                    int  count;
                    int* genBuff;
                    int  baction = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENBACT, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(0, 255, baction, GEN_B_ACTION, &(dr.genArr[genBuff[i]].bAction), bActionBuff);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].bAction;
                            newStat  = getValFromPerc(baction, currStat, 255);
                            dr.genArr[genBuff[i]].editOneByteStat(0, 255, newStat, GEN_B_ACTION, &(dr.genArr[genBuff[i]].bAction), bActionBuff);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENBTLACT:
                {
                    int  count;
                    int* genBuff;
                    int  btlAction = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENBTLACT, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(0, 255, btlAction, GEN_BTL_ACTION, &(dr.genArr[genBuff[i]].btlAction), btlActionBuff);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].btlAction;
                            newStat  = getValFromPerc(btlAction, currStat, 255);
                            dr.genArr[genBuff[i]].editOneByteStat(0, 255, newStat, GEN_BTL_ACTION, &(dr.genArr[genBuff[i]].btlAction), btlActionBuff);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENWARLK:
                {
                    int  count;
                    int* genBuff;
                    int  warlike = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENWARLK, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(0, 255, warlike, GEN_WARLIKE, &(dr.genArr[genBuff[i]].warlike), warlikeBuff);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].warlike;
                            newStat  = getValFromPerc(warlike, currStat, 255);
                            dr.genArr[genBuff[i]].editOneByteStat(0, 255, newStat, GEN_WARLIKE, &(dr.genArr[genBuff[i]].warlike), warlikeBuff);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENNEGO:
                {
                    int  count;
                    int* genBuff;
                    int nego = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENNEGO, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 65535, nego, GEN_NEGO, &(dr.genArr[genBuff[i]].nego), negoBuff);

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].nego;
                            newStat  = getValFromPerc(nego, currStat, 65535);
                            dr.genArr[genBuff[i]].editTwoByteStat(0, 65535, newStat, GEN_NEGO, &(dr.genArr[genBuff[i]].nego), negoBuff);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENATKPLS:
                {
                    int  count;
                    int* genBuff;
                    int  atkPlus = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENATKPLS, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(0, 170, atkPlus, GEN_ATK_PLUS, &(dr.genArr[genBuff[i]].atkPlus), atkPlusBuff);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].atkPlus;
                            newStat  = getValFromPerc(atkPlus, currStat, 170);
                            dr.genArr[genBuff[i]].editOneByteStat(0, 170, newStat, GEN_ATK_PLUS, &(dr.genArr[genBuff[i]].atkPlus), atkPlusBuff);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_SET_GENDEFPLS:
                {
                    int  count;
                    int* genBuff;
                    int  defPlus = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_GENDEFPLS, NULL, FALSE);
                    prepareGenBuff(&genBuff, &count);
                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                        {
                            dr.genArr[genBuff[i]].editOneByteStat(0, 255, defPlus, GEN_DEF_PLUS, &(dr.genArr[genBuff[i]].defPlus), defPlusBuff);
                        }

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            currStat = dr.genArr[genBuff[i]].defPlus;
                            newStat  = getValFromPerc(defPlus, currStat, 255);
                            dr.genArr[genBuff[i]].editOneByteStat(0, 255, newStat, GEN_DEF_PLUS, &(dr.genArr[genBuff[i]].defPlus), defPlusBuff);
                        }
                    }
                    free(genBuff);
                }
                break;
                case ID_ME_RB_GEN_VAL:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            if(SendMessage(MassEditTabCtrls.rb_MassEditGenByValue, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
                            {
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_VAL, BM_SETCHECK, 1, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_PERC, BM_SETCHECK, 0, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_PC_CUR, BM_SETCHECK, 0, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_PC_MAX, BM_SETCHECK, 0, 0);
                            }
                        }
                         break;
                    }
                }
                break;
                case ID_ME_RB_GEN_PERC:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            if(SendMessage(MassEditTabCtrls.rb_MassEditGenByPercent, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
                            {
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_VAL, BM_SETCHECK, 0, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_PERC, BM_SETCHECK, 1, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_PC_CUR, BM_SETCHECK, 1, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_PC_MAX, BM_SETCHECK, 0, 0);
                            }
                        }
                         break;
                    }
                }
                break;
                case ID_ME_RB_GEN_PC_CUR:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            if(SendMessage(MassEditTabCtrls.rb_MassEditGenOfCurrent, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
                            {
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_VAL, BM_SETCHECK, 0, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_PERC, BM_SETCHECK, 1, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_PC_CUR, BM_SETCHECK, 1, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_PC_MAX, BM_SETCHECK, 0, 0);
                            }
                        }
                         break;
                    }
                }
                break;
                case ID_ME_RB_GEN_PC_MAX:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            if(SendMessage(MassEditTabCtrls.rb_MassEditGenOfMax, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
                            {
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_VAL, BM_SETCHECK, 0, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_PERC, BM_SETCHECK, 1, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_PC_CUR, BM_SETCHECK, 0, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_GEN_PC_MAX, BM_SETCHECK, 1, 0);
                            }
                        }
                         break;
                    }
                }
                break;
                case ID_ME_RB_CASLIST:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            if(SendMessage(MassEditTabCtrls.rb_MassEditCasList, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
                            {   
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_CASOWN_CB, BM_SETCHECK, 0, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_CASLIST, BM_SETCHECK, 1, 0);
                                EnableWindow(MassEditTabCtrls.cb_MassEditCasOwnerList, FALSE);
                                EnableWindow(MassEditTabCtrls.lb_MassEditCasList, TRUE); //turn on listbox for Castles list
                                SendMessage(MassEditTabCtrls.eb_selectedCas, WM_SETTEXT, 0, LPARAM(""));
                            }

                        }
                         break;
                    }
                }
                break;
                case ID_ME_RB_CASOWN_CB:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            if(SendMessage(MassEditTabCtrls.rb_MassEditCasOwnerList, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
                            {
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_CASLIST, BM_SETCHECK, 0, 0);
                                SendDlgItemMessage(hTabMassEdit, ID_ME_RB_CASOWN_CB, BM_SETCHECK, 1, 0);
                                SendMessage(MassEditTabCtrls.lb_MassEditCasList, LB_SETSEL, FALSE, -1); //clears all selections from a listbox
                                MassEditShowCasByOwner();
                            }
                        }
                         break;
                    }
                }
                break;
                case ID_ME_LB_CASLIST:
                {
                    switch(HIWORD(wParam))
                    {
                        case LBN_SELCHANGE:
                        {
                            int  count   = SendMessage(MassEditTabCtrls.lb_MassEditCasList, LB_GETSELCOUNT, 0, 0);;
                            int* casBuff = (int*)malloc(sizeof(int) * count);
                            SendMessage(MassEditTabCtrls.lb_MassEditCasList, LB_GETSELITEMS, WPARAM(count), LPARAM(casBuff));

                            MassEditUpdateCasAffected(casBuff, count);

                            free(casBuff);
                        }
                         break;
                    }
                }
                break;
                case ID_ME_CB_CAS_OWNER:
                {
                    switch(HIWORD(wParam))
                    {
                        case CBN_SELCHANGE:
                        {
                            int owner = SendMessage(MassEditTabCtrls.cb_MassEditCasOwnerList, CB_GETCURSEL, 0, 0);
                            MassEditUpdateCasAffected(castleOwners[owner]);
                        }
                        break;
                    }
                }
                break;
                case ID_ME_SET_CASOWNER:
                {
                    int  count;
                    int* casBuff;
                    int newRuler = SendMessage(MassEditTabCtrls.cb_ME_CasOwnerList, CB_GETCURSEL, 0, 0);
                    prepareCasBuff(&casBuff, &count);

                    for(int i = 0; i < count; i++)
                        dr.casArr[casBuff[i]].changeRuler(newRuler);
                    free(casBuff);

                    PopulateCastleOwners();
                    if(SendMessage(MassEditTabCtrls.rb_MassEditCasOwnerList, BM_GETCHECK, 0, 0) == BST_CHECKED)
                        MassEditShowCasByOwner();
                }
                break;
                case ID_ME_SET_CASLEVEL:
                {
                    int  count;
                    int* casBuff;
                    int  newLevel = SendMessage(MassEditTabCtrls.cb_ME_CasLevel, CB_GETCURSEL, 0, 0);
                    newLevel++; //castle levels start at 1, but array indexing starts at 0
                    prepareCasBuff(&casBuff, &count);

                    for(int i = 0; i < count; i++)
                        dr.casArr[casBuff[i]].adjustLevel(newLevel);
                    free(casBuff);

                }
                break;
                case ID_ME_SET_CASTROOPS:
                {
                    int  count;
                    int* casBuff;
                    int  casMaxTroops;
                    int  newTroopCount = (int)GetDlgItemInt(hTabMassEdit, ID_ME_EB_CASTROOPS, NULL, FALSE);
                    prepareCasBuff(&casBuff, &count);

                    for(int i = 0; i < count; i++)
                    {
                        if(checkMassEditMethod() == 1)
                            dr.casArr[casBuff[i]].adjustTroops(newTroopCount);

                        if((checkMassEditMethod() == 2) || (checkMassEditMethod() == 3))
                        {
                            casMaxTroops = dr.casArr[casBuff[i]].maxTroops;
                            currStat     = dr.casArr[casBuff[i]].troopCount;
                            newStat      = getValFromPerc(newTroopCount, currStat, casMaxTroops);
                            dr.casArr[casBuff[i]].adjustTroops(newStat);
                        }
                    }
                    free(casBuff);

                }
                break;
            }
        break;
        default:
            return CallWindowProc(g_MainWndProc, hwnd, msg, wParam, lParam);
    }

    return 0;
}
