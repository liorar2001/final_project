#include "general_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/** The main function of the program.
 *
 * @param argc - The number of command-line arguments.
 * @param argv - An array of command-line argument strings.
 * @return 0 indicating successful execution.
 */
int main(int argc, char* argv[]){
    int count=2;
    struct LineData* am_file;
    struct LineData* temp;
    struct lists* orderlist=NULL;
    int error_flag = 0;
    line_count = 1;
	/*Iterate through command - line arguments*/
    while(count<=argc){
        char* name = argv[count-1];
       am_file=am_logic(argc,argv,count-1); /*build am file*/
       temp = am_file;
       while (temp!=NULL)
       {
           error_flag += search_errors(temp,name);
           line_count++;
          temp= temp->next;
       }
       /*if I don't have errors*/
       if (error_flag == 0) {
           /* If AM file is successfully built*/
           if (am_file != 0)
               orderlist = searchEntryAndExtern(am_file, argv, count - 1); /*build ent,ext files*/

            /* If orderlist is successfully built*/
           if (orderlist != NULL && am_file != 0)
               makeObjFile(orderlist, argv, count - 1);  /*build obj file*/
      }
	  /*next file*/
	   IC=0,DC=0;
       line_count = 0, line_count_am = 0,error_flag=0;
        count++;
    }
    return 0;
}
