
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// fonction du main
void affiPassager(billet passager);

billet ajoutPassager( avion *tabAvion);

void generBillet(billet passager, char *numBillet);

void affiSiege(int placeLibre[][500], int longeur, int largeur);

avion initalisationVol(char destination[], char modele[], int nbrplace, char numero[], int longueur, int largeur);


#ifndef NF05_PROJECT_FONCTION_H
#define NF05_PROJECT_FONCTION_H

#endif //NF05_PROJECT_FONCTION_H
