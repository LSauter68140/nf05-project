#ifndef NF05_PROJECT_SEATS_H
#define NF05_PROJECT_SEATS_H

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

void boardPassengers(Ticket *flightTickets, int flightTicketCount, int flightCount);
void boardFlight(Flight* flights, int *flightCount, Ticket* tickets, int ticketCount);

void displaySecurityInfo(Flight flight);
int checkFrontiers(Ticket tickets, int flightCount);
void deleteTickets(Ticket *ticketsToDelete, int ticketsToDeleteCount, Ticket *tickets, int *ticketCount);

void addFlight(Flight **flight, int *flightCount);
void removeFlight(Flight *flights, int *flightCount, int flightIndex);

int sortFlights(const void* a, const void* b);

#endif // NF05_PROJECT_SEATS_H