#include "cipherBacon.h"
//extern HWND EditCipher;
/*  Declare Windows procedure  */
int tabItem;
extern HINSTANCE hInstance;
struct mode_Ret modeAll;
//char FileName[255]="D:\\project\\cipherBacon\\cipherBacon\\config\\config.ini";
char FileName[255];
char HelpFile[255];
/*  Make the class name into a global variable  */

void createModeA(HWND hwnd,HFONT hfontST, HFONT hfontED){
    HWND hLabelTMess,hLabelFMess,hLabelCTMess,
    hLabelListAlph, hLabelListCiph,hLabelListTK, hLabelListFK;
    char buf[1000];
    int i;
    modeAll.A.hwnd=hwnd;
    hLabelListAlph=CreateWindow("Static", "Алф.", WS_CHILD | WS_VISIBLE
                                  ,15,10,40,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListAlph, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelListCiph=CreateWindow("Static", "Шифр", WS_CHILD | WS_VISIBLE
                                  ,80,10,50,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListCiph, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelListTK=CreateWindow("Static", "И.К.", WS_CHILD | WS_VISIBLE
                                  ,150,10,40,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListTK, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelListFK=CreateWindow("Static", "Л.К.", WS_CHILD | WS_VISIBLE
                                  ,200,10,40,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListFK, WM_SETFONT, (WPARAM)hfontST, 0);

    modeAll.A.hListBox=CreateWindow("ListBox",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_WANTKEYBOARDINPUT |
                               LBS_SORT | LBS_NOTIFY,15,30,300,540,hwnd,(HMENU)ID_ListBox,hInstance, NULL);
    SendMessage(modeAll.A.hListBox, WM_SETFONT, (WPARAM)hfontED, 0);

    for(i=0; i<sizeAlph; i++){
        char lpszStr[20];
        sprintf(lpszStr,"%c     %s   %c   %c",i+'A',modeAll.A.CiphAlph[i],
                modeAll.A.trueKey[i],modeAll.A.falseKey[i]?modeAll.A.falseKey[i]:' ');
        SendMessage(modeAll.A.hListBox,LB_ADDSTRING, NULL, (LPARAM)(LPCSTR)lpszStr);
    }
    SendMessage(modeAll.A.hListBox,LB_SETCURSEL, (WPARAM)0, NULL);
    SendMessage(modeAll.A.hListBox,LB_GETTEXT, (WPARAM)0, (LPARAM)(int FAR *)buf);
    buf[1]='\0';
    buf[11]='\0';
    buf[15]='\0';
    //-------------------------------------------------------------------------------------
    hLabelTMess=CreateWindow("Static", "Истинное Сообщение", WS_CHILD | WS_VISIBLE
                                  , 330, 10, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelTMess, WM_SETFONT, (WPARAM)hfontST, 0);

    hLabelFMess=CreateWindow("Static", "Ложное Сообщение", WS_CHILD | WS_VISIBLE
                                  , 330,60, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelFMess, WM_SETFONT, (WPARAM)hfontST, 0);

    hLabelCTMess=CreateWindow("Static", "Зашифрованное Сообщение", WS_CHILD | WS_VISIBLE
                                  , 330, 110, 400, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelCTMess, WM_SETFONT, (WPARAM)hfontST, 0);
    //---------------------------------

    modeAll.A.hTrueMess=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP
                                  , 330,30, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.A.hTrueMess, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.A.hTrueMess, EM_SETLIMITTEXT, sizeMess-1, 0);
    SendMessage(modeAll.A.hTrueMess, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.A.trueMess);

    SetWindowPos(modeAll.A.hTrueMess,hwnd,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.A.hFalseMess=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP
                                  , 330,80, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.A.hFalseMess, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.A.hFalseMess, EM_SETLIMITTEXT, sizeMess-1, 0);
    SendMessage(modeAll.A.hFalseMess, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.A.falseMess);

    SetWindowPos(modeAll.A.hFalseMess,modeAll.A.hTrueMess,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.A.hCryptMess=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP | ES_AUTOHSCROLL
                                  , 330,130, 600, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.A.hCryptMess, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.A.hCryptMess, EM_SETLIMITTEXT, sizeCiph-1, 0);
    SendMessage(modeAll.A.hCryptMess, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.A.cryptMess);
    SendMessage(modeAll.A.hCryptMess,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);

    SetWindowPos(modeAll.A.hCryptMess,modeAll.A.hFalseMess,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    //-------------------------------------------------------------------------------------------------

    modeAll.A.hEditAlph=CreateWindow("Edit",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                            ,15,555,50,20,hwnd,(HMENU)ID_EditAlph,hInstance, NULL);
    SendMessage(modeAll.A.hEditAlph,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.A.hEditAlph, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.A.hEditAlph, EM_SETLIMITTEXT, 1, 0);
    SendMessage(modeAll.A.hEditAlph, EM_REPLACESEL, NULL, (LPARAM)(LPCSTR)buf);

    modeAll.A.hEditCipher=CreateWindow("Edit",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | WS_GROUP | WS_TABSTOP
                            ,75,555,60,20,hwnd,(HMENU)ID_EditCipher,hInstance, NULL);
    SendMessage(modeAll.A.hEditCipher, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.A.hEditCipher, EM_SETLIMITTEXT, 5, 0);
    SendMessage(modeAll.A.hEditCipher, EM_REPLACESEL, NULL, (LPARAM)(LPCSTR)(buf+6));

    SetWindowPos(modeAll.A.hEditCipher,modeAll.A.hCryptMess,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.A.hEditTrueKey=CreateWindow("Edit",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | WS_GROUP | WS_TABSTOP
                            ,150,555,30,20,hwnd,(HMENU)ID_EditTrueKey,hInstance, NULL);
    SendMessage(modeAll.A.hEditTrueKey, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.A.hEditTrueKey, EM_SETLIMITTEXT, 1, 0);
    SendMessage(modeAll.A.hEditTrueKey, EM_REPLACESEL, NULL, (LPARAM)(LPCSTR)(buf+14));

    SetWindowPos(modeAll.A.hEditTrueKey,modeAll.A.hEditCipher,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.A.hButtonReplace=CreateWindow("Button","Заменить", WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP
                            ,235,555,80,30,hwnd,(HMENU)ButtRep,hInstance, NULL);
    SendMessage(modeAll.A.hButtonReplace, WM_SETFONT, (WPARAM)hfontST, 0);

    SetWindowPos(modeAll.A.hButtonReplace,modeAll.A.hEditTrueKey,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

}

void createModeB(HWND hwnd,HFONT hfontST, HFONT hfontED){
    HWND hLabelListAlph, hLabelListCiph,hLabelListTK, hLabelListFK;
    HWND hLabelTMess,hLabelCTMess,hLabelDFMess;
    //---------------------------------------------------------------------------
    char buf[1000];
    int i;
    modeAll.B.hwnd=hwnd;
    hLabelListAlph=CreateWindow("Static", "Алф.", WS_CHILD | WS_VISIBLE
                                  ,15,10,40,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListAlph, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelListCiph=CreateWindow("Static", "Шифр", WS_CHILD | WS_VISIBLE
                                  ,80,10,50,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListCiph, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelListTK=CreateWindow("Static", "И.К.", WS_CHILD | WS_VISIBLE
                                  ,150,10,40,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListTK, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelListFK=CreateWindow("Static", "Л.К.", WS_CHILD | WS_VISIBLE
                                  ,200,10,40,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListFK, WM_SETFONT, (WPARAM)hfontST, 0);

    modeAll.B.hListBox=CreateWindow("ListBox",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_WANTKEYBOARDINPUT |
                               LBS_SORT | LBS_NOTIFY,15,30,300,540,hwnd,(HMENU)ID_ListBox,hInstance, NULL);
    SendMessage(modeAll.B.hListBox, WM_SETFONT, (WPARAM)hfontED, 0);

    for(i=0; i<sizeAlph; i++){
        char lpszStr[20];
        sprintf(lpszStr,"%c     %s   %c   %c",i+'A',modeAll.B.CiphAlph[i],
                modeAll.B.trueKey[i],modeAll.B.falseKey[i]?modeAll.B.falseKey[i]:' ');
        SendMessage(modeAll.B.hListBox,LB_ADDSTRING, NULL, (LPARAM)(LPCSTR)lpszStr);
    }
    SendMessage(modeAll.B.hListBox,LB_SETCURSEL, (WPARAM)0, NULL);
    SendMessage(modeAll.B.hListBox,LB_GETTEXT, (WPARAM)0, (LPARAM)(int FAR *)buf);
    buf[1]='\0';
    buf[11]='\0';
    buf[15]='\0';
     //----------------------------------------------------------------------
    hLabelTMess=CreateWindow("Static", "Зашифрованное сообщение", WS_CHILD | WS_VISIBLE
                                  , 330, 10, 400, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelTMess, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelCTMess=CreateWindow("Static", "Расшифрованное истинное сообщение", WS_CHILD | WS_VISIBLE
                                  , 330,60, 400, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelCTMess, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelDFMess=CreateWindow("Static", "Расшифрованное ложное сообщение", WS_CHILD | WS_VISIBLE
                                  , 330,110, 400, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelDFMess, WM_SETFONT, (WPARAM)hfontST, 0);
    //--------------------------------------------------------------------
    modeAll.B.hCiphMess=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                                     | WS_GROUP | WS_TABSTOP, 330,30, 550, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.B.hCiphMess, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.B.hCiphMess, EM_SETLIMITTEXT, sizeCiph-1, 0);
    SendMessage(modeAll.B.hCiphMess, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.B.cryptMess);

    SetWindowPos(modeAll.B.hCiphMess,hwnd,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.B.hDecryptTrueMess=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                                            | WS_GROUP | WS_TABSTOP , 330,80, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.B.hDecryptTrueMess,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.B.hDecryptTrueMess, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.B.hDecryptTrueMess, EM_SETLIMITTEXT, sizeMess-1, 0);
    SendMessage(modeAll.B.hDecryptTrueMess, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.B.decrTrueMess);

    SetWindowPos(modeAll.B.hDecryptTrueMess,modeAll.B.hCiphMess,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.B.hDecryptFalseMess=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL
                                             | WS_GROUP | WS_TABSTOP , 330,130, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.B.hDecryptFalseMess,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.B.hDecryptFalseMess, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.B.hDecryptFalseMess, EM_SETLIMITTEXT, sizeMess-1, 0);
    SendMessage(modeAll.B.hDecryptFalseMess, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.B.decrFalseMess);

    SetWindowPos(modeAll.B.hDecryptFalseMess,modeAll.B.hDecryptTrueMess,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    //--------------------------------------------------------------------------------
    modeAll.B.hEditAlph=CreateWindow("Edit",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                            ,15,555,50,20,hwnd,(HMENU)ID_EditAlph,hInstance, NULL);
    SendMessage(modeAll.B.hEditAlph,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.B.hEditAlph, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.B.hEditAlph, EM_SETLIMITTEXT, 1, 0);
    SendMessage(modeAll.B.hEditAlph, EM_REPLACESEL, NULL, (LPARAM)(LPCSTR)buf);

    modeAll.B.hEditCipher=CreateWindow("Edit",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                            | WS_GROUP | WS_TABSTOP,75,555,60,20,hwnd,(HMENU)ID_EditCipher,hInstance, NULL);
    SendMessage(modeAll.B.hEditCipher, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.B.hEditCipher, EM_SETLIMITTEXT, 5, 0);
    SendMessage(modeAll.B.hEditCipher, EM_REPLACESEL, NULL, (LPARAM)(LPCSTR)(buf+6));

    SetWindowPos(modeAll.B.hEditCipher,modeAll.B.hDecryptFalseMess,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.B.hEditTrueKey=CreateWindow("Edit",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER
                            | WS_GROUP | WS_TABSTOP,150,555,30,20,hwnd,(HMENU)ID_EditTrueKey,hInstance, NULL);
    SendMessage(modeAll.B.hEditTrueKey, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.B.hEditTrueKey, EM_SETLIMITTEXT, 1, 0);
    SendMessage(modeAll.B.hEditTrueKey, EM_REPLACESEL, NULL, (LPARAM)(LPCSTR)(buf+14));

    SetWindowPos(modeAll.B.hEditTrueKey,modeAll.B.hEditCipher,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.B.hEditFalseKey=CreateWindow("Edit",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER
                            | WS_GROUP | WS_TABSTOP,190,555,30,20,hwnd,(HMENU)ID_EditFalseKey,hInstance, NULL);
    SendMessage(modeAll.B.hEditFalseKey, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.B.hEditFalseKey, EM_SETLIMITTEXT, 1, 0);
    SendMessage(modeAll.B.hEditFalseKey, EM_REPLACESEL, NULL, (LPARAM)(LPCSTR)(buf+18));

    SetWindowPos(modeAll.B.hEditFalseKey,modeAll.B.hEditTrueKey,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    //-----------------------------------------------------------------
    modeAll.B.hButtonReplace=CreateWindow("Button","Заменить", WS_CHILD | WS_VISIBLE
                           | WS_GROUP | WS_TABSTOP ,235,555,80,30,hwnd,(HMENU)ButtRep,hInstance, NULL);
    SendMessage(modeAll.B.hButtonReplace, WM_SETFONT, (WPARAM)hfontST, 0);
    SetWindowPos(modeAll.B.hButtonReplace,modeAll.B.hEditFalseKey,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
}

void createModeC(HWND hwnd,HFONT hfontST, HFONT hfontED){
    HWND hLabelTMess,hLabelFMess1,hLabelFMess2;
    HWND hLabelCTMess,hLabelCFMess1,hLabelCFMess2;
    HWND hLabelListAlph, hLabelListCiph,hLabelListTK, hLabelListFK1, hLabelListFK2;
    //----------------------------------------------------------------------------
    int i;
    modeAll.C.hwnd=hwnd;
    hLabelListAlph=CreateWindow("Static", "Алф.", WS_CHILD | WS_VISIBLE
                                  ,15,10,40,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListAlph, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelListCiph=CreateWindow("Static", "Шифр", WS_CHILD | WS_VISIBLE
                                  ,80,10,50,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListCiph, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelListTK=CreateWindow("Static", "И.К.", WS_CHILD | WS_VISIBLE
                                  ,150,10,40,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListTK, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelListFK1=CreateWindow("Static", "Л.К.", WS_CHILD | WS_VISIBLE
                                  ,195,10,40,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListFK1, WM_SETFONT, (WPARAM)hfontST, 0);

    hLabelListFK2=CreateWindow("Static", "Л.К.", WS_CHILD | WS_VISIBLE
                                  ,240,10,40,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListFK2, WM_SETFONT, (WPARAM)hfontST, 0);

    modeAll.C.hListBox=CreateWindow("ListBox",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_WANTKEYBOARDINPUT |
                               LBS_SORT | LBS_NOTIFY,15,30,300,540,hwnd,(HMENU)ID_ListBox,hInstance, NULL);
    SendMessage(modeAll.C.hListBox, WM_SETFONT, (WPARAM)hfontED, 0);

    for(i=0; i<sizeAlph; i++){
        char lpszStr[30];
        sprintf(lpszStr,"%c     %s   %c   %c   %c",i+'A',modeAll.C.CiphAlph[i],
                modeAll.C.trueKey[i],modeAll.C.falseKey1[i]?modeAll.C.falseKey1[i]:' ',
                modeAll.C.falseKey2[i]?modeAll.C.falseKey2[i]:' ');
        SendMessage(modeAll.C.hListBox,LB_ADDSTRING, NULL, (LPARAM)(LPCSTR)lpszStr);
    }
    //-----------------------------------------------------------------------------
    hLabelTMess=CreateWindow("Static", "Истинное сообщение", WS_CHILD | WS_VISIBLE
                                  , 330, 10, 400, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelTMess, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelFMess1=CreateWindow("Static", "Первое ложное сообщение", WS_CHILD | WS_VISIBLE
                                  , 330,60, 400, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelFMess1, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelFMess2=CreateWindow("Static", "Второе ложное сообщение", WS_CHILD | WS_VISIBLE
                                  , 330,110, 400, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelFMess2, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelCTMess=CreateWindow("Static", "Зашифрованное сообщение", WS_CHILD | WS_VISIBLE
                                  , 330,160, 400, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelCTMess, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelCFMess1=CreateWindow("Static", "Расшифрованное первое ложное сообщение", WS_CHILD | WS_VISIBLE
                                  , 330,210, 400, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelCFMess1, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelCFMess2=CreateWindow("Static", "Расшифрованное второе ложное сообщение", WS_CHILD | WS_VISIBLE
                                  , 330,260, 400, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelCFMess2, WM_SETFONT, (WPARAM)hfontST, 0);

    //------------------------------------------------------------------------------
    modeAll.C.hTrueMess=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                             | WS_GROUP | WS_TABSTOP , 330,30, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.C.hTrueMess,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.C.hTrueMess, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.C.hTrueMess, EM_SETLIMITTEXT, sizeMess-1, 0);
    SendMessage(modeAll.C.hTrueMess, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.C.trueMess);

    SetWindowPos(modeAll.C.hTrueMess,hwnd,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.C.hFalseMess1=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                             | WS_GROUP | WS_TABSTOP , 330,80, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.C.hFalseMess1,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.C.hFalseMess1, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.C.hFalseMess1, EM_SETLIMITTEXT, sizeMess-1, 0);
    SendMessage(modeAll.C.hFalseMess1, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.C.falseMess1);

    SetWindowPos(modeAll.C.hFalseMess1,modeAll.C.hTrueMess,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.C.hFalseMess2=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                             | WS_GROUP | WS_TABSTOP , 330,130, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.C.hFalseMess2,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.C.hFalseMess2, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.C.hFalseMess2, EM_SETLIMITTEXT, sizeMess-1, 0);
    SendMessage(modeAll.C.hFalseMess2, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.C.falseMess2);

    SetWindowPos(modeAll.C.hFalseMess2,modeAll.C.hFalseMess1,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.C.hCryptTrueMess=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                             | WS_GROUP | WS_TABSTOP , 330,180, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.C.hCryptTrueMess,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.C.hCryptTrueMess, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.C.hCryptTrueMess, EM_SETLIMITTEXT, sizeCiph-1, 0);
    SendMessage(modeAll.C.hCryptTrueMess, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.C.cryptMess);

    SetWindowPos(modeAll.C.hCryptTrueMess,modeAll.C.hFalseMess2,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    ///Вот эти эдиты под вопросом (не зашифровка, а расшифровка)
    modeAll.C.hDecryptFalseMess1=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                             | WS_GROUP | WS_TABSTOP , 330,230, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.C.hDecryptFalseMess1,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.C.hDecryptFalseMess1, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.C.hDecryptFalseMess1, EM_SETLIMITTEXT, sizeCiph-1, 0);
    SendMessage(modeAll.C.hDecryptFalseMess1, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.C.decryptFalseMess1);

    SetWindowPos(modeAll.C.hDecryptFalseMess1,modeAll.C.hCryptTrueMess,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.C.hDecryptFalseMess2=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                              | WS_GROUP | WS_TABSTOP, 330,280, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.C.hDecryptFalseMess2,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.C.hDecryptFalseMess2, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.C.hDecryptFalseMess2, EM_SETLIMITTEXT, sizeCiph-1, 0);
    SendMessage(modeAll.C.hDecryptFalseMess2, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.C.decryptFalseMess2);

    SetWindowPos(modeAll.C.hDecryptFalseMess2,modeAll.C.hDecryptFalseMess1,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

}
void createModeD(HWND hwnd,HFONT hfontST, HFONT hfontED){
    HWND hLabelTMess,hLabelContainer,hLabelCTMess;
    //--------------------------------------------------------------------
    HWND hLabelListAlph, hLabelListCiph;
    //----------------------------------------------------------------------------
    int i;
    modeAll.D.hwnd=hwnd;
    hLabelListAlph=CreateWindow("Static", "Алф.", WS_CHILD | WS_VISIBLE
                                  ,15,10,40,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListAlph, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelListCiph=CreateWindow("Static", "Шифр", WS_CHILD | WS_VISIBLE
                                  ,80,10,50,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListCiph, WM_SETFONT, (WPARAM)hfontST, 0);

    modeAll.D.hListBox=CreateWindow("ListBox",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_WANTKEYBOARDINPUT |
                               LBS_SORT | LBS_NOTIFY,15,30,300,540,hwnd,(HMENU)ID_ListBox,hInstance, NULL);
    SendMessage(modeAll.D.hListBox, WM_SETFONT, (WPARAM)hfontED, 0);

    for(i=0; i<sizeAlph; i++){
        char lpszStr[20];
        sprintf(lpszStr,"%c     %s",i+'A',modeAll.D.CiphAlph[i]);
        SendMessage(modeAll.D.hListBox,LB_ADDSTRING, NULL, (LPARAM)(LPCSTR)lpszStr);
    }
    //----------------------------------------------------------------
    hLabelTMess=CreateWindow("Static", "Сообщение", WS_CHILD | WS_VISIBLE
                                  , 330,10, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelTMess, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelContainer=CreateWindow("Static", "Контейнер", WS_CHILD | WS_VISIBLE
                                  , 330,60, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelContainer, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelCTMess=CreateWindow("Static", "Сокрытое сообщение", WS_CHILD | WS_VISIBLE
                                  , 330,110, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelCTMess, WM_SETFONT, (WPARAM)hfontST, 0);
    //---------------------------------------------------------------------------
    modeAll.D.hMess=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                              | WS_GROUP | WS_TABSTOP, 330,30, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.D.hMess,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.D.hMess, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.D.hMess, EM_SETLIMITTEXT, sizeMess-1, 0);
    SendMessage(modeAll.D.hMess, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.D.Message);

    SetWindowPos(modeAll.D.hMess,hwnd,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.D.hContainer=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER| ES_AUTOHSCROLL
                             | WS_GROUP | WS_TABSTOP , 330,80, 610, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.D.hContainer,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.D.hContainer, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.D.hContainer, EM_SETLIMITTEXT, sizeCont-1, 0);
    SendMessage(modeAll.D.hContainer, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.D.Container);

    SetWindowPos(modeAll.D.hContainer,modeAll.D.hMess,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.D.hHiddenMessage=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                            | WS_GROUP | WS_TABSTOP  , 330,130, 610, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.D.hHiddenMessage,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.D.hHiddenMessage, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.D.hHiddenMessage, EM_SETLIMITTEXT, sizeCiph-1, 0);
    SendMessage(modeAll.D.hHiddenMessage, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.D.cryptMess);

    SetWindowPos(modeAll.D.hHiddenMessage,modeAll.D.hContainer,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    //--------------------------------------------------------------------------------------
}

void createModeE(HWND hwnd,HFONT hfontST, HFONT hfontED){
    HWND hLabelTMess, hLabelCTMess;
    //----------------------------------------------------------------
    HWND hLabelListAlph, hLabelListCiph, hLabelLine;
    //----------------------------------------------------------------------------
    HWND hGBCont,hGBMode;
    int i, f,t;
    modeAll.E.hwnd=hwnd;
    char buf[1000];

    switchModeE(hwnd);

    hLabelListAlph=CreateWindow("Static", "Алф.", WS_CHILD | WS_VISIBLE
                                  ,15,10,40,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListAlph, WM_SETFONT, (WPARAM)hfontST, 0);
    hLabelListCiph=CreateWindow("Static", "Шифр", WS_CHILD | WS_VISIBLE
                                  ,80,10,50,20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelListCiph, WM_SETFONT, (WPARAM)hfontST, 0);

    modeAll.E.hListBox=CreateWindow("ListBox",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_WANTKEYBOARDINPUT |
                               LBS_SORT | LBS_NOTIFY,15,30,300,540,hwnd,(HMENU)ID_ListBox,hInstance, NULL);
    SendMessage(modeAll.E.hListBox, WM_SETFONT, (WPARAM)hfontED, 0);

    for(i=0; i<sizeAlph; i++){
        char lpszStr[20];
        sprintf(lpszStr,"%c     %s",i+'A',modeAll.E.CiphAlph[i]);
        SendMessage(modeAll.E.hListBox,LB_ADDSTRING, NULL, (LPARAM)(LPCSTR)lpszStr);
    }
    SendMessage(modeAll.E.hListBox,LB_SETCURSEL, (WPARAM)0, NULL);
    SendMessage(modeAll.E.hListBox,LB_GETTEXT, (WPARAM)0, (LPARAM)(int FAR *)buf);
    buf[1]='\0';
    buf[11]='\0';

    //-------------------------------------------------
    hLabelTMess=CreateWindow("Static", "Сообщение", WS_CHILD | WS_VISIBLE
                                  , 330,10, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelTMess, WM_SETFONT, (WPARAM)hfontST, 0);

    hLabelCTMess=CreateWindow("Static", "Сокрытое сообщение", WS_CHILD | WS_VISIBLE
                                  , 330,60, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelCTMess, WM_SETFONT, (WPARAM)hfontST, 0);
    //-------------------------------------------------------------------------
    modeAll.E.hMess=CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                              | WS_GROUP | WS_TABSTOP, 330,30, 200, 20, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.E.hMess, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.E.hMess, EM_SETLIMITTEXT, sizeMess-1, 0);
    SendMessage(modeAll.E.hMess, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.E.Message);

    SetWindowPos(modeAll.E.hMess,hwnd,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.E.hHiddenMessage=CreateWindow("RICHEDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL
                                , 330,80, 600, 25, hwnd, NULL, NULL, NULL);
    SendMessage(modeAll.E.hHiddenMessage,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.E.hHiddenMessage, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.E.hHiddenMessage, EM_SETLIMITTEXT, sizeCiph-1, 0);
    SendMessage(modeAll.E.hHiddenMessage, WM_SETTEXT, (WPARAM)hfontED, (LPARAM)modeAll.E.cryptMess);

    SetWindowPos(modeAll.E.hHiddenMessage,modeAll.E.hMess,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    //---------------------------------------------------------------------------
    f=WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON;

    modeAll.E.hContRB1=CreateWindow("Button", modeAll.E.Container[0], f | WS_GROUP | WS_TABSTOP,
                                 330,110, 600, 20, hwnd, (HMENU)ID_ContRB1, NULL, NULL);
    SendMessage(modeAll.E.hContRB1, WM_SETFONT, (WPARAM)hfontST, 0);
    SendMessage(modeAll.E.hContRB1, BM_SETCHECK , (WPARAM)(ID_ContRB1 == modeAll.E.nCont ? BST_CHECKED : BST_UNCHECKED), 0);

    SetWindowPos(modeAll.E.hContRB1,modeAll.E.hHiddenMessage,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);


    modeAll.E.hContRB2=CreateWindow("Button", modeAll.E.Container[1], f,
                                 330,130, 600, 20, hwnd, (HMENU)ID_ContRB2, NULL, NULL);
    SendMessage(modeAll.E.hContRB2, WM_SETFONT, (WPARAM)hfontST, 0);
    SendMessage(modeAll.E.hContRB2, BM_SETCHECK , (WPARAM)(ID_ContRB2 == modeAll.E.nCont ? BST_CHECKED : BST_UNCHECKED), 0);

    SetWindowPos(modeAll.E.hContRB2,modeAll.E.hContRB1,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);


    modeAll.E.hContRB3=CreateWindow("Button", modeAll.E.Container[2], f,
                                 330,150, 600, 20, hwnd, (HMENU)ID_ContRB3, NULL, NULL);
    SendMessage(modeAll.E.hContRB3, WM_SETFONT, (WPARAM)hfontST, 0);
    SendMessage(modeAll.E.hContRB3, BM_SETCHECK , (WPARAM)(ID_ContRB3 == modeAll.E.nCont ? BST_CHECKED : BST_UNCHECKED), 0);

    SetWindowPos(modeAll.E.hContRB3,modeAll.E.hContRB2,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);


    modeAll.E.hContRB4=CreateWindow("Button", modeAll.E.Container[3], f,
                                 330,170, 600, 20, hwnd, (HMENU)ID_ContRB4, NULL, NULL);
    SendMessage(modeAll.E.hContRB4, WM_SETFONT, (WPARAM)hfontST, 0);
    SendMessage(modeAll.E.hContRB4, BM_SETCHECK , (WPARAM)(ID_ContRB4 == modeAll.E.nCont ? BST_CHECKED : BST_UNCHECKED), 0);

    SetWindowPos(modeAll.E.hContRB4,modeAll.E.hContRB3,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    //-----------------------------------------------------------------
    hLabelLine=CreateWindow("Static", "------------------------------------------------------"
                            "-------------------------------------------------------------"
                            "-------------------------------------------------------------"
                            "-------------------------------------------------------------", WS_CHILD | WS_VISIBLE
                                  , 330,190, 500, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelTMess, WM_SETFONT, (WPARAM)hfontST, 0);

    modeAll.E.hModeRBA1=CreateWindow("Button", "A - Нижний регистр, B - Верхний регистр", f | WS_GROUP | WS_TABSTOP,
                                 330,210, 400, 20, hwnd, (HMENU)ID_modeRBA1, NULL, NULL);
    SendMessage(modeAll.E.hModeRBA1, WM_SETFONT, (WPARAM)hfontST, 0);
    SendMessage(modeAll.E.hModeRBA1, BM_SETCHECK , (WPARAM)(ID_modeRBA1 == modeAll.E.nMode ? BST_CHECKED : BST_UNCHECKED), 0);

    SetWindowPos(modeAll.E.hModeRBA1,modeAll.E.hContRB4,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.E.hModeRBA2=CreateWindow("Button", "A - Красный, B - Зеленый", f,
                                 330,230, 400, 20, hwnd, (HMENU)ID_modeRBA2, NULL, NULL);
    SendMessage(modeAll.E.hModeRBA2, WM_SETFONT, (WPARAM)hfontST, 0);
    SendMessage(modeAll.E.hModeRBA2, BM_SETCHECK, (WPARAM)(ID_modeRBA2 == modeAll.E.nMode ? BST_CHECKED : BST_UNCHECKED), 0);

    SetWindowPos(modeAll.E.hModeRBA2,modeAll.E.hModeRBA1,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.E.hModeRBA3=CreateWindow("Button", "A - Times New Roman, B - Arial", f,
                                 330,250, 600, 20, hwnd, (HMENU)ID_modeRBA3, NULL, NULL);
    SendMessage(modeAll.E.hModeRBA3, WM_SETFONT, (WPARAM)hfontST, 0);
    SendMessage(modeAll.E.hModeRBA3, BM_SETCHECK, (WPARAM)(ID_modeRBA3 == modeAll.E.nMode ? BST_CHECKED : BST_UNCHECKED), 0);

    SetWindowPos(modeAll.E.hModeRBA3,modeAll.E.hModeRBA2,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.E.hModeRBA4=CreateWindow("Button", "A - Полужирный шрифт, B - Курсивный шрифт", f,
                                 330,270, 600, 20, hwnd, (HMENU)ID_modeRBA4, NULL, NULL);
    SendMessage(modeAll.E.hModeRBA4, WM_SETFONT, (WPARAM)hfontST, 0);
    SendMessage(modeAll.E.hModeRBA4, BM_SETCHECK, (WPARAM)(ID_modeRBA4 == modeAll.E.nMode ? BST_CHECKED : BST_UNCHECKED), 0);

    SetWindowPos(modeAll.E.hModeRBA4,modeAll.E.hModeRBA3,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    hLabelLine=CreateWindow("Static","------------------------------------------------------"
                            "-------------------------------------------------------------"
                            "-------------------------------------------------------------"
                            "-------------------------------------------------------------", WS_CHILD | WS_VISIBLE
                                  , 330,290, 500, 20, hwnd, NULL, NULL, NULL);
    SendMessage(hLabelTMess, WM_SETFONT, (WPARAM)hfontST, 0);

    modeAll.E.hModeRBB1=CreateWindow("Button", "A - Верхний регистр, B - Нижний регистр", f,
                                 330,310, 400, 20, hwnd, (HMENU)ID_modeRBB1, NULL, NULL);
    SendMessage(modeAll.E.hModeRBB1, WM_SETFONT, (WPARAM)hfontST, 0);
    SendMessage(modeAll.E.hModeRBB1, BM_SETCHECK, (WPARAM)(ID_modeRBB1 == modeAll.E.nMode ? BST_CHECKED : BST_UNCHECKED), 0);

    SetWindowPos(modeAll.E.hModeRBB1,modeAll.E.hModeRBA4,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.E.hModeRBB2=CreateWindow("Button", "A - Зеленый, B - Красный", f,
                                 330,330, 400, 20, hwnd, (HMENU)ID_modeRBB2, NULL, NULL);
    SendMessage(modeAll.E.hModeRBB2, WM_SETFONT, (WPARAM)hfontST, 0);
    SendMessage(modeAll.E.hModeRBB2, BM_SETCHECK, (WPARAM)(ID_modeRBB2 == modeAll.E.nMode ? BST_CHECKED : BST_UNCHECKED), 0);

    SetWindowPos(modeAll.E.hModeRBB2,modeAll.E.hModeRBB1,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.E.hModeRBB3=CreateWindow("Button", "A - Arial, B - Times New Roman", f,
                                 330,350, 600, 20, hwnd, (HMENU)ID_modeRBB3, NULL, NULL);
    SendMessage(modeAll.E.hModeRBB3, WM_SETFONT, (WPARAM)hfontST, 0);
    SendMessage(modeAll.E.hModeRBB3, BM_SETCHECK, (WPARAM)(ID_modeRBB3 == modeAll.E.nMode ? BST_CHECKED : BST_UNCHECKED), 0);

    SetWindowPos(modeAll.E.hModeRBB3,modeAll.E.hModeRBB2,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    modeAll.E.hModeRBB4=CreateWindow("Button", "A - Курсивный шрифт, B - Полужирный шрифт", f,
                                 330,370, 600, 20, hwnd, (HMENU)ID_modeRBB4, NULL, NULL);
    SendMessage(modeAll.E.hModeRBB4, WM_SETFONT, (WPARAM)hfontST, 0);
    SendMessage(modeAll.E.hModeRBB4, BM_SETCHECK, (WPARAM)(ID_modeRBB4 == modeAll.E.nMode ? BST_CHECKED : BST_UNCHECKED), 0);

    SetWindowPos(modeAll.E.hModeRBB4,modeAll.E.hModeRBB3,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    //------------------------------------------------------------------------

    modeAll.E.hEditAlph=CreateWindow("Edit",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                            ,15,555,50,20,hwnd,(HMENU)ID_EditAlph,hInstance, NULL);
    SendMessage(modeAll.E.hEditAlph,EM_SETREADONLY,(WPARAM)(UINT)TRUE,NULL);
    SendMessage(modeAll.E.hEditAlph, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.E.hEditAlph, EM_SETLIMITTEXT, 1, 0);
    SendMessage(modeAll.E.hEditAlph, EM_REPLACESEL, NULL, (LPARAM)(LPCSTR)buf);

    modeAll.E.hEditCipher=CreateWindow("Edit",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
                          | WS_GROUP | WS_TABSTOP  ,75,555,60,20,hwnd,(HMENU)ID_EditCipher,hInstance, NULL);
    SendMessage(modeAll.E.hEditCipher, WM_SETFONT, (WPARAM)hfontED, 0);
    SendMessage(modeAll.E.hEditCipher, EM_SETLIMITTEXT, 5, 0);
    SendMessage(modeAll.E.hEditCipher, EM_REPLACESEL, NULL, (LPARAM)(LPCSTR)(buf+6));

    SetWindowPos(modeAll.E.hEditCipher,modeAll.E.hModeRBB4,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    //-----------------------------------------------------------------
    modeAll.E.hButtonReplace=CreateWindow("Button","Заменить", WS_CHILD | WS_VISIBLE| WS_GROUP | WS_TABSTOP
                                          ,235,555,80,30,hwnd,(HMENU)ButtRep,hInstance, NULL);
    SendMessage(modeAll.E.hButtonReplace, WM_SETFONT, (WPARAM)hfontST, 0);

    SetWindowPos(modeAll.E.hButtonReplace,modeAll.E.hEditCipher,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    //--------------------------------------------------------------------------------------------------------

    if(modeAll.E.nMode == ID_modeRBA2 || modeAll.E.nMode == ID_modeRBB2){
        CHARRANGE C;
        CHARFORMAT Color;
        Color.cbSize=sizeof(Color);
        Color.dwMask=CFM_COLOR;
        Color.dwEffects=0;
        Color.yHeight=0;
        Color.yOffset=0;
        //Color.crTextColor=0;
        Color.bCharSet=0;
        Color.bPitchAndFamily=0;
        //Color.szFaceName=NULL;
        for(i=0; i<strlen(modeAll.E.cryptMess); i++)
                if(modeAll.E.binaryMess[i]!='*'){
                    C.cpMin=i;
                    C.cpMax=i+1;
                    SendMessage(modeAll.E.hHiddenMessage,EM_EXSETSEL,NULL,(LPARAM)&C);
                    //MessageBox(hwnd,"Test","Test",MB_OK);
                    if(modeAll.E.nMode % 2 == 0 && modeAll.E.binaryMess[i] == '0'
                       || modeAll.E.nMode % 2 == 1 && modeAll.E.binaryMess[i] == '1'){
                        Color.crTextColor=RGB(200,0,0);
                        SendMessage(modeAll.E.hHiddenMessage,EM_SETCHARFORMAT,(WPARAM)SCF_SELECTION,(LPARAM)&Color);
                    }
                    else{
                        Color.crTextColor=RGB(0,200,0);
                        SendMessage(modeAll.E.hHiddenMessage,EM_SETCHARFORMAT,(WPARAM)SCF_SELECTION,(LPARAM)&Color);
                    }
                    C.cpMin=0;
                    C.cpMax=0;
                    SendMessage(modeAll.E.hHiddenMessage,EM_EXSETSEL,NULL,(LPARAM)&C);
                }
    }

    if(modeAll.E.nMode == ID_modeRBA3 || modeAll.E.nMode == ID_modeRBB3){
        CHARRANGE C;
        CHARFORMAT Color;
        Color.cbSize=sizeof(Color);
        Color.dwMask=CFM_FACE;
        Color.dwEffects=0;
        Color.yHeight=0;
        Color.yOffset=0;
        Color.crTextColor=0;
        Color.bCharSet=0;
        Color.bPitchAndFamily=0;
        //Color.szFaceName=NULL;

        for(i=0; i<strlen(modeAll.E.cryptMess); i++)
                if(modeAll.E.binaryMess[i]!='*'){
                    C.cpMin=i;
                    C.cpMax=i+1;
                    SendMessage(modeAll.E.hHiddenMessage,EM_EXSETSEL,NULL,(LPARAM)&C);
                    //MessageBox(hwnd,"Test","Test",MB_OK);
                    if(modeAll.E.nMode % 2 == 0 && modeAll.E.binaryMess[i] == '0'
                       || modeAll.E.nMode % 2 == 1 && modeAll.E.binaryMess[i] == '1'){
                        strcpy(Color.szFaceName,"Times New Roman");
                        SendMessage(modeAll.E.hHiddenMessage,EM_SETCHARFORMAT,(WPARAM)SCF_SELECTION,(LPARAM)&Color);
                    }
                    else{
                        strcpy(Color.szFaceName,"Arial");
                        SendMessage(modeAll.E.hHiddenMessage,EM_SETCHARFORMAT,(WPARAM)SCF_SELECTION,(LPARAM)&Color);
                    }
                    C.cpMin=0;
                    C.cpMax=0;
                    SendMessage(modeAll.E.hHiddenMessage,EM_EXSETSEL,NULL,(LPARAM)&C);
                }
    }

    if(modeAll.E.nMode == ID_modeRBA4 || modeAll.E.nMode == ID_modeRBB4){
        CHARRANGE C;
        CHARFORMAT Color;
        Color.cbSize=sizeof(Color);
        Color.dwMask=CFM_EFFECTS;
        //Color.dwEffects=0;
        Color.yHeight=0;
        Color.yOffset=0;
        Color.crTextColor=0;
        Color.bCharSet=0;
        Color.bPitchAndFamily=0;
        //Color.szFaceName=NULL;

        for(i=0; i<strlen(modeAll.E.cryptMess); i++)
                if(modeAll.E.binaryMess[i]!='*'){
                    C.cpMin=i;
                    C.cpMax=i+1;
                    SendMessage(modeAll.E.hHiddenMessage,EM_EXSETSEL,NULL,(LPARAM)&C);
                    //MessageBox(hwnd,"Test","Test",MB_OK);
                    if(modeAll.E.nMode % 2 == 0 && modeAll.E.binaryMess[i] == '0'
                       || modeAll.E.nMode % 2 == 1 && modeAll.E.binaryMess[i] == '1'){
                        Color.dwEffects=CFM_BOLD;
                        SendMessage(modeAll.E.hHiddenMessage,EM_SETCHARFORMAT,(WPARAM)SCF_SELECTION,(LPARAM)&Color);
                    }
                    else{
                        Color.dwEffects=CFM_ITALIC;
                        SendMessage(modeAll.E.hHiddenMessage,EM_SETCHARFORMAT,(WPARAM)SCF_SELECTION,(LPARAM)&Color);
                    }
                    C.cpMin=0;
                    C.cpMax=0;
                    SendMessage(modeAll.E.hHiddenMessage,EM_EXSETSEL,NULL,(LPARAM)&C);
                }
    }
}
