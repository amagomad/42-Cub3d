/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/08 11:51:13 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_data(t_data *data)
{
	if (data->parse)
	{
		free(data->parse->map);
		free(data->parse->description);
		free(data->parse);
	}
	if (data->player)
		free(data->player);
	free(data);
}

void clear_image(t_data *data, uint32_t color)
{
	unsigned int x;
	unsigned int y;

	y = -1;
	while (++y < data->img->height)
	{
		x = -1;
		while (++x < data->img->width)
			my_put_pixel(data, x, y, color);
	}
}