#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int only_digits(string argument);
int getChar(char c, int position);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
    int key = only_digits(argv[1]);
    if (key == 0)
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        int newLetter;

        newLetter = key % 26;
        newLetter = getChar(text[i], newLetter);

        printf("%c", newLetter);
    }
    printf("\n");
    return 0;
}

int only_digits(string argument)
{
    for (int i = 0, len = strlen(argument); i < len; i++)
    {
        int isDigit = isdigit(argument[i]);
        if (isDigit == 0)
        {
            return 0;
        }
    }
    return atoi(argument);
}

int getChar(char c, int position)
{
    if (c >= 'A' && c <= 'Z')
    {
        if (c + position > 'Z')
        {
            return 64 + (position - ('Z' - c));
        }
        else
        {
            return c + position;
        }
    }
    else if (c >= 'a' && c <= 'z')
    {
        if (c + position > 'z')
        {
            return 96 + (position - ('z' - c));
        }
        else
        {
            return c + position;
        }
    }
    else
    {
        return c;
    }
}

// 65 % 26 (13)
// Letter   : A (65) Z (122) O(111) a(97)!  r     AZOa!
// Expercted: N (78) M (77)  B(66)  n(110)! e

// tests
// barfoo  world, say hello!
// onesbb  iadxp, emk tqxxa!

// More formally, Caesar’s algorithm (i.e., cipher) encrypts messages by “rotating” each letter by
//  positions. More formally, if
//  is some plaintext (i.e., an unencrypted message),
//  is the
//  character in
// , and
//  is a secret key (i.e., a non-negative integer), then each letter,
// , in the ciphertext,
// , is computed as

// wherein
//  here means “remainder when dividing by 26.” This formula perhaps makes the cipher seem more
//  complicated than it is, but it’s really just a concise way of expressing the algorithm
//  precisely. Indeed, for the sake of discussion, think of A (or a) as
// , B (or b) as
// , …, H (or h) as
// , I (or i) as
// , …, and Z (or z) as
// . Suppose that Caesar just wants to say Hi to someone confidentially using, this time, a key,
// , of 3. And so his plaintext,
// , is Hi, in which case his plaintext’s first character,
// , is H (aka 7), and his plaintext’s second character,
// , is i (aka 8). His ciphertext’s first character,
// , is thus K, and his ciphertext’s second character,
// , is thus L. Make sense?

// In a file called caesar.c in a folder called caesar, write a program that enables you to encrypt
// messages using Caesar’s cipher. At the time the user executes the program, they should decide, by
// providing a command-line argument, what the key should be in the secret message they’ll provide
// at runtime. We shouldn’t necessarily assume that the user’s key is going to be a number; though
// you may assume that, if it is a number, it will be a positive integer.
