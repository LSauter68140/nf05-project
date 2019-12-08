
#include "fonction.h"


void affiPassager(billet passager) {

    printf("Billet Numero :  %c ---- \n", passager.numBillet);
    printf("______________________________________________\n");
    if (passager.privilege == 1) {

        printf("Felicitation vous etes VIP !\n");

    }
    printf("|\tNom : \t%s  \t Prenom : %s \n", passager.nom, passager.prenom);
    printf("|\tAge :\t %d \n", passager.age);
    printf("|\tCategorie : \t");
    if (passager.age < 13) {
        printf("Enfant\n");
    } else {
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
    printf("|\tPlace dans l'avion (X;Y) %d, %d\n", passager.numsiege_X, passager.numsiege_Y);
    printf("|\tDestination %s \n\n", passager.destination);
    printf("______________________________________________\n");
};

billet ajoutPassager(avion *tabAvion, int nbrAvions) {

    char choix;
    avion intermediare;
    int nbrPassager = 1, choixDest, i = 0, siegeAlea;
    billet newPassager;


    printf("Vous allez ajouter un nouveau passager\n");
    printf("Classe economique ou Business ? 0 ->eco / 1 -> business\n");
    scanf("%d", &newPassager.privilege);
    printf("\nVotre nom : \t");
    getchar();
    gets(newPassager.nom);
    printf("\nVotre prenom : \t ");
    scanf("%s", &newPassager.prenom);
    // gets(newPassager.prenom);
    //  printf("%s", newPassager.prenom);
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
    /* */

    i = 0;
    printf("\n| Prevoir 2h avant le depart pour l'embarquement plus passage de la securite\n");
    while (i < nbrAvions && tabAvion[i].nbrplacelibre > 0) {
        printf("Vol %d ---------- \n|\tDestination  : %s \tModele d'avion : %s \n|\tHoraire %d/%d/%d a  %d h %d \n",
               i + 1, tabAvion[i].destination, tabAvion[i].modeleAvion, tabAvion[i].horaire.jour,
               tabAvion[i].horaire.mois, tabAvion[i].horaire.annee, tabAvion[i].horaire.heure,
               tabAvion[i].horaire.minute);

        ++i;
    }
    do {
        printf("Choissez votre destination \n");
        scanf("%d", &choixDest);
    } while (choixDest < 1 || choixDest > nbrAvions);

    choixDest--;

    strcpy(newPassager.destination, tabAvion[choixDest].destination);
    tabAvion[choixDest].nbrplacelibre--;

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


    //  printf(" l'autre billet %s", tabPassager[nbrPassager - 1].passager.numBillet);

    /* tabAvion[choixDest].placelibre[1][1] = 1;
     tabAvion[choixDest].placelibre[2][1] = 1;
     tabAvion[choixDest].placelibre[3][1] = 1;*/
    printf("choix destinaiton %d %s", choixDest, newPassager.destination);
    affiSiege(tabAvion[nbrAvions - 1].placelibre, tabAvion[choixDest].taille_X, tabAvion[choixDest].taille_Y);


    do {
        printf("Voulez vous choisir votre place ? O/N");
        scanf("%c", &choix);

    } while (choix != 'o' && choix != 'O' && choix != 'n' && choix != 'N' && choix != '0');

    if (choix == 'o' || choix == 'O' || choix == '0') {
        printf("Choississez votre place : (taper la ligne et la colone- 0_libre - 1_occcupé  )\n");
        do {
            printf("\n la colonne :");
            scanf("%d", &newPassager.numsiege_X);
            newPassager.numsiege_X--;
            while (newPassager.numsiege_X > tabAvion[choixDest].taille_X && newPassager.numsiege_X < 0) {
                printf("veuillez renseigner une colonne valide");
                scanf("%d", &newPassager.numsiege_X);
                newPassager.numsiege_X--;

            }
            printf("\n la ligne :");
            scanf("%d", &newPassager.numsiege_Y);
            newPassager.numsiege_Y--;
            while (newPassager.numsiege_Y > tabAvion[choixDest].taille_Y && newPassager.numsiege_Y < 0) {
                printf("veuillez renseigner une ligne valide");
                newPassager.numsiege_Y--;
                scanf("%d", &newPassager.numsiege_Y);

            }
            if (tabAvion[choixDest].placelibre[newPassager.numsiege_X][newPassager.numsiege_Y] != 0)
                printf("place dejà prise veuillez en selectionner une autre\n");
        } while (tabAvion[choixDest].placelibre[newPassager.numsiege_X][newPassager.numsiege_Y] != 0);


    } else {
        srand(time(NULL));
        siegeAlea = (int) (rand() % (tabAvion[choixDest].nbrplacelibre + 1));
        printf(" \n alea %d", siegeAlea);
        newPassager.numsiege_X = 0;
        newPassager.numsiege_Y = 0;
        while (siegeAlea > 0) {
            if (tabAvion[choixDest].placelibre[newPassager.numsiege_X][newPassager.numsiege_Y] == 0)
                siegeAlea--;
            if (newPassager.numsiege_Y >= tabAvion[choixDest].taille_X) {
                newPassager.numsiege_X++;
                newPassager.numsiege_Y = 0;
            }
            newPassager.numsiege_Y++;
        }

    }
    printf("\n siege  %d %d", newPassager.numsiege_X, newPassager.numsiege_Y);
    tabAvion[choixDest].placelibre[newPassager.numsiege_Y][newPassager.numsiege_X] =
            (newPassager.privilege == 1) ? 2 : 1; // les vip sont notés 2 et les "normaux" sont 1;
    // on réaffiche
    affiSiege(tabAvion[choixDest].placelibre, tabAvion[choixDest].taille_X, tabAvion[choixDest].taille_Y);
    printf("Votre siege a bien ete reserve \n");

    newPassager = generBillet(newPassager); // genere le billet
    // on sauvegarde la place dans le fichier idoine


    return newPassager;
}

int sauvPlace(avion *tabAvion, billet passager ){

    char nameVol[50];
    FILE *ptrVol;
    float tabDonne[4];
    int choixDest =0, placeOccupees;
    // on recupere le numéro de destination du vol choisi par le passager via strcmp
   while (strcmp(tabAvion[choixDest].destination, passager.destination) !=0){
       choixDest ++;
   }
    sprintf(nameVol, "donnees/destination/%s.txt",tabAvion[choixDest].destination);

    ptrVol = fopen(nameVol, "r");

    if (ptrVol == NULL){
        printf("Erreur fichier de vol manquant");
        return EXIT_FAILURE;
    }

    // on recupere les 4 valeurs fixes

    fscanf(ptrVol,"%f %f %f %f", &tabDonne[0], &tabDonne[1], &tabDonne[2], &tabDonne[3]);

    int **tabPlace = (int**) malloc((int)tabDonne[0] * sizeof(int*)); // on fait tableau d'entier avec le nbr de place prises
    placeOccupees = tabAvion[choixDest].taille_X * tabAvion[choixDest].taille_Y-(int)tabDonne[0];
    for (int i = 0; i < placeOccupees ; ++i) {
        tabPlace[i] = (int *) malloc(3 * sizeof(int)); // une colonne x et y, plus priorité
        // on recupère les places dans le fichier
        fscanf(ptrVol, "%d %d %d", &tabPlace[i][0], &tabPlace[i][1], &tabPlace[i][3]);
    }
    fclose(ptrVol); //on referme le fichier et apres on ecrase les données par dessus pour faire une modification
    ptrVol = fopen(nameVol, "w");
    // on change les valeurs à changer
    tabDonne[0] --; // on enleve une place de libre
    tabDonne[1] += (passager.privilege == 1) ? 1 : 0; // si vip  on ajoute un passager vip dans l'avvion
    tabDonne[2] += (float)passager.nbrBagages;

    for (int j = 0; j < passager.nbrBagages; ++j) {
        tabDonne[3] += passager.bagage[j].poids;
    }

    // on remet tout dans le fichier puis on ajoute la nouvelle place dans le fichier
    fprintf(ptrVol, "%d %d %d %f\n",(int)tabDonne[0], (int)tabDonne[1], (int)tabDonne[2], tabDonne[3]);

    for (int k = 0; k < placeOccupees; ++k) {
        fprintf(ptrVol,"%d %d %d\n",tabPlace[k][0], tabPlace[k][1], tabPlace[k][3]);
    }
    fprintf(ptrVol,"%d %d %d\n", passager.numsiege_X, passager.numsiege_X, passager.privilege );
    fclose(ptrVol);
    printf("\nEmbarquement enregistre");
    return EXIT_SUCCESS;
}

billet generBillet(billet passager) {

    char numBillet[12];
    FILE *ptrBillet;
    char chaine[10], nameBillet[20];
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
    strcat(numBillet, "\0"); // pour bien définir la fin de la chaine de caractère


    for (int i = 0; i < 10; ++i) {
        numBillet[i] = toupper(numBillet[i]); // on a généré le numéro de billet
    }
    // maintenant on l'export en .txt
    printf("\n\n\t----- le billet se trouve à la racine du programme en .txt-----\n");

    ptrBillet = fopen("donnees/passagers.txt", "a+");
    fprintf(ptrBillet, "\n%s %s %s %s %d %d %d %s %s %d %d %d", numBillet, passager.destination,
            passager.nom, passager.prenom, passager.age, passager.civilite, passager.privilege,
            passager.nationalite, passager.numPassport, passager.nbrBagages, passager.numsiege_X, passager.numsiege_Y);

    fclose(ptrBillet);

    strcpy(passager.numBillet, numBillet);

    return passager;
}

billet deposeBag(billet passager) {

    printf("Vous pouvez deposer %d bagages en soute \n", passager.nbrBagages);

    for (int i = 0; i < passager.nbrBagages; ++i) {
        passager.bagage[i] = generTicketBag(passager, i);
    }

    return passager;
}

ticketBagage generTicketBag(billet passager, int n) {

    FILE *ptr;
    char ticket[20] = "Ticket ";
    ticketBagage NewBagage;
    NewBagage.numbagage = n;
    sprintf(ticket, "Ticket %d.txt", n + 1);
    ptr = fopen(ticket, "w");
    printf("Poids de votre bagage en kg ? (max 20kg sinon supplement)\n");
    scanf("%f", &NewBagage.poids);
    passager.bagage[n].numbagage = n + 1;
    passager.bagage[n].poids = NewBagage.poids;
    fprintf(ptr, "------------------------------------------------------\n");
    fprintf(ptr, " Bagage appartenant à %s %s \n", passager.prenom, passager.nom);
    fprintf(ptr, "Numero de bagage \t %d\n", n + 1);
    fprintf(ptr, " Poids \t%f\n", NewBagage.poids);
    if (passager.privilege == 1) {
        fprintf(ptr, "Bagage prioritaire \n");
    } else {
        fprintf(ptr, "Bagage non prioritaire\n");
    }
    fprintf(ptr, "\n------------------------------------------------------");
    fclose(ptr);
    return NewBagage;
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

avion * initialisationVol(int *nbrAvions){

    FILE *ptrAvion, *ptrVol;
    int place_x, place_y, placeOccupees, placeVip;
    ptrAvion = fopen("donnees/avion.txt", "r");
    char nameVol[50];
    avion *tabAvion = (avion *) malloc(0);// recupere tout les vols dans le fichier
    while (feof(ptrAvion) == 0) {
        *nbrAvions +=1;
        tabAvion = (avion *) realloc(tabAvion, *nbrAvions * sizeof(avion));
        fscanf(ptrAvion, "%s", tabAvion[*nbrAvions - 1].destination);
        fscanf(ptrAvion, "%s", tabAvion[*nbrAvions -
                                        1].modeleAvion); //on me signale dans l'oreillette qu'on peut le faire en 1ligne mais c'est plus SEX comme ca....
        fscanf(ptrAvion, "%d", &tabAvion[*nbrAvions - 1].nbrplace);
        fscanf(ptrAvion, "%s", tabAvion[*nbrAvions - 1].numeroVol);
        fscanf(ptrAvion, "%d", &tabAvion[*nbrAvions - 1].taille_X);
        fscanf(ptrAvion, "%d", &tabAvion[*nbrAvions - 1].taille_Y);

        // on récpere l'horaire de l'avion
        fscanf(ptrAvion, "%d %d %d %d %d", &tabAvion[*nbrAvions - 1].horaire.jour, &tabAvion[*nbrAvions - 1].horaire.mois,
               &tabAvion[*nbrAvions - 1].horaire.annee, &tabAvion[*nbrAvions - 1].horaire.heure,
               &tabAvion[*nbrAvions - 1].horaire.minute);
        for (int i = 0; i < tabAvion[*nbrAvions - 1].taille_X; ++i) {
            for (int j = 0; j < tabAvion[*nbrAvions - 1].taille_Y; ++j)  // on initialise ttes les places à zéro -> vide;
                tabAvion[*nbrAvions - 1].placelibre[i][j] = 0;
        }
        // fichier spécifique pour chaque vol et on regarde s'il existe avec les nbr de place de bagages....
        strcpy(nameVol, "donnees/destination/");
        strcat(nameVol,
               tabAvion[*nbrAvions - 1].destination);
        strcat(nameVol, ".txt");
        ptrVol = fopen(nameVol, "r+");
        if (ptrVol != NULL) {
            fscanf(ptrVol, "%d", &tabAvion[*nbrAvions - 1].nbrplacelibre);
            fscanf(ptrVol, "%d", &tabAvion[*nbrAvions - 1].passagerPriority);
            fscanf(ptrVol, "%d", &tabAvion[*nbrAvions - 1].nbrBagage);
            fscanf(ptrVol, "%f", &tabAvion[*nbrAvions - 1].ttpdsbagages);

            placeOccupees = tabAvion[*nbrAvions-1].taille_X * tabAvion[*nbrAvions-1].taille_Y -tabAvion[*nbrAvions - 1].nbrplacelibre;

            for (int k = 0;
                 k < placeOccupees; ++k) { // on recupere les places qui sont déjà occupées et on le met dans l'avion
                fscanf(ptrVol, "%d", &place_x);
                fscanf(ptrVol, "%d", &place_y);
                fscanf(ptrAvion, "%d", &placeVip);
                tabAvion[*nbrAvions - 1].placelibre[place_x][place_y] = (placeVip ==1) ? 2 : 1;
            }


        } else {
            // si existe pas on initialisre les variables à 0 et on creer le fichier.
            fclose(ptrVol);
            ptrVol = fopen(nameVol, "w+");
            tabAvion[*nbrAvions - 1].nbrplacelibre = tabAvion[*nbrAvions-1].taille_X * tabAvion[*nbrAvions-1].taille_Y;
            tabAvion[*nbrAvions - 1].passagerPriority = 0;
            tabAvion[*nbrAvions - 1].nbrBagage = 0;
            tabAvion[*nbrAvions - 1].ttpdsbagages = 0;
            fprintf(ptrVol, "%d %d %d %f\n", tabAvion[*nbrAvions - 1].nbrplacelibre,
                    tabAvion[*nbrAvions - 1].passagerPriority, tabAvion[*nbrAvions - 1].nbrBagage,
                    tabAvion[*nbrAvions - 1].ttpdsbagages);
        }
        fclose(ptrVol);

    }
    fclose(ptrAvion);
    return tabAvion;

}

billet * initialisationPassager(int *nbrPassager){


    billet *tabPassager = (billet*) malloc(0);

    FILE *ptrpassager;
    ptrpassager = fopen("donnees/passagers.txt", "r");
    if (ptrpassager == NULL) {
        printf("Erreur fichier manquant avion/avion.txt veuillez reessayer");
        return 0;
    }

        while (feof(ptrpassager) == 0) {

            tabPassager = (billet *) realloc(tabPassager, (*nbrPassager + 1) * sizeof(billet));

            //fprintf(ptrBillet,"%s %s %d",numBillet, passager.destination, passager.privilege );
            //    fprintf(ptrBillet,"%s %s %d %d %s %s %s",passager.nom, passager.prenom,passager.age, passager.civilite == 0,passager.nationalite, passager.numPassport);

            fscanf(ptrpassager, "%s %s %s %s %d %d %d %s %s %d %d %d", tabPassager[*nbrPassager].numBillet,
                   tabPassager[*nbrPassager].destination, tabPassager[*nbrPassager].prenom, tabPassager[*nbrPassager].nom,
                   &tabPassager[*nbrPassager].age,
                   &tabPassager[*nbrPassager].civilite, &tabPassager[*nbrPassager].privilege,
                   tabPassager[*nbrPassager].nationalite,
                   tabPassager[*nbrPassager].numPassport,&tabPassager[*nbrPassager].nbrBagages, &tabPassager[*nbrPassager].numsiege_X, &tabPassager[*nbrPassager].numsiege_Y ); // on recupere les coordonnéees du passager

            *nbrPassager +=1;
        }

    fclose(ptrpassager);
    return tabPassager;
}

int main(int argc, char **argv) {

    // on commence par récupérer les avions et passagers

    billet *tabPassager;
    avion *tabAvion;
    int nbrPassager = 0, nbrAvions = 0;

    printf("Projet d'NF05 - Gestion des passagers dans un aeroport\n");

    //initialisation des vols et passagers
    tabPassager = initialisationPassager(&nbrPassager);
    tabAvion = initialisationVol(&nbrAvions);


    int j = 0;
    printf("nbr passager %d ", nbrPassager);
    while (j < nbrPassager) {
        printf("Vol %d ---------- \n Passager  : %s \t Destination : %s \n", j + 1, tabPassager[j].nom,
               tabPassager[j].destination);
        ++j;
    }
    //tabPassager[0] = ajoutPassager(tabAvion, nbrAvions);
    printf("Depose des bagages \n");
    tabPassager[0] = deposeBag(tabPassager[0]);
    tabPassager[0].numsiege_X = 10;
    tabPassager[0].numsiege_Y = 5;
    sauvPlace(tabAvion, tabPassager[0]);
/*



    //printf("Vous allez ajouter un nouveau passager \n")

   // tabPassager[nbrPassager - 1] = ajoutPassager(tabAvion);
    strcpy(tabPassager[nbrPassager - 1].prenom, "azerty");
    strcpy(tabPassager[nbrPassager - 1].nom, "azzerty");
    strcpy(tabPassager[nbrPassager - 1].nationalite, "francaise");
    strcpy(tabPassager[nbrPassager - 1].numPassport, "azefg25f2");
    strcpy(tabPassager[nbrPassager - 1].destination, "USA");
    tabPassager[nbrPassager - 1].age = 12;
    tabPassager[nbrPassager - 1].nbrBagages = 3;
    tabPassager[nbrPassager - 1].privilege = 1;
    tabPassager[nbrPassager - 1].civilite = 2;
    printf("zety");
    tabPassager[nbrPassager - 1]= generBillet(tabPassager[nbrPassager - 1]);
    printf("vous avez rentre \n");
    affiPassager(tabPassager[nbrPassager - 1]);//affiche le tout

*/

    return EXIT_SUCCESS;
}