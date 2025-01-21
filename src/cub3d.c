/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/01/21 00:49:58 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int ac, char **av)
{
	t_parsing		*parse;
	t_data			*data;
	mlx_texture_t	*icon;

	if (ac != 2)
		return_error("Invalid number of arguments");
	icon = mlx_load_png("src/img/icon.png");
	if (!icon)
		return_error("Can't load icon");
	parse = malloc(sizeof(t_parsing));
	data = malloc(sizeof(t_data));
	data->player = malloc(sizeof(t_player));
	if (!parse || !data)
		return_error("Malloc error");
	parse->description = NULL;
	parse->map = NULL;
	if (!parsing(av[1], parse, data))
		return_error("Parsing error");
	printf("Description:\n");
	for (int i = 0; parse->description[i]; i++)
		printf("%s\n", parse->description[i]);
	printf("Map:\n");
	for (int i = 0; parse->map[i]; i++)
		printf("%s\n", parse->map[i]);
	printf("Parsing done\n");
	//init_data(data);
	//if (!initialize_game(data, parse))
	//	return_error("Can't initialize game");
	//mlx_set_icon(data->mlx, icon);
	//mlx_key_hook(data->mlx, handle_keypress, data);
	//mlx_loop(data->mlx);
}