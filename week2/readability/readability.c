#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int readabilityChecker(string prompt);

int main(void)
{
    string prompt = get_string("Text: ");

    if (readabilityChecker(prompt) == 0)
    {
        printf("Before Grade 1\n");
    }
    else if (readabilityChecker(prompt) >= 1 && readabilityChecker(prompt) < 16)
    {
        printf("Grade %i\n", readabilityChecker(prompt));
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int readabilityChecker(string prompt)
{
    int length = 0;
    int words = 1;
    int sentences = 0;
    for (int i = 0, n = strlen(prompt); i < n; i++)
    {
        if (isalpha(prompt[i]))
        {
            length++;
        }
        if (prompt[i] == ' ')
        {
            words++;
        }
        if (prompt[i] == '.' || prompt[i] == '!' || prompt[i] == '?')
        {
            sentences++;
        }
    }
    float L = (float) length / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    float complexityunrounded = 0.0588 * L - 0.296 * S - 15.8;
    double complexity = round(0.0588 * L - 0.296 * S - 15.8);

    if (complexity < 1)
    {
        return 0;
    }
    if (complexity >= 16)
    {
        return 17;
    }

    return (int) complexity;
}
