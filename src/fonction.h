

#ifndef NF05_PROJECT_FONCTION_H
#define NF05_PROJECT_FONCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "struct.h"
// fonction du main
void displayTicket(billet passager);

void displayPassenger (billet *tabPassenger, int passengerNb);

int displayFlight (avion *tabPlane, int planeNb);

void selectPassenger(billet *tabPassenger, int passengerNb);

billet ajoutPassager( avion *tabAvion, int nbrAvions);

billet generBillet(billet passager);

billet deposeBag(billet passager );

ticketBagage generTicketBag( billet passsager, int n);

void affiSiege(int placeLibre[][500], int longeur, int largeur);

void securite();

int triVol (const void* a,const void* b);

avion * initialisationVol(int *nbrAvions);

billet * initialisationPassager(int *nbrPassager);

void boardFlight(avion *tabAvion, billet *tabPassager, int nbrAvions, int nbrPassager );

void clear();

billet *addPassenger(billet *strg, billet *tabPassager, int nb);

#endif //NF05_PROJECT_FONCTION_H
