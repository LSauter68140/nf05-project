#include "utils.h"

void formatDate(Date date, char* formattedDate) {
    sprintf(formattedDate, "%d/%d/%d %dh%d", date.day, date.month, date.year, date.hour, date.minute);
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
#ifdef WINDOWS
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}