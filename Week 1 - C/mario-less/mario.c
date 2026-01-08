#include <cs50.h>
#include <stdio.h>

void addSpace(int gap);
void makePyramid(int height);

int main(void)
{
    int pyramidHeight;
    do
    {
        pyramidHeight = get_int("What's the pyramid height?");
    }
    while (pyramidHeight < 1);
    makePyramid(pyramidHeight);
}

void makePyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        addSpace(height - (i + 1));
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

void addSpace(int gap)
{
    for (int i = 0; i < gap; i++)
    {
        printf(" ");
    }
}
