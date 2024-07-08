#ifndef MEGLEVOKBE_H_INCLUDED
#define MEGLEVOKBE_H_INCLUDED
#include "meglevokBE.h"
/* Egy összetevõ felépítése */
typedef struct Osszetevo
{
    char nev[101];
    int sorszam;
    char mertek[101];
    struct Osszetevo *kovossz;
} Osszetevo;
/* Egy teljes recept felépítése */
typedef struct Recept
{
    char nev[101];
    int hozza[2][30];
    char *leiras;
    struct Recept *kovrec;
} Recept;

Recept *meglevokBE (Recept *eleje);
Osszetevo *osszetevoBE(Osszetevo *eleje);

#endif // MEGLEVOKBE_H_INCLUDED
