#ifndef NF05_PROJECT_UTILS_H
#define NF05_PROJECT_UTILS_H

#include <string.h>
#include <stdio.h>

#include "structs.h"

// Format
void formatDate(Date date, char* formattedDate);
char* formatGender(int gender);

// Files
void writeFile(char* filename, char* content);
void appendFile(char* filename, char* content);

// Inputs
void getLine(char* line, int maxLength);

#endif //NF05_PROJECT_UTILS_H
