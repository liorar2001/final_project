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
struct FileData {
    FILE* fpw;
    char* name;
};
struct entext_list {
    int lineNumber;
    char* value;
    struct entext_list* next;
};
struct lists {
    struct entext_list* entry;
    struct entext_list* external;
    struct LineData* orders;
};
struct macro
{
    char* name;
    struct LineData* content;
};
struct binaryInstruct {
    char* ARE;
    char* dest;
    char* opcode;
    char* source;
    char* binNum;
};
//obj file
void makeObjFile(struct LineData* orderlist);
char* decimalToBinary(int num);
char* binaryToBase64(const unsigned char* binaryData);
char* ARE(char* param, int operand, struct entext_list* entry, struct entext_list* external);
int SearchOperand(char* param, char* opcode);

void removeWhiteSpace(char* str);
void append(struct  LineData* head, struct  LineData* label);
void printList(struct LineData* head);
void printListM(struct macro* head);
void freeList(struct LineData* head);
struct LineData* am_logic(int argc, char* argv[], int count);
struct lists* searchEntryAndExtern(struct LineData* LineDataHead, char* argv[], int count);
void append_entext(struct entext_list* head, char* node, int address);
void printList_entext(struct entext_list* head, FILE* fp);
void freeList_entext(struct entext_list* head);
int contains(const char* str, const char* substr);
struct FileData* open_file(char *extention,char*name);
struct LineData* divide_line(char* line);
int check_operands(char *param);

