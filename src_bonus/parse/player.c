/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:23:32 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 17:07:40 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_dir(t_data *data, int angle, double px, double py)
{
	data->player->angle = angle;
	data->player->plane_x = px;
	data->player->plane_y = py;
	data->player->pos_x = (data->player_x + 0.5) * T_SIZE;
	data->player->pos_y = (data->player_y + 0.5) * T_SIZE;
}

void	set_player_starting_direction(t_data *data)
{
	if (data->player_dir == 'N')
	{
		init_dir(data, 90, PLANE_SIZE, 0);
		data->player->dir_x = 0;
		data->player->dir_y = -1;
	}
	else if (data->player_dir == 'S')
	{
		init_dir(data, 270, -PLANE_SIZE, 0);
		data->player->dir_x = 0;
		data->player->dir_y = 1;
	}
	else if (data->player_dir == 'W')
	{
		init_dir(data, 0, 0, -PLANE_SIZE);
		data->player->dir_x = -1;
		data->player->dir_y = 0;
	}
	else if (data->player_dir == 'E')
	{
		init_dir(data, 180, 0, PLANE_SIZE);
		data->player->dir_x = 1;
		data->player->dir_y = 0;
	}
}
