/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:35:11 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 22:01:11 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_mouse_move(double xpos, double ypos, void *param)
{
	t_data			*data;
	static double	last_x = -1;

	(void)ypos;
	data = (t_data *)param;
	if (last_x == -1)
	{
		last_x = xpos;
		return ;
	}
	if (last_x < xpos)
		rotate_right(data, MOUSE_SENSITIVITY);
	else if (last_x > xpos)
		rotate_left(data, MOUSE_SENSITIVITY);
	last_x = xpos;
}

void	handle_keypress(mlx_key_data_t key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key.action == MLX_PRESS)
		data->keys[key.key] = true;
	else if (key.action == MLX_RELEASE)
		data->keys[key.key] = false;
	if (data->keys[MLX_KEY_ESCAPE])
		mlx_close_window(data->mlx);
}
