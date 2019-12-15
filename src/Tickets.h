#ifndef NF05_PROJECT_TICKETS_H
#define NF05_PROJECT_TICKETS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "structs.h"
#include "utils.h"
#include "Flights.h"

Ticket* parseTickets(int* ticketCount);
void addTicket(Flight* flight, int flightCount);
void displayTicket(Ticket ticket);
void generateTicket(Ticket* ticket);
void generateTicketId(const Ticket* ticket, char* ticketId);

void addLuggages(Ticket* ticket);
void generateLuggage(Ticket* ticket, int index);

#endif // NF05_PROJECT_TICKETS_H