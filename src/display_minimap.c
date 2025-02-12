/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/12 15:42:29 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void my_put_pixel(t_data *data, int x, int y, uint32_t color)
{
    uint32_t *pixels;
    
    // Bounds checking
    if (data->img == NULL || x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    if (data->img->pixels == NULL)
        return;

    // Get the pixel array as uint32_t*
    pixels = (uint32_t *)data->img->pixels;
    
    // Calculate the offset directly (no need to multiply by sizeof)
    pixels[y * data->img->width + x] = color;
}

void	draw_player(t_data *data)
{
	int	i;
	int	j;
	int	px;
	int	py;

	px = MAP_OFFSET_X + (int)(data->player->player_pos_x / TILE_SIZE * data->minimap_tile_size);
	py = MAP_OFFSET_Y + (int)(data->player->player_pos_y / TILE_SIZE * data->minimap_tile_size);
	i = -2;
	while (++i <= 2)
	{
		j = -2;
		while (++j <= 2)
			my_put_pixel(data, px + i, py + j, BLUE);
	}
}

void	draw_line(t_data *data, int x1, int y1, int x2, int y2, uint32_t color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	if (x1 < x2)
		sx = 1;
	else
		sx = -1;
	if (y1 < y2)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (x1 != x2 || y1 != y2)
	{
		my_put_pixel(data, x1, y1, color);
		e2 = err * 2;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	draw_direction(t_data *data)
{
	float	player_x;
	float	player_y;
	float	end_x;
	float	end_y;

	player_x = MAP_OFFSET_X + (data->player->player_pos_x / TILE_SIZE)
		* data->minimap_tile_size + 0.5;
	player_y = MAP_OFFSET_Y + (data->player->player_pos_y / TILE_SIZE)
		* data->minimap_tile_size;
	end_x = player_x + data->player->player_dir_x * data->minimap_tile_size;
	end_y = player_y + data->player->player_dir_y * data->minimap_tile_size;
	draw_line(data, (int)player_x, (int)player_y, (int)end_x, (int)end_y,
		RED);
}

void	draw_minimap_border(t_data *data, t_minimap mini)
{
	int	x;
	int	y;

	x = -4;
	while (++x <= mini.map_width_px + 2)
	{
		my_put_pixel(data, MAP_OFFSET_X + x, MAP_OFFSET_Y - 3, MINIMAP_BORDER_COLOR);
		my_put_pixel(data, MAP_OFFSET_X + x, MAP_OFFSET_Y + mini.map_height_px + 2, MINIMAP_BORDER_COLOR);
	}
	y = -4;
	while (++y <= mini.map_height_px + 2)
	{
		my_put_pixel(data, MAP_OFFSET_X - 3, MAP_OFFSET_Y + y, MINIMAP_BORDER_COLOR);
		my_put_pixel(data, MAP_OFFSET_X + mini.map_width_px + 2, MAP_OFFSET_Y + y, MINIMAP_BORDER_COLOR);
	}
	x = -2;
	while (++x <= mini.map_width_px)
	{
		my_put_pixel(data, MAP_OFFSET_X + x, MAP_OFFSET_Y - 1, MINIMAP_INNER_BORDER_COLOR);
		my_put_pixel(data, MAP_OFFSET_X + x, MAP_OFFSET_Y + mini.map_height_px, MINIMAP_INNER_BORDER_COLOR);
	}
	y = -2;
	while (++y <= mini.map_height_px)
	{
		my_put_pixel(data, MAP_OFFSET_X - 1, MAP_OFFSET_Y + y, MINIMAP_INNER_BORDER_COLOR);
		my_put_pixel(data, MAP_OFFSET_X + mini.map_width_px, MAP_OFFSET_Y + y, MINIMAP_INNER_BORDER_COLOR);
	}
}

void draw_minimap_background(t_data *data, t_minimap mini)
{
	int y;
	int x;

	y = -5;
	while (++y <= mini.map_height_px + 4)
	{
		x = -5;
		while (++x <= mini.map_width_px + 4)
		{
			if (MAP_OFFSET_X + x <= WIDTH && MAP_OFFSET_Y + y <= HEIGHT)
				my_put_pixel(data, MAP_OFFSET_X + x,
				MAP_OFFSET_Y + y, MINIMAP_BG_COLOR);  // Fond transparent ou noir
		}
	}
}

uint32_t	get_minimap_color(int tile)
{
	if (tile == 1)
		return (GREY); // Mur (Gris)
	if (tile == 0)
		return (BLACK); // Sol (Noir)
	if (tile == 2)
		return (YELLOW); // Porte (Jaune)
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
			while (++i < data->minimap_tile_size)
			{
				j = -1;
				while (++j < data->minimap_tile_size)
					my_put_pixel(data, MAP_OFFSET_X + x
						* data->minimap_tile_size + i, MAP_OFFSET_Y + y
						* data->minimap_tile_size + j, color);
			}
		}
	}
}

void	draw_minimap(t_data *data)
{
	t_minimap	minimap;

	minimap.map_width_px = data->map_width * data->minimap_tile_size;
	minimap.map_height_px = data->map_height * data->minimap_tile_size;
	draw_minimap_background(data, minimap);
	draw_minimap_interior(data);
	draw_minimap_border(data, minimap);
	draw_direction(data);
	draw_player(data);
}
