#include "am_file_functions.h"
#include "am_file_logic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, char* argv[]){
    int count=2;
    struct LineData* am_file;
    while(count<=argc){
        am_file=am_logic(argc,argv,count-1); /*build am file*/
        if(am_file!=0)
        searchEntry(am_file,argv,count-1);

        count++;
    }
    return 0;
}
