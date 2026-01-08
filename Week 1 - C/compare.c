#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int("What's x? ");
    int y = get_int("Whats y? ");

    if (x < y)
    {
        printf("X is less than Y\n");
    }
    else if (x > y)
    {
        printf("X is greater than Y\n");
    }
    else
    {
        printf("X is Equal to Y\n");
    }
}
