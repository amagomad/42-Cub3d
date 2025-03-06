/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagomad <amagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 07:13:59 by amagomad          #+#    #+#             */
/*   Updated: 2025/03/06 07:37:35 by amagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	copy_sprites(t_data *data, t_sprite *new_array)
{
	int	i;

	i = 0;
	while (i < data->num_sprites)
	{
		new_array[i] = data->sprites[i];
		i += 1;
	}
}

static t_sprite	*allocate_sprite_array(t_data *data, int new_size)
{
	t_sprite	*new_array;

	new_array = malloc(sizeof(t_sprite) * new_size);
	if (new_array == NULL)
	{
		return_error("Malloc error for sprites", data, true);
		return ((t_sprite *) NULL);
	}
	copy_sprites(data, new_array);
	if (data->sprites != NULL)
		free(data->sprites);
	return (new_array);
}

static void	load_sprite_frames(t_data *data, t_sprite *sprite)
{
	int		i;
	char	path[50];

	i = 0;
	sprite->frames = malloc(sizeof(mlx_texture_t *) * 10);
	if (sprite->frames == NULL)
	{
		return_error("Malloc error for sprite frames", data, true);
		return ;
	}
	while (i < 10)
	{
		snprintf(path, sizeof(path), "src_bonus/img/medaillon%d.png", i + 1);
		sprite->frames[i] = mlx_load_png(path);
		if (sprite->frames[i] == NULL)
		{
			return_error("Failed to load sprite frame", data, true);
			return ;
		}
		i = i + 1;
	}
}

void	add_sprite(t_data *data, int map_x, int map_y)
{
	t_sprite	*new_array;
	int			new_size;
	t_sprite	*sprite;

	new_size = data->num_sprites + 1;
	new_array = allocate_sprite_array(data, new_size);
	if (new_array == NULL)
		return ;
	data->sprites = new_array;
	sprite = &data->sprites[data->num_sprites];
	sprite->x = (map_x + 0.5) * T_SIZE;
	sprite->y = (map_y + 0.5) * T_SIZE;
	sprite->current_frame = 0;
	sprite->total_frames = 10;
	sprite->frame_delay = 0.1;
	sprite->last_update = 0.0;
	load_sprite_frames(data, sprite);
	data->num_sprites = data->num_sprites + 1;
}
