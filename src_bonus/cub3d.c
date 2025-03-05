/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashxo <nashxo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/03/02 22:33:20 by nashxo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_frame(void *param)
{
	t_data	*data;
	double	current;

	data = (t_data *)param;
	current = mlx_get_time();
	data->delta_time = current - data->last_frame;
	data->last_frame = current;
	if (data->mouse_shown)
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
	else
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	if (data->state == STATE_GAME)
	{
		process_keys(data);
		raycasting(data);
		update_sprites(data);
		render_sprites(data);
		if (data->show_minimap)
			draw_minimap(data);
	}
	else if (data->state == STATE_MENU)
		draw_menu(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
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
	mlx_cursor_hook(data.mlx, handle_mouse_move, &data);
	mlx_loop_hook(data.mlx, (void (*)(void *))render_frame, &data);
	mlx_loop(data.mlx);
	free_all(&data);
}
