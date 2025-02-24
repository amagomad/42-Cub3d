/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/23 18:09:43 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_put_pixel(t_data *data, int x, int y, uint32_t color)
{
	uint32_t	*pixels;

	if (data->img == NULL || x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	if (data->img->pixels == NULL)
		return ;
	pixels = (uint32_t *)data->img->pixels;
	pixels[y * data->img->width + x] = color;
}
