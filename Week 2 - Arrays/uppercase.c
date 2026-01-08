#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("Before: ");
    printf("After:  ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // this block could be replaced with the function toupper(char)
        // printf("%c", toupper(s[i]));
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            // change to uppercase
            // you could replace 32 with 'a' - 'A'
            printf("%c", s[i] - ('a' - 'A'));
        }
        else
        {
            // print s[i]
            printf("%c", s[i]);
        }
    }
    printf("\n");
}
