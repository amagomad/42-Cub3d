/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 20:31:31 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_menu(t_data *data)
{
	data->state = STATE_MENU;
	data->selected_option = 0;
	data->img_menu[0] = mlx_load_image(data, "img/menu_start.png");
	if (!data->img_menu[0])
		return_error("Can't load menu image", data, false);
	data->img_menu[1] = mlx_load_image(data, "img/menu_quit.png");
	if (!data->img_menu[1])
		return_error("Can't load menu image", data, false);
}

void	draw_menu(t_data *data)
{
	menu_key(data);
	mlx_image_to_window(data->mlx, data->img_menu[0], 0, 0);
	mlx_image_to_window(data->mlx, data->img_menu[1], 0, 0);
	if (data->selected_option == 0)
	{
		data->img_menu[0]->enabled = true;
		data->img_menu[1]->enabled = false;
	}
	else
	{
		data->img_menu[0]->enabled = false;
		data->img_menu[1]->enabled = true;
	}
}
