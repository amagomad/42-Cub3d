/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:25:16 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/17 02:56:32 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * Draws a rectangle on the screen.
 *
 * @param x The x-coordinate of the top-left corner of the rectangle.
 * @param y The y-coordinate of the top-left corner of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param color The color of the rectangle.
 */
void	draw_rect(t_data *data, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			my_put_pixel(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_wall(t_ray *ray)
{
	int		y;
	double	tex_pos;
	int		tex_y;
	int		pixel_pos;
	t_color	color;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_pos = (y - ((HEIGHT / 2 - 100) - ray->line_height / 2)) *
			(ray->texture->height / (float)ray->line_height);
		tex_y = (int)tex_pos % ray->texture->height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)ray->texture->height) 
			tex_y = ray->texture->height;
		if (ray->tex_x < 0)
			ray->tex_x = 0;
		if (ray->tex_x >= (int)ray->texture->width)
			ray->tex_x = ray->texture->width - 1;
		pixel_pos = (tex_y * ray->texture->width + ray->tex_x) * 4;
		color.r = ray->texture->pixels[pixel_pos + 0];
		color.g = ray->texture->pixels[pixel_pos + 1];
		color.b = ray->texture->pixels[pixel_pos + 2];
		color.a = ray->texture->pixels[pixel_pos + 3];
		color.abgr = (color.a << 24) | (color.b << 16)
			| (color.g << 8) | color.r;
		ray->pixel_buffer[y * WIDTH + ray->x] = color.abgr;
		y++;
	}
}
