#include "szovegbekero.h"
#include <stdio.h>
#include <stdlib.h>
#include "meglevokBE.h"
#include "debugmalloc.h"
#include <string.h>
/*
    Beolvas egy sz�veget ami max 100 karakter �s bele�rja a kapott v�ltoz�ba
*/
void szovegmerettel(char *szoveg)
{
    char betu;
    int i=0;
    getchar();
    while (scanf("%c", &betu)==1 && betu !='\n')
        szoveg[i++]=betu;
    szoveg[i]='\0';
    szoveg[101]='\0';
}
/*
    Beolvas egy ismeretlen hossz�s�g� sz�veget ami egy sorba van �rva
    Dinamikusan foglal neki helyet �s visszaadja
*/
char *szovegbekero()
{
    int n = 0;
    char *szoveg = (char*) malloc(sizeof(char));
    szoveg[0] = '\0';
    char ujbetu;
    while ((ujbetu=getchar())!='\n' /*scanf("%c", &ujbetu) == 1 && ujbetu != '\n'*/)
    {
        char *ujtomb = (char*) malloc((n+2)* sizeof(char));
        strcpy(ujtomb, szoveg);
        free(szoveg);
        szoveg= ujtomb;
        ujtomb[n]= ujbetu;
        ujtomb[n+1]= '\0';
        n++;
    }
    return szoveg;
}
/*
    Beolvas egy ismeretlen hossz�s�g� sz�veget a kapott f�jlb��l ami egy sorba van �rva
    Dinamikusan foglal neki helyet �s visszaadja
*/
char *fajlszoveg(FILE *recepteskonyv)
{
    int n = 0;
    char *szoveg = (char*) malloc(1* sizeof(char));
    szoveg[0] = '\0';
    char ujbetu;
    while (fscanf(recepteskonyv,"%c", &ujbetu) == 1 && ujbetu != '\n')
    {
        char *ujtomb = (char*) malloc((n+2)* sizeof(char));
        strcpy(ujtomb, szoveg);
        free(szoveg);
        szoveg= ujtomb;
        ujtomb[n]= ujbetu;
        ujtomb[n+1]= '\0';
        n++;
    }
    return szoveg;
}
