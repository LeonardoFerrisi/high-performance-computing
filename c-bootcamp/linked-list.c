// linked-list.c
// author: John Rieffel
#include <stdio.h>
#include <stdlib.h>
// ------ a node has              \
// | ---|--->a pointer-to-node field
// ------   a data field
// | 17 | and it has the type-name: Node
//------
typedef struct node
{
    struct node *next;
    int data;
} Node;

Node *insert(int N, Node *listptr)
{
    // allocate space for new Node

    struct node *tmpptr = (struct node *)malloc(sizeof(Node));
    tmpptr->data = N;
    tmpptr->next = NULL;

    // check if the list pointer is empty or if the integer
    // is less than the current list pointers data
    if (listptr == NULL || N < listptr->data)
    {
        // The temp pointers next data (NULL) is set to the current listpointer's next
        tmpptr->next = listptr;
        listptr = tmpptr; // the list pointer is set to temp pointer
    }
    else
    {
        // if the list pointer does not equal null, the current pointer is the list pointer
        struct node *curptr = listptr;
        while (curptr->next != NULL && curptr->next->data <= N)
        {
            // Iterate through the the list until we find a value that is less than or equal to N
            curptr = curptr->next;
        }
        tmpptr->next = curptr->next;
        curptr->next = tmpptr;

        // insert the new integer
    }
    return listptr; // return the now changed list
}

Node *insertRecursive(int N, Node *listptr)
{

    if (listptr == NULL || N < listptr->data)
    {
        struct node *tmpptr = (struct node *)malloc(sizeof(Node));
        tmpptr->data = N;
        tmpptr->next = NULL;
        // The temp pointers next data (NULL) is set to the current listpointer's next
        tmpptr->next = listptr;
        listptr = tmpptr; // the list pointer is set to temp pointer
    }
    else
    {
        // make the next node the the result of a recursive insert of N to the next node
        listptr->next = insertRecursive(N, listptr->next);
    }
    return listptr;
}

void PrintList(Node *listptr)
{
    printf("%d", listptr->data);
    struct node *curptr = listptr;
    if (curptr->next != NULL)
    {
        printf("->");
        PrintList(curptr->next);
    }
    else
    {
        printf("->NULL\n");
    }
}

int main(int argc, char *argv[])
{

    int toInsert = 2;

    if (argc > 1)
    {
        toInsert = (atoi(argv[1]));
    }

    struct node *list = NULL;
    list = insert(10, list);
    list = insert(5, list);
    list = insert(7, list);
    list = insert(12, list);
    list = insert(1, list);
    printf("%d\n", list->data);
    PrintList(list);
    printf("\nInserting: %d", toInsert);
    list = insertRecursive(toInsert, list);
    printf("\n\nList after recursive insert:\n\n");
    PrintList(list);
}