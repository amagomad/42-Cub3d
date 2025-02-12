/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:14:22 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/12 23:05:48 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calcul_ray_pos(t_ray *ray, t_data *data)
{
	ray->camera_x = 2 * ray->x / (double)WIDTH - 1;
	ray->dir_x = data->player->dir_x + data->player->plane_x * ray->camera_x;
	ray->dir_y = data->player->dir_y + data->player->plane_y * ray->camera_x;
	ray->map_x = (int)floor(data->player->pos_x / T_SIZE);
	ray->map_y = (int)floor(data->player->pos_y / T_SIZE);
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

void	calcul_initial_side_dist(t_ray *ray, t_data *data)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player->pos_x / T_SIZE - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player->pos_x
				/ T_SIZE) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player->pos_y / T_SIZE - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player->pos_y
				/ T_SIZE) * ray->delta_dist_y;
	}
}

void	dda(t_ray *ray, t_data *data)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map[ray->map_y][ray->map_x] > 0)
			ray->hit = 1;
	}
}

void	calcul_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = (-(ray->line_height) / 2) + (HEIGHT / 2 - 100);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (HEIGHT / 2 - 100);
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	calcul_texture(t_ray *ray, t_data *data)
{
	if (data->map[ray->map_y][ray->map_x] == 2)
		ray->texture = data->door_texture;
	else if (ray->side == 0)
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

void	print_wall(t_ray *ray)
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

void	raycasting(t_data *data)
{
	t_ray	ray;

	ray.pixel_buffer = (uint32_t *)data->img->pixels;
	ray.x = 0;
	draw_rect(data, 0, 0, data->ceiling_color);
	draw_rect(data, 0, 450, data->floor_color);
	while (ray.x < WIDTH)
	{
		calcul_ray_pos(&ray, data);
		calcul_initial_side_dist(&ray, data);
		dda(&ray, data);
		calcul_wall_distance(&ray);
		calcul_texture(&ray, data);
		calcul_wall_x(&ray, data);
		print_wall(&ray);
		ray.x++;
	}
}

//For flat_color
/*int y = draw_start;
// Inside your raycasting loop, replace the color part with:
	uint32_t color;
if (data->map[ray.map_y][ray.map_x] == 2)
	color = YELLOWY;  // Yellow
else if (side == 0)  // East-West walls (vertical walls)
{
	if (ray.dir_x > 0)  // East facing
		color = REDY;  // Red
	else                // West facing
		color = GREENY;  // Green
}
else  // North-South walls (horizontal walls)
{
	if (ray.dir_y > 0)  // North facing
		color = PINKY;  // Yellow
	else                // South facing
		color = BLUEY;  // Blue
}

// Then use this color in your drawing loop:
while (y <= draw_end)
{
	my_put_pixel(data, ray.x, y, color);
	y++;
}
ray.x++; */