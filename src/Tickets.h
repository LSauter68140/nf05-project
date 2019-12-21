#ifndef NF05_PROJECT_TICKETS_H
#define NF05_PROJECT_TICKETS_H

#include "structs.h"
#include "utils.h"
#include "Flights.h"

/**
 * @file Tickets.h
 * @brief Ce fichier définit toutes les fonctions en rapport avec l'achat, l'affichage, et la sauvegarde des billets dans le programme
 */



/**
 * @brief     Récupère les tickets des passagers à partir du fichier @a data/
 * @param    date               Forme brute
 * @param    formattedDate         Retourne la date formatée.
 */


Ticket* parseTickets(int* ticketCount);
void addTicket(Flight* flights, int flightCount, Ticket* tickets, int* ticketCount);
void displayTicket(Ticket* ticket);
void displayTicketsList(Ticket* tickets, int ticketCount);
void selectAndDisplayTicket(Ticket* tickets, int ticketCount);
void saveTicket(Ticket* ticket);
void getTicketId(const Ticket* ticket, char* ticketId);

void addLuggages(Ticket* ticket);
void generateLuggage(Ticket* ticket, int index);

#endif // NF05_PROJECT_TICKETS_H