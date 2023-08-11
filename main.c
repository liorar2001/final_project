#include "general_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, char* argv[]){
    int count=2;
    struct LineData* am_file;
    struct lists* orderlist=NULL;
    while(count<=argc){
       am_file=am_logic(argc,argv,count-1); /*build am file*/
       if(am_file!=0)
        orderlist=searchEntryAndExtern(am_file,argv,count-1); /*build ent,ext files*/
      if(orderlist!=NULL)
       makeObjFile(orderlist, argv, count - 1);
        count++;
    }
    return 0;
}
