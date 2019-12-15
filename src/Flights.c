#include "Flights.h"

Flight* parseFlights(int* flightCount) {
    Flight* flights = (Flight*) malloc(0);

    FILE* flightsFile;
    FILE* destinationFile;
    int occupiedSeatCount, seatX, seatY, seatVip, i;
    char destinationFilename[75];

    flightsFile = fopen("donnees/avion.txt", "r");

    for(i = 0; feof(flightsFile) == 0; i++) {
        flights = (Flight*) realloc(flights, (i + 1) * sizeof(Flight));
        fscanf(flightsFile, "%s", flights[i].destination);
        fscanf(flightsFile, "%s", flights[i].plane);
        fscanf(flightsFile, "%s", flights[i].flightId);
        fscanf(flightsFile, "%d", &flights[i].rowCount);
        fscanf(flightsFile, "%d", &flights[i].columnCount);

        // on récupere l'horaire du vol
        fscanf(flightsFile, "%d %d %d %d %d",
            &flights[i].date.day,
            &flights[i].date.month,
            &flights[i].date.year,
            &flights[i].date.hour,
            &flights[i].date.minute);

        // on initialise toutes les places à 0 (places vides)
        for (int j = 0; j < flights[i].rowCount; j++) {
            for (int k = 0; k < flights[i].columnCount; k++) {
                flights[i].seats[j][k] = 0;
            }
        }

        // fichier spécifique pour chaque vol et on regarde s'il existe avec les nbr de place de bagages
        sprintf(destinationFilename, "donnees/destination/%s.txt", flights[i].destination);

        destinationFile = fopen(destinationFilename, "r+");

        if (destinationFile != NULL) {
            fscanf(destinationFile, "%f", &flights[i].luggagesWeight);
            fscanf(destinationFile, "%d", &flights[i].onboardCount);
            occupiedSeatCount = flights[i].rowCount * flights[i].columnCount - getFreeSeatCount(flights[i]);

            // on recupere les places qui sont déjà occupées et on le met dans l'avion
            for (int i = 0; i < occupiedSeatCount; i++) {
                fscanf(destinationFile, "%d", &seatX);
                fscanf(destinationFile, "%d", &seatY);
                fscanf(destinationFile, "%d", &seatVip);

                flights[i].seats[seatX][seatY] = seatVip + 1;
            }
        }
        else {
            // si le fichier de destination n'existe pas on initialise les variables à 0 et on crée le fichier
            destinationFile = fopen(destinationFilename, "w+");
            flights[i].luggagesWeight = 0;
            flights[i].onboardCount = 0;
            fprintf(destinationFile, "%f %d\n", flights[i].luggagesWeight, flights[i].onboardCount);
        }
        fclose(destinationFile);
    }
    fclose(flightsFile);

    // on fait un tri pour mettre les avion pleins en fin de tableau et pour ne pas avoir à les afficher
    qsort(flights, i, sizeof(Flight), sortFlights);

    *flightCount = i;
    return flights;

}

void displaySeats(Flight flight) {
    int x = flight.rowCount;
    int y = flight.columnCount;

    printf("\n. = libre");
    printf("\n1 = occupée");
    printf("\n2 = occupée par un VIP");

    printf("\n\n\t    ");

    for (int i = 0; i < x; i++) {
        printf((i < 9 ? "%d  " : "%d "), i + 1);
    }
    printf("\n\t   ");
    for (int i = 0; i < x; i++) {
        printf("---");
    }
    for (int i = 0; i < y; i++) {
        printf("\n\t%d | ", i + 1);

        for (int j = 0; j < x; ++j) {
            // We replace free seats by dots to be more lisible
            // `'0' + seat` is used here to parse an integer to a character
            char seat = flight.seats[j][i] != 0 ? '0' + flight.seats[j][i] : '.';
            printf("%c  ", seat);
        }
    }
    printf("\n");
}

int getFreeSeatCount(Flight flight) {
    int freeSeats = 0;

    for(int i = 0; i < flight.rowCount; i++) {
        for(int j = 0; j < flight.columnCount; j++) {
            if(flight.seats[i][j] == 0) {
                freeSeats++;
            }
        }
    }

    return freeSeats;
}

void addPassenger(Flight* flights, Ticket ticket) {
    char destinationFilename[75];
    FILE *destinationFile;
    int freeSeats, vipCount, luggageCount, lastData;
    float luggagesWeight;
    int destinationChoice = 0, occupiedSeatCount;

    // on recupere la destination du vol choisi par le passager
    while (strcmp(flights[destinationChoice].destination, ticket.destination) != 0) {
        destinationChoice++;
    }

    sprintf(destinationFilename, "donnees/destination/%s.txt", flights[destinationChoice].destination);
    destinationFile = fopen(destinationFilename, "r");

    if (destinationFile == NULL) {
        printf("Erreur : fichier de vol manquant");
        return;
    }

    // on recupere les 4 valeurs fixes
    fscanf(destinationFile, "%d %d %d %f %d", &freeSeats, &vipCount, &luggageCount, &luggagesWeight, &lastData);

    int **seats = (int **) malloc(freeSeats * sizeof(int *)); // on fait tableau d'entier avec le nbr de place prises
    occupiedSeatCount = flights[destinationChoice].rowCount * flights[destinationChoice].columnCount - freeSeats;
    for (int i = 0; i < occupiedSeatCount; i++) {
        seats[i] = (int *) malloc(3 * sizeof(int)); // une colonne x et y, plus priorité
        // on recupère les places dans le fichier
        fscanf(destinationFile, "%d %d %d", &seats[i][0], &seats[i][1], &seats[i][3]);
    }
    fclose(destinationFile); //on referme le fichier et apres on ecrase les données par dessus pour faire une modification

    destinationFile = fopen(destinationFilename, "w");

    // on met à jour les valeurs à changer
    freeSeats--;
    vipCount += ticket.vip;
    luggageCount += ticket.luggageCount;

    for (int j = 0; j < ticket.luggageCount; ++j) {
        luggagesWeight += ticket.luggages[j].weight;
    }

    // on remet tout dans le fichier puis on ajoute la nouvelle place dans le fichier
    fprintf(destinationFile, "%d %d %d %f %d\n", freeSeats, vipCount, luggageCount, luggagesWeight, lastData);

    for (int k = 0; k < occupiedSeatCount; ++k) {
        fprintf(destinationFile, "%d %d %d\n", seats[k][0], seats[k][1], seats[k][3]);
    }
    fprintf(destinationFile, "%d %d %d\n", ticket.seat.x, ticket.seat.y, ticket.vip);
    fclose(destinationFile);
    printf("\nEmbarquement enregistre");
}

void displaySecurityInfo() {
    printf("\nVous allez passer la securite, vous devez enlever les objets suivant: \n");
    printf("----------------------------------------------------------------------\n");
    printf("|\tTout produit liquide, parfum, gel douche, shampoing, lotion, dentifrice, >100ml chacun\n");
    printf("|\tArme à feu ou  munition ou cartouche pour armes de chasse ou de sport... Y compris explosif\n");
    printf("|\tArme blanche soit tout objet contondant, coupant qu'il soit métallique ou non (ciseaux, lame, cutter...)\n");
    printf("|\tTout produit inflamable, acide, pesticide....\n");
    printf("|\tBatterie lithuim > 160 Wh\n");
    printf("----------------------------------------------------------------------\n");
}

void checkFrontiers(Flight* flights, Ticket* tickets, int ticketCount, int flightCount) {
    FILE *visaFile;
    visaFile = fopen("donnees/tableVisa.txt", "r");
    if (visaFile == NULL) {
        printf("\nFichier de Visa introuvable\n Veuillez reesayer....");
        return;
    }

    char ***countries = (char ***) malloc(flightCount * sizeof(char **));
    for (int i = 0; i < flightCount; i++) {
        countries[i] = (char **) malloc(2 * sizeof(char *));
    }
    for (int i = 0; i < flightCount; i++) {
        for (int j = 0; j < 2; j++) {
            // taille de 65 caractères max pour une destination
            countries[i][j] = (char *) malloc(65 * sizeof(char));
        }
    }
    
    // Get country/nationality associations
    rewind(visaFile);
    for (int i = 0; i < flightCount; i++) {
        fscanf(visaFile, "%s %s", countries[i][0], countries[i][1]);
    }

    for (int i = 0; i < ticketCount; i++) {
        for (int j = 0; j < flightCount; j++) {
            // On recherche l'association pays/nationalité voulue
            if (strcmp(tickets[i].destination, countries[j][0]) == 0) {
                // on compare la nationalité du passager avec sa destination
                if (strcmp(tickets[j].passenger.nationality, countries[j][1]) == 0) {
                    printf("\n| Passager %s %s \tNationalite %s a destination de %s  numero de billet %s \nPas besoin de Visa\n",
                        tickets[j].passenger.lastname, tickets[j].passenger.firstname, tickets[j].passenger.nationality, countries[j][0],
                        tickets[j].id);
                }
                else {
                    printf("\n| Passager %s %s \tNationalite %s billet num %s a besoin de presenter un Visa pour aller en %s \nVeuillez remettre votre Visa au service des douanes\n",
                        tickets[j].passenger.lastname, tickets[j].passenger.firstname, tickets[j].passenger.nationality,
                        tickets[j].id, countries[j][0]);
                }
            }
        }
    }
}

int sortFlights(const void* a, const void* b) {
    return getFreeSeatCount(*(Flight*)a) < getFreeSeatCount(*(Flight*)b);
}