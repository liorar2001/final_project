#include "am_file_functions.h"
#include "am_file_logic.h"
#include "general_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 81
char* am_logic(int argc, char* argv[], int count) {
    /* declearations */
    int i;
    struct list *head_lable = NULL;
    char line[MAX_SIZE], *lable, *command, *paramB, *paramA, *name,*token;
    FILE *fp, *fpw=NULL;
    struct list *head_mcro = NULL;
    struct list *p = NULL;
    struct list* temp = (struct list*)malloc(sizeof(struct list));
    struct LineData *lineData;
    struct FileData fileData;
    
    /*open input file */
    fp = fopen(argv[count], "r");
    if (fp != NULL) {
        fileData = open_file(".am", fpw, argv, count); /*open am file */
    START:
        while (fgets(line, sizeof(line), fp)) {
            /*divide into parts*/
            lineData = divide_line(line);
            /*mcro stuff */
            if (lineData->command != NULL) {
                if (strcmp(lineData->command, "mcro") == 0) {
                    if (check_operands(lineData->paramA) == -1) {
                        printf("Error, mcro name invalid");
                        remove(fileData.name);
                        fclose(fp);
                        fclose(fileData.fpw);
                        return -1;
                    }
                    head_mcro = append(head_mcro, lineData->paramA);
                    p = head_mcro;
                    temp = p;
                   // temp->lines = (struct list*)malloc(sizeof(struct list));
                    while (strcmp(temp->value, lineData->paramA) != 0 && temp->next!= NULL)
                        temp = temp->next;
                    while (strcmp(line, "endmcro\n") != 0) {
                        if (strcmp(lineData->command, "mcro") == 0) {
                            temp->lines = (struct list*)malloc(sizeof(struct list));
                            fgets(line, sizeof(line), fp);
                        }
                        else {
                           
                            strcat(temp->lines, line);
                            fgets(line, sizeof(line), fp);
                        }
                    }
                    p = temp;
                    goto START;
                }
            }
            /*print lines*/
            if (lineData->lable != NULL && lineData->command != NULL && lineData->paramA != NULL && lineData->paramB != NULL)
                fprintf(fileData.fpw, "%s: %s %s,%s\n", lineData->lable, lineData->command, lineData->paramA, lineData->paramB);
            else if (lineData->command != NULL && lineData->paramA != NULL && lineData->paramB != NULL)
                fprintf(fileData.fpw, "%s %s,%s\n", lineData->command, lineData->paramA, lineData->paramB);
            else if (lineData->command != NULL && lineData->paramA != NULL )
                fprintf(fileData.fpw, "%s %s\n", lineData->command, lineData->paramA);
            else if (lineData->command != NULL) {
                while (p != NULL) {
                    if (strcmp(p->value, lineData->command) == 0) {
                        fprintf(fileData.fpw, "%s", p->lines);
                        break;
                    } else
                        p = p->next;
                }
            }
            printf("Printing the labels:\n");
            printList(lineData->head_lable);
            freeList(lineData->head_lable);
        }
        fclose(fp);
        fclose(fileData.fpw);
    } else {
        printf("file %s does not exist\n", argv[count]);
    }
    printf("Printing the macros:\n");
    printList(head_mcro);
    freeList(head_mcro);
    return fileData.name;
}