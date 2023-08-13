#include "general_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 81
/**
 * Searches for entry and extern labels in the assembly code and populates relevant lists.
 *
 * @param LineDataHead - The head of the LineData list containing assembly code.
 * @param argv - The command-line arguments.
 * @param count - The number of arguments.
 * @return A struct containing lists of entry, external, order labels, and more.
 */
struct lists* searchEntryAndExtern(struct LineData* LineDataHead, char* argv[], int count) {
    /* Initialization*/
	int flagEnt = 0, flagExt = 0;
    struct LineData* lineData = NULL;
    struct LineData* orderList = NULL;
    struct entext_list* LableList = NULL;
    struct entext_list* orderLablesList = NULL;
    struct entext_list* externP = NULL;
    struct entext_list* ent_head = NULL;
    struct entext_list* ext_head = NULL;
    struct entext_list* tempEnt = NULL;
    struct entext_list* tempExt = NULL;
    struct entext_list* tempLbl = NULL;
    struct entext_list* tempLblOrder = NULL;
    struct FileData* fileEnt = NULL;
    struct FileData* fileExt = NULL;
    struct lists* list = malloc(sizeof(struct lists));
    int lineNum = 100,step;
    char* name = argv[count];
    char*token;
    char *param;
    fileEnt = open_file(".ent", name); /*open ent file*/
    fileExt = open_file(".ext", name); /*open ext file*/
    lineData = LineDataHead;
    while (lineData) {
		/*Check if it's an entry directive*/
        if (strcmp(lineData->command, ".entry") == 0) {
            if (ent_head != NULL)
                append_entext(ent_head, lineData->paramA, 0);
            else {
                ent_head = malloc(sizeof(struct entext_list));
                if (ent_head!=NULL) {
                    ent_head->value = lineData->paramA;
                    ent_head->next = NULL;
                    ent_head->lineNumber = 0;
                }
            }
            flagEnt = 1;
        }
		/* Check if it's an extern directive*/
        else if (strcmp(lineData->command, ".extern") == 0) {
            if (ext_head != NULL)
                append_entext(ext_head, lineData->paramA, 0);
            else {
                ext_head = malloc(sizeof(struct entext_list));
                if (ext_head!=NULL) {
                    ext_head->value = lineData->paramA;
                    ext_head->next = NULL;
                    ext_head->lineNumber = 0;
                }
            }
            flagExt = 1;
        }
        else { /*it's an order*/
            if (!orderList)
                orderList = lineData;

            /* Make a list of labels in orders*/
            /* Check param A if letter*/
            if (lineData->paramA != NULL &&
                ((lineData->paramA[0] >= 'a' && lineData->paramA[0] <= 'z') ||
                    (lineData->paramA[0] >= 'A' && lineData->paramA[0] <= 'Z'))) {
                if (orderLablesList != NULL)
                    append_entext(orderLablesList, lineData->paramA, lineNum + IC);
                else {
                    orderLablesList = malloc(sizeof(struct entext_list));
                    if (orderLablesList!=NULL) {
                        orderLablesList->value = lineData->paramA;
                        orderLablesList->next = NULL;
                        orderLablesList->lineNumber = lineNum + IC;
                    }
                }
            }
            /* Check param B*/
            else if (lineData->paramB != NULL &&
                ((lineData->paramB[0] >= 'a' && lineData->paramB[0] <= 'z') ||
                    (lineData->paramB[0] >= 'A' && lineData->paramB[0] <= 'Z'))) {
                if (orderLablesList != NULL)
                    append_entext(orderLablesList, lineData->paramB, lineNum + IC);
                else {
                    orderLablesList = malloc(sizeof(struct entext_list));
                    if (orderLablesList!=NULL) {
                        orderLablesList->value = lineData->paramB;
                        orderLablesList->next = NULL;
                        orderLablesList->lineNumber = lineNum + IC;
                    }
                }
            }
            /* Make label list*/
            if (LableList != NULL && lineData->lable != NULL)
                append_entext(LableList, lineData->lable, lineNum + IC);
            else if (LableList == NULL) {
                LableList = malloc(sizeof(struct entext_list));
                if (LableList!=NULL) {
                    LableList->value = lineData->lable;
                    LableList->next = NULL;
                    LableList->lineNumber = lineNum + IC;
                }
            }
            /* Next instruction */
            step = check_operands(lineData->command);
            param= lineData->paramA;
            if (lineData->paramA) {
                param = malloc(sizeof(char) * strlen(lineData->paramA));
                strcpy(param, lineData->paramA);
            }
            if(step==3)
            if (dataType(param) == 5 && dataType(lineData->paramB) == 5)step = 2;          
            if (strcmp(lineData->command, ".string") == 0) {
                step = strlen(param) - 1;
                DC += step;
            }
            if (strcmp(lineData->command,".data") == 0)
            {
                strcpy(param, lineData->paramA);
               step = 0;
                token = strtok(param, ",");
                while (token != NULL)
                {
                    /*Get next token:*/
                    token = strtok(NULL, ",");
                    step++;
                    
                }
                DC += step;
            }
            IC = IC + step;
        }

        /* Next line*/
        lineData = lineData->next;
    }

    /* Return to default positions*/
    tempEnt = ent_head;
    tempLbl = LableList;

    /* Check entry labels*/
    while (ent_head != NULL && LableList != NULL) {
        if (strcmp(ent_head->value, LableList->value) == 0) {
            ent_head->lineNumber = LableList->lineNumber;
            ent_head = ent_head->next;
            LableList = tempLbl;
        }
        else
            LableList = LableList->next;
    }
    ent_head = tempEnt;
    LableList = tempLbl;

    /* Check external labels*/
    /* Return to default positions*/
    tempExt = ext_head;
    tempLblOrder = orderLablesList;

    while (ext_head != NULL) {
        while (orderLablesList != NULL) {
            if (strcmp(ext_head->value, orderLablesList->value) == 0) {
                if (externP != NULL)
                    append_entext(externP, orderLablesList->value, orderLablesList->lineNumber);
                else {
                    externP = malloc(sizeof(struct entext_list));
                    if (externP!=NULL) {
                        externP->value = orderLablesList->value;
                        externP->next = NULL;
                        externP->lineNumber = orderLablesList->lineNumber;
                    }
                }
                orderLablesList = orderLablesList->next;
            }
            else
                orderLablesList = orderLablesList->next;
        }
        ext_head = ext_head->next;
        orderLablesList = tempLblOrder;
    }
    ext_head = tempExt;
    orderLablesList = tempLblOrder;

    /* Cleanup and finalize the files*/
    if (flagEnt == 0 && fileEnt->name != NULL) {
        fclose(fileEnt->fpw);
        remove(fileEnt->name);
    }
    if (flagExt == 0 && fileExt->name != NULL) {
        fclose(fileExt->fpw);
        remove(fileExt->name);
    }
    list->entry = ent_head;
    list->external = externP;
    list->orders = orderList;
    list->Lables = LableList;
    /* Print results to files*/
    printList_entext(ent_head, fileEnt->fpw);
    printList_entext(externP, fileExt->fpw);
    IC-=DC;
    return list;
}
/** Appends a node with a value and an address to the end of an entext_list.
 *
 * @param head - The head of the entext_list.
 * @param node - The value to append.
 * @param address - The address associated with the value.
 */
void append_entext(struct entext_list* head, char* node, int address)
{
    struct entext_list* temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = malloc(sizeof(struct entext_list));
    if (temp->next != NULL) {
        temp->next->value = node;
        temp->next->next = NULL;
        temp->next->lineNumber = address;
    }
}
/** Prints the values and addresses of an entext_list to a file.
 *
 * @param head - The head of the entext_list.
 * @param fp - The file pointer to write to.
 */
void printList_entext(struct entext_list* head, FILE* fp) {
    struct entext_list* temp = head;
    while (temp != NULL) {
        fprintf(fp, "%s: %d\n", temp->value, temp->lineNumber);
        temp = temp->next;
    }
}
/** Frees the memory occupied by an entext_list.
 *
 * @param head - The head of the entext_list.
 */
void freeList_entext(struct entext_list* head) {
    struct entext_list* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->value);
        free(temp);
    }
}
