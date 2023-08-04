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
struct entext_list* append_entext(struct entext_list* head, char* node) {
    struct entext_list* newp = (struct entext_list*)malloc(sizeof(struct entext_list));
    if (newp == NULL) {
        printf("Could not find free memory for malloc\n");
        return head; /* Return the original list if memory allocation fails */
    } 
    newp->lineNumber = 0;
    newp->value = node;

    newp->next = NULL;
    if (head == NULL) {
        head = newp;
    }
    else {
        struct entext_list* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newp;
    }
    return head;
}

void printList_entext(struct entext_list* head) {
    struct entext_list* temp = head;
    while (temp != NULL) {
        printf("%s: %d\n", temp->value, temp->lineNumber);
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
