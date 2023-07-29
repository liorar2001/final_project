#include "entry_file_functions.h"
#include "general_functions.h"
#include "am_file_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 81
void searchEntry(char* filename)
{
	printf("#### search entry ###\n");
	char* line[MAX_SIZE];
	int lineNum = 100, IC = 0, DC = 0;
	struct LineData* lineData;
	struct entext_list entList;
	struct entext_list extList;
	FILE* fp = fopen(filename, "r");
	if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) 
		{
			
			lineData = divide_line(line);
			if (strcmp(lineData->command, ".entry") == 0) {
			   // strcat(lineData->paramA, "\n");
				entList.name = lineData->paramA;
				printf("found entry %s\n", entList.name);
				DC++;
			}
			if (strcmp(lineData->command, ".extern") == 0) {
			   // strcat(lineData->paramA, "\n");
				extList.name = lineData->paramA;
				printf("found extern %s\n", extList.name);
				DC++;
			}
			  lineNum++;
		}
	}
  
}