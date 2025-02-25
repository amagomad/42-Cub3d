/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 18:42:01 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_line(t_data *data, t_minimap mini, uint32_t color)
{
	mini.err = mini.dx - mini.dy;
	while (mini.player_x != mini.end_x || mini.player_y != mini.end_y)
	{
		my_put_pixel(data, mini.player_x, mini.player_y, color);
		mini.e2 = mini.err * 2;
		if (mini.e2 > -mini.dy)
		{
			mini.err -= mini.dy;
			mini.player_x += mini.sx;
		}
		if (mini.e2 < mini.dx)
		{
			mini.err += mini.dx;
			mini.player_y += mini.sy;
		}
	}
}

void	draw_direction(t_data *data, t_minimap mini)
{
	mini.player_x = MAP_OFFSET_X + (data->player->pos_x / T_SIZE)
		* data->minimap_t_size + 0.5;
	mini.player_y = MAP_OFFSET_Y + (data->player->pos_y / T_SIZE)
		* data->minimap_t_size;
	mini.end_x = mini.player_x + data->player->dir_x * data->minimap_t_size;
	mini.end_y = mini.player_y + data->player->dir_y * data->minimap_t_size;
	mini.dx = abs(mini.end_x - mini.player_x);
	mini.dy = abs(mini.end_y - mini.player_y);
	if (mini.player_x < mini.end_x)
		mini.sx = 1;
	else
		mini.sx = -1;
	if (mini.player_y < mini.end_y)
		mini.sy = 1;
	else
		mini.sy = -1;
	draw_line(data, mini, RED);
}

void	draw_player(t_data *data, t_minimap mini)
{
	int	i;
	int	j;
	int	px;
	int	py;
	int	size_player;

	size_player = data->minimap_t_size / 3;
	px = MAP_OFFSET_X + (data->player->pos_x / T_SIZE * data->minimap_t_size);
	py = MAP_OFFSET_Y + (data->player->pos_y / T_SIZE * data->minimap_t_size);
	i = -size_player;
	while (++i <= size_player)
	{
		j = -size_player;
		while (++j <= size_player)
			my_put_pixel(data, px + i, py + j, BLUE);
	}
	draw_direction(data, mini);
}
