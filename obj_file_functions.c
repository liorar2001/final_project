#include "general_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
void makeObjFile(struct lists* orderlist)
{
    int i = 0;
    struct LineData* lineData = NULL;
    struct  binaryInstruct* instruct=NULL;
    lineData = orderlist->orders;
    while (lineData)
    {
        char opcode[][5] = { "mov","cmp","add","sub","not","clr","lea",
                            "inc","dec","jmp","bne","red","prn","jsr","rts","stop" };
        for (i = 0; i <=15; i++) 
        {
            if (strcmp(lineData->command, opcode[i]) == 0)
            {
                instruct = malloc(sizeof(struct binaryInstruct));
                 instruct->opcode = decimalToBinary(i);
            }
        }
        /*check if searchoperand returns lable if yes check in exter or entry list, else 00
        // use strcat to merge the struct in source and dest take last 3 by array
        // send strcat to base64 convert next row will be just param A in base64 and then param B */
      
        instruct->source = decimalToBinary(SearchOperand(lineData->paramA,opcode));
        instruct->dest= decimalToBinary(SearchOperand(lineData->paramB,opcode));
        instruct->ARE =ARE(lineData->command, SearchOperand(lineData->command,opcode), orderlist->entry, orderlist->external);
        instruct->source = &instruct->source[9];
        instruct->dest =   &instruct->dest[9];
        instruct->opcode = &instruct->opcode[8];
        strcat(instruct->source, instruct->opcode);
        strcat(instruct->dest, instruct->ARE);
        strcat(instruct->source, instruct->dest);
         printf("base64 - %s\n",binaryToBase64(instruct->source));
         if (lineData->paramA != NULL) {
             instruct->source = decimalToBinary(atoi(&lineData->paramA[2]));
             instruct->source = &instruct->source[7];

             if (lineData->paramB != NULL)
             {
                 if (dataType(lineData->paramB) == 1)
                 {
                     instruct->dest = decimalToBinary(atoi(&lineData->paramA[2]));
                     instruct->dest = &instruct->dest[7];
                     strcat(instruct->source, instruct->dest);
                 }
                 else
                 {
                     strcat(instruct->source, "00000");
                 }
                 strcat(instruct->source, ARE(lineData->paramA, SearchOperand(lineData->paramA, opcode), orderlist->entry, orderlist->external));
             }
                 printf("base64 - %s\n", binaryToBase64(instruct->source));
         }
        lineData = lineData->next;
    }
}

char* decimalToBinary(int num) {
int i;
    char* binaryString = (char*)malloc(13); /* 12 bits + null-terminator*/

    if (binaryString == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    /*Fill the binary string with leading zeros*/
    for (i = 0; i < 12; i++) {
        binaryString[i] = '0';
    }
    binaryString[12] = '\0'; /* Null-terminate the binary string*/

     i = 11;
    while (num > 0 && i >= 0) {
        binaryString[i--] = (num % 2) + '0';
        num = num / 2;
    }

    return binaryString;
}

char* binaryToBase64(const char* binaryString) 
{
 int i = 0, j = 0;
    int bits = 0;
    int value = 0;
    size_t binarySize = strlen(binaryString);
    size_t base64Size = 4 * ((binarySize + 2) / 3) + 1;

    char* base64String = (char*)malloc(base64Size);

    if (base64String == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    while (i < binarySize) 
    {
        value = (value << 1) | (binaryString[i++] - '0');
        bits++;

        if (bits == 6) 
        
        {
            base64String[j++] = base64_chars[value];
            bits = 0;
            value = 0;
        }
    }

    /*Process remaining bits (if any)*/
    if (bits > 0)
    {
        value = value << (6 - bits);
        base64String[j++] = base64_chars[value];
    }

    base64String[j] = '\0'; /* Null-terminate the Base64 string*/

    return base64String;
}
int SearchOperand(char* param,char opcode[][5]) {
    int i;
    if (param != NULL) {
         for (i = 0; i <= 15; i++)
        {
             char(*p)[5] = &opcode[i];
             if (strcmp(*p, param)==0)
                 return 0;
        }
        /*register=5 , number=1,lable=3*/
        if (dataType(param)== 1)
            return 5;
        else if (dataType(param) == 2)
            return 1;
        else 
            return 3;
    }
    else
        return 0;
}
char* ARE(char* param,int operand,struct entext_list* entry, struct entext_list* external){
   int i;
    if (operand == 3) /*lable*/
    {
        while (entry->value != NULL)
        {
            for (i = 0; i <= sizeof(entry); i++)
                if (strcmp(entry->value, param) == 0)
                    return "10";
            entry->value = entry->next->value;
        }
        while (external->value != NULL)
        {
            for (i = 0; i <= sizeof(external); i++)
                if (strcmp(external->value, param) == 0)
                    return "01";
            external->value = external->next->value;
        }
    }
    else    
         return "00";
return "0";
}
int dataType(char* param) {
    /*if register*/
    char* p = &param[2];
    if (contains(param, "@r")== 1){
        if(atoi(p)>=0 && atoi(p)<=7)
             return 1;
             }
    /*if number*/
    else if (atoi(param)!=0)
             return 2;
    else /*lable*/
                return 3;
return 0;
}
