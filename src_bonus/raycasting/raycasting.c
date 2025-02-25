/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:14:22 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 17:48:12 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

void	raycasting(t_data *data)
{
	t_ray				ray;

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
		draw_wall(&ray);
		ray.x++;
	}
}
