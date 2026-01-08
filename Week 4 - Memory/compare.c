#include <cs50.h>
#include <stdio.h>
#include <string.h>

void strcmp_example(void);

int main(void)
{
    strcmp_example();
}

void strcmp_example(void)
{
    char *s = get_string("s: ");
    char *t = get_string("t: ");

    // because * is the adress of the first char, it compares the adresses
    // if (s==t)
    // {
    //     printf("Same\n");
    // }
    // else
    // {
    //     printf("Different\n");
    // }

    if (strcmp(s,t) == 0)
    {
        printf("Same\n");
    }
    else
    {
        printf("Different\n");
    }
}
