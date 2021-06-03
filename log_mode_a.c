#include "cipherBacon.h"
     /*1) Режим А:
    Что будет зашито в конфиге:
	1.1) Таблица кодирования
	1.2) Правильный ключ.
	Что будет вводить пользователь:
	1.3) Истинное сообщениеV
	1.4) Ложное сообщениеV
	Что формирует программа (и выводит):
	1.1) Формирует ложный ключV
	1.2) Выводит зашифрованное сообщение (И)V
	1.3) Выводит зашифрованное сообщение (Л)V*/
int mode_A(char ciphAlph[][sizeCiphAlph],  char* trueKey,  char* trueMess,
            char* falseMess,  char* falseKey, char* cryptMess){
    char c;
    int i,j,k,f1,f2,paa,pab,pba,pbb;
    char aa[8], ab[8], ba[8], bb[8];
    char falseCiph[sizeCiph];
    char trueCiph[sizeCiph];
    if(!correctMess(trueMess))
        return 6;
    if(!correctMess(falseMess))
        return 7;
    if(alphaLen(trueMess)!=alphaLen(falseMess) ||
        alphaLen(falseMess)>10)
        return 1;


    if(strlen(trueKey)!= 26)
        return 2;
    for(i=0,j=0,k=0; i<26; i++){
        if(trueKey[i]=='A')
            j++;
        if(trueKey[i]=='B')
            k++;
    }
    if(j!=13 || k!=13)
        return 3;
    for(i=0, strcpy(trueCiph,""); i<strlen(trueMess); i++)
        if(isalpha(trueMess[i]))
            strcat(trueCiph, ciphAlph[trueMess[i]>='a'?trueMess[i]-'a':trueMess[i]-'A']);
    for(i=0, strcpy(falseCiph,""); i<strlen(falseMess); i++)
        if(isalpha(falseMess[i]))
            strcat(falseCiph, ciphAlph[falseMess[i]>='a'?falseMess[i]-'a':falseMess[i]-'A']);
    for(i=0,f1=0,f2=0,strcpy(falseKey,"00000000000000000000000000"),
        strcpy(aa,""),strcpy(ab,""),strcpy(ba,""),strcpy(bb,""); i<26; i++){
        c='A'+i;
        if(trueKey[i]=='A'){
            if(f1){
                strncat(aa,&c,1);
                falseKey[i]='A';
            }
            else{
                strncat(ab,&c,1);
                falseKey[i]='B';
            }
            f1=!f1;
        }
        else{
            if(f2){
                strncat(ba,&c,1);
                falseKey[i]='A';
            }
            else{
                strncat(bb,&c,1);
                falseKey[i]='B';
            }
            f2=!f2;
        }
    }
    for(i=0,paa=0,pab=0,pba=0,pbb=0, strcpy(cryptMess,""); i<strlen(trueCiph); i++){
        if(trueCiph[i]=='A'){
            if(falseCiph[i]=='A'){
                strncat(cryptMess,&aa[paa++],1);
                aa[paa]=='\0'?(paa=0):0;
            }
            if(falseCiph[i]=='B'){
                strncat(cryptMess,&ab[pab++],1);
                ab[pab]=='\0'?(pab=0):0;
            }
        }
        if(trueCiph[i]=='B'){
            if(falseCiph[i]=='A'){
                strncat(cryptMess,&ba[pba++],1);
                ba[pba]=='\0'?(pba=0):0;
            }
            if(falseCiph[i]=='B'){
                strncat(cryptMess,&bb[pbb++],1);
                bb[pbb]=='\0'?(pbb=0):0;
            }
        }
    }

    return 0;
}
