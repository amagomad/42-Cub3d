/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashxo <nashxo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/03/03 13:29:13 by nashxo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	data->img_menu[0] = NULL;
	data->img_menu[1] = NULL;
	data->door_texture = NULL;
	data->minimap_t_size = T_SIZE / 4;
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
	data->mouse_shown = false;
	data->sprites = NULL;
	data->z_buffer = NULL;
	to_zero(data);
	if (!parsing(av[1], data))
		return_error("Parsing error", data, true);
}

bool	initialize_game(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!data->mlx)
		return_error((char *)mlx_strerror(mlx_errno), data, false);
	init_menu(data);
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
	if (data->icon)
		mlx_set_icon(data->mlx, data->icon);
	data->z_buffer = malloc(sizeof(double) * WIDTH);
	if (!data->z_buffer)
		return_error("Malloc error for z_buffer", data, false);
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
	data->icon = NULL;
	data->num_sprites = 0;
	init_data(data, av);
	if (!initialize_game(data))
		return_error("Can't initialize game", data, false);
}
