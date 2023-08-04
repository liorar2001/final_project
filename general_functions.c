#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "general_functions.h"
#include "am_file_functions.h"
#define MAX_SIZE 81
struct FileData* open_file(char *extension,char* name) {
   struct FileData* fileData=malloc(sizeof(struct FileData));
   char* fname = malloc(sizeof(name));
   strcpy(fname,name);
   if (fileData)
   {
      // name = strtok(name, ".");
       strcat(fname, extension);
       fileData->fpw = fopen(fname, "w+");
       fileData->name = fname;
   }
    return fileData;
}

struct LineData* divide_line(char line[]) {
    struct LineData *lineData =(struct LineData*) malloc(sizeof(struct LineData));
    char *token;
    if (lineData == NULL)return NULL;
    lineData->command = NULL;
    lineData->paramA = NULL;
    lineData->paramB = NULL;
    lineData->lable= NULL;
    lineData->next = NULL;
    
    printf("Processing line: %s", line);
    if (strncmp(line, ";", 1) != 0) {
        /* Divide by semicolon */
        token = strtok(line, ";");
        if (strchr(line, ':') != NULL) {
            /* Divide by colons */
            lineData->lable = strtok(token, ":");
            token = strtok(NULL, ":");
            /* append(lineData, lineData->lable); */
        } 
        /* Divide by comma */
        lineData->command = strtok(token, ",");
        lineData->paramB = strtok(NULL, ",");
        /* Divide by spaces */
        token = strtok(lineData->command, " ");
        lineData->paramA = strtok(NULL, " ");
        /* Remove white characters */
        removeWhiteSpace(lineData->lable);
        removeWhiteSpace(lineData->command);
        removeWhiteSpace(lineData->paramA);
        removeWhiteSpace(lineData->paramB);
    }
    return lineData;
}
int check_operands(char *param) {
    char twoOperands[][4] = {"mov", "cmp", "add", "lea"};
    char oneOperands[][4] = {"not", "clr", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "sub" };
    char noOperands[][4] = {"rts", "stop"};
    int i;
    for (i = 0; i < sizeof(twoOperands) / sizeof(twoOperands[0]); i++) {
        if (strcmp(param, twoOperands[i]) == 0) {
            return 3;
        }
    }
    for (i = 0; i < sizeof(oneOperands) / sizeof(oneOperands[0]); i++) {
        if (strcmp(param, oneOperands[i]) == 0) {
            return 2;
        }
    }
    for (i = 0; i < sizeof(noOperands) / sizeof(noOperands[0]); i++) {
        if (strcmp(param, noOperands[i]) == 0) {
            return 1;
        }
    }
    return 1;
}
