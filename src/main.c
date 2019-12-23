#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "structs.h"
#include "utils.h"
#include "Flights.h"
#include "Tickets.h"

/**
 * @file        main.c
 * @authors     Valentin Peltier & Loïc Sauter
 * @version     1.0
 * @date        22 Decembre 2019
 * @brief       Fichier principal du projet
 * @details     On retrouve ici le menu qui permet d'accéder à toutes les fonctionnalités du programme
 */

int main() {
    char action, skipWait;
    srand(time(NULL));
    clearScreen();

    // on commence par récupérer les avions et passagers
    Ticket *tickets;
    Flight *flights;
    int ticketCount = 0, flightCount = 0;

    do {
        flights = parseFlights(&flightCount);
        tickets = parseTickets(&ticketCount);

        printf("Projet de NF05 - Gestion des passagers dans un aeroport\n\n");
        printf("============== Menu principal ==============\n");

        printf("\n1. Ajouter un billet");
        printf("\n2. Ajouter un vol");
        printf("\n3. Embarquer un vol");
        printf("\n4. Consulter les billets");
        printf("\n5. Consulter les vols disponibles");
        printf("\n6. Consulter le billet d'un passager");
        printf("\n7. Consulter l'historique des vols (sur une periode donnee)");
        printf("\nQ. Quitter");

        printf("\n\n> Que voulez vous faire ? ");

        getValue("%c", &action);

        switch (action) {
            case '1':
                printf("\n=== Ajout d'un billet ===\n\n");
                addTicket(flights, flightCount);
                break;
            case '2':
                printf("\n=== Ajout d'un vol ===\n\n");
                addFlight();
                break;
            case '3':
                printf("\n=== Embarquement d'un vol ===\n\n");
                boardFlight(flights, flightCount, tickets, ticketCount);
                break;
            case '4':
                printf("\n=== Affichage des billets ===\n\n");
                displayTicketsList(tickets, ticketCount);
                break;
            case '5':
                printf("\n=== Affichage des vols disponibles ===\n\n");
                displayAvailableFlightsList(flights, flightCount);
                break;
            case '6':
                printf("\n=== Affichage d'un billet ===\n\n");
                selectAndDisplayTicket(tickets, ticketCount);
                break;
            case '7':
                printf("\n=== Afficher l'historique des vols ===\n\n");
                printf("Fonctionalite non disponible pour le moment\n\n"); // TODO
                break;
            case 'Q':
            case 'q':
            default:
                skipWait = 1;
                break;
        }

        if (!skipWait) {
            printf("\n(Appuyez sur entree pour continuer...)");
            while(getchar() != '\n');
            skipWait = 0;
        }

        if (action != 'q' && action != 'Q') {
            clearScreen();
        }
    } while(action != 'Q' && action !='q');

    // Free memory
    free(flights);
    free(tickets);

    return EXIT_SUCCESS;
}