#include "entry_file_functions.h"
#include "am_file_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 81
void searchEntry(struct LineData* LineDataHead,char *argv[],int count)
{
	
	/*char* line[MAX_SIZE]; */
	/*int lineNum = 100;*/ 
	
	int IC = 0, DC = 0;
	struct LineData* lineData=NULL;
	struct entext_list *entList=NULL;
	struct entext_list *extList=NULL;
	struct LineData* orderList=NULL;
	struct entext_list* ent_head=NULL;
	struct entext_list* ext_head=NULL;

	/*struct entext_list* orders_head = NULL;*/
	
	printf("#### search entry ###\n");
	lineData = LineDataHead;
		while (lineData)
		{			
			if (strcmp(lineData->command, ".entry") == 0) {
			  
			ent_head=append_entext(entList, lineData->paramA);
	
				DC++;
			}
			else if (strcmp(lineData->command, ".extern") == 0) {
			  
				ext_head=append_entext(extList, lineData->paramA);
				
				DC++;
			}
			else
			{
				IC = IC + check_operands(lineData->command);
				if (!orderList)
					orderList = lineData;
			
					
			}
			lineData = lineData->next;
		}
	
		
	}
  
