#include "general_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char opcode[][5] = { "mov","cmp","add","sub","not","clr","lea",
                            "inc","dec","jmp","bne","red","prn","jsr","rts","stop" };
void makeObjFile(struct lists* orderlist)
{
    struct LineData* lineData = NULL;
    struct entext_list* lablep = NULL;
    char* param1=NULL;
    char* param2;
    char* Bin1;
    char* p;
    lineData = orderlist->orders;
    while (lineData)
    {       
        if(lineData->command[0]!='.')
        {
            if (lineData->paramA != NULL && lineData->paramB == NULL)
            {
                lineData->paramB = lineData->paramA;
                lineData->paramA = NULL;
            }
            Bin1 = general_code(lineData);
            printf("%s\n", binaryToBase64(Bin1));
            if (lineData->paramA != NULL)
            {
                p = &lineData->paramA[2];
                switch (dataType(lineData->paramA))
                {
                   
                case 5: /*register*/
                   
                    param1 = decimalToBinary(atoi(p), 5);
                    if (dataType(lineData->paramB) != 5)
                    {
                        strcat(param1, "00000");
                        strcat(param1, "00");
                        printf("%s\n", binaryToBase64(param1));
                    }
                    break;
                case 1: /*number*/
                    param1 = decimalToBinary(atoi(lineData->paramA), 10);
                    strcat(param1, "00");
                    printf("%s\n", binaryToBase64(param1));
                    break;
                case 3: /*lable*/
                    lablep = orderlist->Lables;
                    while (lablep != NULL)
                    {
                        if (strcmp(lineData->paramB, lablep->value) == 0)
                        {
                            param1 = decimalToBinary(lablep->lineNumber, 10);
                            break;
                        }
                        lablep = lablep->next;
                    }
                    if(lablep!=NULL)
                    strcat(param1, ARE(lablep->value, orderlist));
                    printf("%s\n", binaryToBase64(param1));
                    break;
                default:
                    break;
                }
            }
            if (lineData->paramB != NULL)
            {
                char* p = &lineData->paramB[2];
                switch (dataType(lineData->paramB))
                {
                case 5: /*register*/
                    
                    param2 = decimalToBinary(atoi(p), 5);
                    if (dataType(lineData->paramA) == 5)
                    {
                        strcat(param2, "00000");
                        strcat(param2, "00");
                        printf("%s\n", binaryToBase64(param2));
                    }
                    else
                    {
                        strcat(param2, "00000");
                        strcat(param2, "00");
                        printf("%s\n", binaryToBase64(param2));
                    }
                    break;
                case 1: /*number*/
                    param2 = decimalToBinary(atoi(lineData->paramB), 10);
                    strcat(param2, "00");
                    printf("%s\n", binaryToBase64(param2));
                    break;
                case 3: /*lable*/
                    lablep = orderlist->Lables;
                    param2 = decimalToBinary(0, 10);
                    while (lablep != NULL)
                    {
                        if (strcmp(lineData->paramB, lablep->value) == 0)
                        {
                            param2 = decimalToBinary(lablep->lineNumber, 10);
                            break;
                        }
                        lablep = lablep->next;
                    }
                    strcat(param2, ARE(lineData->paramB, orderlist));
                    printf("%s\n", binaryToBase64(param2));
                    break;
                default:
                    break;
                }
            }
        }
        lineData = lineData->next;
    }
}

char* decimalToBinary(int num,int digits) {
int i;
    char* binaryString = (char*)malloc(13); /* digits bits + null-terminator*/

    if (binaryString == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    /*Fill the binary string with leading zeros*/
    for (i = 0; i < digits; i++) {
        binaryString[i] = '0';
    }
    binaryString[digits] = '\0'; /* Null-terminate the binary string*/

     i = digits-1;
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
int SearchOperand(char* param) {
    int i;
    if (param != NULL)
    {
         for (i = 0; i <= 15; i++)
        {
             char(*p)[5] = &opcode[i];
             if (strcmp(*p, param)==0)
                 return i;
        }
    }
    else
        return -1;
return 0;
}
char* ARE(char* param, struct lists* list){
   struct entext_list* p1 = list->entry;
   struct entext_list* p2 = list->external;
   struct entext_list* p3 = list->Lables;
        while (p1 != NULL)
        {
                if (strcmp(p1->value, param) == 0)
                    return "10";
            p1 = p1->next;
        }
        while (p2 != NULL)
        {
            if (strcmp(p2->value, param) == 0)
                return "01";
            p2 = p2->next;
        }
        while (p3 != NULL)
        {
            if (strcmp(p3->value, param) == 0)
                return "10";
            p3 = p3->next;
        }
return "Error:This label does not exist!!!";
}

char* general_code(struct LineData* lineData)
{
    char* source= decimalToBinary(0, 3);
    char* dest = decimalToBinary(0, 3);
    char* opcode = decimalToBinary(0, 4);
    char* ARE = "00";
    if(lineData->paramA!=NULL) source = decimalToBinary(dataType(lineData->paramA),3);
    if (lineData->paramB != NULL)dest = decimalToBinary(dataType(lineData->paramB),3);
    if (lineData->command != NULL) opcode =decimalToBinary(SearchOperand(lineData->command),4);
    if (opcode == NULL)
    	return NULL;
    
        strcat(source,opcode);
        strcat(dest, ARE);
        strncat(source,dest,5);
return source;
}

