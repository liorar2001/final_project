
/*This is header file for pre assembly level*/
struct macro
{
 	 char *name;
    struct LineData* content;
};
void removeWhiteSpace(char *str);
void append(struct  LineData*head, struct  LineData*label);
void printList(struct LineData*head) ;
void printListM(struct macro* head);
void freeList(struct LineData*head);
