/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:30:06 by amagomad          #+#    #+#             */
/*   Updated: 2025/01/21 18:32:20 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	stock_map(t_parsing *parse)
{
	char	*line;

	while (1)
	{
		line = get_next_line(parse->file_fd);
		if (!line)
			break ;
		parse->map = ft_add_str_tab(parse->map, line);
		if (!parse->map)
			return (false);
	}
	return (true);
}

bool	stock_description(t_parsing *parse)
{
	int		count;
	char	*line;
	
	line = ft_strdup(" ");
	count = 0;
	while (count < 6 && line)
	{
		line = get_next_line(parse->file_fd);
		while (ft_isspace(*line))
			line++;
		if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
		{
			parse->description = ft_add_str_tab(parse->description, line);
			if (!parse->description)
				return (false);
			count++;
			continue ;
		}
		else if (ft_isalnum(*line))
			return (false);
	}
	return (true);
}

void	delete_texture(mlx_texture_t **texture)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (texture[i])
			mlx_delete_texture(texture[i]);
}

void delete_png(mlx_texture_t **texture)
{
	if (texture[0])
		free(texture[0]);
	if (texture[1])
		free(texture[1]);
	if (texture[2])
		free(texture[2]);
	if (texture[3])
		free(texture[3]);
}

bool	load_texture(t_data *data, t_parsing *parse)
{
	mlx_texture_t	*texture[4];

	printf("load_texture\n");
	if (!(texture[0] = mlx_load_png(parse->no_texture)) || 
		!(texture[1] = mlx_load_png(parse->so_texture)) ||
		!(texture[2] = mlx_load_png(parse->ea_texture)) ||
		!(texture[3] = mlx_load_png(parse->we_texture)))
		return (false);
	printf("load_texture\n");
	if (!(data->no_texture = mlx_texture_to_image(data->mlx, texture[0])) ||
		!(data->so_texture = mlx_texture_to_image(data->mlx, texture[1])) ||
		!(data->ea_texture = mlx_texture_to_image(data->mlx, texture[2])) ||
		!(data->we_texture = mlx_texture_to_image(data->mlx, texture[3])))
	{
		delete_texture(texture);
		return (false);
	}
	delete_texture(texture);
	return (true);
}

bool	parsing(char *file, t_parsing *parse, t_data *data)
{
	(void)data;
	if (!file_validity(file))
		return_error("Invalid file");
	if (!open_file(file, parse))
		return_error("Can't open file");
	if (!stock_description(parse))
		return_error("Invalid description");
	if (!validity_description(parse))
		return_error("Invalid description");
	//if (!load_texture(data, parse))
	//	exit(1);
	if (!stock_map(parse))
		return_error("Invalid map");
	if (!validity_map(parse->map))
		return_error("Invalid map");
	return (true);
}