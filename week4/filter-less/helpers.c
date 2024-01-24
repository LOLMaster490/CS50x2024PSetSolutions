#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float pixelSum = 0;
            pixelSum += image[i][j].rgbtRed;
            pixelSum += image[i][j].rgbtGreen;
            pixelSum += image[i][j].rgbtBlue;
            pixelSum /= 3.0;
            image[i][j].rgbtRed = (int) round(pixelSum);
            image[i][j].rgbtGreen = (int) round(pixelSum);
            image[i][j].rgbtBlue = (int) round(pixelSum);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            // TODO - Write a function that returns lesser of 2 numbers, then use it here like this // sepiaRed =
            // returnLesser(sepiaRed, 255), etc. ...
            if (sepiaRed > 255.0)
            {
                sepiaRed = 255.0;
            }
            if (sepiaGreen > 255.0)
            {
                sepiaGreen = 255.0;
            }
            if (sepiaBlue > 255.0)
            {
                sepiaBlue = 255.0;
            }
            image[i][j].rgbtRed = (int) round(sepiaRed);
            image[i][j].rgbtGreen = (int) round(sepiaGreen);
            image[i][j].rgbtBlue = (int) round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image pixel by pixel.
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Iterate over each pixel.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumBlue = 0;
            int sumGreen = 0;
            int divider = 0;
            // Iterate over each neighboring pixel.
            for (int h = -1; h <= 1; h++)
            {
                // If out of border, skip this column.
                if (h + i < 0 || h + i > height - 1)
                {
                    continue;
                }

                for (int w = -1; w <= 1; w++)
                {
                    // If out of order skip this row.
                    if (w + j < 0 || w + j > width - 1)
                    {
                        continue;
                    }
                    // Add together RGB values of neighboring pixels,
                    // and remember by what amount to divide final result.

                    // Get pixel value from created copy,
                    // so the algorithm doesn't use previously blurred values.
                    sumRed += copy[i + h][j + w].rgbtRed;
                    sumBlue += copy[i + h][j + w].rgbtBlue;
                    sumGreen += copy[i + h][j + w].rgbtGreen;
                    divider++;
                }
            }
            // Set original pixel to calculated blurred version.
            image[i][j].rgbtRed = (int) round((float) sumRed / (float) divider);
            image[i][j].rgbtGreen = (int) round((float) sumGreen / (float) divider);
            image[i][j].rgbtBlue = (int) round((float) sumBlue / (float) divider);
        }
    }

    return;
}
