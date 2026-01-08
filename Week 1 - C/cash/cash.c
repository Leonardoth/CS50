#include <cs50.h>
#include <stdio.h>

// get $ (change)
// return minimal number of coins to be given

int main(void)
{
    int change;
    int coinsCount = 0;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 0);
    while (change > 0)
    {
        if (change >= 25)
        {
            change -= 25;
            coinsCount++;
        }
        else if (change >= 10)
        {
            change -= 10;
            coinsCount++;
        }
        else if (change >= 5)
        {
            change -= 5;
            coinsCount++;
        }
        else if (change >= 1)
        {
            change -= 1;
            coinsCount++;
        }
    }
    printf("%i \n", coinsCount);
}
