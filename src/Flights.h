#ifndef NF05_PROJECT_SEATS_H
#define NF05_PROJECT_SEATS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "utils.h"
#include "Tickets.h"

Flight* parseFlights(int* flightCount);
void displaySeats(Flight* flight);
void displayFlightsList(Flight* flights, int flightCount);
void displayAvailableFlightsList(Flight* flights, int flightCount);
int getFreeSeatCount(Flight* flight);
int getAvailableFlightCount(Flight* flights, int flightCount);
void saveSeat(Flight* flight, Ticket* ticket);
void boardFlight(Flight* flights, int flightCount, Ticket* tickets, int ticketCount);
void displaySecurityInfo();
void checkFrontiers(Flight* flights, Ticket* tickets, int ticketCount, int flightCount);
int sortFlights(const void* a, const void* b);

#endif // NF05_PROJECT_SEATS_H