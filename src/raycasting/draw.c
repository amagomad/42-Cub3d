#include "../../includes/cub3d.h"

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

void drawMap2D(t_data *data)
{
	int			y;
	int			x;
	int			xo;
	int			yo;
	uint32_t	color;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			xo = x * 64;
			yo = y * 64;
			if (data->map[y][x] != -1)
			{
				if (data->map[y][x] == 1)
					color = 0xFFFFFFFF;
				else
					color = 0x000000FF;
				draw_rect(data, xo + 1, yo + 1, 64 - 2, 64 - 2, color);
			}
		}
	}
}

void drawPlayer2D(t_data *data, t_player *p)
{
	uint32_t yellow = 0xFFFF00FF;
	int x2 = (int)(p->player_pos_x + p->player_dir_x * 20);
	int y2 = (int)(p->player_pos_y + p->player_dir_y * 20);
	draw_rect(data, (int)p->player_pos_x - data->map_height/2, (int)p->player_pos_y - data->map_width/2, data->map_height, data->map_width, yellow);
	draw_line(data, (int)p->player_pos_x, (int)p->player_pos_y, x2, y2, yellow);
}


void render(void *param)
{
	t_data *data;

	data = (t_data *)param;
	clear_image(data, 0xFF3030FF);
	//drawMap2D(data);
	//drawPlayer2D(data, data->player);
	drawRays2D(data->player, data);
}
