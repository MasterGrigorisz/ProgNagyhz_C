#include "receptkezelo.h"
#include "meglevokBE.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include <time.h>
#include "szovegbekero.h"
#include <string.h>
#include "lefogjarni.h"
/*
    Kapott új receptet a kapott receptlista elejére fűzi majd visszaadja
*/
Recept *listamasolRecept(Recept *eleje, Recept *ujrec)
{
    Recept *letrehozott =(Recept*)malloc(sizeof(Recept));
    *letrehozott=*ujrec;
    letrehozott->kovrec=eleje;
    return letrehozott;
}
/*
    A kapott listán végiglépegetve megnézi, melyik felel meg a követelményke (amit kapott)
    Ha megfelel, átadja a listamasolRecpet-nek
    visszaadja az új listát amit készíttetett
*/
Recept *lefogjarniseged(Recept *ujeleje,Recept *regieleje, Osszetevo *meglevoosszetevok, Osszetevo *mozgo)
{
    int sorszam=mozgo->sorszam;
    Recept *mozgorec=regieleje;
    while (mozgorec!=NULL) //végéig megyek a recepteken
    {
        int i=0;
        while (mozgorec->hozza[0][i] != -1) //végéig megyek a hozzavalokon
        {
            if (mozgorec->hozza[0][i]==sorszam) //megnézem hogy benne van-e a receptben
            {
                ujeleje=listamasolRecept(ujeleje,mozgorec); //listába fûzöm
            }
            i++;
        }
        mozgorec=mozgorec->kovrec;
    }
    return ujeleje;
}
/*
    Elsődleges: Lerceptkiíró
    Két funkció:
        1. kilistázza név szerint a kapott receptes lista neveit
        2. receptkiiroval kiiratja az eng-sorszámú receptet
*/
void listarolnevkiiro(Recept *eleje, int eng, Osszetevo *meglevoosszetevok)
{
    if (eleje==NULL)
        printf("Nincs megfelelo recept\n");
    else
    {
        Recept *mozgo=eleje;
        int i=1;
        while (mozgo!=NULL)
        {
            if (eng==0)
                printf("%d. %s\n", i, mozgo->nev);
            else if (i==eng)
                receptkiiro(meglevoosszetevok,mozgo);
            mozgo=mozgo->kovrec;
            i++;
        }
        if (eng >i)
            printf("Ervenytelen szam\n");
    }
}
/*
    Felszabadítja a kapott lista össze elemét
*/
void felszabadito(Recept* eleje)
{
    if (eleje!=NULL)
    {
        Recept *temp=NULL, *mozgo=eleje;
        while (mozgo!=NULL)
        {
            temp=mozgo->kovrec;
            free(mozgo);
            mozgo=temp;
        }
    }
}
/*
    Bekér egy hozzávalónevet, megkeresi azt
    A hozzávaló sorszámát átadja a segédnek
    A visszakapott listát átadja kiírónak
    Bekéri, mit választ a felhasználó:
        kilépés
        visszatér 1-el, azaz újra hivatja magát
        következő szűrőt alkalmazni- újrahívja magát, de az új listát adja oda magának
        kiválasztott receptet kiíratja a listanevkiiroval
        futása végén az új listát átadja a felszabadítónak
*/
int lefogjarni(Recept *meglevorecept,Recept *ujkor, Osszetevo *meglevoosszetevok)
{
    Recept *ezthasznald;
    if (ujkor!=NULL)
        ezthasznald=ujkor;
    else
        ezthasznald=meglevorecept;
    printf("Adj meg egy osszetevot, amit el kell hasznalni!\n");
    char amitenne[101];
    szovegmerettel(amitenne);
    printf("\n");
    Osszetevo *mozgo=meglevoosszetevok;
    while (mozgo!=NULL && strcmp(mozgo->nev,amitenne)!=0)
        mozgo=mozgo->kovossz;
    bool megvan =false;
    if (mozgo==NULL)
        printf("Nem talaltam meg ezt: %s\n",amitenne);
    else
        megvan=true;
    Recept *ujlista=NULL;
    if (megvan)
    {
        int valasz, sajatvalasz;
        ujlista=lefogjarniseged(ujlista,ezthasznald,meglevoosszetevok,mozgo);
        printf("Melyiket valasztod? Ird be a szamat\n-2. Hozzavalok nullazasa\n-1. Uj hozzavalot adok\n0. Egyiket sem (vissza)\n");
        listarolnevkiiro(ujlista,0,meglevoosszetevok);
        printf("Valaszod: ");
        do
        {
            scanf(" %d", &valasz);
            switch (valasz)
            {
            case 0:
                //felszabadito(ujlista);
                //return 0;
                break;
            case -2:
                felszabadito(ujlista);
                return 1;
                break;
            case -1:
                sajatvalasz =lefogjarni(ezthasznald,ujlista,meglevoosszetevok);
                felszabadito(ujlista);
                if (sajatvalasz ==1)
                    return 1;
                return 0;
                break;
            default:
                if( valasz<-2)
                {
                    printf("Ervenytelen szam\n");
                    valasz=0;
                }
                else
                {
                    listarolnevkiiro(ujlista,valasz,meglevoosszetevok);
                    valasz=0;
                }
                break;
            }
        }
        while(valasz!=0);
        //felszabadito(ujlista);
        //return 0;
    }
    else
    {
        printf("Nincs megfelelo recept\n");
        //felszabadito(ujlista);
        //return 0;
    }
    felszabadito(ujlista);
    return 0;
}
