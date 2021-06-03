#include "cipherBacon.h"
    /*Режим B:
	Что будет зашито в конфиге:
	1.1) Таблица кодирования
	1.2) Правильный ключ.
	Что будет вводить пользователь:
	1.1) Сообщение (И)
	1.2) Ложный ключ
	Что выводит программа:
	1.1) Результат шифрования на И.Ключе
	1.2) Результат расшифрования на Л.К*/
int mode_B(char ciphAlph[][sizeCiphAlph], char* trueKey, char* ciphMess,  char* falseKey,
            char* decrTrueMess, char* decrFalseMess){
    //char trueKey[sizeAlph]="AAABBABBBABBABBABABBBAAAAA";
    //char trueKey[sizeAlph+1]="AAABBABBAAABBABBAAABBABBAB";
    char trueCiph[sizeCiph], tmp[sizeCiph],tmp2[sizeCiph],c,cc;
    int i,j,l,k,d,pa,pb;
    char a[14], b[14];
    if(!correctMess(ciphMess))
        return 6;
    if(alphaLen(ciphMess)>50)
        return 1;
    if(strlen(falseKey)!= 26)
        return 2;
    for(i=0,j=0,k=0; i<26; i++){
        if(falseKey[i]=='A')
            j++;
        if(falseKey[i]=='B')
            k++;
    }
    if(j!=13 || k!=13)
        return 4;
    for(i=0, j=0, k=0, l=0, d=0; i<26; i++){
        if(trueKey[i]=='A')
            if(falseKey[i]=='A')
                j++;
            else
                k++;
        else
            if(falseKey[i]=='A')
                l++;
            else
                d++;
    }

    if(j!=6 && j!=7 || k!=6 && k!=7 || l!=6 && l!=7 || d!=6 && d!=7)
        return 5;
    mode_decr(ciphAlph,ciphMess,trueKey,decrTrueMess);
    mode_decr(ciphAlph,ciphMess,falseKey,decrFalseMess);
    return 0;
}
