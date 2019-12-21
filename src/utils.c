#include "utils.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void formatDate(Date date, char* formattedDate) {
    char day[3], month[3], year[5], hour[3], minute[3];

    sprintf(day, "%s%d", date.day < 10 ? "0" : "", date.day);
    sprintf(month, "%s%d", date.month < 10 ? "0" : "", date.month);
    sprintf(year, "%s%d", date.year < 10 ? "0" : "", date.year);
    sprintf(hour, "%s%d", date.hour < 10 ? "0" : "", date.hour);
    sprintf(minute, "%s%d", date.minute < 10 ? "0" : "", date.minute);

    sprintf(formattedDate, "%s/%s/%s %sh%s", day, month, year, hour, minute);
}

char* formatGender(int gender) {
    switch(gender) {
        case 0:
            return "Homme";
        case 1:
            return "Femme";
        case 2:
            return "Non binaire";
        default:
            return "";
    }
}

void getLine(char* line, int maxLength) {
    int ch, len;

    fgets(line, maxLength, stdin);

    // On clean stdin
    len = strlen(line);
    if(len == maxLength - 1)
        while ((ch = getchar()) != '\n' && ch != EOF);
    
    for(int i = 0; i < maxLength && line[i] != '\0'; i++) {
        // On retire les sauts de ligne
        if(line[i] == '\n') {
            line[i] = '\0';
        }

        // On remplace les espaces par des underscores
        // pour montrer qu'il s'agit d'une seule variable dans les fichiers
        if(line[i] == ' ') {
            line[i] = '_';
        }
    }
}

void getValue(char* format, void* value) {
    scanf(format, value);

    // Clear others characters until \n and \n itself
    while(getchar() != '\n');
}

void print(char *format, ...) {
    int i, j = 0;
    char formattedString[500] = "", formatBuffer[500];
    va_list args;
    int argc = 0;

    argc += countOccurrences(format, "%c");
    argc += countOccurrences(format, "%s");
    argc += countOccurrences(format, "%d");
    argc += countOccurrences(format, "%f");

    // Le fait de ne pas passer le dernier argument de la fonction print
    // en second paramètre de va_start peut poser problème pour les anciens compilateurs
    va_start(args, argc);
    
    // On parcoure le format
    for (i = 0; format[i] != '\0'; i++) {
        if (format[i] != '%') {
            formattedString[j++] = format[i];
        }
        else {
            switch(format[i + 1]) {
                case 'c':
                    sprintf(formatBuffer, "%c", va_arg(args, int));
                    break;
                case 's':
                    sprintf(formatBuffer, "%s", va_arg(args, char*));
                    break;
                case 'd':
                    sprintf(formatBuffer, "%d", va_arg(args, int));
                    break;
                case 'f':
                    sprintf(formatBuffer, "%f", va_arg(args, double));
                    break;
                case '%':
                    sprintf(formatBuffer, "%%");
                    break;
                default:
                    sprintf(formatBuffer, "%%%c", format[i + 1]);
                    break;

            }

            strcat(formattedString, formatBuffer);

            int formatBufferLength = 0;
            for (; formatBuffer[formatBufferLength] != '\0'; formatBufferLength++);
            j += formatBufferLength;

            // On passe le caractère de formatage
            i++;
        }
    }

    formattedString[j] = '\0';
    
    va_end(args);

    printf("%s", formattedString);
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}

int countOccurrences(char *string, char* search) {
    int count = 0;
    
    for (int i = 0; string[i] != '\0'; i++) {
        int j;
        for (j = 0; search[j] != '\0'; j++) {
            if (string[i + j] != search[j]) {
                break;
            }
        }

        // Si on a atteint la fin de la chaîne de caractères recherchée
        if (search[j] == '\0') {
            count++;
        }
    }

    return count;
}