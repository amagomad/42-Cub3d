/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:25:16 by cgorin            #+#    #+#             */
/*   Updated: 2025/03/13 17:00:59 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_rect(t_data *data, int x, int y, uint32_t color)
{
	int	i;
	int	*pixel;

	i = 0;
	pixel = (int *)data->img->pixels;
	while (i < WIDTH * HEIGHT)
	{
		if ((i % WIDTH >= x && i % WIDTH < x + WIDTH)
			&& (i / WIDTH >= y && i / WIDTH < y + HEIGHT))
			pixel[i] = color;
		i++;
	}
}

void	calcul_texture(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			ray->texture = data->ea_texture;
		else
			ray->texture = data->we_texture;
	}
	else
	{
		if (ray->dir_y > 0)
			ray->texture = data->so_texture;
		else
			ray->texture = data->no_texture;
	}
}

void	calcul_wall_x(t_ray *ray, t_data *data)
{
	float	wall_x;

	if (ray->side == 0)
		wall_x = data->player->pos_y / T_SIZE + ray->perp_wall_dist
			* ray->dir_y;
	else
		wall_x = data->player->pos_x / T_SIZE + ray->perp_wall_dist
			* ray->dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * (double)ray->texture->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
}

uint32_t	transform_color(t_ray *ray, int pixel_pos)
{
	t_color	color;

	color.r = ray->texture->pixels[pixel_pos + 0];
	color.g = ray->texture->pixels[pixel_pos + 1];
	color.b = ray->texture->pixels[pixel_pos + 2];
	color.a = ray->texture->pixels[pixel_pos + 3];
	color.abgr = (color.a << 24) | (color.b << 16)
		| (color.g << 8) | color.r;
	return (color.abgr);
}

void	draw_wall(t_ray *ray)
{
	int		y;
	double	tex_pos;
	int		tex_y;
	int		pixel_pos;

	y = ray->draw_start - 1;
	while (++y < ray->draw_end)
	{
		tex_pos = (y - ((HEIGHT / 2 - 100) - ray->line_height / 2))
			* (ray->texture->height / (float)ray->line_height);
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
		ray->pixel_buffer[y * WIDTH + ray->x] = transform_color(ray, pixel_pos);
	}
}
