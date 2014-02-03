#include <windows.h>
#include <commctrl.h>
#include <cmath>

#include "DFGui.h"

void CreateItemsTab(void)
{
    HWND lb_ItemInvListTag;
    HWND lb_FullItemListTag;
    
    // create a Static control for our view window
    hTabItemInv = CreateWindowEx(
        0, "STATIC", NULL, WS_CHILD | WS_TABSTOP,
        0, 22, 1009, 688,
        hTabCntrl, NULL, hThisInst, NULL);

    g_MainWndProc = (WNDPROC)SetWindowLongPtr(hTabItemInv, GWL_WNDPROC, (LONG) ItemsTabWndProc);

    lb_ItemInvListTag = CreateWindowEx(              //item inventory listbox tag
        0, "STATIC", TEXT("Your Items:"), WS_CHILD | WS_VISIBLE,
        10, 28, 60, 20, 
        hTabItemInv, NULL, hThisInst, NULL); 

    ItemsTabCtrls.lb_itemInvList = CreateWindowEx( //item inventory listbox
        WS_EX_CLIENTEDGE, "LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL |
        WS_TABSTOP | WS_DISABLED | LBS_EXTENDEDSEL | LBS_NOTIFY,
        70, 28, 120, 660,
        hTabItemInv, (HMENU)ID_LB_ITEMINV_LIST, hThisInst, NULL);

    lb_FullItemListTag = CreateWindowEx(              //full item  listbox tag
        0, "STATIC", TEXT("Item List:"), WS_CHILD | WS_VISIBLE,
        230, 28, 50, 20, 
        hTabItemInv, NULL, hThisInst, NULL); 

    ItemsTabCtrls.lb_fullItemList = CreateWindowEx( //full item list listbox
        WS_EX_CLIENTEDGE, "LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL |
        WS_TABSTOP | WS_DISABLED | LBS_EXTENDEDSEL | LBS_NOTIFY,
        290, 28, 120, 660,
        hTabItemInv, (HMENU)ID_LB_FULL_ITEMLIST, hThisInst, NULL);

    ItemsTabCtrls.but_removeItems = CreateWindowEx(   //delete items from inventory button
        0, "BUTTON", TEXT("Remove"), WS_CHILD | WS_TABSTOP | WS_DISABLED | WS_VISIBLE,
        10, 48, 50, 20,
        hTabItemInv, (HMENU)ID_BUT_REMOVE_ITEMS, hThisInst, NULL);

    ItemsTabCtrls.but_addItems = CreateWindowEx(   //add items to inventory button
        0, "BUTTON", TEXT("Add"), WS_CHILD | WS_TABSTOP | WS_DISABLED | WS_VISIBLE,
        230, 48, 50, 20,
        hTabItemInv, (HMENU)ID_BUT_ADD_ITEMS, hThisInst, NULL);

    SetDefaultFont(hTabItemInv);
    SetDefaultFont(lb_ItemInvListTag);
    SetDefaultFont(ItemsTabCtrls.lb_itemInvList);
    SetDefaultFont(lb_FullItemListTag);
    SetDefaultFont(ItemsTabCtrls.lb_fullItemList);
    SetDefaultFont(ItemsTabCtrls.but_removeItems);
    SetDefaultFont(ItemsTabCtrls.but_addItems);

    return;
}

void PopulateItemsTab(void)
{
/*
    Copied here from PopulateGeneralsTab as reminder that this stuff has been set up already
    dr.fr.readFile();   //read the save file
    dr.initGenerals();  //create the generals array
    dr.setMonarch();    //find who the player's monarch is
    dr.initCastles();   //create the castles array
    dr.initDivisions(); //create the divisions array
    dr.initItemInv();   //create the item inventory from domestic affairs
*/
    EnableWindow(ItemsTabCtrls.lb_itemInvList, TRUE); //turn on item inventory listbox
    EnableWindow(ItemsTabCtrls.lb_fullItemList, TRUE); //turn on full item list listbox
    EnableWindow(ItemsTabCtrls.but_removeItems, TRUE); //turn on remove items button
    EnableWindow(ItemsTabCtrls.but_addItems, TRUE); //turn on add items button

    if(!alreadyOpened)
    {
        for(int i = 1; i < 73; i++)
            SendMessage(ItemsTabCtrls.lb_fullItemList, LB_ADDSTRING, 0, LPARAM(itemList[i]));
    }

    updateInvList();

    return;
}

void updateInvList(void)
{
    SendMessage(ItemsTabCtrls.lb_itemInvList, LB_RESETCONTENT, 0, 0);
    int numItems = dr.itemInv.numItems;
    for(int i = 0; i < numItems; i++)
    {
        int item = dr.itemInv.items[i];
        SendMessage(ItemsTabCtrls.lb_itemInvList, LB_ADDSTRING, 0, LPARAM(itemList[item]));
    }

    return;
}

LRESULT CALLBACK ItemsTabWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_BUT_REMOVE_ITEMS:
                {
                    int  count    = SendMessage(ItemsTabCtrls.lb_itemInvList, LB_GETSELCOUNT, 0, 0);
                    int* itemBuff = (int*)malloc(sizeof(int) * count);
                    SendMessage(ItemsTabCtrls.lb_itemInvList, LB_GETSELITEMS, WPARAM(count), LPARAM(itemBuff));

                    dr.delItemsInv(itemBuff, count);
                    dr.fw.writeInventoryToFile();
                    updateInvList();

                    free(itemBuff);
                } //ID_BUT_REMOVE_ITEMS
                break;
                case ID_BUT_ADD_ITEMS:
                {
                    int  count    = SendMessage(ItemsTabCtrls.lb_fullItemList, LB_GETSELCOUNT, 0, 0);
                    int* itemBuff = (int*)malloc(sizeof(int) * count);
                    SendMessage(ItemsTabCtrls.lb_fullItemList, LB_GETSELITEMS, WPARAM(count), LPARAM(itemBuff));

/* Because the first item in the master-items-list listbox on this tab starts at 0 (so mars blade
   is item 0 here), but the actual items list in DragonForce.cpp starts at 0 (so "none" is item 0
   and mars blade is item 1). Hence, we need to +1 every item in itemsBuff */
                    for(int i = 0; i < count; i++)
                        itemBuff[i] = itemBuff[i] + 1;

                    dr.addItemsInv(itemBuff, count);
                    dr.fw.writeInventoryToFile();
                    updateInvList();

                    free(itemBuff);
                } //ID_BUT_ADD_ITEMS
                break;
            }
        break;//WM_COMMAND
        default:
            return CallWindowProc(g_MainWndProc, hwnd, msg, wParam, lParam);
    }

    return 0;
}
