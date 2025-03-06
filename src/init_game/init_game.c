/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/02/22 22:03:48 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	to_zero(t_data *data)
{
	int	i;

	i = -1;
	while (++i < MLX_TOTAL_KEYS)
		data->keys[i] = false;
}

void	init_data(t_data *data, char **av)
{
	data->no_texture = NULL;
	data->so_texture = NULL;
	data->we_texture = NULL;
	data->ea_texture = NULL;
	data->map = NULL;
	data->parse->map = NULL;
	data->parse->line = NULL;
	data->parse->desc = NULL;
	data->parse->ceiling_color = NULL;
	data->parse->floor_color = NULL;
	data->parse->no_texture = NULL;
	data->parse->so_texture = NULL;
	data->parse->we_texture = NULL;
	data->parse->ea_texture = NULL;
	data->player->move_speed = WALK_SPEED;
	data->state = STATE_GAME;
	to_zero(data);
	if (!parsing(av[1], data))
		return_error("Parsing error", data, true);
}

bool	initialize_game(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!data->mlx)
		return_error((char *)mlx_strerror(mlx_errno), data, false);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		mlx_close_window(data->mlx);
		return_error((char *)mlx_strerror(mlx_errno), data, false);
	}
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		return_error((char *)mlx_strerror(mlx_errno), data, false);
	}
	return (true);
}

void	init(t_data *data, char **av)
{
	data->parse = malloc(sizeof(t_parsing));
	data->player = malloc(sizeof(t_player));
	if (!data->parse || !data->player)
		return_error("Malloc error", data, true);
	data->mlx = NULL;
	data->img = NULL;
	init_data(data, av);
	if (!initialize_game(data))
		return_error("Can't initialize game", data, false);
}
