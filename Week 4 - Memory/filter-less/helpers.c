#include "helpers.h"

#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            float average = (red + blue + green) / 3.0;

            image[i][j].rgbtRed = (int) round(average);
            image[i][j].rgbtGreen = (int) round(average);
            image[i][j].rgbtBlue = (int) round(average);
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
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            float sepiaRed = .393 * red + .769 * green + .189 * blue;
            float sepiaGreen = .349 * red + .686 * green + .168 * blue;
            float sepiaBlue = .272 * red + .534 * green + .131 * blue;

            image[i][j].rgbtRed = (int) round(sepiaRed) > 255 ? 255 : (int) round(sepiaRed);
            image[i][j].rgbtGreen = (int) round(sepiaGreen) > 255 ? 255 : (int) round(sepiaGreen);
            image[i][j].rgbtBlue = (int) round(sepiaBlue) > 255 ? 255 : (int) round(sepiaBlue);
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
            // Saves the left side before changing it
            int tempRed = image[i][j].rgbtRed;
            int tempGreen = image[i][j].rgbtGreen;
            int tempBlue = image[i][j].rgbtBlue;

            // Needed to consider width - j - 1
            // (last index would be width - 0, needed to be width - 1)
            // Changes the right side to the left side
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            // Changes the left side to the rigth side
            image[i][width - j - 1].rgbtRed = tempRed;
            image[i][width - j - 1].rgbtGreen = tempGreen;
            image[i][width - j - 1].rgbtBlue = tempBlue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
            float pixelCount = 0;
            int averageRed = 0;
            int averageGreen = 0;
            int averageBlue = 0;

            // positions
            int top = i - 1;
            int down = i + 1;
            int left = j - 1;
            int right = j + 1;

            averageRed += copy[i][j].rgbtRed;
            averageGreen += copy[i][j].rgbtGreen;
            averageBlue += copy[i][j].rgbtBlue;
            pixelCount++;

            // top-left
            if (i > 0 && j > 0)
            {
                averageRed += copy[top][left].rgbtRed;
                averageGreen += copy[top][left].rgbtGreen;
                averageBlue += copy[top][left].rgbtBlue;
                pixelCount++;
            }

            // above
            if (i > 0)
            {
                averageRed += copy[top][j].rgbtRed;
                averageGreen += copy[top][j].rgbtGreen;
                averageBlue += copy[top][j].rgbtBlue;
                pixelCount++;
            }

            // top right
            if (i > 0 && j < width - 1)
            {
                averageRed += copy[top][right].rgbtRed;
                averageGreen += copy[top][right].rgbtGreen;
                averageBlue += copy[top][right].rgbtBlue;
                pixelCount++;
            }

            // left
            if (j > 0)
            {
                averageRed += copy[i][left].rgbtRed;
                averageGreen += copy[i][left].rgbtGreen;
                averageBlue += copy[i][left].rgbtBlue;
                pixelCount++;
            }

            // Beyound this line we have to copy too
            // right
            if (j < width - 1)
            {
                copy[i][right] = image[i][right];
                averageRed += copy[i][right].rgbtRed;
                averageGreen += copy[i][right].rgbtGreen;
                averageBlue += copy[i][right].rgbtBlue;
                pixelCount++;
            }

            // down-left
            if (i < height - 1 && j > 0)
            {
                copy[down][left] = image[down][left];
                averageRed += copy[down][left].rgbtRed;
                averageGreen += copy[down][left].rgbtGreen;
                averageBlue += copy[down][left].rgbtBlue;
                pixelCount++;
            }

            // down
            if (i < height - 1)
            {
                copy[down][j] = image[down][j];
                averageRed += copy[down][j].rgbtRed;
                averageGreen += copy[down][j].rgbtGreen;
                averageBlue += copy[down][j].rgbtBlue;
                pixelCount++;
            }

            // down-right
            if (i < height - 1 && j < width - 1)
            {
                copy[down][right] = image[down][right];
                averageRed += copy[down][right].rgbtRed;
                averageGreen += copy[down][right].rgbtGreen;
                averageBlue += copy[down][right].rgbtBlue;
                pixelCount++;
            }

            image[i][j].rgbtRed = (int) round(averageRed / pixelCount);
            image[i][j].rgbtGreen = (int) round(averageGreen / pixelCount);
            image[i][j].rgbtBlue = (int) round(averageBlue / pixelCount);
        }
    }

    return;
}
