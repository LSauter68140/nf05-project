/**
 * @file Flights.h
 * @brief Ce fichier définit toutes les fonctions en rapport avec l'ajout, embarquement et l'affichage des vols dans le programme
 */

#ifndef NF05_PROJECT_FLIGHTS_H
#define NF05_PROJECT_FLIGHTS_H

#include "structs.h"
#include "utils.h"
#include "Tickets.h"

/**
 * @brief   Récupère les vols à partir du fichier @a data/flights.txt
 * @param   flightCount     Renvoie le nombre de vols se trouvant dans le fichier
 * @return  Retourne un tableau de @a Flight contenant tous les vols du fichier
 */
Flight* parseFlights(int *flightCount);

/**
 * @brief   Affiche les places du vol (disponibles ou non)
 * @param   flight          Vol pour lequel on affiche les places
 */
void displaySeats(Flight *flight);

/**
 * @brief   Affiche les informations principales des vols (destination, modèle, date de départ)
 * @param   flights         Tableau des vols à afficher
 * @param   flightCount     Nombre de vol dans @a flights
 */
void displayFlightsList(Flight *flights, int flightCount);

/**
 * @brief   Affiche les informations principales des vols (destination, modèle, départ), pour lesquels il reste des places libres
 * @param   flights         Tableau des vols. Seuls les vols où il reste des places seront affichés
 * @param   flightCount     Nombre de vols dans @a flights
 */
void displayAvailableFlightsList(Flight *flights, int flightCount);

/**
 * @brief   Compte le nombre de places libres restantes pour un vol
 * @param   flight      Vol pour lequel on compte le nombre de places libres
 * @return  Retourne le nombre de places restantes
 */
int getFreeSeatCount(Flight *flight);

/**
 * @brief   Compte le nombre de vols pour lesquels il reste au moins une place libre
 * @param   flights         Tableau des vols
 * @param   flightCount     Nombre de vol dans @a flights
 */
int getAvailableFlightCount(Flight *flights, int flightCount);

/**
 * @brief   Enregistre la place du passager dans le ficher data/flights/[destination].txt
 * @param   flight      Vol du passager
 * @param   ticket      Billet du passager
 */
void saveSeat(Flight *flight, Ticket *ticket);

/**
 * @brief   Embarque les passagers. Tous les passagers peuvent déposer leurs bagages et on vérifie leur visa
 * @param   flightTickets       Tableau contenant les billets du vol à embarquer
 * @param   flightTicketCount   Nombre de billets dans @a flightTickets
 * @param   flightCount         Nombre de vols au total
 */
void boardPassengers(Ticket *flightTickets, int flightTicketCount, int flightCount);

/**
 * @brief   Embarque un vol défini par l'utilisateur. Les passagers prioritaires sont embarqués en premiers
 * @param   flights         Tableau de vols
 * @param   flightCount     Nombre de vols dans @a flights
 * @param   tickets         Tableau de billets
 * @param   ticketCount     Nombre de billets dans @a tickets
 */
void boardFlight(Flight *flights, int *flightCount, Ticket *tickets, int ticketCount);

/**
 * @brief   Affiche les infos concernant les objets interdits à bord d'un avion
 * @param   flight    Vol concerné par ces informations de sécurité
 */
void displaySecurityInfo(Flight *flight);

/**
 * @brief   Vérifie si un passager a besoin de visa pour changer de pays (vérifie sa nationalité avec le fichier @a data/nationalities.txt)
 * @param   ticket      Billet du passager à vérifier
 * @param   flightCount Nombre de vols
 */
int checkFrontiers(Ticket *ticket, int flightCount);

/**
 * @brief   Supprime les billets spécifiés et met à jour le fichier data/passengers.txt avec les billets restants
 * @param   ticketsToDelete         Tableau des billets à supprimer
 * @param   ticketsToDeleteCount    Nombre de billets dans @a ticketsToDelete
 * @param   tickets                 Tableau de tous les billets
 * @param   ticketCount             Nombre de billets dans @a tickets
 */
void deleteTickets(Ticket *ticketsToDelete, int ticketsToDeleteCount, Ticket *tickets, int *ticketCount);

/**
 * @brief   Permet d'ajouter un vol avec toutes les infos le concenant
 * @param   flights     Tableau contenant tous les vols. Le nouveau vol va y être ajouté
 * @param   flightCount Nombre de vols dans @a flights
 */
Flight *addFlight(Flight *flights, int *flightCount);

/**
 * @brief   Supprime le vol du fichier @a data/flights.txt et le met dans le fichier @a data/history/flights.txt pour avoir un historique des vols
 * @param   flights      Tableau de tous les vols
 * @param   flightCount  Nombre d'avions dans @a flights. Va être décrémenté de 1
 * @param   flightIndex  Indice du vol à supprimer de @a flights
 */
void removeFlight(Flight *flights, int *flightCount, int flightIndex);

/**
 * @brief   Compare deux vols en fonction du nombre de places libres
 * @param   a    Vol a
 * @param   b    Vol b
 * @return  Retourne la différence de places libres entre les vols @a a et @a b
 */
int compareFlights(const void* a, const void* b);

#endif // NF05_PROJECT_FLIGHTS_H