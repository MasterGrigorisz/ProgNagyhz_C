#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "meglevokBE.h"
#include "receptkezelo.h"
#include "fajliro.h"

int main(void)
{
    Recept *meglevorecept=NULL;
    Osszetevo *meglevoosszetevok=NULL;
    meglevoosszetevok =osszetevoBE(meglevoosszetevok);
    int torlovalasz;
    if (meglevoosszetevok ==NULL)
        printf("Nem sikerult megnyitni a fajlt (beolvasas)\n");
    else
    {
        meglevorecept =meglevokBE(meglevorecept);
        if (meglevorecept==NULL)
            printf("Nem sikerult megnyitni a fajlt (beolvasas)\n");
        else
        {
            printf("Ulj le mellem\nValamit mondok\nEhes vagy latom\nEgy uveg lekvart kibontok\nFigyelj...\n");
            int valasz;
            do
            {
                printf("\nFOMENU\n1. Enni szeretnek valamit\n2. Recept letrehozasa\n3. Recept torlese\n0. Kilepes\nValaszod: ");
                scanf("%d", &valasz);
                switch (valasz)
                {
                case 1:
                    receptkezelo(meglevoosszetevok,meglevorecept);
                    break;
                case 2:
                    meglevorecept=ujrecept(meglevorecept,meglevoosszetevok);
                    printf("Sikerult letrehozni az uj receptet :)\n");
                    break;
                case 3:
                    torlovalasz =1;
                    while (torlovalasz !=0)
                        torlovalasz=recepttorlo(meglevoosszetevok,meglevorecept);
                    break;
                case 69:
                    EE();
                    break;
                case 0:
                    printf("Joetvagyat!\n");
                    break;
                default:
                    printf("Ervenytelen szam\n");
                    break;
                }
            }
            while (valasz !=0);
            int hiba1, hiba2;
            hiba1 =fajlbairoRec(meglevorecept);
            if (hiba1 !=0)
                printf("Nem sikerult megnyitni a fajlt - nem sikerult a receptek mentese\n");
            hiba2 =fajlbairoOssz(meglevoosszetevok);
            if (hiba2 !=0)
                printf("Nem sikerult megnyitni a fajlt - nem sikerult az osszetevok mentese\n");

        }
    }
    return 0;
}
