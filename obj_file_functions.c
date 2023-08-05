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
        //check if searchoperand returns lable if yes check in exter or entry list, else 00
        // use strcat to merge the struct in source and dest take last 3 by array
        // send strcat to base64 convert next row will be just param A in base64 and then param B
      
        instruct->source = decimalToBinary(SearchOperand(lineData->paramA,opcode));
        instruct->dest= decimalToBinary(SearchOperand(lineData->paramB,opcode));
        instruct->ARE =ARE(lineData->command, SearchOperand(lineData->command,opcode), orderlist->entry, orderlist->external);
        instruct->source = &instruct->source[1];
        instruct->dest =   &instruct->dest[1];
        strcat(instruct->source, instruct->opcode);
        strcat(instruct->dest, instruct->ARE);
        strcat(instruct->source, instruct->dest);
         printf("base64 - %s\n",binaryToBase64(instruct->source));

        lineData = lineData->next;
    }
}

char* decimalToBinary(int num) {
    char* binaryString = (char*)malloc(5); // 4 bits + null-terminator

    if (binaryString == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    int i = 3;
    for (; i >= 0; i--) {
        binaryString[i] = (num % 2) + '0';
        num = num / 2;
    }
    binaryString[4] = '\0'; // Null-terminate the binary string

    return binaryString;
}
char* binaryToBase64(const char* binaryString) 
{
    size_t binarySize = strlen(binaryString);
    size_t base64Size = 4 * ((binarySize + 2) / 3) + 1;

    char* base64String = (char*)malloc(base64Size);

    if (base64String == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    int i = 0, j = 0;
    int bits = 0;
    int value = 0;

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

    // Process remaining bits (if any)
    if (bits > 0)
    {
        value = value << (6 - bits);
        base64String[j++] = base64_chars[value];
    }

    base64String[j] = '\0'; // Null-terminate the Base64 string

    return base64String;
}
int SearchOperand(char* param,char opcode[][5]) {
    int i;
    if (param != NULL) {
         for (i = 0; i <= 15; i++)
        {
             char* p = &opcode[i];
             if (strcmp(p, param)==0)
                 return 0;
        }
        //register=5 , number=1,lable=3
        if (contains(param, "@") == 1)
            return 5;
        else if (param[0] >= '0' && param[0] <= '9')
            return 1;
        else if ((param[0] >= 'a' && param[0] <= 'z') ||
            (param[0] >= 'A' && param[0] <= 'Z'))
            return 3;
    }
    else
        return 0;
}
char* ARE(char* param,int operand,struct entext_list* entry, struct entext_list* external){
    if (operand == 3) //lable
    {
        while (entry->value != NULL)
        {
            for (int i = 0; i <= sizeof(entry); i++)
                if (strcmp(entry->value, param) == 0)
                    return "10";
            entry->value = entry->next;
        }
        while (external->value != NULL)
        {
            for (int i = 0; i <= sizeof(external); i++)
                if (strcmp(external->value, param) == 0)
                    return "01";
            external->value = external->next;
        }
    }
    else    
         return "00";
}