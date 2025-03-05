/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/02/22 22:03:01 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	compare_position(t_player *player)
{
	static int		x = 0;
	static int		y = 0;
	static float	rotation_x = 0;
	static float	rotation_y = 0;

	if (player->pos_x == x && player->pos_y == y
		&& player->dir_x == rotation_x && player->dir_y == rotation_y)
		return (false);
	x = player->pos_x;
	y = player->pos_y;
	rotation_x = player->dir_x;
	rotation_y = player->dir_y;
	return (false);
}

void	render_frame(void *param)
{
	t_data	*data;
	double	current;

	data = (t_data *)param;
	current = mlx_get_time();
	data->delta_time = current - data->last_frame;
	data->last_frame = current;
	if (data->state == STATE_GAME)
	{
		process_keys(data);
		if (!compare_position(data->player))
		{
			mlx_clear_image(data);
			raycasting(data);
		}
	}
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
	{
		ft_fprintf(2, "Invalid number of arguments\n");
		return (0);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	init(data, av);
	mlx_key_hook(data->mlx, handle_keypress, data);
	mlx_loop_hook(data->mlx, (void (*)(void *))render_frame, data);
	mlx_loop(data->mlx);
	free_all(data);
}
