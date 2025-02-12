/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/12 22:39:28 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_valid_position(t_data *data, float x, float y)
{
	int map_x;
	int map_y;

	map_x = (int)(x / T_SIZE);
	map_y = (int)(y / T_SIZE);
	if (data->map[map_y][map_x] != 0)
		return (false);
	if (data->map[map_y][(int)((x + PLAYER_RADIUS) / T_SIZE)] != 0)
		return (false);
	if (data->map[map_y][(int)((x - PLAYER_RADIUS) / T_SIZE)] != 0)
		return (false);
	if (data->map[(int)((y + PLAYER_RADIUS) / T_SIZE)][map_x] != 0)
		return (false);
	if (data->map[(int)((y - PLAYER_RADIUS) / T_SIZE)][map_x] != 0)
		return false;
	return (true);
}

void	move_player(t_data *data, float move_x, float move_y)
{
	float	next_x;
	float	next_y;

	next_x = data->player->pos_x + move_x * data->player->move_speed;
	next_y = data->player->pos_y + move_y * data->player->move_speed;
	if (is_valid_position(data, next_x, next_y))
	{
		data->player->pos_x = next_x;
		data->player->pos_y = next_y;
	}
}
