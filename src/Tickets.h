/**
 * @file Tickets.h
 * @brief Ce fichier définit toutes les fonctions en rapport avec l'achat, l'affichage, et la sauvegarde des billets dans le programme
 */

#ifndef NF05_PROJECT_TICKETS_H
#define NF05_PROJECT_TICKETS_H

#include "structs.h"
#include "utils.h"
#include "Flights.h"

/**
 * @brief   Récupère les billets des passagers à partir du fichier @a data/passengers.txt
 * @param   ticketCount     Renvoie le nombre de billets dans le fichier
 * @return  Retourne un tableau contenant tous les billets du fichier
 */
Ticket* parseTickets(int *ticketCount);

/**
 * @brief   Ajoute un billet en demandant toutes les données du passager
 * @param   flights         Tableau de tous les vols
 * @param   flightCount     Nombre de vols dans @a flights
 * @param   tickets         Tableau de tous les billets. Le billet créé y sera ajouté
 * @param   ticketCount     Nombre de billets dans @a tickets. Il sera incrémenté de 1
 */
void addTicket(Flight *flights, int flightCount, Ticket *tickets, int *ticketCount);

/**
 * @brief    Affiche toutes les informations d'un billet
 * @param    ticket     Le billet à afficher
 */
void displayTicket(Ticket *ticket);

/**
 * @brief   Affiche les informations principales (nom et prénom du passager, numéro de billet, destination) des billets
 * @param   tickets         Tableau des billets à afficher
 * @param   ticketCount     Nombre de billets dans @a tickets
 */
void displayTicketsList(Ticket *tickets, int ticketCount);

/**
 * @brief   Affiche les informations principales des billets, puis sélectionne un passager pour afficher toutes ses données
 * @param   tickets         Tableau des billets
 * @param   ticketCount     Nombre de billets dans @a tickets
 */
void selectAndDisplayTicket(Ticket *tickets, int ticketCount);

/**
 * @brief    Ajoute un billet dans le fichier @a data/passengers.txt
 * @param    ticket     Billet à ajouter
 */
void saveTicket(Ticket *ticket);

/**
 * @brief   Génère un numéro de billet à partir des informations du billet (nom, prénom, âge, nationalité, numéro de passeport, destination) le tout en 12 caractères
 * @param   ticket       Billet du passager pour lequel on veut génerer le numéro de billet
 * @param   ticketId     Renvoie le numéro de billet
 */
void getTicketId(Ticket *ticket, char *ticketId);

/**
 * @brief   Demande le poids du/des bagage(s) du passager et génère un billet de bagage dans @a data/Ticket_[id].txt
 * @param   ticket       Billet du passager. Permet d'y enregistrer le poids de son/ses bagage(s)
 */
void addLuggages(Ticket *ticket);

#endif // NF05_PROJECT_TICKETS_H