/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:08:32 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 17:11:37 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_texture(t_data *data)
{
	data->no_texture = mlx_load_png(data->parse->no_texture);
	data->so_texture = mlx_load_png(data->parse->so_texture);
	data->ea_texture = mlx_load_png(data->parse->ea_texture);
	data->we_texture = mlx_load_png(data->parse->we_texture);
	data->door_texture = mlx_load_png("src_bonus/img/P.png");
	if (!data->no_texture || !data->so_texture
		|| !data->ea_texture || !data->we_texture || !data->door_texture)
		return_error("Can't load textures", data, true);
}
