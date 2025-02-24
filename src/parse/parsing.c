/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 21:15:12 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

bool	parsing(char *file, t_data *data)
{
	if (!file_validity(file))
		return_error("Invalid file extension", data, true);
	if (!open_file(file, data->parse))
		return_error("Can't open file", data, true);
	if (!stock_desc(data->parse))
		return_error("Failed to stock desc, invalid format.", data, true);
	if (!validity_desc(data->parse))
		return_error("Invalid desc", data, true);
	load_texture(data);
	valid_color(data->parse, data);
	stock_map(data);
	validity_map(data);
	transform_map(data);
	validity_map_wall(data);
	set_player_starting_direction(data);
	free_parsing(data);
	return (true);
}
