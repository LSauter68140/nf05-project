
typedef struct  {

    int numbagage; // numéro du bagage 1 ou 2 si vip ou non
    float poids; // en kg max 20kg par bagages et 5kg pour celui de la soute

} ticketBagage;
typedef struct {

    int jour, mois, annee, heure, minute;

}date;


typedef struct {

    char nom[50], prenom[40], numPassport[10], destination[50], nationalite[50], numBillet[12];
    int nbrBagages; // jusqu'à 3 bagages soute (un bagage cabine d'office)
    int age; //si <12 considéré comme enfant
    int categorie; // 0 enfant 1 adulte
    int civilite; // 0 homme, 1 femme, 2 non-binaire
    int privilege; // 0 Rien , 1 VIP
    int numsiege_X; //généré en fonction des places disponible ou le voyageur peut choisir egalement sa place
    int numsiege_Y;
    ticketBagage bagage[2]; // un passager peut en avoir 2 maximum
} billet;




typedef struct {
    char modeleAvion[20], destination[50], numeroVol[15];
    int nbrplace, nbrplacelibre;
    int placelibre[500][500];// vu 2d de haut des places de l'avion 1/2 occupé   0 -> libre on initialise le tableau à 0
    int taille_X, taille_Y; // taille reel de l'avion qu'on met lors de son initialisation
    int nbrBagage;
    int passagerPriority; // nombre de passagers VIP
    int passagerEmbarque; // nombre de passagers qui "sont" déjà dans l'avion
    float ttpdsbagages; // somme du poids de tout les bagages
    date horaire;
} avion;


#ifndef NF05_PROJECT_STRUCT_H
#define NF05_PROJECT_STRUCT_H

#endif //NF05_PROJECT_STRUCT_H
