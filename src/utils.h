#ifndef NF05_PROJECT_UTILS_H
#define NF05_PROJECT_UTILS_H

#include "structs.h"

// Format
void formatDate(Date date, char* formattedDate);
char* formatGender(int gender);

// Inputs
void getLine(char* line, int maxLength);
void getValue(char* format, void* value);

// Outputs
void print(char *format, ...);
void clearScreen();

// Misc
int countOccurrences(char *string, char* search);

#endif //NF05_PROJECT_UTILS_H
