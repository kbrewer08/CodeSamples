#include <windows.h>

#include "DFGui.h"

typedef struct
{
    HWND cb_GenNameList;
    HWND cb_GenOwnerList;
    HWND but_SetGenOwner;
    HWND eb_GenLevel;
    HWND but_SetGenLevel;
    HWND eb_GenExp;
    HWND but_SetGenExp;
    HWND eb_GenCurHP;
    HWND eb_GenMaxHP;
    HWND but_SetGenHP;
    HWND eb_GenCurMP;
    HWND eb_GenMaxMP;
    HWND but_SetGenMP;
    HWND eb_GenStr;
    HWND but_SetGenStr;
    HWND eb_GenCom;
    HWND but_SetGenCom;
    HWND eb_GenInt;
    HWND but_SetGenInt;
    HWND cb_GenTrpType;
    HWND but_SetGenTrpType;
    HWND eb_GenTrpCnt;
    HWND but_SetGenTrpCnt;
    HWND cb_GenSoldier;
    HWND but_SetGenSoldier;
    HWND cb_GenCavalry;
    HWND but_SetGenCavalry;
    HWND cb_GenMage;
    HWND but_SetGenMage;
    HWND cb_GenSamurai;
    HWND but_SetGenSamurai;
    HWND cb_GenArcher;
    HWND but_SetGenArcher;
    HWND cb_GenMonk;
    HWND but_SetGenMonk;
    HWND cb_GenBeast;
    HWND but_SetGenBeast;
    HWND cb_GenHarpy;
    HWND but_SetGenHarpy;
    HWND cb_GenDragon;
    HWND but_SetGenDragon;
    HWND cb_GenZombie;
    HWND but_SetGenZombie;
    HWND rb_GenCastleLocation;
    HWND cb_GenLocation;
    HWND but_SetGenLocation;
    HWND rb_GenHiddenLocation;
    HWND cb_GenHidden;
    HWND but_SetGenHidden;
    HWND rb_GenDivision;
    HWND eb_GenWins;
    HWND but_SetGenWins;
    HWND eb_GenLosses;
    HWND but_SetGenLosses;
    HWND eb_GenMerits;
    HWND but_SetGenMerits;
    HWND eb_GenLives;
    HWND but_SetGenLives;
    HWND eb_GenLoyalty;
    HWND but_SetGenLoyalty;
    HWND eb_GenDefp;
    HWND but_SetGenDefp;
    HWND eb_GenEscape;
    HWND but_SetGenEscape;
    HWND cb_GenSpellTier;
    HWND but_SetGenSpellTier;
    HWND cb_GenItem;
    HWND but_SetGenItem;
    HWND ckbox_GenSearchFortify;
    HWND but_setGenSearchFortify;
    HWND eb_GenDefVsSword;
    HWND but_SetGenDefVsSword;
    HWND eb_GenDefVsIce;
    HWND but_SetGenDefVsIce;
    HWND eb_GenDefVsFire;
    HWND but_SetGenDefVsFire;
    HWND eb_GenDefVsLight;
    HWND but_SetGenDefVsLight;
    HWND eb_GenDefVsDark;
    HWND but_SetGenDefVsDark;
    HWND eb_GenNAction;
    HWND but_SetGenNAction;
    HWND eb_GenBAction;
    HWND but_SetGenBAction;
    HWND eb_GenBtlAction;
    HWND but_SetGenBtlAction;
    HWND eb_GenMoral;
    HWND but_SetGenMoral;
    HWND eb_GenWarlike;
    HWND but_SetGenWarlike;
    HWND eb_GenNego;
    HWND but_SetGenNego;
    HWND eb_GenAtkPlus;
    HWND but_SetGenAtkPlus;
    HWND eb_GenDefPlus;
    HWND but_SetGenDefPlus;
} GENERALS_TAB;

typedef struct
{
    HWND cb_CasNameList;
    HWND cb_CasRulerList;
    HWND but_SetCasRuler;
    HWND cb_CasLeaderList;
    HWND but_SetCasLeader;
    HWND cb_CasLevel;
    HWND but_SetCasLevel;
    HWND eb_CasTroopCount;
    HWND but_SetCasTroopCount;
    HWND lb_casGenerals;
    HWND lb_casCaptives;
    HWND lb_casGenList;
    HWND but_CasAddGenerals;
    HWND but_CasDelGenerals;
    HWND but_CasAddCaptives;
    HWND but_CasDelCaptives;
    HWND but_CasGeneralToCaptive;
    HWND but_CasCaptiveToGeneral;
} CASTLES_TAB;

typedef struct
{
    HWND cb_DivNameList;
    HWND cb_DivRulerList;
    HWND but_SetDivRuler;
    HWND cb_DivLeaderList;
    HWND but_SetDivLeader;
    HWND cb_DivGoalList;
    HWND but_SetDivGoal;
    HWND cb_DivLocList;
    HWND but_SetDivLoc;
    HWND cb_DivStatusList;
    HWND but_SetDivStatus;
    HWND lb_DivGenerals;
    HWND lb_DivCaptives;
    HWND lb_DivGenList;
    HWND but_DivAddGenerals;
    HWND but_DivDelGenerals;
    HWND but_DivAddCaptives;
    HWND but_DivDelCaptives;
    HWND but_DivGeneralToCaptive;
    HWND but_DivCaptiveToGeneral;
} DIVISIONS_TAB;

typedef struct
{
    HWND rb_MassEditGen;
    HWND rb_MassEditCas;
    HWND rb_MassEditDiv;
    HWND rb_MassEditGenList;
    HWND rb_MassEditClassList;
    HWND lb_MassEditGenList;
    HWND cb_MassEditClassList;
    HWND ckbox_MonarchsWithClass;
    HWND eb_selectedGens;
    HWND rb_MassEditGenByValue;
    HWND rb_MassEditGenByPercent;
    HWND rb_MassEditGenOfMax;
    HWND rb_MassEditGenOfCurrent;
    HWND cb_ME_GenOwnerList;
    HWND but_ME_SetGenOwner;
    HWND eb_ME_GenLevel;
    HWND but_ME_SetGenLevel;
    HWND eb_ME_GenExp;
    HWND but_ME_SetGenExp;
    HWND eb_ME_GenHP;
    HWND but_ME_SetGenHP;
    HWND eb_ME_GenMP;
    HWND but_ME_SetGenMP;
    HWND eb_ME_GenStr;
    HWND but_ME_SetGenStr;
    HWND eb_ME_GenCom;
    HWND but_ME_SetGenCom;
    HWND eb_ME_GenInt;
    HWND but_ME_SetGenInt;
    HWND eb_ME_GenLives;
    HWND but_ME_SetGenLives;
    HWND eb_ME_GenLoyalty;
    HWND but_ME_SetGenLoyalty;
    HWND cb_ME_GenTroopType;
    HWND but_ME_SetGenTroopType;
    HWND eb_ME_GenTroopCnt;
    HWND but_ME_SetGenTrpCnt;
    HWND cb_ME_GenSoldier;
    HWND but_ME_SetGenSoldier;
    HWND cb_ME_GenCavalry;
    HWND but_ME_SetGenCavalry;
    HWND cb_ME_GenMage;
    HWND but_ME_SetGenMage;
    HWND cb_ME_GenSamurai;
    HWND but_ME_SetGenSamurai;
    HWND cb_ME_GenArcher;
    HWND but_ME_SetGenArcher;
    HWND cb_ME_GenMonk;
    HWND but_ME_SetGenMonk;
    HWND cb_ME_GenBeast;
    HWND but_ME_SetGenBeast;
    HWND cb_ME_GenHarpy;
    HWND but_ME_SetGenHarpy;
    HWND cb_ME_GenDragon;
    HWND but_ME_SetGenDragon;
    HWND cb_ME_GenZombie;
    HWND but_ME_SetGenZombie;
    HWND eb_ME_GenWins;
    HWND but_ME_SetGenWins;
    HWND eb_ME_GenLoss;
    HWND but_ME_SetGenLoss;
    HWND eb_ME_GenMerits;
    HWND but_ME_SetGenMerits;
    HWND eb_ME_GenEscape;
    HWND but_ME_SetGenEscape;
    HWND cb_ME_GenSpellTier;
    HWND but_ME_SetGenSpellTier;
    HWND cb_ME_GenItem;
    HWND but_ME_SetGenItem;
    HWND xb_ME_GenNaisei;
    HWND but_ME_SetGenNaisei;
    HWND eb_ME_GenDefTrps;
    HWND but_ME_SetGenDefTrps;
    HWND eb_ME_GenDefSwd;
    HWND but_ME_SetGenDefSwd;
    HWND eb_ME_GenDefIce;
    HWND but_ME_SetGenDefIce;
    HWND eb_ME_GenDefFire;
    HWND but_ME_SetGenDefFire;
    HWND eb_ME_GenDefLight;
    HWND but_ME_SetGenDefLight;
    HWND eb_ME_GenDefDark;
    HWND but_ME_SetGenDefDark;
    HWND eb_ME_GenNAction;
    HWND but_ME_SetGenNaction;
    HWND eb_ME_GenBAction;
    HWND but_ME_SetGenBAction;
    HWND eb_ME_GenBtlAction;
    HWND but_ME_SetGenBtlAction;
    HWND eb_ME_GenWarlike;
    HWND but_ME_SetGenWarlike;
    HWND eb_ME_GenNego;
    HWND but_ME_SetGenNego;
    HWND eb_ME_GenAtkPlus;
    HWND but_ME_SetGenAtkPlus;
    HWND eb_ME_GenDefPlus;
    HWND but_ME_SetGenDefPlus;

    HWND rb_MassEditCasList;
    HWND rb_MassEditCasOwnerList;
    HWND lb_MassEditCasList;
    HWND cb_MassEditCasOwnerList;
    HWND eb_selectedCas;
    HWND cb_ME_CasOwnerList;
    HWND but_ME_SetCasOwner;
    HWND cb_ME_CasLevel;
    HWND but_ME_SetCasLevel;
    HWND eb_ME_CasTrpCnt;
    HWND but_ME_SetCasTrpCnt;
} MASSEDIT_TAB;

extern HWND hTabCntrl;   // The main tab control

extern HWND hTabGenerals;
extern GENERALS_TAB GenTabCtrls; //struct to contain all the controls for Generals tab

extern HWND hTabCastles;
extern CASTLES_TAB CasTabCtrls; //struct to contain all the controls for Castles tab

extern HWND hTabDivisions;
extern DIVISIONS_TAB DivTabCtrls; //struct to contain all the controls for Divisions tab

extern HWND hTabMassEdit;
extern MASSEDIT_TAB MassEditTabCtrls;

extern HWND hTabItemInv;
extern HWND hTabMisc;

void CreateTabControl (void);

