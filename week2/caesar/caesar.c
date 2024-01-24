#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string encryptMessage(string message, int key);
bool isDigit(string input);
char rotate(char input, int key);

int main(int argc, string argv[])
{
    if (argc == 2 && isDigit(argv[1]))
    {
        string message = get_string("plaintext: ");
        printf("ciphertext: %s\n", encryptMessage(message, atoi(argv[1])));
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

string encryptMessage(string message, int key)
{
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        message[i] = rotate(message[i], key);
    }
    return message;
}

char rotate(char input, int key)
{
    bool isUppercase;

    if (isalpha(input) == 0)
    {
        return input;
    }
    else if (input >= 'A' && input <= 'Z')
    {
        isUppercase = true;
        input -= 65;
        input += key;
        input = input % 26;
    }
    else // if (input >= 'a' && input <= 'z')
    {
        isUppercase = false;
        input -= 97;
        input += key;
        input = input % 26;
    }

    if (isUppercase == true)
    {
        input += 65;
    }
    else
    {
        input += 97;
    }
    return input;
}

bool isDigit(string input)
{
    bool hasNonDigitAppeared = true;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (isdigit(input[i]) == 0)
        {
            hasNonDigitAppeared = false;
        }
    }
    return hasNonDigitAppeared;
}
