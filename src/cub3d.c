/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/01/28 18:41:01 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_data *data, char **av)
{
	data->parse = malloc(sizeof(t_parsing));
	data->player = malloc(sizeof(t_player));
	if (!data->parse || !data->player)
		return_error("Malloc error");
	data->mlx = NULL;
	data->win = NULL;
	data->no_texture = NULL;
	data->so_texture = NULL;
	data->we_texture = NULL;
	data->ea_texture = NULL;
	data->icon = NULL;
	data->t_size_x = 0;
	data->t_size_y = 0;
	data->width = 0;
	data->height = 0;
	data->map_width = 0;
	data->map_height = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->player_dir = 0;
	data->map = NULL;
	data->parse->map = NULL;
	data->parse->description = NULL;
	if (!parsing(av[1], data))
		return_error("Parsing error");
}

bool	initialize_game(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!data->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (false);
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return (false);
	}
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return (false);
	}
	if (data->icon)
		mlx_set_icon(data->mlx, data->icon);
	return (true);
}

void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			return (mlx_close_window(data->mlx));
	}
}

void	display_map(t_data *data)
{
	uint32_t	color;
	int			x;
	int			y;
	int			xo;
	int			yo;
	int			i;
	int			j;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			xo = x * mapS;
			yo = y * mapS;
			if (data->map[y * data->map_width + x] == 0)
				color = 0x000000FF;
			else
				color = 0xFFFFFFFF;
			i = 0;
			while (++i < mapS - 1)
			{
				j = 0;
				while (++j < mapS - 1)
					mlx_put_pixel(data->img, xo + i, yo + j, color);
			}
		}
	}
}

void drawPlayer2D(t_data *data)
{
    mlx_put_pixel(data->img, (int)data->player->px, (int)data->player->py, 0xFFFF00FF);
}

void draw_line(t_data *data, int x1, int y1, int x2, int y2, uint32_t color)
{
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
		if (x1 >= 0 && x1 < (int)data->img->width && y1 >= 0 && y1 < (int)data->img->height)
        	mlx_put_pixel(data->img, x1, y1, color);
		else
			fprintf(stderr, "Error: Pixel out of bounds: x=%d, y=%d\n", x1, y1);
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; }
        if (e2 <= dx) { err += dx; y1 += sy; }
    }
}
float degToRad(int a)
{
    return a * M_PI / 180.0;
}

int FixAng(int a) {
    if (a > 359) {
        a -= 360;
    }
    if (a < 0) {
        a += 360;
    }
    return a;
}

void init_player(t_data *data)
{
	data->player->px = 0;
	data->player->py = 0;
	data->player->pdx = 0;
	data->player->pdy = 0;
	data->player->pa = 0;
    data->player->pa = 0; // Initial angle in degrees
    data->player->pdx = cos(degToRad(data->player->pa)); // Initial x-direction
    data->player->pdy = -sin(degToRad(data->player->pa)); // Initial y-direction
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return_error("Invalid number of arguments");
	data = malloc(sizeof(t_data));
	if (!data)
		return_error("Malloc error");
	init_data(data, av);
	if (!initialize_game(data))
		return_error("Can't initialize game");
	init_player(data);
	display_map(data);
	drawPlayer2D(data);
	mlx_key_hook(data->mlx, handle_keypress, data);
	mlx_loop(data->mlx);
}

//exemple de map 
/* int map[]
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,1,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,	
}; */
