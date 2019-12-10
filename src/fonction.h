
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


// fonction du main
void affiPassager(billet passager);

billet ajoutPassager( avion *tabAvion, int nbrAvions);

billet generBillet(billet passager);

billet deposeBag(billet passager );

ticketBagage generTicketBag( billet passsager, int n);

void affiSiege(int placeLibre[][500], int longeur, int largeur);

void securite();

int triVol (const void* a,const void* b);

avion * initialisationVol(int *nbrAvions);

billet * initialisationPassager(int *nbrPassager);

#ifndef NF05_PROJECT_FONCTION_H
#define NF05_PROJECT_FONCTION_H

#endif //NF05_PROJECT_FONCTION_H
