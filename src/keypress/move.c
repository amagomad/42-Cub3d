/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 19:44:14 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate(t_data *data, double angle)
{
	double	c_ang;
	double	s_ang;
	double	old_d_x;
	double	old_p_x;

	c_ang = cos(angle);
	s_ang = sin(angle);
	old_d_x = data->player->dir_x;
	data->player->dir_x = old_d_x * c_ang - data->player->dir_y * s_ang;
	data->player->dir_y = old_d_x * s_ang + data->player->dir_y * c_ang;
	old_p_x = data->player->plane_x;
	data->player->plane_x = old_p_x * c_ang - data->player->plane_y * s_ang;
	data->player->plane_y = old_p_x * s_ang + data->player->plane_y * c_ang;
}

bool	is_valid_position(t_data *data, float x, float y)
{
	int	px;
	int	py;
	int	r;

	px = (int)(x / T_SIZE);
	py = (int)(y / T_SIZE);
	r = PLAYER_RADIUS / T_SIZE;
	return (px - r >= 0 && px + r < data->map_width
		&& py - r >= 0 && py + r < data->map_height
		&& data->map[py][px] == 0);
}

void	move_player(t_data *data, float dx, float dy, float p_speed)
{
	float	speed;
	float	new_x;
	float	new_y;

	speed = p_speed * data->delta_time;
	new_x = data->player->pos_x + dx * speed;
	new_y = data->player->pos_y + dy * speed;
	if (is_valid_position(data, new_x, new_y))
	{
		data->player->pos_x = new_x;
		data->player->pos_y = new_y;
	}
	else if (is_valid_position(data, data->player->pos_x + dx
			* data->player->move_speed, data->player->pos_y))
		data->player->pos_x += dx * data->player->move_speed;
	else if (is_valid_position(data, data->player->pos_x,
			data->player->pos_y + dy * data->player->move_speed))
		data->player->pos_y += dy * data->player->move_speed;
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
		move_speed = (data->player->move_speed * 1.5f);
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
		rotate(data, -ROTATION_SPEED * data->delta_time);
	if (data->keys[MLX_KEY_RIGHT])
		rotate(data, ROTATION_SPEED * data->delta_time);
}
