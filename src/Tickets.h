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
 * @brief     Récupère les tickets des passagers à partir du fichier @a data/passengers.txt
 * @param    ticketCount     Renvoie sous la forme d'un pointeur d'entier le nombre de ticket se trouvant dans le fichier
 * @return   Tickets         Retourne un tableau de @a Ticket contenant tout les billets du fichier
 */

Ticket* parseTickets(int* ticketCount);

/**
 * @brief     Permet d'ajouter un billet en y entrant toutes les données nécessaire du passager
 * @param   flights         Tableau de @a Flight permettant d'afficher tout les vols disponible
 * @param   flightCount     Nombre de vol dans le tableau précédement importé
 * @param   tickets         Tableau de billets, la fonction renvoie le tableau avec le billet ajouté dedans
 * @param   ticketCount     Nombre de billets acheté, il sera incrémenté de 1 à la fin de la fonction
 */

void addTicket(Flight* flights, int flightCount, Ticket* tickets, int* ticketCount);

/**
 * @brief    Affiche toutes le billet complet d'un passager
 * @param    ticket     le billet du passager en question
 */

void displayTicket(Ticket* ticket);

/**
 * @brief    Affiche les informations principales (numéro de billet, destination, nom & prénom du passager)  de tous les billets qui ont été enregistrés
 * @param   tickets         Tableau de billets, qui vont être affiché
 * @param   ticketCount     Nombre de billets dans ce tableau
 */

void displayTicketsList(Ticket* tickets, int ticketCount);

/**
 * @brief    Affiche les informations principales à partir de la fonction \b displayTicketList afin de sélectionner un passager pour afficher toutes ses données avec la fonction \b displayTicket
 * @param   tickets         Tableau de billets, qui vont être affiché
 * @param   ticketCount     Nombre de billets dans ce tableau
 */

void selectAndDisplayTicket(Ticket* tickets, int ticketCount);

/**
 * @brief    Enregistre tout les billets des passagers dans le fichier @a data/passengers.txt à partir du tableau @a ticket
 * @param    ticket     Tableau des billets de tout les passagers
 */

void saveTicket(Ticket* ticket);

/**
 * @brief   Génere un numéro de billet à partir des données de son passager (nom, prénom, age, nationalité, numéro de passport, destination) le tout en 12 caractères
 * @param   ticket       Billet du passager avec le quel on veut génerer le numéro de billet
 * @param   ticketId     Renvoie le numéro de ticket en majuscule
 */

void getTicketId(const Ticket* ticket, char* ticketId);

/**
 * @brief   Demande le poids du/des bagage/s du passager avant son embarquement
 * @param   ticket       Billet du passager, et permet d'y enregistrer le poids de son/ses bagage/s
 */

void addLuggages(Ticket* ticket);

#endif // NF05_PROJECT_TICKETS_H