/**
 * @file utils.h
 * @brief Ce fichier définit toutes les fonctions de formatage de données et d'entrée
 */

#ifndef NF05_PROJECT_UTILS_H
#define NF05_PROJECT_UTILS_H

#include "structs.h"

/**
 * @brief    Formate la date sous le format "JJ/MM/AAAA HH[h]mm"
 * @param    date               Date à formater
 * @param    formattedDate      Retourne la date formatée
 */
void formatDate(Date date, char *formattedDate);

/**
 * @brief    Formate le genre de la personne en chaîne de caractères
 * @param    gender        Le genre de la personne
 * @return   Retourne "Homme", "Femme", ou "Non binaire" en fonction de @a gender
 */
char* formatGender(Gender gender);

/**
 * @brief   Permet de récupérer une ligne de caractères depuis l'entrée standard en remplaçant les espaces par des underscores
 * @param   line        Renvoie la ligne tapée au clavier sous la forme d'une chaîne de caractères
 * @param   maxLength   La taille maximum que peut avoir la chaine de caractères
 */
void getLine(char *line, int maxLength);

/**
 * @brief   Permet de récupérer une valeur depuis l'entrée standard
 * @param   format        Le format que l'on souhaite récupérer (même paramètre que pour la fonction standard @a scanf)
 * @param   value         Renvoie la valeur
 */
void getValue(char *format, void *value);

/**
 * @brief    Efface la console en fonction du système d'exploitation sous lequel est exécuté le programme (ici on regarde si on est sous Windows ou non)
 */
void clearScreen();

#endif //NF05_PROJECT_UTILS_H
