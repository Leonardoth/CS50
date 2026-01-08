#include <cs50.h>
#include <stdio.h>

void leftSide(int height, int i);
void rightSide(int i);
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
        leftSide(height, i);
        rightSide(i);
        printf("\n");
    }
}

void leftSide(int height, int i)
{
    addSpace(height - (i + 1));
    for (int j = 0; j <= i; j++)
    {
        printf("#");
    }
}

void rightSide(int i)
{
    printf("  ");
    for (int j = 0; j <= i; j++)
    {
        printf("#");
    }
}

void addSpace(int gap)
{
    for (int i = 0; i < gap; i++)
    {
        printf(" ");
    }
}
