#include <stdlib.h>
#include <time.h>

#include "structs.h"
#include "utils.h"
#include "Flights.h"
#include "Tickets.h"

int main() {
    srand(time(NULL));
    printf("Projet de NF05 - Gestion des passagers dans un aeroport\n");

    // on commence par récupérer les avions et passagers
    Ticket* tickets;
    Flight* flights;
    int ticketCount = 0, flightCount = 0;

    tickets = parseTickets(&ticketCount);
    flights = parseFlights(&flightCount);

    for(int i = 0; i < ticketCount; i++) {
        displayTicket(tickets[i]);
    }

    // on ajoute un billet
    addTicket(flights, flightCount);

    /*
    ticketCount++;
    addTicket(flights, flightCount);

    printf("Depot des bagages \n");
    addLuggages(&tickets[ticketCount]);
    sauvPlace(flights, tickets[ticketCount]);

    printf("\nPassage de la frontiere");
    frontiere(flights, tickets, ticketCount, flightCount);

    displaySecurityInfo();
    */

    return EXIT_SUCCESS;
}