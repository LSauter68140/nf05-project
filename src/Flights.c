#include "Flights.h"

Flight *parseFlights(int *flightCount) {
    Flight *flights = (Flight *) malloc(0);

    FILE *flightsFile;
    FILE *destinationFile;
    int seatX, seatY, seatVip, i;
    char destinationFilename[75];

    flightsFile = fopen("donnees/avion.txt", "r");

    for (i = 0; !feof(flightsFile); i++) {
        flights = (Flight *) realloc(flights, (i + 1) * sizeof(Flight));
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

            // on recupere les places qui sont déjà occupées et on le met dans l'avion
            for (int j = 0; !feof(destinationFile); j++) {
                fscanf(destinationFile, "%d", &seatX);
                fscanf(destinationFile, "%d", &seatY);
                fscanf(destinationFile, "%d", &seatVip);

                flights[i].seats[seatX][seatY] = seatVip + 1;
            }
        } else {
            // si le fichier de destination n'existe pas on initialise les variables à 0 et on crée le fichier
            destinationFile = fopen(destinationFilename, "w+");
            flights[i].luggagesWeight = 0;
            flights[i].onboardCount = 0;
            fprintf(destinationFile, "%f %d", flights[i].luggagesWeight, flights[i].onboardCount);
        }
        fclose(destinationFile);
    }
    fclose(flightsFile);

    // on fait un tri pour mettre les avion pleins en fin de tableau et pour ne pas avoir à les afficher
    qsort(flights, i, sizeof(Flight), sortFlights);

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
        char date[16];
        //formatDate(flights[i].date, date);

        printf("%d)", i + 1);
        printf("\tDestination : %s\n", flights[i].destination);
        printf("\tModele d'avion : %s\n", flights[i].plane);
        printf("\tDepart : %s\n\n", date);
    }
}

void displayAvailableFlightsList(Flight *flights, int flightCount) {
    for (int i = 0; i < flightCount && getFreeSeatCount(&flights[i]) > 0; ++i) {
        char date[16];
        // formatDate(flights[i].date, date);

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
    sprintf(destinationFilename, "donnees/destination/%s.txt", flight->destination);
    destinationFile = fopen(destinationFilename, "a");
    fprintf(destinationFile, "\n%d %d %d", ticket->seat.x, ticket->seat.y, ticket->vip);
    fclose(destinationFile);
}

void boardPassenger(Ticket *flightTickets, int flightTicketCount, int flightCount) {

    int checkVisa = 0, ticketIndex;

    // On embarque les passagers un par un
    while (flightTicketCount > 0) {
        printf("\n");
        for (int i = 0; i < flightTicketCount; i++) {
            printf("%d) %s %s\n", i + 1, flightTickets[i].passenger.lastname, flightTickets[i].passenger.firstname);
        }
        do {
            printf("Quel passager voulez-vous embarquer ? ");
            getValue("%d", &ticketIndex);
        } while (ticketIndex < 1 || ticketIndex > flightTicketCount);
        ticketIndex--;



        // on lui rappel s'il faut un visa ou non et on le fait embarquer seulement s'il en a un en sa possession
        checkFrontiers(flightTickets[ticketIndex], flightCount, &checkVisa);
        if (checkVisa == 1) {

            // Le passager peut maintenant déposer des bagages en soute
            // addLuggages(flightTickets[ticketIndex]);
            // On enlève le billet du tableau des passagers à embarquer
            for (int i = ticketIndex; i < flightTicketCount; i++) {
                // On décale toutes valeurs dans le tableau
                flightTickets[ticketIndex] = flightTickets[ticketIndex + 1];
            }
            flightTicketCount--;
        } else {
            printf("Vous ne pouvez pas faire embarquer le passager %s %s a destination de %s en raison d'un visa non valide et/ou non present\n",
                   flightTickets[ticketIndex].passenger.firstname, flightTickets[ticketIndex].passenger.lastname,
                   flightTickets[ticketIndex].destination);

        }
    }

}

void boardFlight(Flight *flights, int flightCount, Ticket *tickets, int ticketCount) {
    Ticket *flightTickets;
    int flightIndex, flightTicketIndex = 0;
    int flightTicketCount;


    displayFlightsList(flights, flightCount);
    do {
        printf("Quel vol voulez-vous faire embarquer ? ");
        getValue("%d", &flightIndex);
    } while (flightIndex < 1 || flightIndex > flightCount);
    flightIndex--;

    // On retrouve tous les billets de ce vol
    flightTickets = (Ticket *) malloc(
            flights[flightIndex].rowCount * flights[flightIndex].columnCount * sizeof(Ticket *));

    //displaySecurityInfo(flights[flightIndex]);

    // talbeau de VIP seulement
    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(tickets[i].destination, flights[flightIndex].destination) == 0 && tickets[i].vip == 1) {

            flightTickets[flightTicketIndex++] = tickets[i];
        }
    }

    // on embarque les VIP en premier et tant que tout les VIP n'ont pas embarqué on ne fait pas embarqer les autres

    if (flightTicketIndex > 0)
        boardPassenger(flightTickets, flightTicketIndex, flightCount);

    // pas tres propre mais je n'arrive pas à le faire fonctionner sinon
    // on reinisalise le tableau

    flightTicketIndex = 0;
    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(tickets[i].destination, flights[flightIndex].destination) == 0 && tickets[i].vip == 1) {

            flightTickets[flightTicketIndex++] = tickets[i];
        }
    }

    //printf("azer |%s|   |%s|", flightTickets[0].passenger.lastname, flightTickets[1].passenger.lastname);

    // on enleve les vip qui sont mtn dans l'avion du dossier passager
    updatePassenger(flightTickets, flightTicketIndex, tickets, &ticketCount);

    printf("ticket count %d\n", ticketCount);

    tickets = parseTickets(&ticketCount);
    // maintenant on peut faire embarquer les autres passagers

    flightTicketIndex = 0;
    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(tickets[i].destination, flights[flightIndex].destination) == 0 && tickets[i].vip == 0) {
            flightTickets[flightTicketIndex++] = tickets[i];
        }
    }
    if (flightTicketIndex > 0)
        boardPassenger(flightTickets, flightTicketIndex, flightCount);

    // on reinisalise le tableau

    flightTicketIndex = 0;
    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(tickets[i].destination, flights[flightIndex].destination) == 0 && tickets[i].vip == 0) {

            flightTickets[flightTicketIndex++] = tickets[i];
        }
    }

    // on enleve les passagers qui sont mtn dans l'avion du dossier passager
    updatePassenger(flightTickets, flightTicketIndex, tickets, &ticketCount);

    // on met a jour les vols et on met celui qui est parti dans l'historique
    updateFlight(flights, flightCount, flightIndex);
    free(flightTickets);
    printf("\n\nTous les passagers du vol ont bien embarqué. Bon voyage !\n");
}

void addFlight(Flight **flight, int *flightCount ){

    FILE *flightsFile = fopen("donnees/avion.txt", "a+");
    FILE *visaFile = fopen("donnees/tableVisa.txt","a+");
    Flight newFlight;
    char contryName[50], buffer[50], nationality[50];

    printf("--- Informations Vol ---\n");

    printf("\tDestination :\n");
    getLine(newFlight.destination, 50);
    printf("\t Modele :\n");
    getLine(newFlight.plane, 20);
    printf("\tNumero de Vol :\n");
    getLine(newFlight.flightId, 15);
    printf("\tNombre de place en longeur :\n");
    scanf("%d", &newFlight.columnCount);
    printf("\tNombre de place en largeur :\n");
    scanf("%d",&newFlight.rowCount);
    printf("### Horaire de depart : (jj/MM/AAAA HH/mm)\n");
    scanf("%d", &newFlight.date.day);
    scanf("%d", &newFlight.date.month); // si jamais motivé ajoiuter des conditions pour ne pas depasser 24h ou 31j ou 60min..
    scanf("%d", &newFlight.date.year);
    scanf("%d", &newFlight.date.hour);
    scanf("%d", &newFlight.date.minute);

    // on le met dans le fichier avion
    fprintf(flightsFile, "\n%s %s %s %d %d \t%d %d %d %d %d", newFlight.destination, newFlight.plane,
            newFlight.flightId, newFlight.rowCount, newFlight.columnCount,
            newFlight.date.day,newFlight.date.month, newFlight.date.year, newFlight.date.hour,
            newFlight.date.minute);

    // on verifie si le pays est déjà répertorier dans le ficher de visa ou non
    for (int i = 0; newFlight.destination[i] !='\0' ; ++i) {
        newFlight.destination[i] = tolower(newFlight.destination[i]);
    }


    while (feof(visaFile) == 0){
        fscanf(visaFile, "%s %s",contryName, buffer);
        contryName[1]= tolower(contryName[1]);
        if (strcmp(newFlight.destination, contryName)==0){
            break;
        }
    }

    if (strcmp(newFlight.destination, contryName)!=0){
        // ce qui veut dire que le pays n'est pas répertorier on l'ajoute
        printf("Quel est la nationalité des habitants au masculin de %s (information visa)\n", newFlight.destination);
        scanf("%c", buffer);
        getLine(nationality, 50);
        nationality[0]= toupper(nationality[0]); // on met la premiere lettre en majuscule uniquement
        for (int i = 1; nationality[i] !='\0' ; ++i) {
            nationality[i] = tolower(nationality[i]);
        }
        newFlight.destination[0]= toupper(newFlight.destination[0]);
        fprintf(visaFile, "\n%s %s",newFlight.destination, nationality);
    }
    fclose(visaFile);
    fclose(flightsFile);
    // on le rajoute dans le ficher flight;
    *flight = parseFlights(flightCount);
}

void updateFlight(Flight *flights, int flightCount, int flightIndex) {

    FILE *flightsFile = fopen("donnees/avion.txt", "w");
    FILE *historicFile = fopen("donnees/historique/ancienVol.txt", "a+");
    FILE *destFile;

    char pathDestination[80];
    int luggage, allPassenger =0 , vipPassenger =0, buffer;
    float weight;

    sprintf(pathDestination, "donnees/destination/%s.txt", flights[flightIndex].destination);
    destFile = fopen(pathDestination, "r");

    // on enleve le vol des vols disponible
    for (int i = 0; i < flightCount; ++i) {

        if (i != flightIndex) {
            if (i != 0)
                fprintf(flightsFile, "\n");
            fprintf(flightsFile, "%s %s %s %d %d \t%d %d %d %d %d", flights[i].destination, flights[i].plane,
                    flights[i].flightId, flights[i].rowCount, flights[i].columnCount,
                    flights[i].date.day,flights[i].date.month, flights[i].date.year, flights[i].date.hour,
                    flights[i].date.minute);

        }
    }

    // et on le met dans l'historique
    fprintf(historicFile, "%s %s %s %d %d %d %d %d %d %d", flights[flightIndex].destination, flights[flightIndex].plane,
            flights[flightIndex].flightId, flights[flightIndex].rowCount, flights[flightIndex].columnCount,
            flights[flightIndex].date.day,flights[flightIndex].date.month, flights[flightIndex].date.year, flights[flightIndex].date.hour,
            flights[flightIndex].date.minute);

    // on recupere les donnees du vol;
    fscanf(destFile, "%f %d", &weight, &luggage);

    while(feof(destFile) == 0){

        fscanf(destFile,"%d %d", &buffer, &buffer);
        fscanf(destFile, "%d", &buffer);
        vipPassenger += (buffer ==0 ) ? 0 : 1; // on rajoute 1 si vip sinon on ne change pas la valeur
        allPassenger ++;

    }

    // et on rajoute les donnees demandées
    fprintf(historicFile, " %d %f %d %d\n", luggage, weight, allPassenger, vipPassenger);

    fclose(flightsFile);
    fclose(destFile);
    fclose(historicFile);

}

void updatePassenger(Ticket *ticketTodelete, int flightTicketCount, Ticket *tickets, int *ticketCount) {

    FILE *ticketsFile;
    int exist, count = 0;
    ticketsFile = fopen("donnees/passagers.txt", "w+");
    //printf("hello %d %d %s -- %s", *ticketCount, flightTicketCount, ticketTodelete[0].passenger.lastname, ticketTodelete[1].passenger.lastname);
    // on remet dans le ficher seulement les passagers qui ne sont pas sur le vol qui vient de partir
    for (int i = 0; i < *ticketCount; ++i) {
        exist = 0;
        printf("%d\n", i);

        for (int j = 0; j < flightTicketCount; ++j) {
            if (strcmp(tickets[i].id, ticketTodelete[j].id) == 0) {
                exist = 1;
                break;
            }
        }
        if (exist == 0) {
            if (count > 0)
                fprintf(ticketsFile, "\n");
            fprintf(ticketsFile, "%s %s %s %d %d %s %s %s %d %d %d %d", tickets[i].id,
                    tickets[i].passenger.lastname, tickets[i].passenger.firstname, tickets[i].passenger.age,
                    tickets[i].passenger.gender, tickets[i].passenger.nationality,
                    tickets[i].passenger.passportNumber, tickets[i].destination, tickets[i].vip,
                    tickets[i].luggageCount,
                    tickets[i].seat.x, tickets[i].seat.y);
            count++;
        }
    }

    *ticketCount = count;

    fclose(ticketsFile);
}

void displaySecurityInfo(Flight flight) {

    printf("=== A l'attention de tout les passagers du vol %s a destination de %s===== \n", flight.flightId,
           flight.destination);
    printf("\nVous allez passer la securite, vous devez enlever les objets suivants :\n");
    printf("----------------------------------------------------------------------\n");
    printf("|\tTout produit liquide, parfum, gel douche, shampooing, lotion, dentifrice, >100ml chacun\n");
    printf("|\tArme à feu, munition ou cartouche pour armes de chasse ou de sport... Y compris explosif\n");
    printf("|\tArme blanche, soit tout objet contondant, coupant qu'il soit metallique ou non (ciseaux, lame, cutter...)\n");
    printf("|\tTout produit inflamable, acide, pesticide....\n");
    printf("|\tBatterie lithuim > 160 Wh\n");
    printf("----------------------------------------------------------------------\n");
}

void checkFrontiers(Ticket tickets, int flightCount, int *checkVisa) {
    FILE *visaFile;
    int j, visa;
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
        for (int k = 0; k < 2; k++) {
            // taille de 65 caractères max pour une destination
            countries[i][k] = (char *) malloc(65 * sizeof(char));
        }
    }

    // Get country/nationality associations
    rewind(visaFile);
    for (int i = 0; i < flightCount; i++) {
        fscanf(visaFile, "%s %s", countries[i][0], countries[i][1]);
    }

    for (j = 0; j < flightCount && strcmp(tickets.destination, countries[j][0]) != 0; ++j);


    if (strcmp(tickets.destination, countries[j][0]) == 0) {

        for(int i = 0; tickets.passenger.nationality[i]!= '\0'; i++) {
            tickets.passenger.nationality[i] = tolower(tickets.passenger.nationality[i]); // si jamais il y a une majuscule
        }

        if (strcmp(tickets.passenger.nationality, countries[j][1]) == 0) {
            printf("\n| Passager %s %s \tNationalite %s a destination de %s  numero de billet %s \nPas besoin de Visa\n",
                   tickets.passenger.lastname, tickets.passenger.firstname, tickets.passenger.nationality,
                   countries[j][0],
                   tickets.id);
            *checkVisa = 1;
        } else {
            printf("\n| Passager %s %s \tNationalite %s billet num %s a besoin de presenter un Visa pour aller en %s \nVeuillez remettre votre Visa au service des douanes\n",
                   tickets.passenger.lastname, tickets.passenger.firstname, tickets.passenger.nationality,
                   tickets.id, countries[j][0]);
            printf("\n\n\n === Service des douanes ===");
            printf("\n\n Etes vous bien en possesion d'un visa a jour ?\n (0) Non (1) Oui\n");
            scanf("%d", &visa);
            while (visa != 0 && visa != 1) {
                printf("\n valeur incorrecte \n");
                scanf("%d", &visa);
            }
            if (visa == 1) {
                *checkVisa = 1;
            }
        }
    }

/*
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
    }*/
}

int sortFlights(const void *a, const void *b) {
    return getFreeSeatCount((Flight *) a) < getFreeSeatCount((Flight *) b);
}