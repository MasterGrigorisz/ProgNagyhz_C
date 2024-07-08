#include "szovegbekero.h"
#include <stdio.h>
#include <stdlib.h>
#include "meglevokBE.h"
#include "debugmalloc.h"
#include <string.h>
/*
    Beolvas egy szöveget ami max 100 karakter és beleírja a kapott változóba
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
    Beolvas egy ismeretlen hosszúságú szöveget ami egy sorba van írva
    Dinamikusan foglal neki helyet és visszaadja
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
    Beolvas egy ismeretlen hosszúságú szöveget a kapott fájlbóül ami egy sorba van írva
    Dinamikusan foglal neki helyet és visszaadja
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
