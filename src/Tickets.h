#ifndef NF05_PROJECT_TICKETS_H
#define NF05_PROJECT_TICKETS_H

#include "structs.h"
#include "utils.h"
#include "Flights.h"

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