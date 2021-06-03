#include "cipherBacon.h"
/*ReadIniFile char * FileName, char* Alph[]*/

int ReadIniFileA(char * FileName){
    int i;
    char c[2];
    c[1]='\0';
    for(i=0; i<sizeAlph; i++){
        c[0]=i+'A';
        if(GetPrivateProfileString("Mode_A",c,NULL,modeAll.A.CiphAlph[i],sizeCiphAlph,FileName) != sizeCiphAlph-1)
            return 0;
    }
    if(GetPrivateProfileString("Mode_A","true_key",NULL,modeAll.A.trueKey,sizeAlph+1,FileName) != sizeAlph)
        return 0;

    return 1;
}

int ReadIniFileB(char * FileName){
    int i;
    char c[2];
    c[1]='\0';
    for(i=0; i<sizeAlph; i++){
        c[0]=i+'A';
        if(GetPrivateProfileString("Mode_B",c,NULL,modeAll.B.CiphAlph[i],sizeCiphAlph,FileName) != sizeCiphAlph-1)
            return 0;
    }
    if(GetPrivateProfileString("Mode_B","true_key",NULL,modeAll.B.trueKey,sizeAlph+1,FileName) != sizeAlph)
        return 0;
    return 1;
}

int ReadIniFileC(char * FileName){
    int i,rc;
    char c[2];
    c[1]='\0';
    for(i=0; i<sizeAlph; i++){
        c[0]=i+'A';
        if(GetPrivateProfileString("Mode_C",c,NULL,modeAll.C.CiphAlph[i],sizeCiphAlph,FileName) != sizeCiphAlph-1)
            return 0;
    }
    rc=GetPrivateProfileString("Mode_C","true_mess",NULL,modeAll.C.trueMess,sizeMess,FileName);
    if(rc<3 || rc>sizeMess-1)
        return 0;
    rc=GetPrivateProfileString("Mode_C","false_mess1",NULL,modeAll.C.falseMess1,sizeMess,FileName);
    if(rc<3 || rc>sizeMess-1)
        return 0;
    rc=GetPrivateProfileString("Mode_C","false_mess2",NULL,modeAll.C.falseMess2,sizeMess,FileName);
    if(rc<3 || rc>sizeMess-1)
        return 0;
    //-----------------
    if(GetPrivateProfileString("Mode_C","true_key",NULL,modeAll.C.trueKey,sizeAlph+1,FileName) != sizeAlph)
        return 0;
    if(GetPrivateProfileString("Mode_C","false_key1",NULL,modeAll.C.falseKey1,sizeAlph+1,FileName) != sizeAlph)
        return 0;
    if(GetPrivateProfileString("Mode_C","false_key2",NULL,modeAll.C.falseKey2,sizeAlph+1,FileName) != sizeAlph)
        return 0;
    return 1;
}
int ReadIniFileD(char * FileName){
    int i,rc;
    char c[2];
    c[1]='\0';
    for(i=0; i<sizeAlph; i++){
        c[0]=i+'A';
        if(GetPrivateProfileString("Mode_D",c,NULL,modeAll.D.CiphAlph[i],sizeCiphAlph,FileName) != sizeCiphAlph-1)
            return 0;
    }
    rc=GetPrivateProfileString("Mode_D","message",NULL,modeAll.D.Message,sizeMess,FileName);
    if(rc<3 || rc>sizeMess-1)
        return 0;
    //-----------------
    rc=GetPrivateProfileString("Mode_D","container",NULL,modeAll.D.Container,sizeCont,FileName);
    if(rc<15 || rc>sizeCont-1)
        return 0;
    return 1;
}

int ReadIniFileE(char * FileName){
    int i,rc;
    char c[2], cont[11], tmp[sizeCont];
    c[1]='\0';
    for(i=0; i<sizeAlph; i++){
        c[0]=i+'A';
        if(GetPrivateProfileString("Mode_E",c,NULL,modeAll.E.CiphAlph[i],sizeCiphAlph,FileName) != sizeCiphAlph-1)
            return 0;
    }
    for(i=0; i<countCont; i++){
        sprintf(cont,"container%d",i+1);
        rc=GetPrivateProfileString("Mode_E",cont,NULL,tmp,sizeCont,FileName);
        if(rc<15 || rc>sizeCont-1)
            return 0;
        strcpy(modeAll.E.Container[i],tmp);
    }
    return 1;
}


int WriteIniFileA(char * FileName){
    int i;
    char c[2];
    c[1]='\0';
    for(i=0; i<sizeAlph; i++){
        c[0]=i+'A';
        if(WritePrivateProfileString("Mode_A",c,modeAll.A.CiphAlph[i],FileName) == 0)
            return 0;
    }
    if(WritePrivateProfileString("Mode_A","true_key",modeAll.A.trueKey,FileName) == 0)
        return 0;
    return 1;
}

int WriteIniFileB(char * FileName){
    int i;
    char c[2];
    c[1]='\0';
    for(i=0; i<sizeAlph; i++){
        c[0]=i+'A';
        if(WritePrivateProfileString("Mode_B",c,modeAll.B.CiphAlph[i],FileName) == 0)
            return 0;
    }
    if(WritePrivateProfileString("Mode_B","true_key",modeAll.B.trueKey,FileName) == 0)
        return 0;
    return 1;
}

int WriteIniFileC(char * FileName){
    int i;
    char c[2];
    c[1]='\0';
    for(i=0; i<sizeAlph; i++){
        c[0]=i+'A';
        if(WritePrivateProfileString("Mode_C",c,modeAll.C.CiphAlph[i],FileName) == 0)
            return 0;
    }
    if(WritePrivateProfileString("Mode_C","true_mess",modeAll.C.trueMess,FileName) == 0)
        return 0;
    if(WritePrivateProfileString("Mode_C","false_mess1",modeAll.C.falseMess1,FileName) == 0)
        return 0;
    if(WritePrivateProfileString("Mode_C","false_mess2",modeAll.C.falseMess2,FileName) == 0)
        return 0;
    //-----------------
    if(WritePrivateProfileString("Mode_C","true_key",modeAll.C.trueKey,FileName) == 0)
        return 0;
    if(WritePrivateProfileString("Mode_C","false_key1",modeAll.C.falseKey1,FileName) == 0)
        return 0;
    if(WritePrivateProfileString("Mode_C","false_key2",modeAll.C.falseKey2,FileName) == 0)
        return 0;
    return 1;
}
int WriteIniFileD(char * FileName){
    int i;
    char c[2];
    c[1]='\0';
    for(i=0; i<sizeAlph; i++){
        c[0]=i+'A';
        if(WritePrivateProfileString("Mode_D",c,modeAll.D.CiphAlph[i],FileName) == 0)
            return 0;
    }
    if(WritePrivateProfileString("Mode_D","message",modeAll.D.Message,FileName) == 0)
        return 0;
    //-----------------
    if(WritePrivateProfileString("Mode_D","container",modeAll.D.Container,FileName) == 0)
        return 0;
    return 1;
}

int WriteIniFileE(char * FileName){
    int i;
    char c[2], cont[11];
    c[1]='\0';
    for(i=0; i<sizeAlph; i++){
        c[0]=i+'A';
        if(WritePrivateProfileString("Mode_E",c,modeAll.E.CiphAlph[i],FileName) == 0 )
            return 0;
    }
    for(i=0; i<countCont; i++){
        sprintf(cont,"container%d",i+1);
        if(WritePrivateProfileString("Mode_E",cont,modeAll.E.Container[i],FileName) == 0)
            return 0;
    }
    return 1;
}
