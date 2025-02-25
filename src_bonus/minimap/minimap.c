/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 19:39:01 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_minimap_background(t_data *data, t_minimap mini)
{
	int	y;
	int	x;

	y = -5;
	while (++y <= mini.map_height_px + 4)
	{
		x = -5;
		while (++x <= mini.map_width_px + 4)
		{
			if (MAP_OFFSET_X + x <= WIDTH && MAP_OFFSET_Y + y <= HEIGHT)
				my_put_pixel(data, MAP_OFFSET_X + x, MAP_OFFSET_Y + y, WHITE);
		}
	}
}

uint32_t	get_minimap_color(int tile)
{
	if (tile == 1)
		return (GREY);
	if (tile == 0)
		return (BLACK);
	if (tile == 2)
		return (GREENY);
	if (tile >= 3)
		return (LIGHT_GREY);
	else
		return (GREY);
}

void	draw_minimap_interior(t_data *data)
{
	int			x;
	int			y;
	int			i;
	int			j;
	uint32_t	color;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			color = get_minimap_color(data->map[y][x]);
			i = -1;
			while (++i < data->minimap_t_size)
			{
				j = -1;
				while (++j < data->minimap_t_size)
					my_put_pixel(data, MAP_OFFSET_X + x
						* data->minimap_t_size + i, MAP_OFFSET_Y + y
						* data->minimap_t_size + j, color);
			}
		}
	}
}

void	change_minimap_size(t_data *data, int size)
{
	if (size < 1)
		data->minimap_t_size = 1;
	else if (size > 40)
		data->minimap_t_size = 40;
	else
		data->minimap_t_size = size;
}

void	draw_minimap(t_data *data)
{
	t_minimap	minimap;

	minimap.map_width_px = data->map_width * data->minimap_t_size;
	minimap.map_height_px = data->map_height * data->minimap_t_size;
	draw_minimap_background(data, minimap);
	draw_minimap_interior(data);
	draw_player(data, minimap);
}
