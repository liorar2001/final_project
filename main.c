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
    struct lists* orderlist=NULL;
	
	/*Iterate through command - line arguments*/
    while(count<=argc){
       am_file=am_logic(argc,argv,count-1); /*build am file*/
	 
	 /* If AM file is successfully built*/
       if(am_file!=0)
        orderlist=searchEntryAndExtern(am_file,argv,count-1); /*build ent,ext files*/
     
	 /* If orderlist is successfully built*/
	  if(orderlist!=NULL && am_file!=0)
       makeObjFile(orderlist, argv, count - 1);  /*build obj file*/
      
	  /*next file*/
	   IC=0,DC=0;
        count++;
    }
    return 0;
}
