#include "helpers.h"

#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE greyScale =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = greyScale;
            image[i][j].rgbtGreen = greyScale;
            image[i][j].rgbtRed = greyScale;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {

            RGBTRIPLE leftImage;
            leftImage.rgbtBlue = image[i][j].rgbtBlue;
            leftImage.rgbtGreen = image[i][j].rgbtGreen;
            leftImage.rgbtRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;

            image[i][width - 1 - j].rgbtBlue = leftImage.rgbtBlue;
            image[i][width - 1 - j].rgbtGreen = leftImage.rgbtGreen;
            image[i][width - 1 - j].rgbtRed = leftImage.rgbtRed;
        }
    }
    return;
}
RGBTRIPLE getCell(int height, int width, RGBTRIPLE image[height][width], int currentY, int currentX,
                  int deltaY, int deltaX)
{
    RGBTRIPLE cell;
    cell.rgbtBlue = 0;
    cell.rgbtGreen = 0;
    cell.rgbtRed = 0;

    if (currentX + deltaX >= 0 && currentX + deltaX <= width - 1 && currentY + deltaY >= 0 &&
        currentY + deltaY <= height - 1)
    {
        cell.rgbtBlue = image[currentY + deltaY][currentX + deltaX].rgbtBlue;
        cell.rgbtGreen = image[currentY + deltaY][currentX + deltaX].rgbtGreen;
        cell.rgbtRed = image[currentY + deltaY][currentX + deltaX].rgbtRed;
    }

    return cell;
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
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalBlue = 0;
            int totalGreen = 0;
            int totalRed = 0;
            int count = 0;

            for (int dy = -1; dy <= 1; dy++)
            {
                for (int dx = -1; dx <= 1; dx++)
                {
                    int y = i + dy;
                    int x = j + dx;

                    if (y >= 0 && y < height && x >= 0 && x < width)
                    {
                        totalBlue += copy[y][x].rgbtBlue;
                        totalGreen += copy[y][x].rgbtGreen;
                        totalRed += copy[y][x].rgbtRed;
                        count++;
                    }
                }
            }

            image[i][j].rgbtBlue = round((float) totalBlue / count);
            image[i][j].rgbtGreen = round((float) totalGreen / count);
            image[i][j].rgbtRed = round((float) totalRed / count);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Copy original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE leftImage = getCell(height, width, copy, i, j, 0, -1);
            RGBTRIPLE topLeftImage = getCell(height, width, copy, i, j, -1, -1);
            RGBTRIPLE topImage = getCell(height, width, copy, i, j, -1, 0);
            RGBTRIPLE topRightImage = getCell(height, width, copy, i, j, -1, 1);
            RGBTRIPLE rightImage = getCell(height, width, copy, i, j, 0, 1);
            RGBTRIPLE bottomRightImage = getCell(height, width, copy, i, j, 1, 1);
            RGBTRIPLE bottomImage = getCell(height, width, copy, i, j, 1, 0);
            RGBTRIPLE bottomLeftImage = getCell(height, width, copy, i, j, 1, -1);

            int gxRed = -topLeftImage.rgbtRed + topRightImage.rgbtRed - 2 * leftImage.rgbtRed +
                        2 * rightImage.rgbtRed - bottomLeftImage.rgbtRed + bottomRightImage.rgbtRed;

            int gyRed = -topLeftImage.rgbtRed - 2 * topImage.rgbtRed - topRightImage.rgbtRed +
                        bottomLeftImage.rgbtRed + 2 * bottomImage.rgbtRed +
                        bottomRightImage.rgbtRed;

            int gxGreen = -topLeftImage.rgbtGreen + topRightImage.rgbtGreen -
                          2 * leftImage.rgbtGreen + 2 * rightImage.rgbtGreen -
                          bottomLeftImage.rgbtGreen + bottomRightImage.rgbtGreen;

            int gyGreen = -topLeftImage.rgbtGreen - 2 * topImage.rgbtGreen -
                          topRightImage.rgbtGreen + bottomLeftImage.rgbtGreen +
                          2 * bottomImage.rgbtGreen + bottomRightImage.rgbtGreen;

            int gxBlue = -topLeftImage.rgbtBlue + topRightImage.rgbtBlue - 2 * leftImage.rgbtBlue +
                         2 * rightImage.rgbtBlue - bottomLeftImage.rgbtBlue +
                         bottomRightImage.rgbtBlue;

            int gyBlue = -topLeftImage.rgbtBlue - 2 * topImage.rgbtBlue - topRightImage.rgbtBlue +
                         bottomLeftImage.rgbtBlue + 2 * bottomImage.rgbtBlue +
                         bottomRightImage.rgbtBlue;

            int r = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            int g = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int b = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            image[i][j].rgbtRed = r > 255 ? 255 : r;
            image[i][j].rgbtGreen = g > 255 ? 255 : g;
            image[i][j].rgbtBlue = b > 255 ? 255 : b;
        }
    }
}
