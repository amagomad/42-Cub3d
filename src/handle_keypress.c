/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:35:11 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/29 13:25:17 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	// Movement step size
	//float move_step = 5.0;

	// Future position
	//float next_px, next_py;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(data->mlx);
			return ;
		}
		/* else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		{
			data->player->pa += 5;
			data->player->pa = FixAng(data->player->pa);
			data->player->pdx = cos(degToRad(data->player->pa));
			data->player->pdy = -sin(degToRad(data->player->pa));
		} else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		{
			data->player->pa -= 5;
			data->player->pa = FixAng(data->player->pa);
			data->player->pdx = cos(degToRad(data->player->pa));
			data->player->pdy = -sin(degToRad(data->player->pa));
		} else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		{
			// Calculate potential new position
			next_px = data->player->px + data->player->pdx * move_step;
			next_py = data->player->py + data->player->pdy * move_step;

			// Check for collision before moving
			if (data->map[(int)(next_py / mapS) * data->map_width + (int)(next_px / mapS)] == 0)
			{
				data->player->px = next_px;
				data->player->py = next_py;
				data->player_x = (int)(data->player->px / mapS);
				data->player_y = (int)(data->player->py / mapS);
			}
		}
		else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		{
			// Calculate potential new position
			next_px = data->player->px - data->player->pdx * move_step;
			next_py = data->player->py - data->player->pdy * move_step;

			// Check for collision before moving
			if (data->map[(int)(next_py / mapS) * data->map_width + (int)(next_px / mapS)] == 0)
			{
				data->player->px = next_px;
				data->player->py = next_py;
				data->player_x = (int)(data->player->px / mapS);
				data->player_y = (int)(data->player->py / mapS);
			}  
		}*/

		// Clear the screen and redraw the player
		//clear_image(data->img, 0x333333FF); // Clear the screen with my color (mac)
		//clear_image(data->img, 0x000000FF); // Clear the screen with black color
		//display_map(data);
		//drawPlayer2D(data);
		//drawRays2D(image, data);
	}
}