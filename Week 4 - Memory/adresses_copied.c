#include <stdio.h>

// Prototypes
void n_example(void);
void string_example(void);
void string_example2(void);


int main(void)
{
    string_example2();
}

void n_example(void)
{
    int n = 50;
    int *p = &n;
    printf("%i\n", *p);
}

void string_example(void)
{
    // for it to work, we have to #include <cs50.h>
    // string s = "HI!";
    // C does not have 'string' type it uses char *
    char *s = "HI!";

    // variable
    printf("%s\n", s);
    // Adress of word (doesn't need a & because it's alreay a pointer, if used & we would get the adress of the pointer not of what it points to)
    printf("%p\n", s);

    // Adress of first letter
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
    printf("%p\n", &s[3]);

    // Printf was going to the first adress, print all of characters
    // until it finds the "\0" character.
}

void string_example2(void)
{
    char *s = "HI!";
    printf("%c\n", *s);
    printf("%c\n", *(s+1));
    printf("%c\n", *(s+2));
}

