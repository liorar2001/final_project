#include "am_file_functions.h"
#include "general_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdlib.h>
void removeWhiteSpace(char *str) {
    if(str!=NULL){
    char *src = str;
    char* dst = str;
    /* Copy characters except whitespace*/
    while (*src != '\0') {
        if (!isspace((unsigned char)*src)) {
            *dst = *src;
            dst++;
        }
        src++;
    }
    /* Terminate the string*/
    *dst = '\0';
    }
}
void append(struct  LineData* head, struct  LineData* node)
{
        struct LineData* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = node;
}
void printList(struct LineData*head) {
    struct LineData*temp = head;
    while (temp != NULL) {
        printf("%s: %s\n", temp->command,temp->paramA);
        temp = temp->next;
    }
}
void printListM(struct macro* head) {
    struct LineData* temp = head->content;
    while (temp != NULL) {
        printf("%s: %s\n", temp->command, temp->paramA);
        temp = temp->next;
    }
}
void freeList(struct LineData* head) 
{
    if (head)
    {
        struct LineData* temp = head->next;
        while (temp != NULL)
        {
            free(head);
            head = temp;
            temp = head->next;
        }
    }
}
void freeListM(struct macro* head) 
{
        freeList(head->content);
 }