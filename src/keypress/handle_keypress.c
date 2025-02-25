/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:35:11 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/23 18:01:59 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	process_keys(t_data *data)
{
	movement_key(data);
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
