/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagomad <amagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 07:14:23 by amagomad          #+#    #+#             */
/*   Updated: 2025/03/06 07:37:13 by amagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	compute_vertical_bounds(t_proj *proj)
{
	int		start_y;
	int		end_y;
	int		offset;

	start_y = -proj->sprite_height / 2 + (HEIGHT / 2 - 100);
	if (start_y < 0)
	{
		start_y = 0;
	}
	end_y = proj->sprite_height / 2 + (HEIGHT / 2 - 100);
	if (end_y >= HEIGHT)
	{
		end_y = HEIGHT - 1;
	}
	offset = (int)(sin(mlx_get_time() * 2.0) * 10);
	proj->draw_start_y = start_y + offset;
	proj->draw_end_y = end_y + offset;
}

static void	compute_horizontal_bounds(t_proj *proj)
{
	int		width;
	int		start_x;
	int		end_x;

	width = abs((int)(HEIGHT / proj->transform_y));
	proj->sprite_width = width;
	start_x = -width / 2 + proj->sprite_screen_x;
	if (start_x < 0)
	{
		start_x = 0;
	}
	end_x = width / 2 + proj->sprite_screen_x;
	if (end_x >= WIDTH)
	{
		end_x = WIDTH - 1;
	}
	proj->draw_start_x = start_x;
	proj->draw_end_x = end_x;
}

static void	compute_sprite_transform(t_data *data, t_sprite *sprite, \
			t_proj *proj)
{
	double	sp_x;
	double	sp_y;
	double	inv_det;

	sp_x = ((double)sprite->x - data->player->pos_x) / T_SIZE;
	sp_y = ((double)sprite->y - data->player->pos_y) / T_SIZE;
	inv_det = 1.0 / (data->player->plane_x * data->player->dir_y - \
					data->player->dir_x * data->player->plane_y);
	proj->transform_x = inv_det * (data->player->dir_y * sp_x - \
									data->player->dir_x * sp_y);
	proj->transform_y = inv_det * (-data->player->plane_y * sp_x + \
									data->player->plane_x * sp_y);
	proj->sprite_screen_x = (int)((WIDTH / 2) * (1 + proj->transform_x / \
								proj->transform_y));
	proj->sprite_height = abs((int)(HEIGHT / proj->transform_y) / 3);
}

static void	calc_sprite_projection(t_data *data, t_sprite *sprite, t_proj *proj)
{
	compute_sprite_transform(data, sprite, proj);
	compute_vertical_bounds(proj);
	compute_horizontal_bounds(proj);
}

void	render_single_sprite(t_data *data, t_sprite *sprite)
{
	t_proj			proj;
	mlx_texture_t	*tex;
	int				stripe;

	calc_sprite_projection(data, sprite, &proj);
	tex = sprite->frames[sprite->current_frame];
	stripe = proj.draw_start_x;
	while (stripe < proj.draw_end_x)
	{
		if (proj.transform_y > 0)
		{
			if (stripe >= 0)
			{
				if (stripe < WIDTH)
				{
					if (proj.transform_y < data->z_buffer[stripe])
						draw_sprite_stripe(data, stripe, &proj, tex);
				}
			}
		}
		stripe = stripe + 1;
	}
}
