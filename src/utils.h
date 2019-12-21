#ifndef NF05_PROJECT_UTILS_H
#define NF05_PROJECT_UTILS_H

#include "structs.h"

// Format
void formatDate(Date date, char* formattedDate);
char* formatGender(int gender);

// Inputs
void getLine(char* line, int maxLength);
void getValue(char* format, void* value);

void clearScreen();

#endif //NF05_PROJECT_UTILS_H
