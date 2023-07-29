#include "pre_asm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
void removeWhiteSpace(char *str) {
    if(str!=NULL){
    char *src = str;
    char *dst = str;

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

struct list *append(struct list *head, char *node) {
    struct list *newp = (struct list *)malloc(sizeof(struct list));
    if (newp == NULL) {
        printf("Could not find free memory for malloc\n");
    } else {
        newp->value = strdup(node);
        newp->lines = strdup("");
        newp->next = NULL;

        if (head == NULL) {
            head = newp;
        } else {
            struct list *temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newp;
        }
    }
    return head;
}

void printList(struct list *head) {
    struct list *temp = head;
    while (temp != NULL) {
        printf("%s: %s\n", temp->value,temp->lines);
        temp = temp->next;
    }
}
void freeList(struct list *head) {
    struct list *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->value);
        
        free(temp);
    }
}

