#include "../../includes/cub3d.h"

/**
 * Draws a rectangle on the screen.
 *
 * @param x The x-coordinate of the top-left corner of the rectangle.
 * @param y The y-coordinate of the top-left corner of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param color The color of the rectangle.
 */
void draw_rect(t_data *data, int x, int y, int width, int height, uint32_t color)
{
	int i;
	int j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			my_put_pixel(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

