#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "general_functions.h"
#include "am_file_functions.h"
#define MAX_SIZE 81
struct FileData open_file(char *extension, FILE *fpw, char *argv[], int count) {
   struct FileData fileData;
    fileData.name = argv[count];
    strcat(fileData.name, extension);
    fileData.fpw = fopen(fileData.name, "w");
    return fileData;
}
struct LineData* divide_line(char *line) {
    struct LineData *lineData = malloc(sizeof(struct LineData));
    lineData->head_lable = NULL;
    lineData->command = NULL;
    lineData->paramA = NULL;
    lineData->paramB = NULL;
    lineData->lable= NULL;
    char *token;
    printf("Processing line: %s", line);
    if (strncmp(line, ";", 1) != 0) {
        /* Divide by semicolon */
        token = strtok(line, ";");
        if (strchr(line, ':') != NULL) {
            /* Divide by colons */
            lineData->lable = strtok(token, ":");
            token = strtok(NULL, ":");
            lineData->head_lable = append(lineData->head_lable, lineData->lable);
        } else {
            lineData->lable = NULL;
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
int check_operands(char *paramA) {
    char twoOperands[][4] = {"mov", "cmp", "add", "sub", "lea"};
    char oneOperands[][4] = {"not", "clr", "inc", "dec", "jmp", "bne", "red", "prn", "jsr"};
    char noOperands[][4] = {"rts", "stop"};
    int i;
    for (i = 0; i < sizeof(twoOperands) / sizeof(twoOperands[0]); i++) {
        if (strcmp(paramA, twoOperands[i]) == 0) {
            return -1;
        }
    }
    for (i = 0; i < sizeof(oneOperands) / sizeof(oneOperands[0]); i++) {
        if (strcmp(paramA, oneOperands[i]) == 0) {
            return -1;
        }
    }
    for (i = 0; i < sizeof(noOperands) / sizeof(noOperands[0]); i++) {
        if (strcmp(paramA, noOperands[i]) == 0) {
            return -1;
        }
    }
    return 1;
}