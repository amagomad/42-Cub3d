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

#include "../includes/cub3d_bonus.h"

void	handle_mouse_move(double xpos, double ypos, void *param)
{
	t_data			*data;
	static double	last_x = -1;

	(void)ypos;
	data = (t_data *)param;
	if (data->state == STATE_MENU)
		return ;
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

void	menu_key(t_data *data)
{
	if (data->keys[MLX_KEY_LEFT])
		data->selected_option = 0;
	else if (data->keys[MLX_KEY_RIGHT])
		data->selected_option = 1;
	if (data->keys[MLX_KEY_ENTER])
	{
		if (data->selected_option == 0)
		{
			data->state = STATE_GAME;
			data->show_minimap = true;
		}
		else if (data->selected_option == 1)
			mlx_close_window(data->mlx);
	}
}

void	process_keys(t_data *data)
{
	movement_key(data);
	if (data->keys[MLX_KEY_KP_ADD])
		change_minimap_size(data, data->minimap_t_size + 1);
	if (data->keys[MLX_KEY_KP_SUBTRACT])
		change_minimap_size(data, data->minimap_t_size - 1);
	if (data->keys[MLX_KEY_TAB])
		data->minimap_t_size = 40;
	else if (!data->keys[MLX_KEY_TAB])
		data->minimap_t_size = T_SIZE / 4;
}

void	handle_keypress(mlx_key_data_t key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key.action == MLX_PRESS)
		data->keys[key.key] = true;
	else if (key.action == MLX_RELEASE)
		data->keys[key.key] = false;
	if (data->keys[MLX_KEY_LEFT_CONTROL])
		data->mouse_shown = !data->mouse_shown;
	if (data->state == STATE_MENU)
		return ;
	if (data->keys[MLX_KEY_ESCAPE])
		mlx_close_window(data->mlx);
	if (key.key == MLX_KEY_SPACE
		&& data->state == STATE_GAME && key.action == MLX_PRESS)
		data->show_minimap = !data->show_minimap;
	if (key.key == MLX_KEY_E && data->state == STATE_GAME
		&& key.action == MLX_PRESS)
		manage_door(data);
}
