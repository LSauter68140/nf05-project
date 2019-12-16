#include "Tickets.h"

Ticket* parseTickets(int* ticketCount) {
    Ticket* tickets = (Ticket*) malloc(0);
    int count = 0;

    FILE *ticketsFile;
    ticketsFile = fopen("donnees/passagers.txt", "r");
    if (ticketsFile == NULL) {
        printf("Erreur fichier manquant donnees/passagers.txt, veuillez reessayer");
        return 0;
    }

    while (feof(ticketsFile) == 0) {
        tickets = (Ticket*) realloc(tickets, (count + 1) * sizeof(Ticket));

        // On recupère les infos du billet
        fscanf(ticketsFile, "%s %s %s %s %d %d %d %s %s %d %d %d",
            tickets[count].id, tickets[count].destination,
            tickets[count].passenger.firstname, tickets[count].passenger.lastname, &tickets[count].passenger.age,
            &tickets[count].passenger.gender, &tickets[count].vip,
            tickets[count].passenger.nationality,
            tickets[count].passenger.passportNumber, &tickets[count].luggageCount,
            &tickets[count].seat.x, &tickets[count].seat.y);

        count++;
    }

    fclose(ticketsFile);

    *ticketCount = count;
    return tickets;
}

void addTicket(Flight *flights, int flightCount) {
    char choice;
    int randomSeat, flightChoice, i;
    Ticket ticket;

    printf("### Ajout d'un nouveau billet ###\n\n");
    printf("=== Informations générales ===\n");

    printf("\tVotre nom : ");
    getLine(ticket.passenger.lastname, 50);
    printf("\tVotre prenom : ");
    getLine(ticket.passenger.firstname, 50);

    do {
        ticket.passenger.gender = -1;
        printf("\tVotre civilite (0 homme / 1 femme / 2 non binaire) : ");
        scanf("%d", &ticket.passenger.gender);
    }
    while(ticket.passenger.gender < 0 || ticket.passenger.gender > 2);

    printf("\tVotre age : ");
    scanf("%d", &ticket.passenger.age);
    getchar();
    printf("\tVotre numéro de passeport : ");
    getLine(ticket.passenger.passportNumber, 10);
    printf("\tVotre nationalité : ");
    getLine(ticket.passenger.nationality, 50);

    do {
        printf("\tClasse economique (0) ou business (1) : ");
        scanf("%d", &ticket.vip);
    }
    while(ticket.vip < 0 || ticket.vip > 1);

    do {
        printf("\tNombre de bagages (jusqu'à 1 en classe economique, 2 en business) : ");
        scanf("%d", &ticket.luggageCount);
    }
    // On met "+ vip" car les vip ont le droit à un bagage en plus
    while (ticket.luggageCount < 0 || ticket.luggageCount > 1 + ticket.vip);

    printf("\n=== Choix du vol ===\n");
    for (i = 0; i < flightCount && flights[i].seats > 0; i++) {
        char date[16];
        formatDate(flights[i].date, date);

        printf("%d)", i + 1);
        printf("\tDestination : %s\n", flights[i].destination);
        printf("\tModele d'avion : %s\n", flights[i].plane);
        printf("\tDepart : %s\n\n", date);
    }

    do {
        printf("Choisissez votre vol : ");
        scanf("%d", &flightChoice);
    } while (flightChoice < 1 || flightChoice > i);

    flightChoice--;
    strcpy(ticket.destination, flights[flightChoice].destination);

    printf("\n=== Choix de la place ===\n");
    displaySeats(flights[flightChoice]);
    getchar();

    do {
        printf("\nVoulez-vous choisir votre place ? O/N : ");
        scanf("%c", &choice);
    } while (choice != 'o' && choice != 'O' && choice != 'n' && choice != 'N');

    if (choice == 'o' || choice == 'O') {
        printf("Choississez votre place :\n");
        do {
            do {
                printf("\tColonne : ");
                scanf("%d", &ticket.seat.x);
            } while (ticket.seat.x < 1 || ticket.seat.x > flights[flightChoice].rowCount);
            ticket.seat.x--;

            do {
                printf("\tLigne : ");
                scanf("%d", &ticket.seat.y);
            } while (ticket.seat.y < 1 || ticket.seat.y > flights[flightChoice].columnCount);
            ticket.seat.y--;

            if (flights[flightChoice].seats[ticket.seat.x][ticket.seat.y] != 0) {
                printf("Cette place est deja prise, veuillez en selectionner une autre\n");
            }
        } while (flights[flightChoice].seats[ticket.seat.x][ticket.seat.y] != 0);
    }
    else {
        randomSeat = rand() % getFreeSeatCount(flights[flightChoice]);

        for (ticket.seat.x = ticket.seat.y = 0; randomSeat >= 0; ticket.seat.x++) {
            // On passe les sièges déjà occupés
            if (flights[flightChoice].seats[ticket.seat.x][ticket.seat.y] == 0) {
                randomSeat--;
            }

            // On passe à la ligne suivante
            if (ticket.seat.x >= flights[flightChoice].rowCount) {
                ticket.seat.y++;
                ticket.seat.x = 0;
            }
        }
    }

    // On réserve le siège
    flights[flightChoice].seats[ticket.seat.x][ticket.seat.y] = ticket.vip + 1;

    // Vérifie si le vol est complet
    if (getFreeSeatCount(flights[flightChoice]) == 0) {
        // On retrie le tableau pour éviter de le réafficher la prochaine fois
        qsort(flights, flightCount, sizeof(Flight), sortFlights);
        printf("\nFelicitation vous avez eu la derniere place\n");
    }

    printf("\nVotre place est en (%d, %d)", ticket.seat.x + 1, ticket.seat.y + 1);
    printf("\n\n/!\\ Prevoir 2h avant le depart pour l'embarquement et le passage de la securite\n\n");

    generateTicket(&ticket);
}

void displayTicket(Ticket ticket) {
    printf("Billet n° %s\n", ticket.id);
    printf("--------------------------------------------\n");
    if (ticket.vip) {
        printf("Felicitation vous etes VIP !\n");
    }
    printf("\tNom : %s \tPrenom : %s\n", ticket.passenger.lastname, ticket.passenger.firstname);
    printf("\tAge : %d \tCategorie : ", ticket.passenger.age);
    if (ticket.passenger.age <= 12) {
        printf("Enfant\n");
    } else {
        printf("Adulte\n");
    }
    printf("\tCivilite : %s\n", formatGender(ticket.passenger.gender));
    printf("\tNationalite : %s\n", ticket.passenger.nationality);
    printf("\tNuméro de passeport : %s\n", ticket.passenger.passportNumber);
    printf("\tNumero de billet : %s \t\n", ticket.id);
    printf("\tDestination : %s\n", ticket.destination);
    printf("\tPlace dans l'avion : (%d, %d)\n", ticket.seat.x, ticket.seat.y);
    printf("\tNombre de bagages : %d\n", ticket.luggageCount);
    printf("--------------------------------------------\n\n");
};

void generateTicket(Ticket* ticket) {
    char fileContent[300];
    FILE* file = NULL;

    // On génère l'id du billet
    generateTicketId(ticket, ticket->id);

    // On formate le billet
    sprintf(fileContent, "\n%s %s %s %d %d %s %s %s %d %d %d %d", ticket->id,
        ticket->passenger.lastname, ticket->passenger.firstname, ticket->passenger.age, ticket->passenger.gender, ticket->passenger.nationality,
        ticket->passenger.passportNumber, ticket->destination, ticket->vip, ticket->luggageCount, ticket->seat.x, ticket->seat.y);

    // On ajoute le billet à la liste
    file = fopen("donnees/passagers.txt", "a");
    if(file != NULL) {
        fputs(fileContent, file);
        fclose(file);
    }

    printf("\n\n----- le billet se trouve à la racine du programme dans passagers.txt-----\n");
}

void generateTicketId(const Ticket* ticket, char* ticketId) {
    char age[3];

    // On convertit l'âge en chaîne de caractères
    sprintf(age, "%d", ticket->passenger.age);

    ticketId[0] = ticket->passenger.firstname[0];
    ticketId[1] = ticket->passenger.firstname[1] != '\0' ? ticket->passenger.firstname[1] : '0';
    ticketId[2] = ticket->passenger.lastname[0];
    ticketId[3] = ticket->passenger.lastname[1] != '\0' ? ticket->passenger.lastname[1] : '0';
    ticketId[4] = age[0];
    ticketId[5] = age[1] != '\0' ? age[1] : 'X';
    ticketId[6] = ticket->passenger.nationality[0];
    ticketId[7] = ticket->passenger.nationality[1] != '\0' ? ticket->passenger.nationality[1] : '0';
    ticketId[8] = ticket->passenger.passportNumber[0];
    ticketId[9] = ticket->passenger.passportNumber[1] != '\0' ? ticket->passenger.passportNumber[1] : '0';
    ticketId[10] = ticket->destination[0];
    ticketId[11] = ticket->destination[1] != '\0' ? ticket->destination[1] : '0';
    ticketId[12] = '\0'; // pour bien définir la fin de la chaine de caractère

    // En majuscule
    for(int i = 0; i < 12; i++) {
        if(ticketId[i] > 97 && ticketId[i] < 122) {
            ticketId[i] = ticketId[i] - 32;
        }
    }
}

void addLuggages(Ticket* ticket) {
    printf("Vous pouvez deposer %d bagages en soute \n", ticket->luggageCount);

    for (int i = 0; i < ticket->luggageCount; ++i) {
        char filename[20] = "Ticket ";
        sprintf(filename, "Ticket %d.txt", i + 1);

        // Get luggage info
        printf("Poids de votre bagage en kg ? (max 20kg sinon supplement) : ");
        scanf("%f", &ticket->luggagesWeight[i]);

        // Generate file
        FILE* file;
        file = fopen(filename, "w");

        fprintf(file, "------------------------------------------------------\n");
        fprintf(file, "Bagage appartenant à %s %s\n", ticket->passenger.firstname, ticket->passenger.lastname);
        fprintf(file, "Numero de bagage \t %d\n", i);
        fprintf(file, "Poids : \t%fkg\n", ticket->luggagesWeight[i]);
        if (ticket->vip == 1) {
            fprintf(file, "Bagage prioritaire \n");
        } else {
            fprintf(file, "Bagage non prioritaire\n");
        }
        fprintf(file, "\n------------------------------------------------------");

        fclose(file);
    }
}