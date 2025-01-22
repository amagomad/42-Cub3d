/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/01/22 16:49:01 by cgorin           ###   ########.fr       */
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
	if (!(data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
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

void handle_keypress(mlx_key_data_t keydata, void* param)
{
	t_data* data = (t_data*)param;

    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			return (mlx_close_window(data->mlx));
	}
}

void	display_map(t_data *data)
{
	uint32_t color;

	int x, y, xo, yo;
	for (y=0; y < data->map_height; y++)
	{
		for (x=0; x<data->map_width;x++)
		{
            xo = x * mapS;
            yo = y * mapS;
			// Set the color based on the map value
			if (data->map[y * data->map_width + x] == 1)
                color = 0xFFFFFFFF; // White (walls)
            else
                color = 0x000000FF; // Black (empty space)
				// Draw the rectangle for the cell
            for (int i = 1; i < mapS - 1; i++) // Exclude borders for a grid-like appearance
            {
                for (int j = 1; j < mapS - 1; j++)
                {
                    mlx_put_pixel(data->img, xo + i, yo + j, color);
                }
			}
		}
	}
}

int main(int ac, char **av)
{
	t_data			*data;

	if (ac != 2)
		return_error("Invalid number of arguments");
	data = malloc(sizeof(t_data));
	if (!data)
		return_error("Malloc error");
	init_data(data, av);
	//if (!initialize_game(data))
	//	return_error("Can't initialize game");
	//display_map(data);
	//mlx_key_hook(data->mlx, handle_keypress, data);
	//mlx_loop(data->mlx);
}
