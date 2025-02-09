#include "../../includes/cub3d.h"

void draw_rect(mlx_image_t *img, int x, int y, int width, int height, uint32_t color)
{
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
			mlx_put_pixel(img, x + i, y + j, color);
}

void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;

	while (1)
	{
		mlx_put_pixel(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void drawMap2D(mlx_image_t *img, t_data *data)
{
	for (int y = 0; y < data->map_height; y++)
	{
		for (int x = 0; x < data->map_width; x++)
		{
			int xo = x * MAP_S;
			int yo = y * MAP_S;
			if (data->map[y][x] != -1)
			{
				uint32_t color = (data->map[y][x] == 1) ? 0xFFFFFFFF : 0x000000FF;
				draw_rect(img, xo + 1, yo + 1, MAP_S - 2, MAP_S - 2, color);
			}
		}
	}
}

void drawPlayer2D(mlx_image_t *img, t_player *p)
{
	uint32_t yellow = 0xFFFF00FF;
	int size = 8;
	int x2 = (int)(p->player_pos_x + p->player_dir_x * 20);
	int y2 = (int)(p->player_pos_y + p->player_dir_y * 20);
	draw_rect(img, (int)p->player_pos_x - size/2, (int)p->player_pos_y - size/2, size, size, yellow);
	draw_line(img, (int)p->player_pos_x, (int)p->player_pos_y, x2, y2, yellow);
}

void clear_image(mlx_image_t *img, uint32_t color)
{
	int size = img->width * img->height;
	for (int i = 0; i < size; i++)
		((uint32_t*)img->pixels)[i] = color;
}

void render(void *param)
{
	t_data *data = (t_data *)param;
	clear_image(data->img, 0x303030FF);
	drawMap2D(data->img, data);
	drawPlayer2D(data->img, data->player);
	drawRays2D(data->img, data->player, data);
}
