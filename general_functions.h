#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*structs*/
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
    struct entext_list* Lables;
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

/*obj file */
void makeObjFile(struct lists* orderlist);
char* decimalToBinary(int num, int digits);
char* binaryToBase64(const char* binaryString);
char* ARE(char* param, struct lists* list);
int SearchOperand(char* param);
char* general_code(struct LineData* lineData);

/*entry_file_functions*/
struct lists* searchEntryAndExtern(struct LineData* LineDataHead, char* argv[], int count);
void append_entext(struct entext_list* head, char* node, int address);
void printList_entext(struct entext_list* head, FILE* fp);
void freeList_entext(struct entext_list* head);

/*general_dunctions*/
struct FileData* open_file(char* extention, char* name);
struct LineData* divide_line(char* line);
int check_operands(char* param);
int contains(const char* str, const char* substr);
int dataType(char* param);

/*am_file_logic*/
void removeWhiteSpace(char* str);
void append(struct  LineData* head, struct  LineData* label);
void printList(struct LineData* head);
void printListM(struct macro* head);
void freeList(struct LineData* head);
struct LineData* am_logic(int argc, char* argv[], int count);