/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagomad <amagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/03/13 17:36:26 by amagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_right(t_data *data, double rotation_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player->dir_x;
	data->player->dir_x = data->player->dir_x * cos(rotation_speed)
		- data->player->dir_y * sin(rotation_speed);
	data->player->dir_y = old_dir_x * sin(rotation_speed)
		+ data->player->dir_y * cos(rotation_speed);
	old_plane_x = data->player->plane_x;
	data->player->plane_x = data->player->plane_x * cos(rotation_speed)
		- data->player->plane_y * sin(rotation_speed);
	data->player->plane_y = old_plane_x * sin(rotation_speed)
		+ data->player->plane_y * cos(rotation_speed);
}

void	rotate_left(t_data *data, double rotation_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player->dir_x;
	data->player->dir_x = data->player->dir_x * cos(-rotation_speed)
		- data->player->dir_y * sin(-rotation_speed);
	data->player->dir_y = old_dir_x * sin(-rotation_speed)
		+ data->player->dir_y * cos(-rotation_speed);
	old_plane_x = data->player->plane_x;
	data->player->plane_x = data->player->plane_x * cos(-rotation_speed)
		- data->player->plane_y * sin(-rotation_speed);
	data->player->plane_y = old_plane_x * sin(-rotation_speed)
		+ data->player->plane_y * cos(-rotation_speed);
}

bool	is_valid_position(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;

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
		return (false);
	return (true);
}

void	move_player(t_data *data, float move_x, float move_y, float move_speed)
{
	float	next_x;
	float	next_y;

	next_x = data->player->pos_x + move_x * move_speed;
	next_y = data->player->pos_y + move_y * move_speed;
	if (is_valid_position(data, next_x, next_y))
	{
		data->player->pos_x = next_x;
		data->player->pos_y = next_y;
	}
	else if (is_valid_position(data, data->player->pos_x + move_x
			* move_speed, data->player->pos_y))
		data->player->pos_x += move_x * move_speed;
	else if (is_valid_position(data, data->player->pos_x,
			data->player->pos_y + move_y * move_speed))
		data->player->pos_y += move_y * move_speed;
}

void	movement_key(t_data *data)
{
	float		move_speed;
	const float	moves[4][2] = {
	{data->player->dir_x, data->player->dir_y},
	{-data->player->dir_x, -data->player->dir_y},
	{data->player->dir_y, -data->player->dir_x},
	{-data->player->dir_y, data->player->dir_x}
	};

	if (data->keys[MLX_KEY_LEFT_SHIFT])
		move_speed = (data->player->move_speed * 2.5f);
	else
		move_speed = (data->player->move_speed * 1.0f);
	if (data->keys[MLX_KEY_W])
		move_player(data, moves[0][0], moves[0][1], move_speed);
	if (data->keys[MLX_KEY_S])
		move_player(data, moves[1][0], moves[1][1], move_speed);
	if (data->keys[MLX_KEY_A])
		move_player(data, moves[2][0], moves[2][1], move_speed);
	if (data->keys[MLX_KEY_D])
		move_player(data, moves[3][0], moves[3][1], move_speed);
	if (data->keys[MLX_KEY_LEFT])
		rotate_left(data, ROTATION_SPEED);
	if (data->keys[MLX_KEY_RIGHT])
		rotate_right(data, ROTATION_SPEED);
}
