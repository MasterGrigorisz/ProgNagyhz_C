#include "meglevokBE.h"
#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "fajliro.h"
/*
    A receptesk�nyv.txt f�jlba �rja ki a kapott receptki lista elemeit
    A list�n v�gigl�pegetve ki�rja a f�jlba az adatokat �s felszabad�tja a dinamukusan foglalt ter�leteket
*/
int fajlbairoRec(Recept *receptki)
{
    FILE *recepteskonyv;
    recepteskonyv = fopen("recepteskonyv.txt", "w");
    if (recepteskonyv == NULL)
        return -1;
    while (receptki != NULL)
    {
        fprintf(recepteskonyv, "-\n%s\n",receptki->nev); //NEV
        int R=-1;
        while (receptki->hozza[0][++R]!=-1) //�SSZETEV�K
            fprintf(recepteskonyv, "|%d-%d", receptki->hozza[0][R],receptki->hozza[1][R]);
        fprintf(recepteskonyv,"\n%s\n",receptki->leiras);
        free(receptki->leiras);
        Recept *temp=receptki->kovrec;
        free(receptki);
        receptki=temp;
    }
    fclose(recepteskonyv);
    return 0;
}
/*
    A osszetevokonyv.txt f�jlba �rja ki a kapott osszetevoki lista elemeit
    A list�n v�gigl�pegetve ki�rja a f�jlba az adatokat �s felszabad�tja a dinamukusan foglalt ter�leteket
*/
int fajlbairoOssz(Osszetevo *osszetevoki)
{
    FILE *osszetevokonyv;
    osszetevokonyv = fopen("osszetevokonyv.txt", "w");
    if (osszetevokonyv == NULL)
        return -1;
    while (osszetevoki != NULL)
    {
        fprintf(osszetevokonyv, "-\n%s\n%d\n%s\n", osszetevoki->nev, osszetevoki->sorszam, osszetevoki->mertek);
        Osszetevo *temp =osszetevoki->kovossz;
        free(osszetevoki);
        osszetevoki=temp;
    }
    fclose(osszetevokonyv);
    return 0;
}
