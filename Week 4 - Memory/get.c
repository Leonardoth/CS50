#include <stdio.h>

void simple_get_int(void);
void simple_get_string(void);


// similar to but not foolproof to get_int

void simple_get_int(void)
{
    int n;
    printf("n: ");
    // we hand the ADRESS to the variable
    scanf("%i", &n);
    printf("n: %i\n", n);
}


void simple_get_string(void)
{
    char *s;
    printf("s: ");
    // THIS LINE IS DANGEROUS because
    // It doesn't know how much memory is available to that string
    scanf("%s", s) Just don't execute it.
    printf("s: %s\n", s);
}
