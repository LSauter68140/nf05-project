/**
 * @file structs.h
 * @brief Ce fichier définit toutes les structures de base
 */

#ifndef NF05_PROJECT_STRUCT_H
#define NF05_PROJECT_STRUCT_H

typedef struct {
    /// Jour. Doit être compris entre 1 et 31 inclus
    int day;
    /// Mois. Doit être compris entre 1 et 12 inclus
    int month;
    /// Année
    int year;
    /// Heure. Doit être comprise entre 0 et 23 inclus
    int hour;
    /// Minutes. Doit être compris entre 0 et 59 inclus
    int minute;
} Date;

typedef struct {
    /// Position x du siège
    int x;
    /// Position y du siège
    int y;
} Seat;

typedef struct {
    /// Prénom du passager. 50 caractères maximum
    char lastname[50];
    /// Nom de famille du passager. 50 caractères maximum
    char firstname[50];
    /// Âge du passager. Si l'âge est inférieur à 12 ans, le passager est considéré comme un enfant
    int age;
    /// Sexe du passager. (0 : Homme, 1 : Femme, 2 : non-binaire)
    int gender;
    /// Nationalité du passager. 50 caractères maximum
    char nationality[50];
    /// Numéro de passeport du passager. 10 caractères maximum
    char passportNumber[10];
} Passenger;

typedef struct {
    /// Identifiant du billet. Généré grâce à la fonction @a generateTicketId
    char id[13];
    /// Passager associé au billet
    Passenger passenger;
    /// Destination du vol associé au billet
    char destination[50];
    /// Classe du billet. (0 correspond à un billet en classe économique, 1 à un billet en classe business) 
    int vip;
    /// Nombre de bagages en soute autorisés. (1 maximum s'il s'agit d'un billet en classe économique, 2 maximum s'il s'agit d'un billet en classe business)
    int luggageCount;
    /// Poids des bagages. Ne doit pas excéder 20kg par bagage. Autrement un supplément sera ajouté au prix du billet
    float luggagesWeight[2];
    /// Siège associé au billet
    Seat seat;
} Ticket;

typedef struct {
    /// Identifiant du vol. 15 caractères maximum
    char flightId[15];
    /// Modèle de l'avion qui assurera le vol. 20 caractères maximum
    char plane[20];
    /// Destination du vol. 50 caractères maximum
    char destination[50];
    /// Tableau des sièges. (0 : place libre, 1 : place réservée, 2 : place réservée par un billet business)
    int seats[500][500];
    /// Nombre de rangées de sièges disponibles dans l'avion
    int rowCount;
    /// Nombre de colonnes de sièges disponibles dans l'avion
    /// Date du départ du vol
    int columnCount;
    Date date;
} Flight;

#endif //NF05_PROJECT_STRUCT_H