/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 21:15:12 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_data(t_data *data)
{
	if (data->parse)
	{
		free(data->parse->map);
		free(data->parse->desc);
		free(data->parse);
	}
	if (data->player)
		free(data->player);
	free(data);
}

void	free_map(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->map_height)
	{
		free(data->map[i]);
	}
	free(data->map);
}

void	free_texture(t_data *data)
{
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	if (data->img_menu[0] && data->img_menu[1])
	{
		mlx_delete_image(data->mlx, data->img_menu[0]);
		mlx_delete_image(data->mlx, data->img_menu[1]);
	}
	if (data->no_texture)
		mlx_delete_texture(data->no_texture);
	if (data->so_texture)
		mlx_delete_texture(data->so_texture);
	if (data->we_texture)
		mlx_delete_texture(data->we_texture);
	if (data->ea_texture)
		mlx_delete_texture(data->ea_texture);
	if (data->icon)
		mlx_delete_texture(data->icon);
	if (data->door_texture)
		mlx_delete_texture(data->door_texture);
}

void	free_parsing(t_data *data)
{
	if (data->parse->no_texture)
		free(data->parse->no_texture);
	if (data->parse->so_texture)
		free(data->parse->so_texture);
	if (data->parse->we_texture)
		free(data->parse->we_texture);
	if (data->parse->ea_texture)
		free(data->parse->ea_texture);
	if (data->parse->ceiling_color)
		free(data->parse->ceiling_color);
	if (data->parse->floor_color)
		free(data->parse->floor_color);
	if (data->parse->desc)
		ft_free_str_tab(data->parse->desc);
	if (data->parse->map)
		ft_free_str_tab(data->parse->map);
	if (data->parse->line)
		free(data->parse->line);
	if (data->parse->file_fd)
		close(data->parse->file_fd);
	if (data->parse)
		free(data->parse);
}

void	free_all(t_data *data)
{
	free(data->player);
	if (data->map)
		free_map(data);
	free_texture(data);
	if (data->mlx)
		mlx_close_window(data->mlx);
	if (data->mlx)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
	exit(EXIT_SUCCESS);
}
