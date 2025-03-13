/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/03/13 17:38:42 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_frame(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->state == STATE_GAME)
	{
		mlx_clear_image(data);
		process_keys(data);
		raycasting(data);
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		ft_fprintf(2, "Invalid number of arguments\n");
		return (0);
	}
	init(&data, av);
	mlx_key_hook(data.mlx, handle_keypress, &data);
	mlx_loop_hook(data.mlx, (void (*)(void *))render_frame, &data);
	mlx_loop(data.mlx);
	free_all(&data);
}
