#ifndef NF05_PROJECT_UTILS_H
#define NF05_PROJECT_UTILS_H

#include <string.h>
#include <stdio.h>

#include "structs.h"

// Format
void formatDate(Date date, char* formattedDate);
char* formatGender(int gender);

// Inputs
void getLine(char* line, int maxLength);

#endif //NF05_PROJECT_UTILS_H
