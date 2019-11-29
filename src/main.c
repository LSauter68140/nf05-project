
#include "fonction.h"


void affiPassager(billet passager) {

    printf("Billet Numero :  %c ---- \n", passager.numBillet);
    printf("______________________________________________\n");
    if (passager.privilege == 1) {

        printf("Felicitation vous êtes VIP !\n");

    }
    printf("|\tNom : \t%s  \t Prenom : %s \n", passager.nom, passager.prenom);
    printf("|\tAge :\t %d \n", passager.age);
    printf("|\tCategorie : \t");
    if (passager.age <13){
        printf("Enfant\n");
    } else{
        printf("Adulte\n");
    }
    printf("|\tCivilite : \t");
    if (passager.civilite == 0) {

        printf("Homme\n");
    } else if (passager.civilite == 1) {

        printf("Femme\n");

    } else if (passager.civilite == 2) {

        printf("Non binaire\n");
    }
    printf("|\tNuméro de passeport %s \t\n", passager.numPassport);
    printf("|\tNombre de bagages : %d \t\n", passager.nbrBagages);
    printf("|\tNationalite : %s \t\n", passager.nationalite);

    printf("|\tNumero de billet : %s \t\n", passager.numBillet);

    printf("|\tDestination %s \n\n", passager.destination);
    printf("______________________________________________\n");
};


billet ajoutPassager(avion *tabAvion ) {

    char choix;
    avion intermediare;
    int nbrPassager = 1, nbrAvions = 1, choixDest, i = 0, siegeAlea;
    billet newPassager;
/*

    printf("Vous allez ajouter un nouveau passager\n");
    printf("Passager prioritaire ? 0 ->Non / 1 -> Oui\n");
    scanf("%d", &newPassager.privilege);
    printf("\nVotre nom : \t");
    getchar();
    gets(newPassager.nom);
    printf("\nVotre prenom : \t ");
    gets(newPassager.prenom);
    printf("\nVotre civilite (0 homme, 1 femme, 2 non binaire) : \t");
    scanf("%d", &newPassager.civilite);
    while (newPassager.civilite < 0 || newPassager.civilite > 2) {
        printf("\nentrer un nombre valide (0 homme, 1 femme, 2 non-binaire) : \t");
        scanf("%d", &newPassager.civilite);

    }
    printf("\nVotre numéro de passeport :  ");
    getchar();
    gets(newPassager.numPassport);
    printf("\nVotre age : ");
    scanf("%d", &newPassager.age);
    printf("\nVotre nationalité :");
    getchar();
    gets(newPassager.nationalite);
    printf("\nNombre de bagage.s 0/1 -> non prioritaire / jusqu'à 2 si prioritaire ");
    scanf("%d", &newPassager.nbrBagages);
    while (newPassager.nbrBagages < 0 || newPassager.nbrBagages > 1 +
                                                                  newPassager.privilege) { // on met plus privilige car dasn ce cas on a cette variable qui est egale à 1 et on a le droit a un bagage de plus
        printf("\nNbr de bagage.s emis non correct max 2 pour prioritaire et sinon 1\n");
        scanf("%d", &newPassager.nbrBagages);
    }
     */

    i = 0;
    while (i < nbrAvions && tabAvion[i].nbrplacelibre > 0) {
        printf("Vol %d ---------- \n Destination  : %s \tModele d'avion : %s \n", i + 1, tabAvion[i].destination,
               tabAvion[i].modeleAvion);
        ++i;
    }
    do {
        printf("Choissez votre destination \n");
        scanf("%d", &choixDest);
    } while (choixDest < 1 || choixDest > nbrAvions);

    choixDest--;

    strcpy(newPassager.destination, tabAvion[choixDest].destination);
    tabAvion[choixDest].nbrplacelibre--;
    printf("arzt");
    // verifie si le nbr de place disponible est supierieur a 0 ou non si oui met le vol à la fin de la liste avec ceux qui sont déjà complet;
    if (tabAvion[choixDest].nbrplacelibre == 0) {
        i = 0;
        while (tabAvion[i].nbrplacelibre > 0)
            ++i;
        intermediare = tabAvion[choixDest];
        tabAvion[choixDest] = tabAvion[i - 1];
        tabAvion[i - 1] = intermediare;
        printf("Felicitation vous avez eu la derniere place\n");
    }



    generBillet(newPassager, &newPassager.numBillet); // genere le billet

    //  printf(" l'autre billet %s", tabPassager[nbrPassager - 1].passager.numBillet);

    tabAvion[choixDest].placelibre[1][1] = 1;
    tabAvion[choixDest].placelibre[2][1] = 1;
    tabAvion[choixDest].placelibre[3][1] = 1;
    printf("zerty  choix destinaiton %d %s", choixDest, newPassager.numBillet);
    affiSiege(tabAvion[nbrAvions - 1].placelibre, 30, 5);


    do {
        printf("Voulez vous choisir votre place ? O/N");
        scanf("%c",&choix);

    } while (choix != 'o' && choix != 'O' && choix != 'n' && choix != 'N');

    if (choix == 'o' || choix == 'O') {
        printf("Choississez votre place : (taper la ligne et la colone- 0_libre - 1_occcupé  )\n");
        do {
            printf("\n la colonne :");
            scanf("%d", &newPassager.numsiege_X);
            newPassager.numsiege_X--;
            while (newPassager.numsiege_X > 31 && newPassager.numsiege_X < 0) {
                printf("veuillez renseigner une colonne valide");
                scanf("%d", &newPassager.numsiege_X);
                newPassager.numsiege_X--;

            }
            printf("\n la ligne :");
            scanf("%d", &newPassager.numsiege_Y);
            newPassager.numsiege_Y--;
            while (newPassager.numsiege_Y > 6 && newPassager.numsiege_Y < 0) {
                printf("veuillez renseigner une ligne valide");
                newPassager.numsiege_Y--;
                scanf("%d", &newPassager.numsiege_Y);

            }
            if (tabAvion[choixDest].placelibre[newPassager.numsiege_X][newPassager.numsiege_Y] == 1)
                printf("place dejà prise veuillez en selectionner une autre\n");
        } while (tabAvion[choixDest].placelibre[newPassager.numsiege_X][newPassager.numsiege_Y] ==
                 1);


    } else {
        srand(time(NULL));
        siegeAlea = (int) (rand() / (double) RAND_MAX * (tabAvion[choixDest].nbrplacelibre - 1));
        newPassager.numsiege_X = 0;
        newPassager.numsiege_Y = 0;
        while (siegeAlea > 0) {
            if (tabAvion[choixDest].placelibre[newPassager.numsiege_X][newPassager.numsiege_Y] == 0)
                siegeAlea--;
            if (newPassager.numsiege_X >= 30) {
                newPassager.numsiege_Y++;
                newPassager.numsiege_X = 0;
            }
            newPassager.numsiege_X ++;
        }
        tabAvion[choixDest].placelibre[newPassager.numsiege_X-1][newPassager.numsiege_Y] =
                newPassager.privilege == 1 ? 2
                                                                     : 1; // les vip sont notés 2 et les "normaux" sont 1;
    }

    // on réaffiche
    affiSiege(tabAvion[nbrAvions - 1].placelibre, 30, 5);
    printf("Votre siege a bien ete reserve \n");

    return newPassager;
}


void generBillet(billet passager, char *numBillet) {

    char chaine[10];
    itoa(passager.age, chaine, 10);

    numBillet[0] = passager.prenom[0];
    numBillet[1] = passager.prenom[1];
    numBillet[2] = passager.nom[0];
    numBillet[3] = passager.nom[1];
    numBillet[4] = chaine[0];
    numBillet[5] = chaine[1];
    numBillet[6] = passager.nationalite[0];
    numBillet[7] = passager.nationalite[1];
    numBillet[8] = passager.numPassport[0];
    numBillet[9] = passager.numPassport[1];

    for (int i = 0; i < 10; ++i) {
        numBillet[i] = toupper(numBillet[i]);
    }

}

void affiSiege(int placeLibre[][500], int longeur,
               int largeur) { //on suppose ici que la longeur de l'avion sera tjrs sup a 10sièges
    printf("\n   ");
    int unite = (longeur < 10) ? longeur : 9;
    for (int j = 0; j < unite; ++j)
        printf("%d  ", j + 1);
    for (int l = 9; l < longeur; ++l)
        printf("%d ", l + 1);
    for (int k = 0; k < largeur; ++k) {
        printf("\n %d ", k + 1);
        for (int j = 0; j < longeur; ++j)
            printf("%d  ", placeLibre[j][k]);
    }
    printf("\n");

}

avion initalisationVol(char destination[], char modele[], int nbrplace, char numero[], int longueur, int largeur) {

    avion newVol;
    strcpy(newVol.destination, destination);
    strcpy(newVol.modeleAvion, modele);
    strcpy(newVol.numeroVol, numero);/**/
    newVol.ttpdsbagages = 0;
    newVol.nbrBagage = 0;
    newVol.nbrplace = nbrplace;
    newVol.nbrplacelibre = nbrplace;
    newVol.passagerPriority = 0;
   for (int i = 0; i < longueur; ++i) {
        for (int j = 0; j < largeur; ++j)
            newVol.placelibre[i][j] = 0;
    }
    return newVol;
}


int main(int argc, char **argv) {


    billet *tabPassager;
    avion *tabAvion;
    int nbrPassager = 1, nbrAvions = 1;
    tabPassager = (billet *) malloc(nbrPassager * sizeof(billet));
    tabAvion = (avion *) malloc(nbrAvions * sizeof(avion));

    printf("aezrgth");

    tabAvion[nbrAvions - 1] = initalisationVol("USA", "A320", 150, "AAA156", 30 , 5);

    printf("Projet d'NF05 - Gestion des passagers dans un aeroport\n");
    //printf("Vous allez ajouter un nouveau passager \n")

    tabPassager[nbrPassager - 1] = ajoutPassager(tabAvion);


    printf("vous avez rentrez \n");
    affiPassager(tabPassager[nbrPassager - 1]);  //affiche le tout
    // on regarde le vol qui correspond à la destination du passager et on ljui donne un numero de place et de billet
    //printf("votre avion est le numéro:\n");*/
    return EXIT_SUCCESS;
}