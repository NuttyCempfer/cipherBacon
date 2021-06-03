#include "cipherBacon.h"

int mode_E(char ciphAlph[][sizeCiphAlph], char* mes,  unsigned char* fool,
            char* binaryMess){
    memset(binaryMess,'*',sizeCont-1);
    binaryMess[sizeCont-1]='\0';
    if(alphaLen(mes)*5 > alphaLen(fool))
        return 8;
    int l,i,s,j;
    s=strlen(mes);
    l=alphaLen(fool);
    if(s==0 || l<s*5)
        return 0;
    //strcpy(cryptMess,fool);

    for(l=0,i=0; mes[i]; i++){ ///word
        if(MyIsAlpha(mes[i])){///���� ������ ����� (�� ������ � �.�.)
            j=mes[i]>='a'?mes[i]-'a':mes[i]-'A'; ///��������� ���, ���� ����� ��������� ����� ��� � j.
            for(s=0; s<5;l++)
                if(MyIsAlpha(fool[l])){ ///���� ������ ����� (�� ������ � �.�.)
                    if(ciphAlph[j][s]=='B') ///��������� ���������� ������ �� ����������� B ��� A
                        binaryMess[l]='1';///������ � ������ �������
                    else
                        binaryMess[l]='0';///������ � ������� �������
                    s++;
                }
        }
    }
    return 0;
}

void switchModeE(HWND hwnd){
    int i;
    if(strlen(modeAll.E.binaryMess) == 0)
        return;
    strcpy(modeAll.E.cryptMess,modeAll.E.Container[modeAll.E.nCont-10000]);
    if(modeAll.E.nMode == ID_modeRBA1 || modeAll.E.nMode == ID_modeRBB1){
        for(i=0; i<strlen(modeAll.E.cryptMess); i++)
                if(modeAll.E.binaryMess[i]!='*'){
                    if(modeAll.E.nMode % 2 == 0 && modeAll.E.binaryMess[i] == '0'
                       || modeAll.E.nMode % 2 == 1 && modeAll.E.binaryMess[i] == '1')
                        modeAll.E.cryptMess[i]=MyToLower(modeAll.E.cryptMess[i]);///������ � ������ �������
                    else
                        modeAll.E.cryptMess[i]=MyToUpper(modeAll.E.cryptMess[i]);
                }
    }


}

