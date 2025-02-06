/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:35:11 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/06 04:42:00 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void handle_mouse_move(double xpos, double ypos, void *param)
{
	t_data *data;
	static double last_x = -1;
	double delta_x;
	double sensitivity;
	
	(void)ypos;
	data = (t_data *)param;
	if (last_x == -1) // Première détection de mouvement
	{
		last_x = xpos;
		return;
	}
	sensitivity = 0.01;  // Ajuste la sensibilité de la souris
	delta_x = xpos - last_x;
	last_x = xpos;
	// Appliquer la rotation en fonction du mouvement de la souris
	data->player->player_angle += delta_x * sensitivity;
}

void	movement_key(mlx_key_data_t key, t_data *data)
{
	if (key.key == MLX_KEY_LEFT_SHIFT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		data->player->move_speed = SPRINT_SPEED;
	else if (key.key == MLX_KEY_LEFT_SHIFT && key.action == MLX_RELEASE)
		data->player->move_speed = WALK_SPEED;
	if (key.key == MLX_KEY_LEFT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		rotate_player(data, 5);  // Rotation à gauche
	else if (key.key == MLX_KEY_RIGHT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		rotate_player(data, -5); // Rotation à droite
	if (key.key == MLX_KEY_W && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		move_player(data, data->player->player_dir_x, data->player->player_dir_y); // Avancer
	else if (key.key == MLX_KEY_S && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		move_player(data, -data->player->player_dir_x, -data->player->player_dir_y); // Reculer
	else if (key.key == MLX_KEY_A && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		move_player(data, -data->player->player_dir_y, data->player->player_dir_x); // Strafe gauche
	else if (key.key == MLX_KEY_D && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		move_player(data, data->player->player_dir_y, -data->player->player_dir_x); // Strafe droite
}

void	handle_keypress(mlx_key_data_t key, void *param)
{
	t_data	*data;
	int save_size;

	data = (t_data *)param;
	if (key.key == MLX_KEY_SPACE && key.action == MLX_PRESS)
		data->show_minimap = !data->show_minimap; // 🔹 Bascule l'affichage de la minimap
	if (key.key == MLX_KEY_ESCAPE && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
	{
		mlx_close_window(data->mlx);
		return ;
	}
	if (key.key == MLX_KEY_KP_ADD && key.action == MLX_PRESS)
	{
		data->minimap_tile_size++;
		if (data->minimap_tile_size >= 50)
			data->minimap_tile_size = 50;
	}
	if (key.key == MLX_KEY_KP_SUBTRACT && key.action == MLX_PRESS)
	{
		data->minimap_tile_size--;
		if (data->minimap_tile_size <= 1)
			data->minimap_tile_size = 1;
	}
	if (key.key == MLX_KEY_TAB && key.action == MLX_REPEAT)
	{
		printf("	🔹 BIG MAP MODE 🔹\n");
		save_size = data->minimap_tile_size;
		data->minimap_tile_size = 45;
		clear_image(data->img, 0x000000FF);
		draw_minimap(data);
		//render_frame(data);
		printf("	🔹 END BIG MAP MODE 🔹\n");
	}
	if (key.key == MLX_KEY_TAB && key.action == MLX_RELEASE)
	{
		printf("	🔹 NORMAL MAP MODE 🔹\n");
		data->minimap_tile_size = MINIMAP_TILE_SIZE;
		clear_image(data->img, 0x000000FF);
		draw_minimap(data);
		//render_frame(data);
		printf("	🔹 END NORMAL MAP MODE 🔹\n");
	}
	/* if (key.key == MLX_KEY_E && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		manage_door(data); */
	printf("key = %d\n", key.key);
	movement_key(key, data);
}
