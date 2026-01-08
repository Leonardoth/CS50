#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

struct TextCount
{
    float sentenceCount;
    float letterCount;
    float wordCount;
};

struct TextCount countData(string text)
{
    struct TextCount textData;

    textData.sentenceCount = 0;
    textData.letterCount = 0;
    textData.wordCount = 0;
    int inWord = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (inWord)
        {
            if (text[i] == ' ')
            {
                inWord = 0;
            }
            else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            {
                inWord = 0;
                textData.sentenceCount++;
            }
        }
        else
        {
            textData.wordCount++;
            inWord = 1;
        }
        if ((text[i] >= 'A' && text[i] <= 'z') || (text[i] > '0' && text[i] < '9'))
        {
            textData.letterCount++;
        }
    }
    // printf("\nSentences: %0.2f Letters: %0.2f Words: %0.2f\n", textData.sentenceCount,
    // textData.letterCount, textData.wordCount);
    return textData;
}

int main(void)
{
    struct TextCount textData;
    // get string input from user
    string text = get_string("Text: ");
    textData = countData(text);
    // count number of letters per word
    // count number of words
    // count number of sentences per 100 words
    float grade;
    float S = (textData.sentenceCount / textData.wordCount) * 100;
    float L = (textData.letterCount / textData.wordCount) * 100;

    grade = (0.0588 * L) - (0.296 * S) - 15.8;
    // return index = 0.0588 * L - 0.296 * S - 15.8 rounded to nearest int
    // L -> number of letters per 100 words -> L = (letters/words) * 100
    // S -> number of sentences per 100 words -> S = (sentences/words) * 100

    if (grade <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", nearbyintf(grade));
    }
}

// you’ll implement a program that calculates the approximate grade level needed to comprehend some
// text. Your program should print as output “Grade X” where “X” is the grade level computed,
// rounded to the nearest integer. If the grade level is 16 or higher (equivalent to or greater than
// a senior undergraduate reading level), your program should output “Grade 16+” instead of giving
// the exact index number. If the grade level is less than 1, your program should output “Before
// Grade 1”.

// So what sorts of traits are characteristic of higher reading levels? Well, longer words probably
// correlate with higher reading levels. Likewise, longer sentences probably correlate with higher
// reading levels, too.

// A number of “readability tests” have been developed over the years that define formulas for
// computing the reading level of a text. One such readability test is the Coleman-Liau index. The
// Coleman-Liau index of a text is designed to output that (U.S.) grade level that is needed to
// understand some text. The formula is

// index = 0.0588 * L - 0.296 * S - 15.8
// where L is the average number of letters per 100 words in the text, and S is the average number
// of sentences per 100 words in the text.

// Specification
// For the purpose of this problem, we’ll consider any sequence of characters separated by a space
// to be a word (so a hyphenated word like “sister-in-law” should be considered one word, not
// three). You may assume that a sentence:

// will contain at least one word;
// will not start or end with a space; and
// will not have multiple spaces in a row.
// Under those assumptions, you might already be able to find a mathematical relationship between
// the number of words and the number of spaces.

// You are, of course, welcome to attempt a more sophisticated solution that can tolerate multiple
// spaces between words! We’ve tuned check50 to accept either approach to spaces, so the choice is
// yours.

// example

// One fish. Two fish. Red fish. Blue fish. (Before Grade 1...)

// Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing
// to do: once or twice she had peeped into the book her sister was reading, but it had no pictures
// or conversations in it, "and what is the use of a book," thought Alice "without pictures or
// conversation?" (8)

// Harry Potter was a highly unusual boy in many ways. For one thing, he hated the summer holidays
// more than any other time of year. For another, he really wanted to do his homework, but was
// forced to do it in secret, in the dead of the night. And he also happened to be a wizard. (5)
