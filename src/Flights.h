#ifndef NF05_PROJECT_SEATS_H
#define NF05_PROJECT_SEATS_H

#include "structs.h"
#include "utils.h"
#include "Tickets.h"

/**
 * @file Flights.h
 * @brief Ce fichier définit toutes les fonctions en rapport avec l'ajout, embarquement et l'affichage des vols dans le programme
 */

/**
 * @brief     Récupère les vols à partir du fichier @a data/flights.txt
 * @param    flightCount     Renvoie sous la forme d'un pointeur d'entier le nombre de vols se trouvant dans le fichier
 * @return   Flights         Retourne un tableau de @a Flight contenant tout les vols du fichier
 */

Flight* parseFlights(int* flightCount);

/**
 * @brief    Affiche les places disponibles dans l'avion
 * @param   flight         Tableau du , qui vont être affiché
 * @param   ticketCount     Nombre de billets dans ce tableau
 */

void displaySeats(Flight* flight);

/**
 * @brief    Affiche les informations principales du vol ( desination, modele, départ)
 * @param   flights         Tableau de vols, qui vont être affichés
 * @param   flightCount     Nombre de vol dans ce tableau
 */

void displayFlightsList(Flight* flights, int flightCount);

/**
 * @brief    Affiche les informations principales du vol ( desination, modele, départ) et seulement si ils ont des places de libre
 * @param   flights         Tableau de vols, qui vont être affichés
 * @param   flightCount     Nombre de vol dans ce tableau
 */

void displayAvailableFlightsList(Flight* flights, int flightCount);

/**
 * @brief   Compte le nombre de places de libres restantes sur le vol
 * @param   flights         Vol analysé
 * @return   int     Nombre de place/s restante/s
 */

int getFreeSeatCount(Flight* flight);

/**
 * @brief    Affiche les informations principales du vol ( desination, modele, départ) et seulement si ils ont des places de libre
 * @param   flights         Tableau de vols, qui vont être affichés
 * @param   flightCount     Nombre de vol dans ce tableau
 */


int getAvailableFlightCount(Flight* flights, int flightCount); // à voir si on la garde

/**
 * @brief    Enregistre la place du passager dans le ficher data/flights/[destination].txt
 * @param   flights    Tableau de vol du passager
 * @param   ticket     Billet du passager
 */
void saveSeat(Flight* flight, Ticket* ticket);

/**
 * @brief    Embarque les passagers un a un, les VIP sont prioitaire aux autres, c'est à ce moment la que tout les passagers peuvent déposer leurs bagages et qu'on vérifie leur visa
 * @param   flightTickets       Tableau contenant tout les billets du vol choisi à embarquer
 * @param   flightTicketCount   Nombre de billets dans ce tableau
 * @param   flightCount         Nombre de vol en tout
 */

void boardPassengers(Ticket *flightTickets, int flightTicketCount, int flightCount);

/**
 * @brief   Permet de choisir le vol à faire embarquer
 * @param   flights         Tableau contenant tout les vols
 * @param   flightCount     Nombre de vols en tout
 * @param   tickets         Tableau de billets
 * @param   ticketCount     Nombre de billets en tout
 */

void boardFlight(Flight* flights, int *flightCount, Ticket* tickets, int ticketCount);

/**
 * @brief   Affiche les infos concernant les objets interdit à bord des avions
 * @param   flight    Vol à qui cela est adressé
 */

void displaySecurityInfo(Flight flight);

/**
 * @brief   Verifie si les passagers du vol on besoin de visa pour changer de pays (vérifie leur nationalité avec le fichier \a data/nationalities.txt)
 * @param   tickets  Tableau de tout les passagers du vol
 * @param   flightCount Nombre de vol
 */

int checkFrontiers(Ticket tickets, int flightCount);

/**
 * @brief   Supprime les billets qui sont dans le vol qui vient d'embarquer du tableau qui contient tout les billet  et met à jour le fichier data/passengers.txt avec les billets restant
 * @param   ticketsToDelete         Tableau de tout les passagers du vol
 * @param   ticketsToDeleteCount    Nombre de billets dans ce tableau
 * @param   tickets                 Tableau avec tout les billets
 * @param   ticketCount             Nombre de billets dans ce talbeau
 */

void deleteTickets(Ticket *ticketsToDelete, int ticketsToDeleteCount, Ticket *tickets, int *ticketCount);

/**
 * @brief   Permet d'ajouter un vol avec toutes les infos le concenant
 * @param   flight   pointeur vers le tableau contenant tout les vols, car celui va être modifié (comme on en ajoute un)
 * @param   flightCount Nombre de vol dans ce tableau
 */

void addFlight(Flight **flight, int *flightCount);

/**
 * @brief   Supprime le vol qui vient d'embarquer du fichier @a data/flights.txt et le met dans le fichier @a data/history/flights.txt pour avoir un historique des vols
 * @param   flights      Tableau de vol ou on va enlever le vol qui vient de partir
 * @param   flightCount  Nombre d'avion dans ce tableau, vas etre décrémenté de 1
 * @param   flightIndex  Index du vol qui vient de partir et qui va être changé de fichier
 */

void removeFlight(Flight *flights, int *flightCount, int flightIndex);

/**
 * @brief   Permet de trier les vols en fonction de leur nombre de places de libre de plus vers le moins
 * @param   a    Vol a
 * @param   b    Vol b
 * @return int   Retourne 1 si b>a et 0 si b<a
 */

int sortFlights(const void* a, const void* b);

#endif // NF05_PROJECT_SEATS_H