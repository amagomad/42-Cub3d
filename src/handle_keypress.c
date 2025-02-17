/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:35:11 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/17 03:10:21 by cgorin           ###   ########.fr       */
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

void handle_mouse_move(double xpos, double ypos, void *param)
{
	t_data			*data;
	static double	last_x;

	last_x = -1;
	(void)ypos;
	data = (t_data *)param;
	if (data->state == STATE_MENU || data->state == STATE_PAUSE)
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

void	movement_key(mlx_key_data_t key, t_data *data)
{
	if (key.key == MLX_KEY_LEFT_SHIFT
		&& (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		data->player->move_speed = SPRINT_SPEED;
	else if (key.key == MLX_KEY_LEFT_SHIFT && key.action == MLX_RELEASE)
		data->player->move_speed = WALK_SPEED;
	if (key.key == MLX_KEY_LEFT
		&& (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		rotate_left(data, ROTATION_SPEED);
	else if (key.key == MLX_KEY_RIGHT
		&& (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		rotate_right(data, ROTATION_SPEED);
	if (key.key == MLX_KEY_W
		&& (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		move_player(data, data->player->dir_x, data->player->dir_y);
	else if (key.key == MLX_KEY_S
		&& (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		move_player(data, -data->player->dir_x, -data->player->dir_y);
	else if (key.key == MLX_KEY_D
		&& (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		move_player(data, -data->player->dir_y, data->player->dir_x);
	else if (key.key == MLX_KEY_A
		&& (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		move_player(data, data->player->dir_y, -data->player->dir_x);
}

void	menu_key(mlx_key_data_t key, t_data *data)
{
	if (data->state == STATE_MENU)
	{
		if (key.key == MLX_KEY_LEFT && key.action == MLX_PRESS)
		{
			data->selected_option--;
			if (data->selected_option < 0)
				data->selected_option = 1;
		}
		else if (key.key == MLX_KEY_RIGHT && key.action == MLX_PRESS)
		{
			data->selected_option++;
			if (data->selected_option > 1)
				data->selected_option = 0;
		}
		if (key.key == MLX_KEY_ENTER)
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
	if (data->state == STATE_PAUSE && key.key == MLX_KEY_P && key.action == MLX_PRESS)
		data->state = STATE_GAME;
	else if (data->state == STATE_GAME && key.key == MLX_KEY_P && key.action == MLX_PRESS)
		data->state = STATE_PAUSE;
}

void	handle_keypress(mlx_key_data_t key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key.key == MLX_KEY_LEFT_CONTROL && key.action == MLX_PRESS)
	{
		if (!data->mouse_shown)
		{
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
			data->mouse_shown = true;
		}
		else
		{
			data->mouse_shown = false;
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
		}
	}
	/* if (data->state == STATE_MENU)
	{
		if (key.key == MLX_KEY_LEFT && key.action == MLX_PRESS)
		{
			data->selected_option--;
			if (data->selected_option < 0)
				data->selected_option = 1;
		}
		else if (key.key == MLX_KEY_RIGHT && key.action == MLX_PRESS)
		{
			data->selected_option++;
			if (data->selected_option > 1)
				data->selected_option = 0;
		}
		if (key.key == MLX_KEY_ENTER)
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
	if (data->state == STATE_PAUSE && key.key == MLX_KEY_P && key.action == MLX_PRESS)
		data->state = STATE_GAME;
	else if (data->state == STATE_GAME && key.key == MLX_KEY_P && key.action == MLX_PRESS)
		data->state = STATE_PAUSE; */
	menu_key(key, data);
	if (key.key == MLX_KEY_ESCAPE && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		mlx_close_window(data->mlx);
	if (data->state == STATE_PAUSE || data->state == STATE_MENU)
		return ;
	if (key.key == MLX_KEY_SPACE && key.action == MLX_PRESS)
		data->show_minimap = !data->show_minimap;
	if (key.key == MLX_KEY_ESCAPE && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
	{
		mlx_close_window(data->mlx);
		return ;
	}
	if (key.key == MLX_KEY_KP_ADD && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
	{
		data->minimap_T_SIZE++;
		if (data->minimap_T_SIZE >= 40)
			data->minimap_T_SIZE = 40;
	}
	if (key.key == MLX_KEY_KP_SUBTRACT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
	{
		data->minimap_T_SIZE--;
		if (data->minimap_T_SIZE <= 1)
			data->minimap_T_SIZE = 1;
	}
	if (key.key == MLX_KEY_TAB && (key.action == MLX_REPEAT))
	{
		data->minimap_T_SIZE = 40;
		clear_image(data, 0x000000FF);
		draw_minimap(data);
	}
	if (key.key == MLX_KEY_TAB && key.action == MLX_RELEASE)
	{
		data->minimap_T_SIZE = MINIMAP_T_SIZE;
		clear_image(data, 0x000000FF);
		draw_minimap(data);
	}
	if (key.key == MLX_KEY_E && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		manage_door(data);
	movement_key(key, data);
}
