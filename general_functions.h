#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct FileData open_file(char *extention,FILE *fpw,char* argv[],int count);
struct LineData* divide_line(char *line);
int check_operands(char *paramA);

struct LineData {
    char *lable;
    char *command;
    char *paramA;
    char *paramB;
    struct list *head_lable;
};
struct FileData {
    FILE *fpw;
    char *name;
};