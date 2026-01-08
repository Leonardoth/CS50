#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int checkKey(string key);
int isUnique(int lengthOfArray, string array, char element);
int replace(string toBeReplaced, string replaceWith);
int getChar(string key, char c);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("ERROR: Wrong number of arguments.\n");
        return 1;
    }
    string key = argv[1];
    if(strlen(key) != 26)
    {
        printf("ERROR: A key with 26 alphabetic characters is needed!\n");
        return 1;
    }
    if(checkKey(key) == 0)
    {
        printf("ERROR: Invalid key! (Use only UNIQUE alphabetic characters) \n");
        return 1;
    }

    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    replace(text, key);
    // Check if argv[1] has 26 UNIQUE ALPHABETIC chars
        // return 1 if not

    // Get user string as plaintext:
    // output: ciphertext: __________
}


int checkKey(string key)
{
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            return 0;
        }
        else if (isUnique(26, key, key[i]) != 1)
        {
            return 0;
        }
    }
    return 1;
}

int isUnique(int lengthOfArray, string array, char element)
{
    int count = 0;
    for (int i = 0; i < lengthOfArray; i++)
    {
        if (count > 1)
        {
            return 0;
        }
        if (tolower(array[i]) == tolower(element))
        {
            count++;
        }
    }

    return 1;
}

int replace(string toBeReplaced, string replaceWith)
{
    for (int i = 0, len = strlen(toBeReplaced); i < len; i++)
    {
        int newChar = getChar(replaceWith, toBeReplaced[i]);
        printf("%c", newChar);
    }
    printf("\n");
    return 0;
}

int getChar(string key, char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return toupper(key[(c-65)]);
    }
    else if (c >= 'a' && c <= 'z')
    {
        return tolower(key[(c-97)]);
    }
    else
    {
        return c;
    }
}

// Design and implement a program, substitution, that encrypts messages using a substitution cipher.

// Implement your program in a file called substitution.c in a directory called substitution.
// Your program must accept a single command-line argument, the key to use for the substitution. The key itself should be case-insensitive, so whether any character in the key is uppercase or lowercase should not affect the behavior of your program.
// If your program is executed without any command-line arguments or with more than one command-line argument, your program should print an error message of your choice (with printf) and return from main a value of 1 (which tends to signify an error) immediately.
// If the key is invalid (as by not containing 26 characters, containing any character that is not an alphabetic character, or not containing each letter exactly once), your program should print an error message of your choice (with printf) and return from main a value of 1 immediately.
// Your program must output plaintext: (without a newline) and then prompt the user for a string of plaintext (using get_string).
// Your program must output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical character in the plaintext substituted for the corresponding character in the ciphertext; non-alphabetical characters should be outputted unchanged.
// Your program must preserve case: capitalized letters must remain capitalized letters; lowercase letters must remain lowercase letters.
// After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main.
// You might find one or more functions declared in ctype.h to be helpful, per manual.cs50.io.
