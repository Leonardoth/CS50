#include <stdio.h>
#include <stdlib.h>

// Part of linked list
//              we have to add "node" here
typedef struct node
{
    int number;
    // to use "struct node" before its definition
    struct node *next;
} node;

int usingLinkedList(void);

int main(void)
{
    usingLinkedList();
}


// using malloc to increase list size after allocation
int usingMalloc(void)
{
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;


    // Time passes and i want to add another number to my list

    int *tmp = malloc(4 * sizeof(int));
    if(tmp == NULL)
    {
        free(list); // ALWAYS free memory that you allocate
        // even if its inside an error!
        return 1;
    }

    for (int = 0; i < 3; i++)
    {
        tmp[i] = list[i];
    }

    tmp[3] = 4;

    free(list);

    list = tmp;

    // i would have to copy list to tmp and recreate everytime
}


// using realloc instead of malloc

int usingRealloc(void)
{
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;


    // Time passes and i want to add another number to my list

    int *tmp = realloc(list, 4 * sizeof(int));
    if(tmp == NULL)
    {
        free(list); // ALWAYS free memory that you allocate
        // even if its inside an error!
        return 1;
    }

    tmp[3] = 4;

    list = tmp;

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }


    free(list);
    return 0;
    // i would have to copy list to tmp and recreate everytime
}



// Using linked list
int usingLinkedList(void)
{
    // Memory for numbers
    node *list = NULL;

    // Build list
    for (int i = 0; i < 3; i++)
    {
        // Allocate node for number
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // Important: Always free() previously alloc'd memory
            // n can be NULL in the third iteration, just closing
            // would leave the two previous memory allocated (memory leak)
            return 1;
        }
        n->number = get_int("Number: ");
        n->next = NULL;

        // Prepend node to list
        n->next = list;
        list = n;
    }

    // Free memory
    node *ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    return 0;
}
