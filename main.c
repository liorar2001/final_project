#include "am_file_functions.h"
#include "am_file_logic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, char* argv[]){
    int count=1;
    char*am_file;
    while(count<argc){
        am_file=am_logic(argc,argv,count); /*build am file*/
        searchEntry(am_file);
        count++;
    }
    return 0;
}
