/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:08:32 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/23 18:02:19 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	delete_texture(mlx_texture_t **texture)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (texture[i])
			mlx_delete_texture(texture[i]);
}

void	load_texture(t_data *data)
{
	data->no_texture = mlx_load_png(data->parse->no_texture);
	data->so_texture = mlx_load_png(data->parse->so_texture);
	data->ea_texture = mlx_load_png(data->parse->ea_texture);
	data->we_texture = mlx_load_png(data->parse->we_texture);
	if (!data->no_texture || !data->so_texture
		|| !data->ea_texture || !data->we_texture)
		return_error("Error: Can't load textures", data, true);
}
