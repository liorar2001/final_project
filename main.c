#include "am_file_functions.h"
#include "am_file_logic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[]){
int count=0;
    while(count<argc){
    am_logic(argc,argv,count); /*build am file*/
    count++;
    }
return 0;
}
