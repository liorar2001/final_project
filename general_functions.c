#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "general_functions.h"
#define MAX_SIZE 81
int IC = 0, DC = 0;
/** Open a file with the specified extension for writing.
 *
 * @param extension - The file extension to be added to the filename.
 * @param name - The name of the file without the extension.
 * @return A pointer to the FileData struct containing the file pointer and filename.
 */
struct FileData* open_file(char *extension,char* name) {
   struct FileData* fileData=malloc(sizeof(struct FileData));
   char* fname = malloc(sizeof(name));
   strcpy(fname,name);
   if (fileData)
   {
       strcat(fname, extension);
       fileData->fpw = fopen(fname, "w+");
       fileData->name = fname;
   }
    return fileData;
}
/** Divide a line of assembly code into LineData components.
 *
 * @param line - The line of assembly code to be divided.
 * @return A pointer to the LineData struct containing the components of the line.
 */
struct LineData* divide_line(char line[]) {
    struct LineData *lineData =(struct LineData*) malloc(sizeof(struct LineData));
    char *token;
    if (lineData == NULL)return NULL;
    lineData->command = NULL;
    lineData->paramA = NULL;
    lineData->paramB = NULL;
    lineData->lable= NULL;
    lineData->next = NULL;
    if (strncmp(line, ";", 1) != 0) {
        /* Divide by semicolon */
        token = strtok(line, ";");
        if (strchr(line, ':') != NULL) {
            /* Divide by colons */
            lineData->lable = strtok(token, ":");
            token = strtok(NULL, ":");
        }
        if (contains(token, ".data") == 1){
            /* Divide by spaces */
            lineData->command = strtok(token, " ");
            lineData->paramA = strtok(NULL, " ");
        }
        else {
            /* Divide by comma */
            lineData->command = strtok(token, ",");
            lineData->paramB = strtok(NULL, ",");
            /* Divide by spaces */
            token = strtok(lineData->command, " ");
            lineData->paramA = strtok(NULL, " ");
        }
        /* Remove white characters */
        removeWhiteSpace(lineData->lable);
        removeWhiteSpace(lineData->command);
        removeWhiteSpace(lineData->paramA);
        removeWhiteSpace(lineData->paramB);
    }
    return lineData;
}
/** Check the number of operands a command requires.
 *
 * @param param - The command to be checked.
 * @return The number of operands required by the command.
 */
int check_operands(char *param) {
    char twoOperands[][4] = {"mov", "cmp", "add", "lea", "sub" };
    char oneOperands[][4] = {"not", "clr", "inc", "dec", "jmp", "bne", "red", "prn", "jsr" };
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
/** Check if a string contains a substring.
 *
 * @param str - The main string to be checked.
 * @param substr - The substring to search for.
 * @return 1 if the substring is found, 0 otherwise.
 */
int contains(const char* str, const char* substr) {
    size_t str_len = strlen(str);
    size_t substr_len = strlen(substr);
    size_t i ;
    if (str == NULL || substr == NULL) {
        /* Handle NULL inputs (optional, depending on your requirements) */
        return 0;
    }

    if (str_len < substr_len) {
        /*The substring cannot exist in a string that is shorter than the substring*/
        return 0;
    }

    for (i = 0; i <= str_len - substr_len; i++) {
        if (strncmp(str + i, substr, substr_len) == 0) {
            return 1; /*Substring found at position i*/
        }
    }

    return 0; /*Substring not found*/
}
/** Determine the data type of a parameter (number, register, or label).
 *
 * @param param - The parameter to be checked.
 * @return 1 if number, 3 if label, 5 if register, 0 otherwise.
 */
int dataType(char* param) {
    /*if register*/
    char* p = &param[2];
    if (contains(param, "@r") == 1) {
        if (atoi(p) >= 0 && atoi(p) <= 7)
            return 5;
    }
    /*if number*/
    else if (atoi(param) != 0)
        return 1;
    else /*lable*/
        return 3;
return 0;
}
