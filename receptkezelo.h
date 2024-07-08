#ifndef RECEPTKEZELO_H_INCLUDED
#define RECEPTKEZELO_H_INCLUDED
#include "meglevokBE.h"
void receptkezelo(Osszetevo *meglevoosszetevok,Recept *meglevorecept);
void receptkiiro(Osszetevo *meglevoosszetevok,Recept *kivalasztott); //L
int /*Z1*/receptkereso(Osszetevo *meglevoosszetevok,Recept *meglevorecept);
int /*Z2*/ randomrecept(Osszetevo *meglevoosszetevok,Recept *meglevorecept); //L
int recepttorlo(Osszetevo *meglevoosszetevok,Recept *meglevorecept); //L
Osszetevo *hozzavalohozzaad(Osszetevo *meglevoosszetevok);
Recept* ujrecept(Recept *meglevorecept, Osszetevo *meglevoosszetevok);
void EE();
int /*Z3*/ ugyennek(Recept *meglevorecept, Osszetevo *meglevoosszetevok);
#endif // RECEPTKEZELO_H_INCLUDED
