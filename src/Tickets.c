#include "Tickets.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

Ticket *parseTickets(int *ticketCount) {
    Ticket *tickets = malloc(0);
    int count = 0;

    FILE *ticketsFile;
    ticketsFile = fopen("data/passengers.txt", "r");
    if (ticketsFile == NULL) {
        // on crée le fichier data s'il n'existe pas
        createPath("data");
        ticketsFile = fopen("data/passengers.txt", "w");
        fclose(ticketsFile);
        return 0;
    }

    fseek(ticketsFile, 0L, SEEK_END);
    if (ftell(ticketsFile) != 0) {
        fseek(ticketsFile, 0L, SEEK_SET);
        for (; !feof(ticketsFile); count++) {
            int gender;
            tickets = realloc(tickets, (count + 1) * sizeof(Ticket));

            // On recupère les infos du billet
            fscanf(ticketsFile, "%s %s %s %d %d %s %s %s %d %d %d %d", tickets[count].id,
                   tickets[count].passenger.lastname, tickets[count].passenger.firstname, &tickets[count].passenger.age,
                   &gender, tickets[count].passenger.nationality,
                   tickets[count].passenger.passportNumber, tickets[count].destination, &tickets[count].vip,
                   &tickets[count].luggageCount,
                   &tickets[count].seat.x, &tickets[count].seat.y);

            tickets[count].passenger.gender = (Gender) gender;
        }
    }

    fclose(ticketsFile);

    *ticketCount = count;
    return tickets;
}

void addTicket(Flight *flights, int flightCount) {
    char choice;
    int randomSeat, flightIndex, i;
    Ticket ticket;

    printf("--- Informations generales ---\n");

    printf("\tVotre nom : ");
    getLine(ticket.passenger.lastname, 50);
    printf("\tVotre prenom : ");
    getLine(ticket.passenger.firstname, 50);

    do {
        ticket.passenger.gender = -1;
        printf("\tVotre civilite (0 homme / 1 femme / 2 non binaire) : ");
        getValue("%d", &ticket.passenger.gender);
    } while (ticket.passenger.gender < 0 || ticket.passenger.gender > 2);

    printf("\tVotre age : ");
    getValue("%d", &ticket.passenger.age);
    printf("\tVotre numero de passeport : ");
    getLine(ticket.passenger.passportNumber, 10);
    printf("\tVotre nationalite : ");
    getLine(ticket.passenger.nationality, 50);

    do {
        printf("\tClasse economique (0) ou business (1) : ");
        getValue("%d", &ticket.vip);
    } while (ticket.vip < 0 || ticket.vip > 1);

    do {
        printf("\tNombre de bagages en soute (1 maximum en classe economique, 2 en business) : ");
        getValue("%d", &ticket.luggageCount);
    }
        // On met "+ vip" car les vip ont le droit à un bagage en plus
    while (ticket.luggageCount < 0 || ticket.luggageCount > 1 + ticket.vip);

    printf("\n--- Choix du vol ---\n");
    displayAvailableFlightsList(flights, flightCount);
    int availableFlightCount = getAvailableFlightCount(flights, flightCount);

    do {
        printf("Choisissez votre vol : ");
        getValue("%d", &flightIndex);
    } while (flightIndex < 1 || flightIndex > availableFlightCount || getFreeSeatCount(&flights[flightIndex - 1]) == 0);

    flightIndex--;
    strcpy(ticket.destination, flights[flightIndex].destination);

    printf("\n--- Choix de la place ---\n");
    displaySeats(&flights[flightIndex]);

    do {
        printf("\nVoulez-vous choisir votre place ? O/N : ");
        getValue("%c", &choice);
    } while (choice != 'o' && choice != 'O' && choice != 'n' && choice != 'N');

    if (choice == 'o' || choice == 'O') {
        printf("Choississez votre place :\n");
        do {
            do {
                printf("\tColonne [1 - %d] : ", flights[flightIndex].rowCount);
                getValue("%d", &ticket.seat.x);
            } while (ticket.seat.x < 1 || ticket.seat.x > flights[flightIndex].rowCount);
            ticket.seat.x--;

            do {
                printf("\tLigne [1 - %d] : ", flights[flightIndex].columnCount);
                getValue("%d", &ticket.seat.y);
            } while (ticket.seat.y < 1 || ticket.seat.y > flights[flightIndex].columnCount);
            ticket.seat.y--;

            if (flights[flightIndex].seats[ticket.seat.x][ticket.seat.y] != 0) {
                printf("Cette place est deja prise, veuillez en selectionner une autre\n");
            }
        } while (flights[flightIndex].seats[ticket.seat.x][ticket.seat.y] != 0);
    } else {
        randomSeat = rand() % getFreeSeatCount(&flights[flightIndex]);

        ticket.seat.x = ticket.seat.y = 0;
        while (randomSeat >= 0) {
            // On passe les sièges déjà occupés
            if (flights[flightIndex].seats[ticket.seat.x][ticket.seat.y] == 0) {
                randomSeat--;
            }

            // On passe à la ligne suivante
            if (ticket.seat.x >= flights[flightIndex].rowCount) {
                ticket.seat.y++;
                ticket.seat.x = 0;
            }

            if (randomSeat >= 0) {
                ticket.seat.x++;
            }
        }
    }

    // On réserve le siège
    flights[flightIndex].seats[ticket.seat.x][ticket.seat.y] = ticket.vip + 1;

    // Vérifie si le vol est complet
    if (getFreeSeatCount(&flights[flightIndex]) == 0) {
        // On retrie le tableau pour éviter de le réafficher la prochaine fois
        qsort(flights, flightCount, sizeof(Flight), compareFlights);
        printf("\nFelicitations vous avez eu la derniere place !");
    }

    printf("\nVotre place est en (%d, %d)", ticket.seat.x + 1, ticket.seat.y + 1);
    printf("\n\n/!\\ Prevoir 2h avant le depart pour l'embarquement et le passage de la securite\n\n");

    saveTicket(&ticket);
    saveSeat(&flights[flightIndex], &ticket);
}

void displayTicket(Ticket *ticket) {
    printf("Billet n° %s\n", ticket->id);
    printf("--------------------------------------------\n");
    if (ticket->vip) {
        printf("Felicitation vous etes VIP !\n");
    }
    printf("\tNom : %s \tPrenom : %s\n", ticket->passenger.lastname, ticket->passenger.firstname);
    printf("\tAge : %d \tCategorie : ", ticket->passenger.age);
    if (ticket->passenger.age <= 12) {
        printf("Enfant\n");
    } else {
        printf("Adulte\n");
    }
    printf("\tCivilite : %s\n", formatGender(ticket->passenger.gender));
    printf("\tNationalite : %s\n", ticket->passenger.nationality);
    printf("\tNumero de passeport : %s\n", ticket->passenger.passportNumber);
    printf("\tNumero de billet : %s \t\n", ticket->id);
    printf("\tDestination : %s\n", ticket->destination);
    printf("\tPlace dans l'avion : (%d, %d)\n", ticket->seat.x + 1, ticket->seat.y + 1);
    printf("\tNombre de bagages : %d\n", ticket->luggageCount);
    printf("--------------------------------------------\n\n");
};

void displayTicketsList(Ticket *tickets, int ticketCount) {
    for (int i = 0; i < ticketCount; i++) {
        printf("%d)\t%s %s\n\tBillet n° %s\n\tDestination : %s\n\n", i + 1,
               tickets[i].passenger.lastname, tickets[i].passenger.firstname, tickets[i].id, tickets[i].destination);
    }
}

void selectAndDisplayTicket(Ticket *tickets, int ticketCount) {
    int ticketIndex;

    displayTicketsList(tickets, ticketCount);

    do {
        printf("Quel billet voulez-vous afficher ? ");
        getValue("%d", &ticketIndex);
    } while (ticketIndex < 1 || ticketIndex > ticketCount);

    printf("\n");
    displayTicket(&tickets[ticketIndex - 1]);
}

void saveTicket(Ticket *ticket) {
    FILE *ticketsFile = NULL;
    FILE *ticketFile;
    char ticketFilename[40];
    // On génère l'id du billet
    getTicketId(ticket, ticket->id);

    // On ajoute le billet à la liste
    ticketsFile = fopen("data/passengers.txt", "a");
    if (ticketsFile == NULL) {
        printf("Erreur : fichier data/passengers.txt introuvable, veuillez reessayer");
        return;
    }

    // Si le fichier n'est pas vide, on peut aller à la ligne suivante
    fseek(ticketsFile, -1, SEEK_END);
    if (ftell(ticketsFile) != 0) {
        fprintf(ticketsFile, "\n");
    }

    fprintf(ticketsFile, "%s %s %s %d %d %s %s %s %d %d %d %d", ticket->id,
            ticket->passenger.lastname, ticket->passenger.firstname, ticket->passenger.age, ticket->passenger.gender,
            ticket->passenger.nationality,
            ticket->passenger.passportNumber, ticket->destination, ticket->vip, ticket->luggageCount, ticket->seat.x,
            ticket->seat.y);

    fclose(ticketsFile);

    // Si le dossier n'existe pas, on le crée
    createPath("data/ticketsPassenger");
    sprintf(ticketFilename, "data/ticketsPassenger/%s.txt", ticket->id);

    ticketFile = fopen(ticketFilename, "a");
    fprintf(ticketFile, "__________________________________________\n\n");

    if (ticket->vip) {
        fprintf(ticketFile, "Felicitation vous etes VIP !\n");
    }
    fprintf(ticketFile, "\tNom : %s \tPrenom : %s\n", ticket->passenger.lastname, ticket->passenger.firstname);

    fprintf(ticketFile, "\tAge : %d \tCategorie : ", ticket->passenger.age);
    if (ticket->passenger.age <= 12) {
        fprintf(ticketFile, "Enfant\n");
    } else {
        fprintf(ticketFile, "Adulte\n");
    }
    fprintf(ticketFile, "\tCivilite : %s\n", formatGender(ticket->passenger.gender));
    fprintf(ticketFile, "\tNationalite : %s\n", ticket->passenger.nationality);
    fprintf(ticketFile, "\tNumero de passeport : %s\n", ticket->passenger.passportNumber);
    fprintf(ticketFile, "\tNumero de billet : %s \t\n", ticket->id);
    fprintf(ticketFile, "\tDestination : %s\n", ticket->destination);
    fprintf(ticketFile, "\tPlace dans l'avion : (%d, %d)\n", ticket->seat.x + 1, ticket->seat.y + 1);
    fprintf(ticketFile, "\tNombre de bagages : %d\n", ticket->luggageCount);
    fprintf(ticketFile, "__________________________________________\n\n");

    fclose(ticketFile);

    printf("\nVotre Billet est disponible a l'adresse data/ticketsPassenger\n");
}

void getTicketId(Ticket *ticket, char *ticketId) {
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
    for (int i = 0; i < 12; i++) {
        ticketId[i] = toupper(ticketId[i]);
    }
}

void addLuggages(Ticket *ticket) {

    char filename[55];
    char nameDestFile[67];
    float luggagesWeight = 0;
    int luggagesCounting = 0, passengerCount = 0;
    int seatXYVIP[500][3]; // on considère qu'il n'y a pas plus de 500pasagers sur chaque vol
    int lugCounting = ticket->luggageCount;

    printf("nbr de bagages %d", ticket->luggageCount);

    sprintf(filename, "data/ticketsPassenger/%s.txt", ticket->id);
    sprintf(nameDestFile, "data/flights/%s.txt", ticket->destination);
    FILE *file =NULL, *destinationFile = NULL;
    file = fopen(filename, "r+");
    if (file == NULL) {
        //fichier manquant on le recrée
        fclose(file);
        saveTicketPassenger(ticket);
        // on le reouvre
        file = fopen(filename, "a+");
    }

    destinationFile = fopen(nameDestFile, "r");
    rewind(destinationFile);
    if (destinationFile != NULL) {
        // on récupère les données du vol pour pouvoir changer le poids total des bagages et le nombre
        fscanf(destinationFile, "%f %d", &luggagesWeight, &luggagesCounting);

        // on recupere les places qui sont déjà occupées et on le met dans l'avion
        for (; !feof(destinationFile); passengerCount++) {
            fscanf(destinationFile, "%d", &seatXYVIP[passengerCount][0]);
            fscanf(destinationFile, "%d", &seatXYVIP[passengerCount][1]);
            fscanf(destinationFile, "%d", &seatXYVIP[passengerCount][2]);
        }
        fclose(destinationFile);
    } else {

        // si inexistant on le signal et on fait sans
        printf("\n Attention le fichier |%s| manquant, le programme continue de fonctionner sans mais l'utilsation pourra en etre degradee\n",
               nameDestFile);
    }


    printf("\n>>>nbr de bagages %d et %d", lugCounting, ticket->luggageCount);
    fseek(file, 0, SEEK_END); // on positionne le curseur à la fin
    if (lugCounting > 0) {
        fprintf(file, "\n\nVo%s bagage%s en soute :\n", lugCounting > 1 ? "s" : "tre",
                ticket->luggageCount > 1 ? "s" : "");

    }

    printf("\n\tVous pouvez deposer %d bagage%s en soute.\n", lugCounting,
           lugCounting > 1 ? "s" : "");

    for (int i = 0; i < lugCounting; ++i) {

        // Récupere le poid du/des bagages
        printf("\tPoids du bagage n°%d en kg (max 20kg sinon supplement) : ", i + 1);
        getValue("%f", &ticket->luggagesWeight[i]);

        // Ajoute le poids du/des bagages dans le fichier du billet
        fprintf(file, "Numero de bagage \t %d\n", i+1);
        fprintf(file, "Poids : \t%.2fkg\n", ticket->luggagesWeight[i]);
        if (ticket->vip == 1) {
            fprintf(file, "Bagage prioritaire \n");
        } else {
            fprintf(file, "Bagage non prioritaire\n");
        }
        // on incrémente le poids total des bagages dans l'avion et le nombre total
        luggagesCounting++;
        luggagesWeight += ticket->luggagesWeight[i];
    }

    fprintf(file, "\n__________________________________________");


    if (lugCounting > 1) {
        printf("\tVos tickets bagages ont ete generes et sont disponibles dans le dossier \"data\"");
    } else if (lugCounting == 1) {
        printf("\tVotre ticket bagage a ete genere et est disponible dans le dossier \"data\"");
    }

    // on remet les nouvelles données dans le fichier

    destinationFile = fopen(nameDestFile, "w");
    fprintf(destinationFile, "%f %d", luggagesWeight, luggagesCounting);
    for (int j = 0; j < passengerCount; ++j)
        fprintf(destinationFile, "\n%d %d %d", seatXYVIP[passengerCount][0], seatXYVIP[passengerCount][1],
                seatXYVIP[passengerCount][2]);

    fclose(destinationFile);
    fclose(file);
}

void saveTicketPassenger(Ticket *ticket) {
    FILE *ticketFile;
    char ticketFilename[40];
    sprintf(ticketFilename, "data/ticketsPassenger/%s.txt", ticket->id);
    ticketFile = fopen(ticketFilename, "a");
    if (ticketFile == NULL)
        // Si le dossier n'existe pas, on le crée
        createPath("data/ticketsPassenger");

    fprintf(ticketFile, "__________________________________________\n\n");

    if (ticket->vip == 2) {
        fprintf(ticketFile, "Felicitation vous etes VIP !\n");
    }
    fprintf(ticketFile, "\tNom : %s \tPrenom : %s\n", ticket->passenger.lastname, ticket->passenger.firstname);

    fprintf(ticketFile, "\tAge : %d \tCategorie : ", ticket->passenger.age);
    if (ticket->passenger.age <= 12) {
        fprintf(ticketFile, "Enfant\n");
    } else {
        fprintf(ticketFile, "Adulte\n");
    }
    fprintf(ticketFile, "\tCivilite : %s\n", formatGender(ticket->passenger.gender));
    fprintf(ticketFile, "\tNationalite : %s\n", ticket->passenger.nationality);
    fprintf(ticketFile, "\tNumero de passeport : %s\n", ticket->passenger.passportNumber);
    fprintf(ticketFile, "\tNumero de billet : %s \t\n", ticket->id);
    fprintf(ticketFile, "\tDestination : %s\n", ticket->destination);
    fprintf(ticketFile, "\tPlace dans l'avion : (%d, %d)\n", ticket->seat.x + 1, ticket->seat.y + 1);
    fprintf(ticketFile, "\tNombre de bagages : %d\n", ticket->luggageCount);

    fprintf(ticketFile, "__________________________________________\n\n");

    fclose(ticketFile);

    printf("\nVotre Billet est disponible a l'adresse data/ticketsPassenger/ \n");
}