#include "cipherBacon.h"
HINSTANCE hInstance;
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
TCHAR szClassChildName[ ] = _T("Child window");
HFONT hfontST,hfontED;


char * messError[9] = {NULL,"Недопустимая длина сообщения!","Недопустимая длина ключа!","Недопустимый шифр!",
                "Некорректный ключ!","Некорректная пара ключей!", "Недопустимое истинное сообщение!",
                 "Недопустимое ложное сообщение!","Недопустимая длина контейнера!"};
char * messStatus[5] = {"Обучающая программа: Шифр Бэкона. Демо режим отрицаемого шифрования",
                        "Обучающая программа: Шифр Бэкона. Демо режим сокрытия сообщения",
                        "Обучающая программа: Шифр Бэкона. Режим генерации ложного ключа",
                        "Обучающая программа: Шифр Бэкона. Режим подбора ложного ключа",
                        "Обучающая программа: Шифр Бэкона. Режим сокрытия сообщения"};
//HWND EditCipher;
//----------------------------------------------------
int checkCiph(char* ciph){
    int i=0;
    if(strlen(ciph)!= 5)
        return 0;
    for(;i<5;i++)
        if(ciph[i]!= 'A' && ciph[i]!= 'B')
            return 0;
    return 1;
}

int LogicalMode(HWND hwnd){
    switch(modeAll.mode){
        case(mode_a):
            return mode_A(modeAll.A.CiphAlph, modeAll.A.trueKey, modeAll.A.trueMess, modeAll.A.falseMess,
                   modeAll.A.falseKey, modeAll.A.cryptMess);
        case(mode_b):
            return mode_B(modeAll.B.CiphAlph, modeAll.B.trueKey, modeAll.B.cryptMess, modeAll.B.falseKey,
                   modeAll.B.decrTrueMess,modeAll.B.decrFalseMess);
        case(mode_c):
            return mode_C(modeAll.C.CiphAlph, modeAll.C.trueKey, modeAll.C.falseKey1, modeAll.C.falseKey2,
                   modeAll.C.trueMess,modeAll.C.falseMess1,modeAll.C.falseMess2,modeAll.C.cryptMess,
                   modeAll.C.decryptFalseMess1, modeAll.C.decryptFalseMess2);
        case(mode_d):
            return mode_D(modeAll.D.CiphAlph, modeAll.D.Message, modeAll.D.Container,
                   modeAll.D.cryptMess);
        case(mode_e):
            return mode_E(modeAll.E.CiphAlph, modeAll.E.Message, modeAll.E.Container[modeAll.E.nCont-10000],
                   modeAll.E.binaryMess);
        break;
    }
    return 1;
}

//--------------------------------------
int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    setlocale(LC_ALL,"RUS");
    //MessageBox(HWND_DESKTOP,, "Внимание!", MB_OK);
    modeAll.E.nCont=ID_ContRB1;
    modeAll.E.nMode=ID_modeRBA1;
    HWND hwnd, hwndChild, Repeat;/* This is the handle for our window */
    HMENU hMenu, hPopUpMenu;
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl, winclChild;        /* Data structure for the windowclass */
    HINSTANCE hRTFLib;
    hRTFLib = LoadLibrary("RICHED32.DLL");

    Repeat=FindWindow(szClassName,NULL);
    if(Repeat != NULL){
        if(IsIconic(Repeat))
            ShowWindow(Repeat,SW_SHOWDEFAULT);
        return 0;
    }


    if(GetCurrentDirectory(244,FileName) == 0){
        MessageBox(HWND_DESKTOP,"Не существует текущая дирректория", "Ошибка!", MB_OK);
        return 0;
    }
    strcpy(HelpFile,FileName);
    strcat(FileName,"\\config.ini");
    strcat(HelpFile,"\\hlp.pdf");
    hfontST=CreateFont(18,0, 0, 0, 0, FALSE, 0, 0, RUSSIAN_CHARSET, 0, 0, 0, 0, "Arial");
    if(hfontST==NULL){
        MessageBox(HWND_DESKTOP,"Шрифт не создан","Внимание!", MB_OK);
        return 0;
    }
    hfontED=CreateFont(20,0, 0, 0, 0,FALSE, 0, 0, RUSSIAN_CHARSET, 0, 0, 0, 0, "Courier New");
    if(hfontED==NULL){
        MessageBox(HWND_DESKTOP,"Шрифт не создан","Внимание!", MB_OK);
        return 0;
    }
    if(hRTFLib==NULL){
        MessageBox(HWND_DESKTOP,"Библиотека RICHED32.DLL не найдена!","Внимание!", MB_OK);
        return 0;
    }
    hMenu=CreateMenu();
    hPopUpMenu=CreatePopupMenu();

    AppendMenu(hPopUpMenu,MF_ENABLED,ID_MenuFileOpen,"Открыть\t\t\tCtrl-O");
    AppendMenu(hPopUpMenu,MF_ENABLED,ID_MenuFileSave,"Сохранить\t\t\tCtrl-S");
    AppendMenu(hPopUpMenu,MF_ENABLED,ID_MenuFileSaveAs,"Сохранить как...\t\t\tCtrl-Shift-S");
    AppendMenu(hPopUpMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hPopUpMenu,MF_ENABLED,ID_MenuExit,"Выход\t\t\tCtrl-W");
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hPopUpMenu,"&Файл");
    AppendMenu(hMenu,MF_ENABLED,ID_MenuHelp,"&Справка \t\t\tF1");
    AppendMenu(hMenu,MF_ENABLED,ID_MenuAbout,"&О программе \t\t\tCtrl-A");
    SetMenu(HWND_DESKTOP, hMenu);

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    hInstance=hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 32,32,0);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;
    if(ReadIniFileA(FileName) == 0){
        MessageBox(HWND_DESKTOP,"Некорректный конфигурационный файл или его отсутствие!","Ошибка!",MB_OK);
        return 0;
    }
    if(ReadIniFileB(FileName) == 0){
        MessageBox(HWND_DESKTOP,"Некорректный конфигурационный файл или его отсутствие!","Ошибка!",MB_OK);
        return 0;
    }
    if(ReadIniFileC(FileName) == 0){
        MessageBox(HWND_DESKTOP,"Некорректный конфигурационный файл или его отсутствие!","Ошибка!",MB_OK);
        return 0;
    }
    if(ReadIniFileD(FileName) == 0){
        MessageBox(HWND_DESKTOP,"Некорректный конфигурационный файл или его отсутствие!","Ошибка!",MB_OK);
        return 0;
    }
    if(ReadIniFileE(FileName) == 0){
        MessageBox(HWND_DESKTOP,"Некорректный конфигурационный файл или его отсутствие!","Ошибка!",MB_OK);
        return 0;
    }
     /* The childe window*/
    winclChild.hInstance = hThisInstance;
    winclChild.lpszClassName = szClassChildName;
    winclChild.lpfnWndProc = WindowChildProcedure;      /* This function is called by windows */
    winclChild.style = 0;                 /* Catch double-clicks */
    winclChild.cbSize = sizeof (WNDCLASSEX);

    winclChild.hIcon = NULL;
    winclChild.hIconSm = NULL;
    winclChild.hCursor = NULL;
    winclChild.lpszMenuName = NULL;                 /* No menu */
    winclChild.cbClsExtra = 0;                      /* No extra bytes after the window class */
    winclChild.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    winclChild.hbrBackground = NULL;
    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&winclChild))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Обучающая программа: Шифр Бэкона"),       /* Title Text */
           WS_MAXIMIZEBOX^WS_THICKFRAME^WS_OVERLAPPEDWINDOW , /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           1000,                 /* The programs width */
           800,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           hMenu,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    int rc;
    while (rc = GetMessage (&messages, NULL, 0, 0))
    {
        if(rc == -1)
            break;
        if (!TranslateAccelerator(hwnd, hAccel, &messages)){
            if(!IsDialogMessage(GetParent(messages.hwnd),&messages)){
                /* Translate virtual-key messages into character messages */
                TranslateMessage(&messages);
                /* Send message to WindowProcedure */
                DispatchMessage(&messages);
            }
        }
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

LRESULT CALLBACK WindowChildProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

    static HDC hdc;
    int i;
    char buf[1000], ciph[sizeCiphAlph], tk[10], fk[10];

    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            //hfontST=CreateFont(18,0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");
            switch(modeAll.mode){
                case mode_a:
                    createModeA(hwnd,hfontST,hfontED);
                break;
                case mode_b:
                    createModeB(hwnd,hfontST,hfontED);
                break;
                case mode_c:
                    createModeC(hwnd,hfontST,hfontED);
                break;
                case mode_d:
                    createModeD(hwnd,hfontST,hfontED);
                break;
                case mode_e:
                    createModeE(hwnd,hfontST,hfontED);
                break;
            }
            break;
        case WM_COMMAND:
                      // Проверяем, не щелкнули ли на первой группе радиокнопок.
            switch (LOWORD(wParam)) {
                    case(ButtRep):
                        if(HIWORD(wParam) == BN_CLICKED){
                            switch(modeAll.mode){
                                case(mode_a):
                                    *(int*)ciph=sizeCiphAlph;
                                    i=(int)SendMessage(modeAll.A.hEditCipher,EM_GETLINE,(WPARAM)(UINT)0,(LPARAM)(LPSTR)ciph);
                                    ciph[i]='\0';//checkCiph(tk)

                                    if(checkCiph(ciph) == 0){
                                        MessageBox(hwnd,"Некорректный шифр!","Ошибка",MB_OK);
                                        break;
                                    }

                                    *(int*)tk=1;
                                    i=(int)SendMessage(modeAll.A.hEditTrueKey,EM_GETLINE,(WPARAM)(UINT)0,(LPARAM)(LPSTR)tk);
                                    tk[i]='\0';
                                    if(tk[0]!='A' && tk[0]!='B'){
                                        MessageBox(hwnd,"Некорректный истинный ключ!","Ошибка",MB_OK);
                                        break;
                                    }

                                    i=(int)SendMessage(modeAll.A.hListBox,LB_GETCURSEL,NULL,NULL);
                                    SendMessage(modeAll.A.hListBox,LB_GETTEXT, (WPARAM)i, (LPARAM)(int FAR *)buf);
                                    strcpy((buf+6),ciph);
                                    strcat(buf,"   ");
                                    strcat(buf,tk);
                                    strcat(buf,"   ");
                                    strcat(buf," ");

                                    SendMessage(modeAll.A.hListBox,LB_DELETESTRING, (WPARAM)i, NULL);
                                    SendMessage(modeAll.A.hListBox,LB_INSERTSTRING, (WPARAM)i, (LPARAM)(int FAR *)buf);
                                    if(++i==sizeAlph)
                                        i=0;
                                    SendMessage(modeAll.A.hListBox,LB_SETCURSEL, (WPARAM)i, NULL);
                                    SendMessage(hwnd,WM_COMMAND,MAKEWPARAM(ID_ListBox,LBN_SELCHANGE),(LPARAM)modeAll.A.hListBox);
                                break;
                                case(mode_b):
                                    *(int*)ciph=sizeCiphAlph;
                                    i=(int)SendMessage(modeAll.B.hEditCipher,EM_GETLINE,(WPARAM)(UINT)0,(LPARAM)(LPSTR)ciph);
                                    ciph[i]='\0';//checkCiph(tk)
                                    if(checkCiph(ciph) == 0){
                                        MessageBox(hwnd,"Некорректный шифр!","Ошибка",MB_OK);
                                        break;
                                    }

                                    *(int*)tk=1;
                                    i=(int)SendMessage(modeAll.B.hEditTrueKey,EM_GETLINE,(WPARAM)(UINT)0,(LPARAM)(LPSTR)tk);
                                    tk[i]='\0';
                                    if(tk[0]!='A' && tk[0]!='B'){
                                        MessageBox(hwnd,"Некорректный истинный ключ!","Ошибка",MB_OK);
                                        break;
                                    }
                                    *(int*)fk=1;
                                    i=(int)SendMessage(modeAll.B.hEditFalseKey,EM_GETLINE,(WPARAM)(UINT)0,(LPARAM)(LPSTR)fk);
                                    fk[i]='\0';
                                    if(fk[0]!='A' && fk[0]!='B'){
                                        MessageBox(hwnd,"Некорректный ложный ключ!","Ошибка",MB_OK);
                                        break;
                                    }

                                    i=(int)SendMessage(modeAll.B.hListBox,LB_GETCURSEL,NULL,NULL);
                                    sprintf(buf, "%c     %s   %c   %c",i+'A',ciph,tk[0],fk[0]);
                                    SendMessage(modeAll.B.hListBox,LB_DELETESTRING, (WPARAM)i, NULL);
                                    SendMessage(modeAll.B.hListBox,LB_INSERTSTRING, (WPARAM)i, (LPARAM)(int FAR *)buf);
                                    if(++i==sizeAlph)
                                        i=0;
                                    SendMessage(modeAll.B.hListBox,LB_SETCURSEL, (WPARAM)i, NULL);
                                    SendMessage(hwnd,WM_COMMAND,MAKEWPARAM(ID_ListBox,LBN_SELCHANGE),(LPARAM)modeAll.B.hListBox);
                                break;
                                case(mode_e):
                                    *(int*)ciph=sizeCiphAlph;
                                    i=(int)SendMessage(modeAll.E.hEditCipher,EM_GETLINE,(WPARAM)(UINT)0,(LPARAM)(LPSTR)ciph);
                                    ciph[i]='\0';//checkCiph(tk)
                                    if(checkCiph(ciph) == 0){
                                        MessageBox(hwnd,"Некорректный шифр!","Ошибка",MB_OK);
                                        break;
                                    }

                                    i=(int)SendMessage(modeAll.E.hListBox,LB_GETCURSEL,NULL,NULL);
                                    SendMessage(modeAll.E.hListBox,LB_GETTEXT, (WPARAM)i, (LPARAM)(int FAR *)buf);
                                    strcpy((buf+6),ciph);
                                    strcat(buf,"         ");

                                    SendMessage(modeAll.E.hListBox,LB_DELETESTRING, (WPARAM)i, NULL);
                                    SendMessage(modeAll.E.hListBox,LB_INSERTSTRING, (WPARAM)i, (LPARAM)(int FAR *)buf);
                                    if(++i==sizeAlph)
                                        i=0;
                                    SendMessage(modeAll.E.hListBox,LB_SETCURSEL, (WPARAM)i, NULL);
                                    SendMessage(hwnd,WM_COMMAND,MAKEWPARAM(ID_ListBox,LBN_SELCHANGE),(LPARAM)modeAll.E.hListBox);
                                break;
                            }

                        }

                    break;
                    case(ID_ListBox):
                        switch(modeAll.mode){
                            case(mode_a):
                                if(HIWORD(wParam) == LBN_SELCHANGE){
                                    i=(int)SendMessage((HWND)lParam,LB_GETCURSEL,NULL,NULL);
                                    SendMessage((HWND)lParam,LB_GETTEXT, (WPARAM)i, (LPARAM)(int FAR *)buf);
                                    buf[1]='\0';
                                    buf[11]='\0';
                                    buf[15]='\0';
                                    SendMessage(modeAll.A.hEditAlph,EM_SETSEL,(WPARAM)(UINT)0,MAKELPARAM(0, -1));
                                    SendMessage(modeAll.A.hEditAlph,EM_REPLACESEL,NULL,(LPARAM)(LPCSTR)buf);

                                    SendMessage(modeAll.A.hEditCipher,EM_SETSEL,(WPARAM)(UINT)0,MAKELPARAM(0, -1));
                                    SendMessage(modeAll.A.hEditCipher,EM_REPLACESEL,NULL,(LPARAM)(LPCSTR)(buf+6));

                                    SendMessage(modeAll.A.hEditTrueKey,EM_SETSEL,(WPARAM)(UINT)0,MAKELPARAM(0, -1));
                                    SendMessage(modeAll.A.hEditTrueKey,EM_REPLACESEL,NULL,(LPARAM)(LPCSTR)(buf+14));

                                }
                            break;
                            case(mode_b):
                                if(HIWORD(wParam) == LBN_SELCHANGE){
                                    i=(int)SendMessage((HWND)lParam,LB_GETCURSEL,NULL,NULL);
                                    SendMessage((HWND)lParam,LB_GETTEXT, (WPARAM)i, (LPARAM)(int FAR *)buf);
                                    buf[1]='\0';
                                    buf[11]='\0';
                                    buf[15]='\0';
                                    SendMessage(modeAll.B.hEditAlph,EM_SETSEL,(WPARAM)(UINT)0,MAKELPARAM(0, -1));
                                    SendMessage(modeAll.B.hEditAlph,EM_REPLACESEL,NULL,(LPARAM)(LPCSTR)buf);

                                    SendMessage(modeAll.B.hEditCipher,EM_SETSEL,(WPARAM)(UINT)0,MAKELPARAM(0, -1));
                                    SendMessage(modeAll.B.hEditCipher,EM_REPLACESEL,NULL,(LPARAM)(LPCSTR)(buf+6));

                                    SendMessage(modeAll.B.hEditTrueKey,EM_SETSEL,(WPARAM)(UINT)0,MAKELPARAM(0, -1));
                                    SendMessage(modeAll.B.hEditTrueKey,EM_REPLACESEL,NULL,(LPARAM)(LPCSTR)(buf+14));

                                    SendMessage(modeAll.B.hEditFalseKey,EM_SETSEL,(WPARAM)(UINT)0,MAKELPARAM(0, -1));
                                    SendMessage(modeAll.B.hEditFalseKey,EM_REPLACESEL,NULL,(LPARAM)(LPCSTR)(buf+18));

                                }
                            break;

                            case(mode_c):
                                case(mode_d):
                                if(HIWORD(wParam) == LBN_SELCHANGE){
                                    i=(int)SendMessage((HWND)lParam,LB_SETCURSEL,(WPARAM)-1,NULL);
                                }

                            break;

                            case(mode_e):
                                if(HIWORD(wParam) == LBN_SELCHANGE){
                                    i=(int)SendMessage((HWND)lParam,LB_GETCURSEL,NULL,NULL);
                                    SendMessage((HWND)lParam,LB_GETTEXT, (WPARAM)i, (LPARAM)(int FAR *)buf);
                                    buf[1]='\0';
                                    buf[11]='\0';

                                    SendMessage(modeAll.E.hEditAlph,EM_SETSEL,(WPARAM)(UINT)0,MAKELPARAM(0, -1));
                                    SendMessage(modeAll.E.hEditAlph,EM_REPLACESEL,NULL,(LPARAM)(LPCSTR)buf);

                                    SendMessage(modeAll.E.hEditCipher,EM_SETSEL,(WPARAM)(UINT)0,MAKELPARAM(0, -1));
                                    SendMessage(modeAll.E.hEditCipher,EM_REPLACESEL,NULL,(LPARAM)(LPCSTR)(buf+6));
                                }
                            break;

                        }


                    break;
                    //LBS_NOTIFY
            }
        break;
       /* case WM_MODE_A:
            for(i=0;i<27;i++){
                modeAllAlph[i]=((char **)wParam)[i];
            }
        break;*/
        case WM_DESTROY:
            switch(modeAll.mode){
                case(mode_a):
                    strcpy(modeAll.A.trueKey,"");
                    strcpy(modeAll.A.falseKey,"");
                    for(i=0; i<sizeAlph; i++){
                        SendMessage(modeAll.A.hListBox,LB_GETTEXT, (WPARAM)i, (LPARAM)(int FAR *)buf);
                        buf[1]='\0';
                        buf[11]='\0';
                        buf[15]='\0';
                        strcpy(modeAll.A.CiphAlph[i],buf+6);
                        strncat(modeAll.A.trueKey,buf+14,1);
                        strncat(modeAll.A.falseKey,buf+18,1);
                    }
                    *(int*)modeAll.A.trueMess=sizeMess;
                    i=(int)SendMessage(modeAll.A.hTrueMess, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.A.trueMess);
                    modeAll.A.trueMess[i]='\0';

                    *(int*)modeAll.A.falseMess=sizeMess;
                    i=(int)SendMessage(modeAll.A.hFalseMess, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.A.falseMess);
                    modeAll.A.falseMess[i]='\0';

                    *(int*)modeAll.A.cryptMess=sizeCiph;
                    i=(int)SendMessage(modeAll.A.hCryptMess, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.A.cryptMess);
                    modeAll.A.cryptMess[i]='\0';

                break;
                case(mode_b):
                    strcpy(modeAll.B.trueKey,"");
                    strcpy(modeAll.B.falseKey,"");
                    for(i=0; i<sizeAlph; i++){
                        SendMessage(modeAll.B.hListBox,LB_GETTEXT, (WPARAM)i, (LPARAM)(int FAR *)buf);
                        buf[1]='\0';
                        buf[11]='\0';
                        buf[15]='\0';
                        strcpy(modeAll.B.CiphAlph[i],buf+6);
                        strncat(modeAll.B.trueKey,buf+14,1);
                        strncat(modeAll.B.falseKey,buf+18,1);
                    }
                    *(int*)modeAll.B.cryptMess=sizeCiph;
                    i=(int)SendMessage(modeAll.B.hCiphMess, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.B.cryptMess);
                    modeAll.B.cryptMess[i]='\0';


                    *(int*)modeAll.B.decrTrueMess=sizeMess;
                    i=(int)SendMessage(modeAll.B.hDecryptTrueMess, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.B.decrTrueMess);
                    modeAll.B.decrTrueMess[i]='\0';

                    *(int*)modeAll.B.decrFalseMess=sizeMess;
                    i=(int)SendMessage(modeAll.B.hDecryptFalseMess, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.B.decrFalseMess);
                    modeAll.B.decrFalseMess[i]='\0';
                break;
                case(mode_c):

                    *(int*)modeAll.C.trueMess=sizeMess;
                    i=(int)SendMessage(modeAll.C.hTrueMess, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.C.trueMess);
                    modeAll.C.trueMess[i]='\0';

                    *(int*)modeAll.C.falseMess1=sizeMess;
                    i=(int)SendMessage(modeAll.C.hFalseMess1, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.C.falseMess1);
                    modeAll.C.falseMess1[i]='\0';

                    *(int*)modeAll.C.falseMess2=sizeMess;
                    i=(int)SendMessage(modeAll.C.hFalseMess2, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.C.falseMess2);
                    modeAll.C.falseMess2[i]='\0';

                    *(int*)modeAll.C.cryptMess=sizeCiph;
                    i=(int)SendMessage(modeAll.C.hCryptTrueMess, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.C.cryptMess);
                    modeAll.C.cryptMess[i]='\0';

                    *(int*)modeAll.C.decryptFalseMess1=sizeMess;
                    i=(int)SendMessage(modeAll.C.hDecryptFalseMess1, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.C.decryptFalseMess1);
                    modeAll.C.decryptFalseMess1[i]='\0';

                    *(int*)modeAll.C.decryptFalseMess2=sizeMess;
                    i=(int)SendMessage(modeAll.C.hDecryptFalseMess2, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.C.decryptFalseMess2);
                    modeAll.C.decryptFalseMess2[i]='\0';

                break;
                case(mode_d):
                    *(int*)modeAll.D.Message=sizeMess;
                    i=(int)SendMessage(modeAll.D.hMess, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.D.Message);
                    modeAll.D.Message[i]='\0';

                    *(int*)modeAll.D.Container=sizeCont;
                    i=(int)SendMessage(modeAll.D.hContainer, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.D.Container);
                    modeAll.D.Container[i]='\0';

                    *(int*)modeAll.D.cryptMess=sizeCont;
                    i=(int)SendMessage(modeAll.D.hHiddenMessage, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.D.cryptMess);
                    modeAll.D.cryptMess[i]='\0';

                break;
                case(mode_e):
                    for(i=0; i<sizeAlph; i++){
                        SendMessage(modeAll.E.hListBox,LB_GETTEXT, (WPARAM)i, (LPARAM)(int FAR *)buf);
                        buf[1]='\0';
                        buf[11]='\0';
                        strcpy(modeAll.E.CiphAlph[i],buf+6);
                    }
                    *(int*)modeAll.E.Message=sizeMess;
                    i=(int)SendMessage(modeAll.E.hMess, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.E.Message);
                    modeAll.E.Message[i]='\0';

                    *(int*)modeAll.E.cryptMess=sizeCont;
                    i=(int)SendMessage(modeAll.E.hHiddenMessage, EM_GETLINE, (WPARAM)(UINT)0,(LPARAM)(LPSTR)modeAll.E.cryptMess);
                    modeAll.E.cryptMess[i]='\0';

                    strcpy(modeAll.E.binaryMess,"");
                    strcpy(modeAll.E.cryptMess,"");

                    if(SendMessage(modeAll.E.hContRB1,BM_GETCHECK ,0,0) == BST_CHECKED)
                        modeAll.E.nCont=ID_ContRB1;
                    if(SendMessage(modeAll.E.hContRB2,BM_GETCHECK ,0,0) == BST_CHECKED)
                        modeAll.E.nCont=ID_ContRB2;
                    if(SendMessage(modeAll.E.hContRB3,BM_GETCHECK ,0,0) == BST_CHECKED)
                        modeAll.E.nCont=ID_ContRB3;
                    if(SendMessage(modeAll.E.hContRB4,BM_GETCHECK ,0,0) == BST_CHECKED)
                        modeAll.E.nCont=ID_ContRB4;

                    if(SendMessage(modeAll.E.hModeRBA1,BM_GETCHECK ,0,0) == BST_CHECKED)
                        modeAll.E.nMode=ID_modeRBA1;
                    if(SendMessage(modeAll.E.hModeRBA2,BM_GETCHECK ,0,0) == BST_CHECKED)
                        modeAll.E.nMode=ID_modeRBA2;
                    if(SendMessage(modeAll.E.hModeRBA3,BM_GETCHECK ,0,0) == BST_CHECKED)
                        modeAll.E.nMode=ID_modeRBA3;
                    if(SendMessage(modeAll.E.hModeRBA4,BM_GETCHECK ,0,0) == BST_CHECKED)
                        modeAll.E.nMode=ID_modeRBA4;

                    if(SendMessage(modeAll.E.hModeRBB1,BM_GETCHECK ,0,0) == BST_CHECKED)
                        modeAll.E.nMode=ID_modeRBB1;
                    if(SendMessage(modeAll.E.hModeRBB2,BM_GETCHECK ,0,0) == BST_CHECKED)
                        modeAll.E.nMode=ID_modeRBB2;
                    if(SendMessage(modeAll.E.hModeRBB3,BM_GETCHECK ,0,0) == BST_CHECKED)
                        modeAll.E.nMode=ID_modeRBB3;
                    if(SendMessage(modeAll.E.hModeRBB4,BM_GETCHECK ,0,0) == BST_CHECKED)
                        modeAll.E.nMode=ID_modeRBB4;


                break;
            }
        break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    static HWND hChild;
    TC_ITEM tabitem;
    static HWND hTControl, hFileLabel, hFileButton;
    static HWND hStatusBar, hListView;
    static MENUITEMINFO hMenuItemInfo;
    int wmId, wmEvent;
    static HDC hdc;
    int i;
    OPENFILENAME ofn;
    ACCEL AccelButt[12]={
        {FCONTROL | FVIRTKEY,'O',ID_MenuFileOpen},
        {FCONTROL | FVIRTKEY |FSHIFT ,'S',ID_MenuFileSaveAs},
        {FCONTROL | FVIRTKEY ,'S',ID_MenuFileSave},
        {FCONTROL | FVIRTKEY,'W',ID_MenuExit},
        {FCONTROL | FVIRTKEY,'A',ID_MenuAbout},
        {FCONTROL | FVIRTKEY,'1',ID_mode_c},
        {FCONTROL | FVIRTKEY,'2',ID_mode_d},
        {FCONTROL | FVIRTKEY,'3',ID_mode_a},
        {FCONTROL | FVIRTKEY,'4',ID_mode_b},
        {FCONTROL | FVIRTKEY,'5',ID_mode_e},
        {FVIRTKEY, VK_F1, ID_MenuHelp},
        {FCONTROL | FVIRTKEY,VK_RETURN,ButtExec}
    };
    static NMHDR nmhdr;

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = FileName;
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not
    // use the contents of szFile to initialize itself.
    //ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 255;
    ofn.lpstrFilter = "Config files(*.ini)\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;       // common dialog box structure
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            hAccel = CreateAcceleratorTable((ACCEL*)&AccelButt, 12);
            if(hAccel == NULL){
                MessageBox(hwnd, "Ошибка с акселератором!", "Ошибка", MB_OK);
                return -1;
            }
            //----------------------------------------------------------------
            hTControl = CreateWindow(WC_TABCONTROL, NULL, WS_CHILD | WS_VISIBLE, 0, 0,
                                     1000, 750, hwnd, NULL, hInstance, NULL);
            tabitem.mask = TCIF_TEXT;

            tabitem.pszText = "Отрицаемое шифрование (Д)";
            tabitem.iImage = mode_c;
            SendMessage(hTControl, TCM_INSERTITEM, mode_c+1, &tabitem);

            tabitem.pszText = "Сокрытие сообщение (Д)";
            tabitem.iImage = mode_d;
            SendMessage(hTControl, TCM_INSERTITEM, mode_d+1, &tabitem);

            tabitem.pszText = "Генерация ложного ключа";
            tabitem.iImage = mode_a;
            SendMessage(hTControl, TCM_INSERTITEM, mode_a+1, &tabitem);

            tabitem.pszText = "Подбор ложного ключа";
            tabitem.iImage = mode_b;
            SendMessage(hTControl, TCM_INSERTITEM, mode_b+1, &tabitem);

            tabitem.pszText = "Сокрытие сообщения";
            tabitem.iImage = mode_e;
            SendMessage(hTControl, TCM_INSERTITEM, mode_e+1, &tabitem);
            SendMessage(hTControl, WM_SETFONT, (WPARAM)hfontST, 0);

            hButtonExec=CreateWindow("Button","Выполнить", WS_CHILD | WS_VISIBLE
                            ,850,650,90,40,hwnd,(HMENU)ButtExec,hInstance, NULL);
            SendMessage(hButtonExec, WM_SETFONT, (WPARAM)hfontST, 0);


            //--------------------------------------------------------------
            hStatusBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE, messStatus[mode_c], hwnd, 0);
            SendMessage(hStatusBar, WM_SIZE, 0, 1000);
            ///--------------------------------------------------------------------

            hChild=CreateWindowEx(0,                   /* Extended possibilites for variation */
               szClassChildName,         /* Classname */
               _T("Обучающая программа: Шифр Бэкона"),       /* Title Text */
               WS_CHILD | WS_VISIBLE , /* default window */
               0,       /* Windows decides the position */
               35,       /* where the window ends up on the screen */
               1000,                 /* The programs width */
               600,                 /* and height in pixels */
               hwnd,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hInstance,       /* Program Instance handler */
               NULL      );

            break;
        case WM_COMMAND:
            wmId    = LOWORD(wParam);
            wmEvent = HIWORD(wParam);
            if(wmEvent == BN_CLICKED || wmEvent == 1){
                switch (LOWORD(wParam)) {
                    case(ID_mode_c):
                    case(ID_mode_d):
                    case(ID_mode_a):
                    case(ID_mode_b):
                    case(ID_mode_e):
                        nmhdr.hwndFrom=hTControl;
                        nmhdr.idFrom=0;
                        nmhdr.code=TCN_SELCHANGE;
                        SendMessage(hTControl,TCM_SETCURSEL,(WPARAM)LOWORD(wParam)-5000,0);
                        SendMessage(hwnd,WM_NOTIFY,0,(LPARAM)&nmhdr);
                    break;
                    case(ID_MenuFileOpen):
                        if(GetOpenFileName(&ofn)==FALSE)
                            break;
                        DestroyWindow(hChild);
                        if(ReadIniFileA(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Некорректный конфигурационный файл или его отсутствие!","Ошибка!",MB_OK);
                        if(ReadIniFileB(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Некорректный конфигурационный файл или его отсутствие!","Ошибка!",MB_OK);
                        if(ReadIniFileC(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Некорректный конфигурационный файл или его отсутствие!","Ошибка!",MB_OK);
                        if(ReadIniFileD(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Некорректный конфигурационный файл или его отсутствие!","Ошибка!",MB_OK);
                        if(ReadIniFileE(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Некорректный конфигурационный файл или его отсутствие!","Ошибка!",MB_OK);

                        hChild=CreateWindowEx(0, /* Extended possibilites for variation */
                                               szClassChildName,         /* Classname */
                                               _T("Обучающая программа: Шифр Бэкона"),       /* Title Text */
                                               WS_CHILD | WS_VISIBLE , /* default window */
                                               0,       /* Windows decides the position */
                                               35,       /* where the window ends up on the screen */
                                               1000,                 /* The programs width */
                                               600,                 /* and height in pixels */
                                               hwnd,        /* The window is a child-window to desktop */
                                               NULL,                /* No menu */
                                               hInstance,       /* Program Instance handler */
                                               NULL      );

                    break;

                    case(ID_MenuFileSave):
                        DestroyWindow(hChild);
                        if(WriteIniFileA(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Ошибка записи!","Ошибка!",MB_OK);
                        if(WriteIniFileB(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Ошибка записи!","Ошибка!",MB_OK);
                        if(WriteIniFileC(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Ошибка записи!","Ошибка!",MB_OK);
                        if(WriteIniFileD(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Ошибка записи!","Ошибка!",MB_OK);
                        if(WriteIniFileE(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Ошибка записи!","Ошибка!",MB_OK);
                        hChild=CreateWindowEx(0, /* Extended possibilites for variation */
                                               szClassChildName,         /* Classname */
                                               _T("Обучающая программа: Шифр Бэкона"),       /* Title Text */
                                               WS_CHILD | WS_VISIBLE , /* default window */
                                               0,       /* Windows decides the position */
                                               35,       /* where the window ends up on the screen */
                                               1000,                 /* The programs width */
                                               600,                 /* and height in pixels */
                                               hwnd,        /* The window is a child-window to desktop */
                                               NULL,                /* No menu */
                                               hInstance,       /* Program Instance handler */
                                               NULL      );
                    break;

                    case(ID_MenuFileSaveAs):
                        ofn.Flags=OFN_OVERWRITEPROMPT;
                        if(GetSaveFileName(&ofn)==FALSE)
                            break;
                        DestroyWindow(hChild);
                        if(WriteIniFileA(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Ошибка записи!","Ошибка!",MB_OK);
                        if(WriteIniFileB(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Ошибка записи!","Ошибка!",MB_OK);
                        if(WriteIniFileC(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Ошибка записи!","Ошибка!",MB_OK);
                        if(WriteIniFileD(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Ошибка записи!","Ошибка!",MB_OK);
                        if(WriteIniFileE(FileName) == 0)
                            MessageBox(HWND_DESKTOP,"Ошибка записи!","Ошибка!",MB_OK);
                        hChild=CreateWindowEx(0, /* Extended possibilites for variation */
                                               szClassChildName,         /* Classname */
                                               _T("Обучающая программа: Шифр Бэкона"),       /* Title Text */
                                               WS_CHILD | WS_VISIBLE , /* default window */
                                               0,       /* Windows decides the position */
                                               35,       /* where the window ends up on the screen */
                                               1000,                 /* The programs width */
                                               600,                 /* and height in pixels */
                                               hwnd,        /* The window is a child-window to desktop */
                                               NULL,                /* No menu */
                                               hInstance,       /* Program Instance handler */
                                               NULL      );

                    break;
                    case(ID_MenuHelp):
                        if(ShellExecute(hwnd,NULL,HelpFile,NULL,NULL,0) < 32)
                            MessageBox(hwnd,"Ошибка загрузки справки, проверьте ее наличие!","Ошибка",MB_OK);

                    break;
                    case(ID_MenuAbout):
                        MessageBox(hwnd,"Обучающая программа: Шифр Бэкона v1.0\n\n© 2021 Kozlova Olga\n","О программе",MB_OK);
                    break;
                    case(ButtExec):
                        DestroyWindow(hChild);
                        i=LogicalMode(hwnd);
                        hChild=CreateWindowEx(0, /* Extended possibilites for variation */
                                            szClassChildName,         /* Classname */
                                             _T("Обучающая программа: Шифр Бэкона"),       /* Title Text */
                                            WS_CHILD | WS_VISIBLE , /* default window */
                                            0,       /* Windows decides the position */
                                            35,       /* where the window ends up on the screen */
                                            1000,                 /* The programs width */
                                            600,                 /* and height in pixels */
                                            hwnd,        /* The window is a child-window to desktop */
                                            NULL,                /* No menu */
                                            hInstance,       /* Program Instance handler */
                                            NULL      );

                        if(i != 0)
                            MessageBox(hwnd,messError[i],"Ошибка",MB_OK);
                    break;
                    case(ID_MenuExit):
                        PostMessage(hwnd,WM_CLOSE,NULL,NULL);
                    break;
                }
            }

        break;
        case WM_NOTIFY:
            switch (((LPNMHDR)lParam)->code){
                case TCN_SELCHANGE:{
                    int iPage = TabCtrl_GetCurSel(hTControl);
                    if(iPage!=modeAll.mode){
                        DestroyWindow(hChild);
                        //MessageBox(hwnd,"","Return Destroy",MB_OK));
                        modeAll.mode=iPage;
                        SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)messStatus[iPage]);
                        hChild=CreateWindowEx(0, /* Extended possibilites for variation */
                                               szClassChildName,         /* Classname */
                                               _T("Обучающая программа: Шифр Бэкона"),       /* Title Text */
                                               WS_CHILD | WS_VISIBLE , /* default window */
                                               0,       /* Windows decides the position */
                                               35,       /* where the window ends up on the screen */
                                               1000,                 /* The programs width */
                                               600,                 /* and height in pixels */
                                               hwnd,        /* The window is a child-window to desktop */
                                               NULL,                /* No menu */
                                               hInstance,       /* Program Instance handler */
                                               NULL      );
                    }
                break;
                }
            }
        break;
        case WM_DESTROY:
            DestroyAcceleratorTable(hAccel);
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
        case WM_CLOSE:
            if(MessageBox(hwnd,"Вы уверены, что хотите выйти из программы?","Вопрос:",MB_YESNO) == IDYES)
                DestroyWindow(hwnd);
        break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
