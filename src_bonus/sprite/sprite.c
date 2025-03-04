/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashxo <nashxo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/03/03 13:42:40 by nashxo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void add_sprite(t_data *data, int map_x, int map_y)
{
	t_sprite	*new_sprites;
	t_sprite	*sprite;
	char		path[50];
	int			i;

	i = 0;
	new_sprites = realloc(data->sprites, sizeof(t_sprite) * (data->num_sprites + 1));
	if (!new_sprites)
		return_error("Malloc error for sprites", data, true);
	data->sprites = new_sprites;
	sprite = &data->sprites[data->num_sprites];
	sprite->x = (map_x + 0.5) * T_SIZE;
	sprite->y = (map_y + 0.5) * T_SIZE;
	sprite->current_frame = 0;
	sprite->total_frames = 10;
	sprite->frame_delay = 0.1;
	sprite->last_update = 0.0;
	sprite->frames = malloc(sizeof(mlx_texture_t *) * 10);
	if (!sprite->frames)
		return_error("Malloc error for sprite frames", data, true);
	while (i < 10)
	{
		snprintf(path, sizeof(path), "src_bonus/img/medaillon%d.png", i + 1);
		sprite->frames[i] = mlx_load_png(path);
		if (!sprite->frames[i])
			return_error("Failed to load sprite frame", data, true);
		i++;
	}
	data->num_sprites++;
}

void update_sprites(t_data *data)
{
	t_sprite	*sprite;
	double		current_time;
	int			i;

		i = 0;
	current_time = mlx_get_time();
	while (i < data->num_sprites)
	{
		sprite = &data->sprites[i];
		if (current_time - sprite->last_update >= sprite->frame_delay)
		{
			sprite->current_frame = (sprite->current_frame + 1) % sprite->total_frames;
			sprite->last_update = current_time;
		}
		i++;
	}
}

void render_single_sprite(t_data *data, t_sprite *sprite)
{
	double			sprite_x = sprite->x - data->player->pos_x;
	double			sprite_y = sprite->y - data->player->pos_y;
	double			inv_det = 1.0 / (data->player->plane_x * data->player->dir_y - data->player->dir_x * data->player->plane_y);
	double			transform_x = inv_det * (data->player->dir_y * sprite_x - data->player->dir_x * sprite_y);
	double			transform_y = inv_det * (-data->player->plane_y * sprite_x + data->player->plane_x * sprite_y);
	int				sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
	int				sprite_height = abs((int)(HEIGHT / transform_y) * 15);
	int				sprite_width = abs((int)(HEIGHT / transform_y) * 15);
	int				draw_start_x = -sprite_width / 2 + sprite_screen_x;
	int				draw_end_x = sprite_width / 2 + sprite_screen_x;
	int				draw_start_y = -sprite_height / 2 + (HEIGHT / 2 - 100);
	int				draw_end_y = sprite_height / 2 + (HEIGHT / 2 - 90);
	double			float_offset = sin(mlx_get_time() * 2.0) * 10;
	mlx_texture_t	*tex = sprite->frames[sprite->current_frame];

	if (draw_start_x < 0)
		draw_start_x = 0;
	if (draw_end_x >= WIDTH)
		draw_end_x = WIDTH - 1;
	draw_start_y += (int)float_offset;
	draw_end_y += (int)float_offset;
	for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
	{
		int tex_x = (int)((stripe - (-sprite_width / 2 + sprite_screen_x)) * tex->width / sprite_width);
		if (transform_y > 0 && stripe >= 0 && stripe < WIDTH)
		{
			for (int y = draw_start_y; y < draw_end_y; y++)
			{
				int d = (y - draw_start_y) * 256 - (draw_end_y - draw_start_y) * 128;
				int tex_y = ((d * tex->height) / (draw_end_y - draw_start_y)) / 256;
				if (tex_y < 0 || tex_y >= (int)tex->height)
					continue ;
				uint8_t *pixel = &tex->pixels[(tex_y * tex->width + tex_x) * 4];
				uint8_t a = pixel[3];
				if (a > 0)
				{
					uint32_t color = (a << 24) | (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
					my_put_pixel(data, stripe, y, color);
				}
			}
		}
	}
}

void render_sprites(t_data *data)
{
	int		*order;
	double	*dist;
	double	dx;
	double	dy;
	int		i;
	int		j;

	i = 0;
	order = malloc(data->num_sprites * sizeof(int));
	dist = malloc(data->num_sprites * sizeof(double));
	if (data->num_sprites == 0)
		return ;
	while (i < data->num_sprites)
	{
		order[i] = i;
		dx = data->sprites[i].x - data->player->pos_x;
		dy = data->sprites[i].y - data->player->pos_y;
		dist[i] = dx * dx + dy * dy;
		i++;
	}
	i = 0;
	while (i < data->num_sprites)
	{
		j = 0;
		while (j < data->num_sprites - i - 1)
		{
			if (dist[j] < dist[j + 1])
			{
				int temp_order = order[j];
				order[j] = order[j + 1];
				order[j + 1] = temp_order;
				double temp_dist = dist[j];
				dist[j] = dist[j + 1];
				dist[j + 1] = temp_dist;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < data->num_sprites)
	{
		render_single_sprite(data, &data->sprites[order[i]]);
		i++;
	}
	free(order);
	free(dist);
}

void	handle_sprites(t_data *data)
{
	t_sprite	*sprite;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < data->num_sprites)
	{
		sprite = &data->sprites[i];
		while (j < sprite->total_frames)
		{
			mlx_delete_texture(sprite->frames[j]);
			j++;
		}
		free(sprite->frames);
		i++;
	}
	free(data->sprites);
	free(data->z_buffer);
}
