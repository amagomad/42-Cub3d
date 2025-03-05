/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 19:48:08 by cgorin           ###   ########.fr       */
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
	pixels[y * data->img_buffer->width + x] = color;
}

mlx_image_t	*mlx_load_image(t_data *data, char *path)
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	image = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		return (NULL);
	return (image);
}

void	mlx_clear_image(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < (int)data->img->height)
	{
		x = -1;
		while (++x < (int)data->img->width)
			my_put_pixel(data, x, y, 0xFF000000);
	}
}
