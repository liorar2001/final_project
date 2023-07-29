#include "am_file_functions.h"
#include "am_file_logic.h"
#include "general_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 81

int am_logic(int argc, char* argv[],int count) {
    int i;
    struct list *head_lable=NULL;
    char line[MAX_SIZE], *lable, *command, *paramB, *paramA, *name;
   FILE *fp,*fpw;
    char *token;
   struct list *head_mcro=NULL;
struct list *p=NULL; 
struct list *temp = head_mcro;
struct LineData* lineData;
struct FileData fileData;
   fp=fopen(argv[count],"r");
    
    
	if(fp!=NULL){
		printf("opening %s...\n",argv[count]);
		name=argv[count];
		 strcat(name, ".am");
		 fpw=fopen(name,"w");
START:
    while (fgets(line, sizeof(line), fp)) {
        // char* lineCopy = strdup(line);
        // lineData = divide_line(lineCopy);
  printf("Processing line: %s", line);

    if (strncmp(line, ";", 1) != 0) {
        /* Divide by semicolon */
        token = strtok(line, ";");
        if (strchr(line, ':') != NULL) {
            /* Divide by colons */
            lable = strtok(token, ":");
            token = strtok(NULL, ":");
            head_lable = append(head_lable, lable);
        } else {
            lable = NULL;
        }
        /* Divide by comma */
        command = strtok(token, ",");
        paramB = strtok(NULL, ",");
        /* Divide by spaces */
        token = strtok(command, " ");
        paramA = strtok(NULL, " ");
        /* Remove white characters */
        removeWhiteSpace(lable);
        removeWhiteSpace(command);
        removeWhiteSpace(paramA);
        removeWhiteSpace(paramB);
        if (strcmp(command, "mcro") == 0) {
            if (check_operands(paramA) == -1) {
                printf("Error, mcro name invalid");
                remove(name);
                fclose(fp);
                fclose(fpw);
                return -1;
            }
            head_mcro = append(head_mcro, paramA);
            p = head_mcro;
            temp = p;
            while (strcmp(temp->value, paramA) != 0 && temp != NULL)
                temp = temp->next;
            while (strcmp(line, "endmcro\n") != 0) {
                if (strcmp(command, "mcro") == 0)
                    fgets(line, sizeof(line), fp);
                else {
                    strcat(temp->lines, line);
                    fgets(line, sizeof(line), fp);
                }
            }
            p = temp;
            goto START;
        }

        if (lable != NULL && command != NULL && paramA != NULL && paramB != NULL)
            fprintf(fpw, "%s: %s %s,%s\n", lable, command, paramA, paramB);
        else if (command != NULL && paramA != NULL && paramB != NULL)
            fprintf(fpw, "%s %s,%s\n", command, paramA, paramB);
        else if (command != NULL) {
            while (p != NULL) {
                if (strcmp(p->value, command) == 0) {
                    fprintf(fpw, "%s", p->lines);
                    break;
                } else
                    p = p->next;
            }
        }
    }

    

    fclose(fp);
    fclose(fpw);
    }
}
else
	printf("file %s does not exist\n",argv[count]);
	
    printf("Printing the labels:\n");
    printList(head_lable);
    freeList(head_lable);
    printf("Printing the macros:\n");
    printList(head_mcro);
    freeList(head_mcro);
return 0;
}
