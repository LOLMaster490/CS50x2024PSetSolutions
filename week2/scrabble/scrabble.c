#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int PLAYERNUMBER = 2;
const int LETTERVALUE[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int computeScore(string prompt);

int main(void)
{
    string chosenWord[PLAYERNUMBER];
    for (int i = 0; i < PLAYERNUMBER; i++)
    {
        chosenWord[i] = get_string("Player %i: ", i + 1);
    }
    if (computeScore(chosenWord[0]) > computeScore(chosenWord[1]))
    {
        printf("Player 1 wins!\n");
    }
    else if (computeScore(chosenWord[0]) < computeScore(chosenWord[1]))
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int computeScore(string prompt)
{
    int score = 0;
    for (int i = 0; i < strlen(prompt); i++)
    {
        if (prompt[i] >= 'a' && prompt[i] <= 'z')
        {
            score += LETTERVALUE[prompt[i] - 97];
        }
        else if (prompt[i] >= 'A' && prompt[i] <= 'Z')
        {
            score += LETTERVALUE[prompt[i] - 65];
        }
    }
    return score;
}
