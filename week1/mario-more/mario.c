#include <cs50.h>
#include <stdio.h>

void buildPyramid(int height);

int main(void)
{
    int height = 0;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    buildPyramid(height);
}

void buildPyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 1; j <= height; j++)
        {
            if (j < height - i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }

        for (int x = 0; x < 2; x++)
        {
            printf(" ");
        }

        for (int j = 0; j < height; j++)
        {
            if (j <= i)
            {
                printf("#");
            }
        }

        printf("\n");
    }
}
