#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void copy_example1(void);
void copy_example2(void);

int main(void)
{

    copy_example2();
}

void copy_example1(void)
{
    char *s = get_string("s: ");

    // this copies the same Adress
    char *t = s;

    // it changes the only version of the word,
    // both point at the same place
    t[0] = toupper(t[0]);

    printf("s: %s\n", s);
    printf("t: %s\n", t);
}

void copy_example2(void)
    {
           // This will use malloc (memory allocation) to fix copy_example1

        char *s = get_string("s: ");

        // this will figure out the size of the string, add 1 for \0 and alloc memory
        char *t = malloc(strlen(s)+1);
        if (t == NULL)
        {
            // insuficcient memory
            return 1;
        }

        // we want to include the \0 so we'll use <= instead of <
        for (int i = 0, n = strlen(s); i <= n; i++)
        {
            t[i] = s[i];
        }

        // We avoid capitalizing if the user didn't type anything
        if(strlen(t) > 0)
        {
            t[0] = toupper(t[0]);
        }



        printf("s: %s\n", s);
        printf("t: %s\n", t);
        // You'll need to free the memory when you are not using it anymore
        free(t);
    }
