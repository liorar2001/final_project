#include "entry_file_functions.h"
#include "am_file_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 81
void searchEntry(struct LineData* LineDataHead, char* argv[], int count)
{

	/*char* line[MAX_SIZE]; */
	/*int lineNum = 100;*/

	int IC = 0, DC = 0, flagEnt = 0, flagExt = 0;
	struct LineData* lineData = NULL;
	struct entext_list* entList = NULL;
	struct entext_list* extList = NULL;
	struct LineData* orderList = NULL;
	struct entext_list* LableList = NULL;
	struct entext_list* ent_head = NULL;
	struct entext_list* ext_head = NULL;
	struct entext_list* tempEnt = NULL;
	struct entext_list* tempLbl = NULL;
	struct FileData* fileEnt =NULL;
	struct FileData* fileExt = NULL;
	int lineNum = 100;
	char* name = argv[count];
	printf("#### search entry ###\n");

	fileEnt = open_file(".ent",name); /*open ent file */
	fileExt = open_file(".ext",name); /*open ext file */
	lineData = LineDataHead;
	while (lineData)
	{
		if (strcmp(lineData->command, ".entry") == 0)
		{
			if (ent_head != NULL)
			append_entext(ent_head, lineData->paramA,0);
			else {
				ent_head = malloc(sizeof(struct entext_list));
				if (ent_head) {
					ent_head->value = lineData->paramA;
					ent_head->next = NULL;
					ent_head->lineNumber=0;
				}
			}
			//fprintf(fileEnt->fpw, "%s	%d\n", ent_head->value,lineNum);
			flagEnt = 1;
			DC++;
		}
		else if (strcmp(lineData->command, ".extern") == 0) 
		{
			if (ext_head != NULL)
				append_entext(ext_head, lineData->paramA,0);
			else {
				ext_head = malloc(sizeof(struct entext_list));
				ext_head->value = lineData->paramA;
				ext_head->next = NULL;
				ext_head->lineNumber = 0;
			}
			//fprintf(fileExt->fpw, "%s	%d\n", ext_head->value, lineNum);
			flagExt = 1;
			DC++;
		}
		else
		{
			
			if (!orderList)
				orderList = lineData;
			if (LableList!=NULL && lineData->lable!=NULL)
				append_entext(LableList, lineData->lable,lineNum+IC);
			else if(LableList==NULL){
				LableList = malloc(sizeof(struct entext_list));
				LableList->value = lineData->lable;
				LableList->next = NULL;
				LableList->lineNumber=lineNum+IC;
			}
			IC = IC + check_operands(lineData->command);
		}
		lineData = lineData->next;
	}
	tempEnt = ent_head;
	tempLbl = LableList;
	while (ent_head!=NULL && LableList!=NULL)
	{
		if (strcmp(ent_head->value,LableList->value)==0)
		{
			ent_head->lineNumber = LableList->lineNumber;
			ent_head = ent_head->next;
			LableList = tempLbl;
		}
		else
		LableList = LableList->next;
	}
	ent_head = tempEnt;
	LableList= tempLbl;
	if (flagEnt == 0 && fileEnt->name != NULL) 
	{
		fclose(fileEnt->fpw);
		remove(fileEnt->name);
	}
	if (flagExt == 0 && fileExt->name != NULL)
	{
		fclose(fileExt->fpw);
		remove(fileExt->name);
	}
	//printList_entext(LableList);
	
	printf("--------------------------\n");
	printList_entext(ent_head,fileEnt->fpw);
	printf("--------------------------\n");
	//printList_entext(ext_head);
}
  
