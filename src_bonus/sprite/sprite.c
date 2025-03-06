/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagomad <amagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/03/06 07:31:13 by amagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_sprites(t_data *data)
{
	t_sprite	*sprite;
	double		current_time;
	int			i;

	i = 0;
	current_time = mlx_get_time();
	while (i < data->num_sprites)
	{
		sprite = &data->sprites[i];
		if ((current_time - sprite->last_update) >= sprite->frame_delay)
		{
			sprite->current_frame = (sprite->current_frame + 1) \
				% sprite->total_frames;
			sprite->last_update = current_time;
		}
		i = i + 1;
	}
}

static void	sort_sprites(int *order, double *dist, int count)
{
	int		i;
	int		j;
	int		temp_order;
	double	temp_dist;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (dist[j] < dist[j + 1])
			{
				temp_order = order[j];
				order[j] = order[j + 1];
				order[j + 1] = temp_order;
				temp_dist = dist[j];
				dist[j] = dist[j + 1];
				dist[j + 1] = temp_dist;
			}
			j = j + 1;
		}
		i = i + 1;
	}
}

static void	fill_order_and_dist(t_data *data, int count, \
								int *order, double *dist)
{
	int	i;

	i = 0;
	while (i < count)
	{
		order[i] = i;
		dist[i] = (data->sprites[i].x - data->player->pos_x) * \
					(data->sprites[i].x - data->player->pos_x) + \
					(data->sprites[i].y - data->player->pos_y) * \
					(data->sprites[i].y - data->player->pos_y);
		i = i + 1;
	}
}

void	render_sprites(t_data *data)
{
	int		*order;
	double	*dist;
	int		count;
	int		i;

	count = data->num_sprites;
	if (count == 0)
		return ;
	order = malloc(count * sizeof(int));
	dist = malloc(count * sizeof(double));
	fill_order_and_dist(data, count, order, dist);
	sort_sprites(order, dist, count);
	i = 0;
	while (i < count)
	{
		render_single_sprite(data, &data->sprites[order[i]]);
		i = i + 1;
	}
	free(order);
	free(dist);
}
