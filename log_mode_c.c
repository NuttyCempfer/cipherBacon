#include "cipherBacon.h"

int mode_C(char ciphAlph[][sizeCiphAlph], char* trueKey, char* falseKey1, char* falseKey2,
           char* trueMess, char* falseMess1, char* falseMess2, char* cipherMess,
           char* decryptFalseMess1, char* decryptFalseMess2 ){
    int i,j;
    char c;
    char trueCipher[16]="",falseCipher1[16]="",falseCipher2[16]="";
    char aaa[5]="", aab[5]="", aba[5]="", abb[5]="", baa[5]="", bab[5]="", bba[5]="", bbb[5]="";
    int paaa=0, paab=0, paba=0, pabb=0, pbaa=0, pbab=0, pbba=0, pbbb=0;
    for(i=0; i<sizeAlph-1; i++){
        c='A'+i;
        if(trueKey[i]=='A'){
            if(falseKey1[i]=='A'){
                if(falseKey2[i]=='A')
                    strncat(aaa,&c,1);

                else
                    strncat(aab,&c,1);
            }
            else{
                if(falseKey2[i]=='A')
                    strncat(aba,&c,1);
                else
                    strncat(abb,&c,1);
            }
        }
        else{
            if(falseKey1[i]=='A'){
                if(falseKey2[i]=='A')
                    strncat(baa,&c,1);
                else
                    strncat(bab,&c,1);
            }
            else{
                if(falseKey2[i]=='A')
                    strncat(bba,&c,1);
                else
                    strncat(bbb,&c,1);
            }
        }
    }

    for(i=0; i<strlen(trueMess); i++){
        j=trueMess[i]-'A'; ///Проверяем код, если буквы совпадают пишем код в j.
        strcat(trueCipher,ciphAlph[j]);
        j=falseMess1[i]-'A';
        strcat(falseCipher1,ciphAlph[j]);
        j=falseMess2[i]-'A';
        strcat(falseCipher2,ciphAlph[j]);
    }
    ///шифровать сообщение
    strcpy(cipherMess,"");
    for(i=0; i<strlen(trueCipher); i++){
        if(trueCipher[i]=='A'){
            if(falseCipher1[i]=='A'){
                if(falseCipher2[i]=='A'){
                    strncat(cipherMess,&aaa[paaa++],1);
                    aaa[paaa]=='\0'?paaa=0:0;
                }
                else{
                    strncat(cipherMess,&aab[paab++],1);
                    aab[paab]=='\0'?paab=0:0;
                }
            }
            else{
                if(falseCipher2[i]=='A'){
                    strncat(cipherMess,&aba[paba++],1);
                    aba[paba]=='\0'?paba=0:0;
                }
                else{
                    strncat(cipherMess,&abb[pabb++],1);
                    abb[pabb]=='\0'?pabb=0:0;
                }
            }
        }
        else{
            if(falseCipher1[i]=='A'){
                if(falseCipher2[i]=='A'){
                    strncat(cipherMess,&baa[pbaa++],1);
                    baa[pbaa]=='\0'?pbaa=0:0;
                }
                else{
                    strncat(cipherMess,&bab[pbab++],1);
                    bab[pbab]=='\0'?pbab=0:0;
                }
            }
            else{
                if(falseCipher2[i]=='A'){
                    strncat(cipherMess,&bba[pbba++],1);
                    bba[pbba]=='\0'?pbaa=0:0;
                }
                else{
                    strncat(cipherMess,&bbb[pbbb++],1);
                    bbb[pbbb]=='\0'?pbbb=0:0;
                }
            }
        }
    }
    mode_decr(ciphAlph,cipherMess,falseKey1,decryptFalseMess1);
    mode_decr(ciphAlph,cipherMess,falseKey2,decryptFalseMess2);
    return 0;
}

int mode_decr(char ciphAlph[][sizeCiphAlph], char* cipherMess,  char* key, char* decrMess){
    int i, j;
    char tmp[sizeCiph], c;
    for(i=0, strcpy(tmp,""); i<strlen(cipherMess); i++)
        strncat(tmp,&key[cipherMess[i]-'A'],1);
    for(i=0, strcpy(decrMess,""); i<strlen(tmp); i+=5){
        for(j=0; j<sizeAlph; j++)
            if(strncmp(&tmp[i],ciphAlph[j],sizeCiphAlph-1) == 0){
                c='A'+j;
                strncat(decrMess,&c,1);
            }
    }
    return 0;
}
