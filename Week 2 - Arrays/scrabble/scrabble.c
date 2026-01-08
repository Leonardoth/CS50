#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int getPoints(string s);
int getValue(char c);

int main(void)
{
    // prompt player 1 word
    string player1Word = get_string("Player 1 ");
    // prompt player 2 word
    string player2Word = get_string("Player 2 ");
    // compare both values against table
    int player1Points = getPoints(player1Word);
    int player2Points = getPoints(player2Word);
    if (player1Points > player2Points)
    {
        printf("Player 1 wins!\n");
    }
    else if (player1Points == player2Points)
    {

        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
    //     // player 1 > player 2 -> player 1 wins
    // player 1 == player 2 -> TIE
    // player 1 < player 2 -> player 2 wins
}

// a function that sums the value of a word
int getPoints(string s)
{
    int sum = 0;
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        sum += getValue(s[i]);
    }
    return sum;
}

// a function that returns a value for a character
int getValue(char c)
{
    c = tolower(c);
    int points[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    if (c < 'a' || c > 'z')
    {
        return 0;
    }
    else
    {
        return points[c - 97];
    }
}
