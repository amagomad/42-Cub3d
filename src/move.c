/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/04 18:31:53 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void rotate_player(t_data *data, float angle)
{
	data->player->player_angle += angle;
	if (data->player->player_angle >= 360)
		data->player->player_angle -= 360;
	else if (data->player->player_angle < 0)
		data->player->player_angle += 360;
	data->player->player_dir_x = cos(degrees_to_radians(data->player->player_angle));
	data->player->player_dir_y = -sin(degrees_to_radians(data->player->player_angle));
}


bool is_valid_position(t_data *data, float x, float y)
{
	int map_x;
	int map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (data->map[map_y][map_x] != 0)
		return false;
	if (data->map[map_y][(int)((x + PLAYER_RADIUS) / TILE_SIZE)] != 0)
		return false;
	if (data->map[map_y][(int)((x - PLAYER_RADIUS) / TILE_SIZE)] != 0)
		return false;
	if (data->map[(int)((y + PLAYER_RADIUS) / TILE_SIZE)][map_x] != 0)
		return false;
	if (data->map[(int)((y - PLAYER_RADIUS) / TILE_SIZE)][map_x] != 0)
		return false;
	return true;
}

void move_player(t_data *data, float move_x, float move_y)
{
	float	next_x;
	float	next_y;

	next_x = data->player->player_pos_x + move_x * data->player->move_speed; // ou MOVE_SPEED
	next_y = data->player->player_pos_y + move_y * data->player->move_speed; // ou MOVE_SPEED
	if (is_valid_position(data, next_x, next_y))
	{
		data->player->player_pos_x = next_x;
		data->player->player_pos_y = next_y;
	}
}
