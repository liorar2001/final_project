#include "pre_asm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 81 
int main(int argc, char* argv[]){
	/*pre_asm level*/
struct list *head_lable=NULL;
struct list *head_mcro=NULL;
struct list *p=NULL; 
struct list *temp = head_mcro;
int count=1,i;
char line[MAX_SIZE],*token,*lable,*command,*paramB,*paramA,*name;
FILE *fp,*fpw;
 char twoOperands[][4] = {"mov", "cmp", "add", "sub", "lea"};
char oneOperands[][4] = {"not", "clr", "inc", "dec", "jmp", "bne", "red", "prn", "jsr"};
char noOperands[][4] = {"rts", "stop"};

while(count<argc){
fp=fopen(argv[count],"r");

	if(fp!=NULL){
		printf("opening %s...\n",argv[count]);
		name=argv[count];
		 strcat(name, ".am");
		 fpw=fopen(name,"w");
		START:
		 while (fgets(line, sizeof(line), fp)){
		
      		  printf("Processing line: %s", line);
      		  if (strncmp(line, ";", 1) != 0) {
      		  /*devide by semicolon*/
		 token = strtok(line,";");
		 if (strchr(line, ':') != NULL) {
		 /*devide by colons*/
		lable = strtok(token,":");
		token = strtok(NULL,":");
		head_lable=append(head_lable,lable);
		}
		else
		lable=NULL;
		/*devide by comma*/
		command = strtok(token,",");
		paramB= strtok(NULL,",");
		/*devide by spaces*/
		token= strtok(command," ");
		paramA = strtok(NULL," ");
		/*remove white charachters*/
		removeWhiteSpace(lable);
		removeWhiteSpace(command);
		removeWhiteSpace(paramA);
		removeWhiteSpace(paramB);
		/*check if mcro*/
		if(strcmp(command,"mcro")==0){
                 for (i = 0; i < sizeof(twoOperands) / sizeof(twoOperands[0]); i++) {
        if (strcmp(paramA, twoOperands[i]) == 0) {
            printf("Error, mcro name invalid");
                remove(name);
            return -1;
        }
    }

    for (i = 0; i < sizeof(oneOperands) / sizeof(oneOperands[0]); i++) {
        if (strcmp(paramA, oneOperands[i]) == 0) {
            printf("Error, mcro name invalid");
                remove(name);
            return -1;
        }
    }

    for (i = 0; i < sizeof(noOperands) / sizeof(noOperands[0]); i++) {
        if (strcmp(paramA, noOperands[i]) == 0) {
            printf("Error, mcro name invalid");
                remove(name);
            return -1;
        }
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
				
      		  }
      	
			fclose(fp);
		fclose(fpw);
			}
			else
	printf("file %s does not exist\n",argv[count]);
	 count++;
		}
		printf("Printing the lables:\n");
		printList(head_lable);
		freeList(head_lable);
		printf("Printing the mcros:\n");
		printList(head_mcro);
		freeList(head_mcro);
		
return 0;
}

