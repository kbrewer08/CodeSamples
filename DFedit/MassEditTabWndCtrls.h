#ifndef MASSEDITTABWNDCTRLS_H
#define MASSEDITTABWNDCTRLS_H

#include <windows.h>
#include <commctrl.h>

#include "DFGui.h"

void CreateMassEditTab          (void);
void PopulateMassEditTab        (void);

void MassEditShowGenerals       (const bool show);
void MassEditShowGenByClass     (void);
void MassEditUpdateGensAffected (const int genClass, const int start);
void MassEditUpdateGensAffected (int* const genBuff, const int count);
void prepareGenBuff             (int** genBuff, int* count);
void fillGenClassBuff           (int* const genClassBuff, const int count, const int genClass);
int  getCountForGenClass        (const int genClass);
int  MassEditCheckBoxState      (void);

void MassEditShowCastles        (const bool show);
void MassEditShowCasByOwner     (void);
void MassEditUpdateCasAffected  (int* const casBuff, const int count);
void MassEditUpdateCasAffected  (const int casOwner);
void PopulateCastleOwners       (void);
void prepareCasBuff             (int** casBuff, int* count);

//void MassEditShowDivisions      (const bool show);

int  checkMassEditMethod        (void);
int  getValFromPerc             (const int targetPerc, const int currValue, const int maxValue);

LRESULT CALLBACK MassEditTabWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif
