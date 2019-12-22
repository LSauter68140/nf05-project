#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Flights.h"

Flight *parseFlights(int *flightCount) {
    Flight *flights = malloc(0);

    FILE *flightsFile;
    FILE *destinationFile;
    int seatX, seatY, seatVip, i, luggagesCount;
    float luggagesWeight;
    char destinationFilename[75];
    char choice;

    flightsFile = fopen("data/flights.txt", "r");
    if (flightsFile == NULL){
        // on crée le fichier
        createPath("data");
        printf("\n Aucun vol trouve \n");
        do{
            printf("Voulez vous en ajouter un ? (O) ou quitter le programme et ajouter un fichier à data/flights.txt (n)\n");
            getValue("%c", &choice);

        } while (choice != 'o' && choice != 'O' && choice != 'n' && choice != 'N');
        if (choice == 'n' || choice == 'N')
            exit(EXIT_SUCCESS);



        flights = addFlight(flights,flightCount);
        printf("nbr vol %d qsdf |%s|", *flightCount, flights[0].destination);
        fclose(flightsFile);
        return flights;
    }



    for (i = 0; !feof(flightsFile); i++) {
        flights = realloc(flights, (i + 1) * sizeof(Flight));
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
        sprintf(destinationFilename, "data/flights/%s.txt", flights[i].destination);

        destinationFile = fopen(destinationFilename, "r+");

        if (destinationFile != NULL) {
            fscanf(destinationFile, "%f %d", &luggagesWeight, &luggagesCount);

            // on recupere les places qui sont déjà occupées et on le met dans l'avion
            for (int j = 0; !feof(destinationFile); j++) {
                fscanf(destinationFile, "%d", &seatX);
                fscanf(destinationFile, "%d", &seatY);
                fscanf(destinationFile, "%d", &seatVip);

                flights[i].seats[seatX][seatY] = seatVip + 1;
            }
        } else {
            // Si le dossier n'existe pas, on le crée
            createPath("data/flights");
            luggagesWeight = 0;
            luggagesCount = 0;

            // on crée le fichier
            destinationFile = fopen(destinationFilename, "w+");
            fprintf(destinationFile, "%f %d", luggagesWeight, luggagesCount);
        }
        fclose(destinationFile);
    }
    fclose(flightsFile);

    // on fait un tri pour mettre les avion pleins en fin de tableau et pour ne pas avoir à les afficher
    qsort(flights, i, sizeof(Flight), compareFlights);

    *flightCount = i;
    return flights;
}

void displaySeats(Flight *flight) {
    int x = flight->rowCount;
    int y = flight->columnCount;

    printf("\n. = libre");
    printf("\n1 = occupee");
    printf("\n2 = occupee par un VIP");

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
            char seat = flight->seats[j][i] != 0 ? '0' + flight->seats[j][i] : '.';
            printf("%c  ", seat);
        }
    }
    printf("\n");
}

void displayFlightsList(Flight *flights, int flightCount) {
    for (int i = 0; i < flightCount; i++) {
        char date[17];
        formatDate(flights[i].date, date);

        printf("%d)", i + 1);
        printf("\tDestination : %s\n", flights[i].destination);
        printf("\tModele d'avion : %s\n", flights[i].plane);
        printf("\tDepart : %s\n\n", date);
    }
}

void displayAvailableFlightsList(Flight *flights, int flightCount) {
    flights = parseFlights(&flightCount);
    for (int i = 0; i < flightCount && getFreeSeatCount(&flights[i]) > 0; ++i) {
        char date[17];
        formatDate(flights[i].date, date);

        printf("%d)", i + 1);
        printf("\tDestination : %s\n", flights[i].destination);
        printf("\tModele d'avion : %s\n", flights[i].plane);
        printf("\tDepart : %s\n\n", date);
    }
}

int getFreeSeatCount(Flight *flight) {
    int freeSeats = 0;
    for (int i = 0; i < flight->rowCount; i++) {
        for (int j = 0; j < flight->columnCount; j++) {
            if (flight->seats[i][j] == 0) {
                freeSeats++;
            }
        }
    }

    return freeSeats;
}

int getAvailableFlightCount(Flight *flights, int flightCount) {
    int i;
    for (i = 0; i < flightCount && getFreeSeatCount(&flights[i]) > 0; i++);
    return i;
}

void saveSeat(Flight *flight, Ticket *ticket) {
    char destinationFilename[75];
    FILE *destinationFile;

    // On ajoute la place choisie
    sprintf(destinationFilename, "data/flights/%s.txt", flight->destination);
    destinationFile = fopen(destinationFilename, "a");
    fprintf(destinationFile, "\n%d %d %d", ticket->seat.x, ticket->seat.y, ticket->vip);
    fclose(destinationFile);
}

void boardPassengers(Ticket *flightTickets, int flightTicketCount, int flightCount) {
    int ticketIndex;

    // On embarque les passagers un par un
    while (flightTicketCount > 0) {
        printf("\n");
        for (int i = 0; i < flightTicketCount; i++) {
            printf("%d) %s %s\n", i + 1, flightTickets[i].passenger.lastname, flightTickets[i].passenger.firstname);
        }
        do {
            printf("Quel passager voulez-vous faire embarquer ? ");
            getValue("%d", &ticketIndex);
        } while (ticketIndex < 1 || ticketIndex > flightTicketCount);
        ticketIndex--;

        // On rappelle au passager s'il a besoin d'un visa ou non et on le fait embarquer seulement s'il en a un en sa possession
        if (checkFrontiers(&flightTickets[ticketIndex], flightCount)) {
            // Le passager peut maintenant déposer des bagages en soute
            addLuggages(&flightTickets[ticketIndex]);
        } else {
            printf("Vous ne pouvez pas faire embarquer le passager %s %s a destination de %s en raison d'un visa non valide et/ou non present\n",
                   flightTickets[ticketIndex].passenger.firstname, flightTickets[ticketIndex].passenger.lastname,
                   flightTickets[ticketIndex].destination);
        }

        // On enlève le billet du tableau des passagers à embarquer
        for (int i = ticketIndex; i < flightTicketCount; i++) {
            // On décale toutes valeurs dans le tableau
            flightTickets[ticketIndex] = flightTickets[ticketIndex + 1];
        }
        flightTicketCount--;
    }

}

void boardFlight(Flight *flights, int *flightCount, Ticket *tickets, int ticketCount) {
    Ticket *flightTickets;
    int flightIndex, flightTicketCount = 0;
    int passengerCount =0;

    displayFlightsList(flights, *flightCount);
    do {
        printf("Quel vol voulez-vous faire embarquer ? ");
        getValue("%d", &flightIndex);
    } while (flightIndex < 1 || flightIndex > *flightCount);
    flightIndex--;

    // On retrouve tous les billets de ce vol
    flightTickets = malloc(flights[flightIndex].rowCount * flights[flightIndex].columnCount * sizeof(Ticket *));

    displaySecurityInfo(&flights[flightIndex]);

    // On embarque les passagers VIP en premier, puis les autres passagers
    for (int vip = 1; vip >= 0; vip--) {
        // On récupère un tableau de passagers VIP ou non uniquement
        for (int i = 0; i < ticketCount; i++) {
            if (strcmp(tickets[i].destination, flights[flightIndex].destination) == 0 && tickets[i].vip == vip) {
                flightTickets[flightTicketCount++] = tickets[i];
            }
        }
        passengerCount += flightTicketCount;
        if (flightTicketCount > 0) {
            if (vip) {
                printf("\n--- Embarquement des passagers prioritaires ---\n");
            }
            else {
                printf("\n--- Embarquement des passagers non prioritaires ---\n");
            }

            // on embarque les passagers
            boardPassengers(flightTickets, flightTicketCount, *flightCount);

            // on enleve les passagers qui sont maintenant dans l'avion
            deleteTickets(flightTickets, flightTicketCount, tickets, &ticketCount);
            flightTicketCount = 0;
        }
    }

    // on met le vol qui est parti dans l'historique

    removeFlight(flights, flightCount, flightIndex);
    free(flightTickets);
    if (passengerCount){
        printf("\n\nTous les passagers du vol ont bien embarqué. Bon voyage !\n");
    }else{
        printf("\n\n L'avion est parti vide car aucun passagers inscris.\n");
    }

}

Flight* addFlight(Flight *flights, int *flightCount) {

    FILE *flightsFile = fopen("data/flights.txt", "a+");
    FILE *visaFile = fopen("data/nationalities.txt","a+");
    Flight newFlight;
    char contryName[50], buffer[50], nationality[50];

    printf("\tDestination : ");
    getLine(newFlight.destination, 50);
    printf("\tModele : ");
    getLine(newFlight.plane, 20);
    printf("\tNumero de vol : ");
    getLine(newFlight.flightId, 15);
    printf("\tNombre de places en longeur : ");
    getValue("%d", &newFlight.columnCount);
    printf("\tNombre de places en largeur : ");
    getValue("%d", &newFlight.rowCount);
    printf("\tDate de depart\n");
    do {
        printf("\t\tJour [1 - 31] : ");
        getValue("%d", &newFlight.date.day);
    } while(newFlight.date.day < 1 || newFlight.date.day > 31);
    do {
        printf("\t\tMois [1 - 12] : ");
        getValue("%d", &newFlight.date.month);
    } while(newFlight.date.month < 1 || newFlight.date.month > 12);
    printf("\t\tAnnee : ");
    getValue("%d", &newFlight.date.year);
    do {
        printf("\t\tHeure [0 - 23] : ");
        getValue("%d", &newFlight.date.hour);
    } while(newFlight.date.hour < 0 || newFlight.date.hour > 23);
    do {
        printf("\t\tMinutes [0 - 59] : ");
        getValue("%d", &newFlight.date.minute);
    } while(newFlight.date.minute < 0 || newFlight.date.minute > 59);

    // on le met dans le fichier avion
    fseek(flightsFile, SEEK_END-1, SEEK_SET);
    if (ftell(flightsFile)!= 0)
        fprintf(flightsFile,"\n");
    fprintf(flightsFile, "%s %s %s %d %d \t%d %d %d %d %d", newFlight.destination, newFlight.plane,
            newFlight.flightId, newFlight.rowCount, newFlight.columnCount,
            newFlight.date.day,newFlight.date.month, newFlight.date.year, newFlight.date.hour,
            newFlight.date.minute);

    // on verifie si le pays est déjà répertorié dans le ficher de visa ou non
    for (int i = 0; newFlight.destination[i] != '\0' ; ++i) {
        newFlight.destination[i] = tolower(newFlight.destination[i]);
    }

    while (!feof(visaFile)) {
        fscanf(visaFile, "%s %s", contryName, buffer);
        contryName[0] = tolower(contryName[0]);

        if (strcmp(newFlight.destination, contryName) == 0) {
            // Le pays est déjà répertorié
            break;
        }
    }

    // Si le pays n'est pas répertorié, on l'ajoute au fichier
    if (strcmp(newFlight.destination, contryName) != 0) {
        newFlight.destination[0] = toupper(newFlight.destination[0]);
        printf("\tQuelle est la nationalité (au masculin) des habitants de %s ? ", newFlight.destination);
        getLine(nationality, 50);

        // On met la première lettre en majuscule uniquement
        nationality[0] = toupper(nationality[0]);
        for (int i = 1; nationality[i] != '\0' ; ++i) {
            nationality[i] = tolower(nationality[i]);
        }
        if (ftell(visaFile) !=0)
            fprintf(visaFile, "\n");
        fprintf(visaFile, "%s %s", newFlight.destination, nationality);
    }

    fclose(visaFile);
    fclose(flightsFile);

    // on le rajoute dans la liste des vols
    (*flightCount)++;
    flights = realloc(flights, *flightCount * sizeof(Flight));
    flights[*flightCount - 1] = newFlight;

    return flights;
}

void removeFlight(Flight *flights, int *flightCount, int flightIndex) {
    FILE *flightsFile = fopen("data/flights.txt", "w");
    FILE *historyFile = fopen("data/history/flights.txt", "a+");
    FILE *destinationFile;
    char destinationFilename[70];
    int passengerCount = 0, vipCount = 0, luggagesCount;
    float luggagesWeight;

    // On ouvre le fichier du vol
    sprintf(destinationFilename, "data/flights/%s.txt", flights[flightIndex].destination);
    destinationFile = fopen(destinationFilename, "r");
    if (destinationFile == NULL) {
        printf("Erreur : fichier %s manquant", destinationFilename);
        return;
    }

    // on recupere le poids des bagages et leur nombre
    fscanf(destinationFile, "%f %d", &luggagesWeight, &luggagesCount);

    while(!feof(destinationFile)) {

        int vip;
        fscanf(destinationFile, "%d %d %d", &vip, &vip, &vip);
        vipCount += (vip == 0) ? 0 : 1; // on rajoute 1 si vip sinon on ne change pas la valeur
        passengerCount++;
    }

    // On ajoute le vol dans le fichier de l'historique des vols
    fseek(historyFile, SEEK_END-1,SEEK_SET);
    if (ftell(historyFile)!=0)
        fprintf(historyFile, "%n");

    fprintf(historyFile, "%s %s %s %d %d %d %d %d %d %d %f %d %d %d\n", flights[flightIndex].destination, flights[flightIndex].plane,
            flights[flightIndex].flightId, flights[flightIndex].rowCount, flights[flightIndex].columnCount,
            flights[flightIndex].date.day,flights[flightIndex].date.month, flights[flightIndex].date.year, flights[flightIndex].date.hour,
            flights[flightIndex].date.minute, luggagesWeight, luggagesCount, passengerCount, vipCount);

    // On remet tous les vols dans le fichier, sauf celui à supprimer
    for (int i = 0; i < *flightCount; ++i) {
        if (i != flightIndex) {
            if (i > 0) {
                fprintf(flightsFile, "\n");
            }
            fprintf(flightsFile, "%s %s %s %d %d \t%d %d %d %d %d", flights[i].destination, flights[i].plane,
                    flights[i].flightId, flights[i].rowCount, flights[i].columnCount,
                    flights[i].date.day,flights[i].date.month, flights[i].date.year, flights[i].date.hour,
                    flights[i].date.minute);
            printf("\n %d", i);
        }
        else {
            // On enlève le vol du tableau des vols
            printf("%d \n", *flightCount);
            for (int j = i; j < (*flightCount)- 1; j++) {
                // On décale tous les éléments vers le début du tableau
                flights[j] = flights[j + 1];

            }


            // On décrémente i pour compenser le fait d'avoir supprimé un élément du tableau
            i--;
            (*flightCount) --;
            flightIndex = -1;

        }
    }


    fclose(flightsFile);
    fclose(destinationFile);
    fclose(historyFile);
}

void deleteTickets(Ticket *ticketsToDelete, int ticketsToDeleteCount, Ticket *tickets, int *ticketCount) {
    FILE *ticketsFile;
    int keepPassenger;
    ticketsFile = fopen("data/passengers.txt", "w+");

    for (int i = 0; i < *ticketCount; ++i) {
        keepPassenger = 1;

        // On cherche si le billet fait parmis de ceux à supprimer
        for (int j = 0; j < ticketsToDeleteCount; ++j) {
            if (strcmp(tickets[i].id, ticketsToDelete[j].id) == 0) {
                keepPassenger = 0;

                // On enlève le billet du tableau des billets
                for (int k = i; k < *ticketCount; k++) {
                    // On décale tous les éléments du tableau vers le début
                    tickets[k] = tickets[k + 1];

                    // On décrémente i pour compenser le fait
                    // que l'on ait supprimé un élément du tableau
                    i--;
                }

                // On met à jour le nombre de billets dans le tableau
                (*ticketCount)--;
                break;
            }
        }
        // Si on doit garder le passager, on le réécrit dans le fichier
        if (keepPassenger) {
            if (ftell(ticketsFile) != 0) {
                fprintf(ticketsFile, "\n");
            }
            fprintf(ticketsFile, "%s %s %s %d %d %s %s %s %d %d %d %d", tickets[i].id,
                    tickets[i].passenger.lastname, tickets[i].passenger.firstname, tickets[i].passenger.age,
                    tickets[i].passenger.gender, tickets[i].passenger.nationality,
                    tickets[i].passenger.passportNumber, tickets[i].destination, tickets[i].vip,
                    tickets[i].luggageCount,
                    tickets[i].seat.x, tickets[i].seat.y);
        }
    }

    fclose(ticketsFile);
}

void displaySecurityInfo(Flight *flight) {
    printf("\n=== A l'attention de tous les passagers du vol %s a destination de %s ===\n",
            flight->flightId, flight->destination);
    printf("\nVous allez passer la securite, vous devez enlever les objets suivants :\n");
    printf("----------------------------------------------------------------------\n");
    printf("|\tTout produit liquide, parfum, gel douche, shampooing, lotion, dentifrice, >100ml chacun\n");
    printf("|\tArme à feu, munition ou cartouche pour armes de chasse ou de sport... Y compris explosif\n");
    printf("|\tArme blanche, soit tout objet contondant, coupant qu'il soit metallique ou non (ciseaux, lame, cutter...)\n");
    printf("|\tTout produit inflamable, acide, pesticide....\n");
    printf("|\tBatterie lithuim > 160 Wh\n");
    printf("----------------------------------------------------------------------\n");
}

int checkFrontiers(Ticket *ticket, int flightCount) {
    FILE *nationalitiesFile;
    int j, result = 0;
    char hasVisa;

    char ***nationalities = malloc(flightCount * sizeof(char **));

    for (int i = 0; i < flightCount; i++) {
        printf("\n %d", i);
        nationalities[i] = malloc(2 * sizeof(char *));

        for (int k = 0; k < 2; k++) {
            // taille de 50 caractères max pour une destination
            nationalities[i][k] = malloc(50 * sizeof(char));
        }
    }

    // On ouvre le fichier qui associe les pays à leur nationalité
    nationalitiesFile = fopen("data/nationalities.txt", "r");
    if (nationalitiesFile == NULL) {
        printf("Fichier data/nationalities.txt introuvable, veuillez reessayer\n");
    }
    else {
        // On lit le fichier
        rewind(nationalitiesFile);
        
        for (int i = 0; i < flightCount; i++) {
            fscanf(nationalitiesFile, "%s %s", nationalities[i][0], nationalities[i][1]);
        }

        for (j = 0; j < flightCount && strcmp(ticket->destination, nationalities[j][0]) != 0; ++j);

        if (strcmp(ticket->destination, nationalities[j][0]) == 0) {
            for(int i = 0; ticket->passenger.nationality[i]!= '\0'; i++) {
                ticket->passenger.nationality[i] = tolower(ticket->passenger.nationality[i]); // si jamais il y a une majuscule
            }

            printf("\tPassager : %s %s\n\tNationalite : %s\n\tDestination : %s\n\tNumero de billet : %s\n",
                    ticket->passenger.lastname, ticket->passenger.firstname, ticket->passenger.nationality,
                    ticket->destination, ticket->id);

            printf("\n--- Service des douanes ---\n");

            if (strcmp(ticket->passenger.nationality, nationalities[j][1]) == 0) {
                printf("--> Pas besoin de Visa\n");
                result = 1;
            } else {
                printf("--> Besoin de presenter un visa\n");
                
                do {
                    printf("\nEtes-vous bien en possession d'un visa a jour (O/N) ? ");
                    getValue("%c", &hasVisa);
                } while(hasVisa != 'O' && hasVisa != 'o' && hasVisa != 'N' && hasVisa != 'n');

                if (hasVisa == 'O' || hasVisa == 'o') {
                    result = 1;
                }
            }
        }
    }

    // Free memory
    for (int i = 0; i < flightCount; i++) {
        for (int k = 0; k < 2; k++) {
            free(nationalities[i][k]);
        }

        free(nationalities[i]);
    }
    free(nationalities);

    return result;
}

int compareFlights(const void *a, const void *b) {
    return getFreeSeatCount((Flight *)b) - getFreeSeatCount((Flight *)a);
}