#include "general_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 81
/** Implementation of AM Logic for processing input assembly code.
 *
 * @param argc - The number of command-line arguments.
 * @param argv - An array of command-line argument strings.
 * @param count - The index of the current input assembly file in argv.
 * @return A linked list of LineData structures representing the assembly code.
 */
struct LineData* am_logic(int argc, char* argv[], int count) {
    /* declearations */
    int i;
    char line[MAX_SIZE];
    FILE *fp=NULL;
    struct macro* head_mcro = NULL;
    int mcroCount = 0;
    struct LineData* lineData=NULL;
    struct LineData* lineDataHead=NULL;
    struct FileData* fileData = NULL;
    struct macro* p;
     struct LineData* pr;
     struct macro* tempMcro ;
    int macroFlag = 0;
    char* name = argv[count];
    char* nameFile= (char*)malloc(MAX_SIZE);
    strcpy(nameFile,name);
    strcat(nameFile,".as");
    /*open input file */
    fp = fopen(nameFile, "r");
    if (fp != NULL)
    {
        fileData = open_file(".am",name); /*open am file */
        while (fgets(line, MAX_SIZE, fp))
        {
            /*divide into parts*/
            char* tmp=(char*)malloc(MAX_SIZE);
            if (tmp == NULL)return NULL;
            strcpy(tmp, line);
            lineData = divide_line(tmp);
            if (lineData == NULL)return NULL;
            if (lineData->command!=NULL && strlen(lineData->command)>1)
            {
                if (strcmp(lineData->command, "mcro") == 0)
                {
                    if (check_operands(lineData->paramA) == -1) {
                        printf("Error, mcro name invalid");
                        fclose(fp);
                        if(fileData->fpw!=NULL)
                        fclose(fileData->fpw);
                        if(fileData->name!=NULL)
                        remove(fileData->name);
                        return NULL;
                    }
                    mcroCount++;
                    if (!head_mcro)
                    {
                        head_mcro = (struct macro*)calloc(mcroCount, sizeof(struct macro));
                        if (head_mcro == NULL)return NULL;
                    }
                    else
                    {
                        tempMcro= (struct macro*)calloc(mcroCount, sizeof(struct macro));
                        if (!tempMcro)return NULL;
                        for (i = 0; i < mcroCount - 1; i++)
                        {
                            tempMcro[i] = head_mcro[i];
                        }
                        head_mcro = tempMcro;
                    }
                    p = &head_mcro[mcroCount - 1];
                    p->name = lineData->paramA;
                    macroFlag = 1;
                }
                if (macroFlag != 0)
                {
                    if (macroFlag == 1)
                        macroFlag = 2;
                    else
                    {
                        if (strcmp(lineData->command, "endmcro") == 0)
                            macroFlag = 0;
                        else
                        {
                             p = &head_mcro[mcroCount - 1];
                            if (p->content == NULL)
                                p->content = lineData;
                            else
                                append(p->content, lineData);
                        }
                        
                    }
                }
                else
                {   
                    for (i = 0; i < mcroCount; i++)
                    {
                       p = &head_mcro[i];
                        if (strcmp(lineData->command, p->name) == 0)
                            lineData = p->content;
                    }
                    if (lineDataHead == NULL)
                        lineDataHead = lineData;
                    else
                    {
                        append(lineDataHead, lineData);
                    }
                   pr= lineData;
                    while (pr)
                    {     /*print lines*/
                        char tmp1[MAX_SIZE];
                        strcpy(tmp1, "");
                        if (pr->lable)
                        {
                            strcat(tmp1,pr->lable);
                            strcat(tmp1, ": ");
                        }
                        if (pr->command != NULL)
                        {
                            strcat(tmp1, pr->command);
                        }
                        if (pr->paramA != NULL)
                        {
                            strcat(tmp1, " ");
                            strcat(tmp1, pr->paramA);
                        }
                        if (pr->paramB != NULL)
                        {
                            strcat(tmp1, ",");
                            strcat(tmp1, pr->paramB);
                        }
                        if(fileData->fpw!=NULL)
                        fprintf(fileData->fpw, "%s\n", tmp1);
                        pr = pr->next;
                    }

                }
            }
        }
        fclose(fp);
        if(fileData->fpw!=NULL)
        fclose(fileData->fpw);
    }
    else {
        printf("file %s.as does not exist\n", argv[count]);
        return 0;
    }
    return lineDataHead;
}
/** Remove white spaces from a string.
 *
 * @param str - The string from which white spaces will be removed.
 */
void removeWhiteSpace(char* str) {
    if (str != NULL) {
        char* src = str;
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
/** Append a LineData node to a linked list.
 *
 * @param head - The head of the linked list.
 * @param node - The LineData node to be appended.
 */
void append(struct  LineData* head, struct  LineData* node)
{
    struct LineData* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = node;
}
/** Print the linked list of LineData.
 *
 * @param head - The head of the linked list.
 */
void printList(struct LineData* head) {
    struct LineData* temp = head;
    while (temp != NULL) {
        if (temp->lable != NULL)
            printf("%s\n", temp->lable);
        temp = temp->next;
    }
}

/** Print the linked list of LineData contained in a macro.
 *
 * @param head - The head of the linked list of LineData.
 */
void printListM(struct macro* head) {
    struct LineData* temp = head->content;
    while (temp != NULL) {
        printf("%s: %s\n", temp->command, temp->paramA);
        temp = temp->next;
    }
}
/** Free the memory allocated for a linked list of LineData.
 *
 * @param head - The head of the linked list to be freed.
 */
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
/** Free the memory allocated for a linked list of LineData within a macro.
 *
 * @param head - The head of the linked list of LineData within a macro.
 */
void freeListM(struct macro* head)
{
    freeList(head->content);
}