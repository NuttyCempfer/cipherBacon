#ifndef CIPHERBACON_H_INCLUDED
#define CIPHERBACON_H_INCLUDED
#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
//-----------------------------------
#define sizeAlph 26
#define sizeMess 11
#define sizeCiph 51
#define sizeCont 81
#define countCont 4
#define sizeCiphAlph 6
//----------------------------------------------
#define IDI_ICON 1
//-------------------------------------------
#define ID_ListBox 3000
#define ID_MenuFileOpen 2006
#define ID_MenuFileSave 2007
#define ID_MenuFileSaveAs 2008
#define ID_MenuExit 2009
#define ID_MenuHelp 2010
#define ID_MenuAbout 2011
#define ButtExec 1000
#define ButtRep 1001
//-------------------------------------------
#define ID_mode_c 5000
#define ID_mode_d 5001
#define ID_mode_a 5002
#define ID_mode_b 5003
#define ID_mode_e 5004
//--------------------------------------
#define ID_TrueMess 4000
#define ID_FalseMess 4001
#define ID_FalseMess1 4002
#define ID_FalseMess2 4003
#define ID_CryptTrueMess 4004
#define ID_CryptFalseMess 4005
#define ID_CryptFalseMess1 4006
#define ID_CryptFalseMess2 4007
#define ID_DecryptFalseMess 4008
#define ID_Container 4009
#define ID_EditAlph 4010
#define ID_EditCipher 4011
#define ID_EditTrueKey 4012
#define ID_EditFalseKey 4013
#define ID_EditContainer 4014
//--------------------------------------
#define ID_ContRB1 10000
#define ID_ContRB2 10001
#define ID_ContRB3 10002
#define ID_ContRB4 10003
//-----------------------------------------
#define ID_modeRBA1 20000
#define ID_modeRBA2 20002
#define ID_modeRBA3 20004
#define ID_modeRBA4 20006
#define ID_modeRBB1 20001
#define ID_modeRBB2 20003
#define ID_modeRBB3 20005
#define ID_modeRBB4 20007

//--------------------------------------
#define mode_c 0
#define mode_d 1
#define mode_a 2
#define mode_b 3
#define mode_e 4
//------------------------------------
#include <tchar.h>
#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <string.h>
#include <locale.h>
#include <richedit.h>
#include <winuser.h>
#include <shellapi.h>
//---------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//---------------------------------------
extern char FileName[255];
extern char HelpFile[255];

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindowChildProcedure (HWND, UINT, WPARAM, LPARAM);
HWND createListBox(char * [], HWND);
HACCEL  hAccel;
HWND hButtonExec;
int checkCiph(char*);
/*ReadIniFile char * FileName, char* Alph[]*/
int ReadIniFileA(char *);
int ReadIniFileB(char *);
int ReadIniFileC(char *);
int ReadIniFileD(char *);
int ReadIniFileE(char *);
//------------------------------------------------
int WriteIniFileA(char *);
int WriteIniFileB(char *);
int WriteIniFileC(char *);
int WriteIniFileD(char *);
int WriteIniFileE(char *);
//------------------------------------------------


int LogicalMode(HWND);
struct modeA{
    char CiphAlph[sizeAlph][sizeCiphAlph];//V
    char trueKey[sizeAlph+1], trueMess[sizeMess]; //
    char falseMess[sizeMess], falseKey[sizeAlph+1];
    char cryptMess[sizeCiph];
    HWND hwnd;
    HWND hListBox;
    HWND hTrueMess, hFalseMess, hCryptMess;
    HWND hButtonReplace, hEditAlph, hEditCipher, hEditTrueKey;
};

struct modeB{
    char CiphAlph[sizeAlph][sizeCiphAlph];
    char trueKey[sizeAlph+1],cryptMess[sizeCiph];
    char falseKey[sizeAlph+1];
    char decrTrueMess[sizeMess], decrFalseMess[sizeMess];
    HWND hwnd;
    HWND hListBox;
    HWND hCiphMess, hDecryptTrueMess, hDecryptFalseMess;
    HWND hButtonReplace, hEditAlph, hEditCipher, hEditTrueKey, hEditFalseKey;
};

struct modeC{
    char CiphAlph[sizeAlph][sizeCiphAlph];
    char trueKey[sizeAlph+1], falseKey1[sizeAlph+1], falseKey2[sizeAlph+1];
    char trueMess[sizeMess], falseMess1[sizeMess], falseMess2[sizeMess];
    char cryptMess[sizeCiph], decryptFalseMess1[sizeMess], decryptFalseMess2[sizeMess];
    HWND hwnd;
    HWND hListBox;
    HWND hTrueMess, hFalseMess1, hFalseMess2;
    HWND hCryptTrueMess, hDecryptFalseMess1, hDecryptFalseMess2;
};
struct modeD{
    char CiphAlph[sizeAlph][sizeCiphAlph];
    char Message[sizeMess];
    char Container[sizeCont];
    char cryptMess[sizeCont];
    HWND hwnd;
    HWND hListBox;
    HWND hMess, hContainer, hHiddenMessage;
};

struct modeE{
    char CiphAlph[sizeAlph][sizeCiphAlph];
    char Container[countCont][sizeCont];
    char Message[sizeMess];
    char cryptMess[sizeCont];
    char binaryMess[sizeCont];
    HWND hwnd;
    HWND hListBox;
    HWND hMess, hHiddenMessage;
    HWND hButtonReplace, hEditAlph, hEditCipher;
    HWND hContRB1, hContRB2,hContRB3,hContRB4;
    HWND hModeRBA1, hModeRBA2,hModeRBA3,hModeRBA4,
            hModeRBB1,hModeRBB2,hModeRBB3,hModeRBB4;
    int nCont, nMode;
};

struct mode_Ret{
    int mode;
    struct modeA A;
    struct modeB B;
    struct modeC C;
    struct modeD D;
    struct modeE E;
};

void createModeA(HWND/*window*/,HFONT,HFONT);
void createModeB(HWND/*window*/,HFONT,HFONT);
void createModeC(HWND/*window*/,HFONT,HFONT);
void createModeD(HWND/*window*/,HFONT,HFONT);
void createModeE(HWND/*window*/,HFONT,HFONT);

int alphaLen(unsigned char*);
int MyIsAlpha(unsigned char);
unsigned char MyToLower(unsigned char);
unsigned char MyToUpper(unsigned char);
int getCiphAlph(unsigned char* [], int*);
int correctMess(unsigned char* );

int mode_A(char [][sizeCiphAlph], char*, char*,
            char*, char*, char*);

int mode_B(char [][sizeCiphAlph], char*, char*, char*,
            char*, char*);
int mode_C(char [][sizeCiphAlph], char*,  char*,
            char*, char*, char*, char*,char*, char*,char*);
int mode_decr(char [][sizeCiphAlph], char*,  char*,
            char*);
int mode_D(char [][sizeCiphAlph], char*,  unsigned char*,
            char*);

int mode_E(char [][sizeCiphAlph], char*,  unsigned char*,
            char*);
void switchModeE(HWND);
extern char * messError[9];
extern char * messStatus[5];

extern struct mode_Ret modeAll;
#endif // CB_H_INCLUDED
