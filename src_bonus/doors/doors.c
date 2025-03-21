/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashxo <nashxo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/03/03 13:26:05 by nashxo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	manage_door_state(t_data *data, int x, int y)
{
	if (data->map[y][x] == 2)
		data->map[y][x] = 0;
	else if (data->map[y][x] == 0 && data->parse->map[y][x] == 'D')
		data->map[y][x] = 2;
}

void	manage_door(t_data *data)
{
	int	px;
	int	py;

	px = (int)(data->player->pos_x / T_SIZE);
	py = (int)(data->player->pos_y / T_SIZE);
	manage_door_state(data, px + 1, py);
	manage_door_state(data, px - 1, py);
	manage_door_state(data, px, py + 1);
	manage_door_state(data, px, py - 1);
}
