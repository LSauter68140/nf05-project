#include "utils.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}