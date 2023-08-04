#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
struct LineData {
    char *lable;
    char *command;
    char *paramA;
    char *paramB;
    struct LineData* next;
};
struct FileData* open_file(char *extention,char*name);
struct LineData* divide_line(char* line);
int check_operands(char *param);


struct FileData {
    FILE *fpw;
    char *name;
};
