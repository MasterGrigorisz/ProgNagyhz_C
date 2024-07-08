#include "meglevokBE.h"
#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "szovegbekero.h"
#include <string.h>

/*
    FÁJL olvasó
    A recepteskonyv.txt fájl tartalmát olvassa be és rendszerezi
        1 recept 4 sorból áll
            -                       *elválasztás*
            receptcím               szöveg
            hozzávalók kódolva      *|* és *-* elválasztást használva a hozzávaló sorszámát és mennyiségét
            leírás                  szöveg (határozatlan hossz)
        A *szovegbekero.c* -ben található *fajlszoveg* függvénynek adja át a fájlt és kéri belőle az egy sor hosszúságú dinamikusan foglalt szövegét
        A hozzávalók beolvasását maga végzi
        Újra meghívja a *fajlszoveg* függvényt a következő sorra
        A meghívásakor kapott Recept pointerre fűzi fel az újonnal létrehozott receptet (végére fűzi)
        A kapott Recept pointert adja vissza
*/
Recept *meglevokBE(Recept *eleje)
{
    FILE *recepteskonyv;
    recepteskonyv = fopen("recepteskonyv.txt", "r");
    if (recepteskonyv == NULL)
        return NULL;
    char betu;
    while (fscanf(recepteskonyv, "%c", &betu)==1 && betu== '-')
    {

        fscanf(recepteskonyv, "%c", &betu);
        Recept *ujr;
        ujr=(Recept*)malloc(sizeof(Recept));
        ujr->kovrec=NULL;
        //ADATOK
        int i=0;
        while (fscanf(recepteskonyv, "%c", &betu)==1 && betu!= '\n') ///NÉV
            ujr->nev[i++]=betu;
        ujr->nev[i]='\0';
        int sors, ind=0;
        while (fscanf(recepteskonyv, "%c", &betu)==1)
        {
            if (betu != '\n')                        // | vagy \n
            {
                fscanf(recepteskonyv, "%d", &sors);  // 2
                ujr->hozza[0][ind]=sors;
                fscanf(recepteskonyv, "%c", &betu);  // -
                fscanf(recepteskonyv, "%d", &sors);  // 1
                ujr->hozza[1][ind++]=sors;
            }
            else
                break;
        }
        ujr->hozza[0][ind]=-1;
        ujr->leiras=fajlszoveg(recepteskonyv);
        if(eleje==NULL)
            eleje=ujr;
        else //Vége megkeresése
        {
            Recept *m=eleje;
            while(m->kovrec !=NULL)
                m=m->kovrec;
            m->kovrec=ujr;
        }
    }
    fclose(recepteskonyv);
    return eleje;
}

/*
    FÁJL olvasó
    A osszetevokonyv.txt fájlt olvassa be és rendszerezi
            Saját maga olvassa be az összetevő nevét, ami enter jelig tart
            Beolvassa az összetevő kódját (szám)
            Saját maga olvassa be az összetevő mértékegységét
    A meghíváskor kapott Osszetevo pointerre fűzi fel az újonnal kapott receptet (végére fűzi)
    A kapott pointert adja vissza
*/

Osszetevo *osszetevoBE(Osszetevo *eleje)
{
    FILE *osszetevokonyv;
    osszetevokonyv = fopen("osszetevokonyv.txt", "r");
    if (osszetevokonyv == NULL)
        return NULL;
    char betu;
    int i;
    while (fscanf(osszetevokonyv, "%c ", &betu)==1 && betu== '-')
    {
        Osszetevo *ujo=(Osszetevo*)malloc(sizeof(Osszetevo));
        ujo->kovossz=NULL;
        i=0;
        while (fscanf(osszetevokonyv, "%c", &betu)==1 && betu!= '\n') //NÉV
            ujo->nev[i++]=betu;
        ujo->nev[i]='\0';
        fscanf(osszetevokonyv, "%d ", & ujo->sorszam);
        i=0;
        while (fscanf(osszetevokonyv, "%c", &betu)==1 && betu!= '\n') //NÉV
            ujo->mertek[i++]=betu;
        ujo->mertek[i]='\0';
        if(eleje==NULL)
            eleje=ujo;
        else
        {
            Osszetevo *m=eleje;
            while(m->kovossz !=NULL)
                m=m->kovossz;
            m->kovossz=ujo;
        }
    }
    fclose(osszetevokonyv);
    return eleje;
}
