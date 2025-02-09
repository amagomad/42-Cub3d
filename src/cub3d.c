/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashxo <nashxo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/02/09 21:11:01 by nashxo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_data(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return_error("Erreur d'allocation pour le joueur");
	data->player->player_pos_x = 350;
	data->player->player_pos_y = 400;
	data->player->player_angle = 90;
	data->player->player_dir_x = cos(degToRad(data->player->player_angle));
	data->player->player_dir_y = -sin(degToRad(data->player->player_angle));
	data->player->move_speed = 5;
	data->parse = malloc(sizeof(t_parsing));
	if (!data->parse)
		return_error("Erreur d'allocation pour le parsing");
	data->parse->map_height = 8;
	data->parse->map_width = 8;
	data->parse->map = malloc(sizeof(char*) * (data->parse->map_height + 1));
	data->parse->map[0] = ft_strdup("11111111");
	data->parse->map[1] = ft_strdup("10000001");
	data->parse->map[2] = ft_strdup("10000001");
	data->parse->map[3] = ft_strdup("10111001");
	data->parse->map[4] = ft_strdup("10000001");
	data->parse->map[5] = ft_strdup("10111001");
	data->parse->map[6] = ft_strdup("10000001");
	data->parse->map[7] = ft_strdup("11111111");
	data->parse->map[8] = NULL;
}

int main(void)
{
	t_data	data;
	int		win_width = WIDTH;
	int		win_height = HEIGHT;
	
	data.mlx = mlx_init(win_width, win_height, "MLX42 cub3d", true);
	if (!data.mlx)
	{
		printf("Erreur lors de l'initialisation de MLX42\n");
		return 1;
	}
	data.img = mlx_new_image(data.mlx, win_width, win_height);
	if (!data.img)
	{
		printf("Erreur lors de la création de l'image MLX42\n");
		return 1;
	}
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	init_data(&data);
	if (!transform_map(&data))
		return_error("Erreur lors de la transformation de la map");
	mlx_key_hook(data.mlx, key_hook, &data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	ft_free(&data);
	return 0;
}
