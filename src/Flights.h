#ifndef NF05_PROJECT_SEATS_H
#define NF05_PROJECT_SEATS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

Flight* parseFlights(int* flightCount);
void displaySeats(Flight flight);
int getFreeSeatCount(Flight flight);
void saveSeat(Flight* flight, Ticket* ticket);
void displaySecurityInfo();
void checkFrontiers(Flight* flights, Ticket* tickets, int ticketCount, int flightCount);
int sortFlights(const void* a, const void* b);

#endif // NF05_PROJECT_SEATS_H