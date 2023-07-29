/*This is header file for pre assembly level*/
struct list
{
 	 char *value;
    struct list *next;
    int decimal;
    char *lines;
};

void removeWhiteSpace(char *str);
struct list *append(struct list *head, char *label);
void printList(struct list *head) ;
void freeList(struct list *head);
char *strdup(const char *s);
