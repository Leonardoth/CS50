#include <stdio.h>

void swap(int a, int b);
void swap_correct(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i\n", x, y);
    swap_correct(&x, &y);
    printf("x is %i, y is %i\n", x, y);

}

void swap(int a, int b)
{
    // it'll change only in scope
    // when you pass arguments to functions, you pass copies of them to the function
    int temp = a;
    a = b;
    b = temp;
}

void swap_correct(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
