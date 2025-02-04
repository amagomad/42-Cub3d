/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/04 18:20:29 by cgorin           ###   ########.fr       */
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

void clear_image(mlx_image_t *image, uint32_t color)
{
	unsigned int x;
	unsigned int y;

	y = -1;
	while (++y < image->height)
	{
		x = -1;
		while (++x < image->width)
			mlx_put_pixel(image, x, y, color);
	}
}