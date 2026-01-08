#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getSum(long cardNumber);
int getMaker(long cardNumberLong);
string toString(long number);
int checkVisa(string cardNumber);
int checkMastercard(string cardNumber);
int checkAmex(string cardNumber);

// TODO
// [x] step 1 - sum digits check if sum % 10 == 0
// [x] step 1 - check if the number given is the correct length (13,15,16)
// [x] step 2 - check if the first digit is 4 or first two digits are in the array {"51", "52", "53",
// "54", "55", "34", "37"}
int main(void)
{
    long cardNumber = get_long("Credit Card Number? ");
    if ((getSum(cardNumber) % 10) != 0)
    {
        printf("INVALID\n");
        exit(0);
    }
    getMaker(cardNumber);
    exit(0);
}

int getSum(long cardNumber)
{
    int sum = 0;
    int odd = 0;

    for (long i = cardNumber; i > 0; i = i / 10)
    {

        if (odd)
        {
            int multiplied = (i % 10) * 2;
            if (multiplied >= 10)
            {
                multiplied -= 9;
            }
            sum += multiplied;
            odd = 0;
        }
        else
        {
            sum += i % 10;
            odd = 1;
        }
    }
    return sum;
}

int getMaker(long cardNumberLong)
{
    string cardNumber = toString(cardNumberLong);
    if (checkVisa(cardNumber))
    {
        return printf("VISA\n");
    }
    else if (checkAmex(cardNumber))
    {
        return printf("AMEX\n");
    }
    else if (checkMastercard(cardNumber))
    {
        return printf("MASTERCARD\n");
    }
    return printf("INVALID\n");
}

string toString(long number)
{
    string t;
    t = malloc(1);
    if (t == NULL)
    {
        exit(0);
    }
    sprintf(t, "%li", number);
    return t;
}

int checkVisa(string cardNumber)
{
    if (strlen(cardNumber) == 16 || strlen(cardNumber) == 13)
    {
        if (cardNumber[0] == '4')
        {
            return 1;
        }
        return 0;
    }
    return 0;
}

int checkMastercard(string cardNumber)
{
    if (strlen(cardNumber) == 16)
    {
        if (cardNumber[0] == '5')
        {
            if (cardNumber[1] == '1' || cardNumber[1] == '2' || cardNumber[1] == '3' ||
                cardNumber[1] == '4' || cardNumber[1] == '5')
            {
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

int checkAmex(string cardNumber)
{
    if (strlen(cardNumber) == 15)
    {
        if (cardNumber[0] == '3')
        {
            if (cardNumber[1] == '4' || cardNumber[1] == '7')
            {
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}
