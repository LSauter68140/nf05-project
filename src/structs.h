#ifndef NF05_PROJECT_STRUCT_H
#define NF05_PROJECT_STRUCT_H

typedef struct {
    int day, month, year, hour, minute;
} Date;

typedef struct {
    int x, y;
} Seat;

typedef struct {
    char lastname[50];
    char firstname[50];
    int age;                // si <= 12 considéré comme enfant
    int gender;             // 0 homme, 1 femme, 2 non-binaire
    char nationality[50];
    char passportNumber[10];
} Passenger;

typedef struct {
    char id[13];
    Passenger passenger;
    char destination[50];
    int vip;            // 0 pas VIP, 1 VIP
    int luggageCount;   // jusqu'à 3 bagages soute (un bagage cabine d'office)
    float luggagesWeight[2]; // un passager peut en avoir 2 maximum
    Seat seat;
} Ticket;

typedef struct {
    char plane[20];
    char destination[50];
    char flightId[15];
    int seats[500][500];// vue 2d de haut des places de l'avion 1/2 occupé   0 -> libre on initialise le tableau à 0
    int rowCount, columnCount; // taille réelle de l'avion qu'on met lors de son initialisation
    float luggagesWeight; // somme du poids de tous les bagages
    Date date;
} Flight;

#endif //NF05_PROJECT_STRUCT_H