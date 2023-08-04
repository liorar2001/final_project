#include "general_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
void searchEntry(struct LineData* LineDataHead,char *argv[],int count);
struct entext_list {
    int lineNumber;
    char* value;
    struct entext_list* next;
};
void append_entext(struct entext_list* head, char* node,int address) 
{
    struct entext_list* temp = head;
    while (temp->next!=NULL) 
    {
        temp = temp->next;
    }
    temp->next = malloc(sizeof(struct entext_list));
    temp->next->value = node;
    temp->next->next = NULL;
    temp->next->lineNumber = address;
}

void printList_entext(struct entext_list* head,FILE *fp) {
    struct entext_list* temp = head;
    while (temp != NULL) {
        printf("%s: %d\n", temp->value, temp->lineNumber);
        fprintf(fp,"%s: %d\n", temp->value, temp->lineNumber);
        temp = temp->next;
    }
}
void freeList_entext(struct entext_list* head) {
    struct entext_list* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->value);
        free(temp);
    }
}
//void check_argument()
