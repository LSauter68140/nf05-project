#ifndef NF05_PROJECT_UTILS_H
#define NF05_PROJECT_UTILS_H

#include "structs.h"
/**
 * @file utils.h
 * @brief Ce fichier définit toutes les fonctions de formatage de données et d'entrée
 */

// Format

/**
 * @brief      Formatage de la date en JJ/MM/AAAA HH/mm
 * @param    date               Forme brute
 * @param    formattedDate         Retourne la date formatée.
 */


void formatDate(Date date, char* formattedDate);
/**
 * @brief      Formatage du genre de la personne en fonction de l'entrée (0,1,2)
 * @param    gender                 Le genre de la personne, (0) @a Homme, (1) @a Femmme, (2) @a Non binaire
 * @return   char*         Retourne 'Homme', 'Femme', ou 'Non binaire' en fonction de l'entrée
 */

char* formatGender(int gender);

// Inputs

/**
 * @brief    Permet de récupérer une ligne de caractères en entrée avec des espaces
 * @param   line            Renvoie la ligne tapée au clavier sous la forme d'une chaine de caractères
 * @param   maxLength         La taille maximum que peut avoir la chaine de caractères que l'on met entrée pour line.
 */

void getLine(char* line, int maxLength);

/**
 * @brief    Permet de récupérer un @a void sous la forme que l'on met en paramètre tout enlevant les espaces indésirables
 * @param   format         Le format que l'on donne en entrée peut être de type char, int, float...
 * @param   value         Renvoie la valeur que l'on a scanée
 */

void getValue(char* format, void* value);

/**
 * @brief    Efface la console, de facon différente en fonction de l'environnement sous lequel est exécuté le programme (ici regarde si on est sous Windows ou non)
 */
void clearScreen();

#endif //NF05_PROJECT_UTILS_H
