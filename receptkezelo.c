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
    *Z nevezetű ALMENÜ
    *Minden receptkereséshez tartozó függvényt innen nyit meg a felhasználó
*/
void receptkezelo(Osszetevo *meglevoosszetevok,Recept *meglevorecept)
{
    int valasz, randvalasz, ugyvalasz, lefogvalasz, keresovalasz;
    do
    {
        printf("\nALMENU\n1. Keresek receptnev szerint\n2. Nincs otletem :/\n3. Ugy ennek egy kis...\n4. Le fog jarni\n0. Vissza\nValaszod: ");
        scanf("%d", &valasz);
        switch (valasz)
        {
        case 1:
            keresovalasz=1;
            while (keresovalasz!=0)
                keresovalasz=receptkereso(meglevoosszetevok,meglevorecept);
            break;
        case 2:
            randvalasz =1;
            while (randvalasz!=0)
                randvalasz= randomrecept(meglevoosszetevok,meglevorecept);
            break;
        case 3:
            ugyvalasz=1;
            while (ugyvalasz!=0)
                ugyvalasz =ugyennek(meglevorecept, meglevoosszetevok);
            break;
        case 4:
            lefogvalasz=1;
            while (lefogvalasz!=0)
                lefogvalasz=lefogjarni(meglevorecept,NULL, meglevoosszetevok);
            break;
        case 0:
            break;
        default:
            printf("\nErvenytelen szam");
            break;
        }
    }
    while (valasz !=0);
}
/*
    *Kiírja a neki odaadott recept nevét, összetevőit és leírását
        -megkeresei az összetevőket a listán
*/
void receptkiiro(Osszetevo *meglevoosszetevok,Recept *kivalasztott)
{
    if (kivalasztott==NULL)
        printf("CRASH");
    int R=0;
    printf("\nTalalat:\n---------\n%s\n---------\nHozzavalok:\n", kivalasztott->nev);
    while (kivalasztott->hozza[0][R] !=-1)
    {
        Osszetevo *mozgo;
        mozgo=meglevoosszetevok;
        while (mozgo !=NULL)
        {
            if (kivalasztott->hozza[0][R] ==mozgo->sorszam)
            {
                printf("    %s-bol kell: %d %s\n",mozgo->nev, kivalasztott->hozza[1][R],mozgo->mertek);
                break;
            }
            mozgo=mozgo->kovossz;
        }
        R++;
    }
    printf("---------\n%s\n---------\n", kivalasztott->leiras);
}
/*
    *Neki megadott receptet keres
        -bekér egy nevet, amit végigfuttat a meglévő recepteken
        -ha megtalálta, kiíratja és kilép
        -ha nem találja, átirányit a választott helyekre:
            +új recept
            +új keresés
*/
int /*Z1*/receptkereso(Osszetevo *meglevoosszetevok,Recept *meglevorecept)
{
    printf("Melyik receptet keresed?\n");
    char keresett[101];
    szovegmerettel(keresett);
    //printf("%s..",keresett);
    bool megvan =true;
    Recept *mozgo=meglevorecept;
    while(mozgo!=NULL)
    {
        if (strcmp(mozgo->nev, keresett)==0)
        {
            receptkiiro(meglevoosszetevok,mozgo);
            megvan=true;
            break;
        }
        else
        {
            megvan = false;
        }
        mozgo=mozgo->kovrec;
    }
    int valasz;
    if (megvan== false)
    {
        printf("Nem letezik: %s\n1. letrehozom\n2. ujat keresek\n0. vissza\nValaszod: ",keresett);

        do
        {
            scanf("%d", &valasz);
            switch (valasz)
            {
            case 2:
                return 1;
                break;
            case 1:
                meglevorecept=ujrecept(meglevorecept,meglevoosszetevok);
                printf("Sikerult letrehozni az uj receptet :)\n");
                valasz= 0;
                break;
            case 0:
                break;
            default:
                printf("\nErvenytelen szam\n1. letrehozom\n2. ujat keresek\n0. vissza\nValaszod: ");
                break;
            }
        }
        while (valasz !=0);
    }
    return 0;
}
/*
    *mekérdt receptnév alapján kikeresi a receptet
    *ha megvan:
        -visszakérdez, hogy biztosan törölni akarja-e a felhasználó a receptet
        -nem létező / rossz keresést kezeli
    *törlésnél a listát módosítja:
        -listából kifűzi az elemet és felszabadítja a memóriát
*/
int recepttorlo(Osszetevo *meglevoosszetevok,Recept *meglevorecept)
{
    printf("Melyik receptet akarod torolni?\n");
    char keresett[101];
    szovegmerettel(keresett);
    int valasz;
    bool megvan =true;
    Recept *mozgo=meglevorecept->kovrec, *lemarado=meglevorecept;
    while (mozgo!=NULL)
    {
        if (strcmp(mozgo->nev, keresett)==0)
        {
            receptkiiro(meglevoosszetevok,mozgo);
            printf("Bitosan torlod?\n0. Nem, vissza\n11. Igen, torlom!\nValaszod: ");
            do
            {
                scanf("%d", &valasz);
                switch (valasz)
                {
                case 11:
                    printf("Recept torlese veglegesen...\n");
                    lemarado->kovrec=mozgo->kovrec;
                    free(mozgo->leiras);
                    free(mozgo);
                    return 0;
                    break;
                case 0:
                    return 0;
                    break;
                default:
                    printf("\nErvenytelen szam\n0. Nem, vissza\n11. Igen, torlom!\nValaszod: ");
                    break;
                }
            }
            while (valasz !=0);
            megvan=true;
            break;
        }
        else
            megvan= false;
        lemarado=lemarado->kovrec;
        mozgo=mozgo->kovrec;
    }
    if (megvan== false)
    {
        printf("Nem letezik: %s\n1. ujat keresek\n0. vissza\nValaszod: ",keresett);
        do
        {
            scanf("%d", &valasz);
            switch (valasz)
            {
            case 1:
                return 1;
                break;
            case 0:
                break;
            default:
                printf("\nErvenytelen szam\n1. ujat keresek\n0. vissza\nValaszod: ");
                break;
            }
        }
        while (valasz !=0);
    }
    return 0;
}
//Easter egg
void EE()
{
    int a;
    scanf("%d", &a);
    if (a==420)
        system("START https://www.youtube.com/watch?v=dQw4w9WgXcQ");

}
/*
    *meglévő receptek közül sorsol egyet és kiiratja
*/
int /*Z2*/ randomrecept(Osszetevo *meglevoosszetevok,Recept *meglevorecept)
{
    srand(time(0));
    int i=rand()%1000+1;
    Recept *mozgo;
    mozgo=meglevorecept;
    if (meglevorecept ==NULL)
    {
        printf("Nincs recept");
        return 0;
    }
    else
    {
        for (int j=0; j<i; j++)
        {
            if (mozgo != NULL)
                mozgo=mozgo->kovrec;
            else
                mozgo=meglevorecept;
        }
        if (mozgo==NULL)
            mozgo=meglevorecept;
        receptkiiro(meglevoosszetevok,mozgo);
        printf("\nElfogadod?\n0 - igen (vissza a menube)\n1 - nem (ujra)\nValaszod: ");
        int szam;
        do
        {
            scanf("%d", &szam);
            switch (szam)
            {
            case 1:
                printf("\n\n");
                return 1;
                break;
            case 0:
                break;
            default:
                printf("\nErvenytelen szam\n1. ujat keresek\n0. vissza\nValaszod: ");
                break;
            }
        }
        while (szam !=0);
    }
    return 0;
}

/*
    *Új hozzávalót hoz létre
        -szovegmerettel függvénnyel bekéri az adatokat
        -létrehoz egy új összetevőt
        -feltölti az adatokat az ujo-ba
        -kapott osszetevok lista végére fűzi az új összetevőt
    *dinamikusan foglal helyet
*/
Osszetevo *hozzavalohozzaad(Osszetevo *meglevoosszetevok)
{
    Osszetevo *mozgo=meglevoosszetevok, *ujo=(Osszetevo*)malloc(sizeof(Osszetevo));
    ujo->kovossz=NULL;
    printf("Add meg a hozzavalo nevet: ");
    szovegmerettel(ujo->nev);           //Feltölti az újat
    printf("Add meg a hozzavalo mertekegyseget: ");
    szovegmerettel(ujo->mertek);
    while(mozgo->kovossz!=NULL) //Lista vége keresése
        mozgo=mozgo->kovossz;
    mozgo->kovossz=ujo;
    ujo->sorszam=mozgo->sorszam+1;
    return meglevoosszetevok;
}
/*
    *Új receptet hoz létre
        -címet kér be
        -összes hozzávalót kiiratja
        -berkéri a használandó hozzávalókat és a mennyiséget ami kell belőlük
            /új igénye esetén meghíva az hozzavalohozzaad fgv-t
        -elkészítési módot bekér: bármilyen hosszú sort írhat a felhasználó
    *hozzáadja a meglévő receptek listához
*/
Recept* ujrecept(Recept *meglevorecept, Osszetevo *meglevoosszetevok)
{
    Recept *ujr=(Recept*)malloc(sizeof(Recept));
    ujr->kovrec=NULL;
    printf("\nIrd le a cimet:\n");
    szovegmerettel(ujr->nev);
    printf("(%s)\n",ujr->nev);
    printf("Milyen osszetevok kellenek? Eddig ezekbol valaszthatsz:\n");
    printf("-1 - tovabblepes\n0 - uj hozzavalo letrehozasa\n");
    Osszetevo *mozgo=meglevoosszetevok;
    while (mozgo!=NULL)
    {
        printf("%d - %s - %s\n", mozgo->sorszam, mozgo->nev, mozgo->mertek);
        mozgo=mozgo->kovossz;
    }
    printf("Egyesevel ird a hozzavalok szamat\n(enterrel elvalasztva)\n");
    int hozzaszam=0, hozzavaloksors=0, mennyiseg;
    do
    {
        scanf("%d", &hozzaszam);
        if (hozzaszam >0 || hozzaszam < -1) //ha vlamilyen hozzávalót választott
        {
            bool nincs =false;
            mozgo=meglevoosszetevok;
            while (mozgo!=NULL) //végigmegyünk a hozzávalókon
            {
                if (mozgo->sorszam == hozzaszam)//kikeresem a hozzavalot
                {
                    printf("Mennyi kell %s -bol?\n",mozgo->nev);
                    scanf(" %d", &mennyiseg);
                    ujr->hozza[0][hozzavaloksors]=hozzaszam;
                    ujr->hozza[1][hozzavaloksors++]=mennyiseg;
                    printf("%s -bol kell: %d %s\nKovetkezo: ", mozgo->nev, mennyiseg, mozgo->mertek);
                    nincs =false;
                    break;
                }
                else
                    nincs =true;
                mozgo=mozgo->kovossz;
            }
            if (nincs)
                printf("Nincs ilyen szamu hozzavalo: (%d) irj be masikat!\n", hozzaszam);
        }
        else
        {
            if (hozzaszam == 0)
            {
                meglevoosszetevok=hozzavalohozzaad(meglevoosszetevok);//meghívom az összetevő hozzáadása fgv-t
                mozgo=meglevoosszetevok;
                while (mozgo->kovossz!=NULL)
                    mozgo=mozgo->kovossz; //megkeresem az utolsót (végére fűzi)
                printf("%s : %s\n",mozgo->nev,mozgo->mertek);
                printf("Mennyi kell belole?\n");
                scanf(" %d", &mennyiseg);
                ujr->hozza[0][hozzavaloksors]=mozgo->sorszam;
                ujr->hozza[1][hozzavaloksors++]=mennyiseg;
                printf("%s -bol kell: %d %s\nKovetkezo: ", mozgo->nev, mennyiseg, mozgo->mertek);
            }
        }
    }
    while (hozzaszam != -1);
    ujr->hozza[0][hozzavaloksors]=hozzaszam;
    printf("Ird le az elkeszitesi modot (egy sorba)\n");
    getchar();
    ujr->leiras=szovegbekero();
    Recept *mozgo2 =meglevorecept;
    while (mozgo2->kovrec!=NULL) //Lista végére fűzés
        mozgo2=mozgo2->kovrec;
    mozgo2->kovrec=ujr;
    return meglevorecept;
}
/*
    Fő feladat: Receptek kiírása
    Két rész:
        1.listázza név szerint
            -a recepteken végiglépeget, megkeresi azokat amelyek megfelelnek a követelménynek
        2.Megkeresi azt az egyet amit adtak neki és kiiratja a receptkiiroval
*/
void ugyennekseged(Recept *meglevorecept, Osszetevo *meglevoosszetevok, Osszetevo *mozgo, int valasz)
{
    int sorszam=mozgo->sorszam, k=1;
    Recept *mozgorec=meglevorecept;
    while (mozgorec!=NULL) //végéig megyek a recepteken
    {
        int i=-1;
        while (mozgorec->hozza[0][++i] != -1) //végéig megyek a hozzavalokon
        {
            if (mozgorec->hozza[0][i]==sorszam) //megnézem hogy benne van-e a receptben
            {
                if (valasz==0)
                    printf("%d. %s\n",k,mozgorec->nev);
                if (valasz==k)
                    receptkiiro(meglevoosszetevok,mozgorec);
                k++;
            }
        }
        mozgorec=mozgorec->kovrec;
    }
    if (valasz>--k)
        printf("Ervenytelen szam\n");
}
/*
    Bekér egy összetevőt, megkeresi annak a sorszámát
    ugyennekseged-nek átadja a számot
    bekéri, melyik opciót választja a felhasználó
        -kilépés
        -valamelyik kiírt recept: átadja a segédnek
*/
int ugyennek(Recept *meglevorecept, Osszetevo *meglevoosszetevok)
{
    printf("Mit szeretnel enni? (osszetevok alapjan kereses)\n");
    char amitenne[101];
    szovegmerettel(amitenne);
    printf("\n");
    Osszetevo *mozgo=meglevoosszetevok;
    while (mozgo!=NULL && strcmp(mozgo->nev,amitenne)!=0)
        mozgo=mozgo->kovossz;
    bool megvan =false;
    if (mozgo==NULL)
        printf("Nem talaltam meg ezt: %s\n",amitenne); //Van ilyen összetevő?
    else
        megvan=true;
    int valasz;
    if (megvan)
    {
        printf("Melyiket kered? Ird be a szamat\n0. Egyiket sem (vissza)\n");
        ugyennekseged(meglevorecept,meglevoosszetevok,mozgo,0);
        printf("Nincs tobb megfelelo recept\n");
        printf("Valaszod: ");
        do
        {
            scanf(" %d", &valasz);
            if( valasz<0)
                printf("Ervenytelen szam\n");
            else
            {
                ugyennekseged(meglevorecept,meglevoosszetevok,mozgo,valasz);
                valasz=0;
            }
        }
        while(valasz!=0);
    }
    else
        printf("Nincs megfelelo recept\n");
    return 0;
}
