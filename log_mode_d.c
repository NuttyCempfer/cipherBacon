#include "cipherBacon.h"

int alphaLen(unsigned char* str){
    int i,len;
    for(i=0, len=0; str[i]; i++)
        len+=MyIsAlpha(str[i])!=0;
    return len;
}

int correctMess(unsigned char* str){
    int i;
        for(i=0; str[i]; i++)
            if(!MyIsAlpha(str[i])&&str[i]!=' ')
                return 0;

        return i!=0;
}

int MyIsAlpha(unsigned char c){
    return c>='A'&&c<='Z'||
           c>='a'&&c<='z'||
           c>=192&&c<=223||
           c>=224&&c<=255;
}
unsigned char MyToLower(unsigned char c){
    if(c>='A'&&c<='Z')
        return c+'a'-'A';
    if(c>=192&&c<=223)
        return c+224-192;
    return c;
}
unsigned char MyToUpper(unsigned char c){
    if(c>='a'&&c<='z')
        return c+'A'-'a';
    if(c>=224&&c<=255)
        return c+192-224;
    return c;
}

int getCiphAlph(unsigned char* ciphAlph[], int* binAlph){
    int i, j;
    for(i=0; i<26; i++){
        for(binAlph[i]=0,j=0; j<5; j++){
            binAlph[i]*=2;
            if(ciphAlph[i][j]=='B' || ciphAlph[i][j]=='b')
                binAlph[i]++;
            else if(ciphAlph[i][j]!='A' && ciphAlph[i][j]!='a')
                return 0;
        }
    }
    for(i=0; i<26; i++){
        for(j=0; j<i; j++)
            if(binAlph[i]==binAlph[j])
                return 0;
    }
    return 1;
}
int mode_D(char ciphAlph[][sizeCiphAlph], char* mes,  unsigned char* fool,
            char* cryptMess){
    strcpy(cryptMess,"");
    int l,i,s,j;
    s=strlen(mes);
    l=alphaLen(fool);
    if(s==0 || l<s*5)
        return 0;
    strcpy(cryptMess,fool);
    for(l=0,i=0; mes[i]; i++){ ///word
        if(MyIsAlpha(mes[i])){///���� ������ ����� (�� ������ � �.�.)
            j=mes[i]>='a'?mes[i]-'a':mes[i]-'A'; ///��������� ���, ���� ����� ��������� ����� ��� � j.
            for(s=0; s<5;l++)
                if(MyIsAlpha(cryptMess[l])){ ///���� ������ ����� (�� ������ � �.�.)
                    if(ciphAlph[j][s]=='B') ///��������� ���������� ������ �� ����������� B ��� A
                        cryptMess[l]=MyToLower(cryptMess[l]);///������ � ������ �������
                    else
                        cryptMess[l]=MyToUpper(cryptMess[l]);///������ � ������� �������
                    s++;
                }
        }
    }

    return 0;
}
