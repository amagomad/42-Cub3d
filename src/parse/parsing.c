/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:30:06 by amagomad          #+#    #+#             */
/*   Updated: 2025/02/18 21:24:30 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	stock_description(t_parsing *parse)
{
	int		count;
	char	*line;

	line = ft_strdup(" ");
	count = 0;
	while (count < 6 && line)
	{
		free(line);
		line = get_next_line(parse->file_fd);
		if (!line)
			return (false);
		while (ft_isspace(*line))
			line++;
		if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
			|| ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
		{
			line[ft_strlen(line) - 1] = '\0';
			parse->description = ft_add_str_tab(parse->description, line);
			if (!parse->description)
				return (false);
			count++;
			continue ;
		}
		else if (ft_isalnum(*line))
		{
			free(line);
			return (false);
		}
	}
	if (line)
		free(line);
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

bool	load_texture(t_data *data)
{
	data->icon = mlx_load_png("src/img/icon.png");
	if (!data->icon)
	{
		printf("Erreur : Impossible de charger l'icone.\n");
		exit(EXIT_FAILURE);
	}
	data->no_texture = mlx_load_png(data->parse->no_texture);
	data->so_texture = mlx_load_png(data->parse->so_texture);
	data->ea_texture = mlx_load_png(data->parse->ea_texture);
	data->we_texture = mlx_load_png(data->parse->we_texture);
	data->door_texture = mlx_load_png("src/img/P.png");
	
	if (!data->no_texture || !data->so_texture
		|| !data->ea_texture || !data->we_texture || !data->door_texture)
	{
		printf("Erreur : Impossible de charger les textures.\n");
		exit(EXIT_FAILURE);
	}
	return (true);
}

void	print_map_str(t_data *data)
{
	int	i;

	i = 0;
	printf("map_width = %d\n", data->map_width);
	printf("map_height = %d\n", data->map_height);
	while (i < data->map_height)
	{
		printf("%s\n", data->parse->map[i]);
		i++;
	}
	printf("\n");
}

void	print_map(t_data *data)
{
	int	row;
	int	col;

	printf("map1\n");
	printf("map_height = %d\n", data->map_height);
	printf("map_width = %d\n", data->map_width);
	row = -1;
	while (++row < data->map_height)
	{
		col = -1;
		while (++col < data->map_width)
		{
			printf("%d", data->map[row][col]);
		}
		printf("\n");
	}
}

void	set_player_starting_direction(t_data *data)
{
	if (data->player_dir == 'N')
	{
		data->player->angle = 90;
		data->player->plane_x = PLANE_SIZE;
		data->player->plane_y = 0;
		data->player->dir_x = 0;
		data->player->dir_y = -1;
	}
	else if (data->player_dir == 'S')
	{
		data->player->angle = 270;
		data->player->plane_x = -PLANE_SIZE;
		data->player->plane_y = 0;
		data->player->dir_x = 0;
		data->player->dir_y = 1;
	}
	else if (data->player_dir == 'W')
	{
		data->player->angle = 0;
		data->player->plane_x = 0;
		data->player->plane_y = -PLANE_SIZE;
		data->player->dir_x = -1;
		data->player->dir_y = 0;
	}
	else if (data->player->angle == 'E')
	{
		data->player->angle = 180;
		data->player->plane_x = 0;
		data->player->plane_y = PLANE_SIZE;
		data->player->dir_x = 1;
		data->player->dir_y = 0;
	}
	data->player->pos_x = (data->player_x + 0.5) * T_SIZE;
	data->player->pos_y = (data->player_y + 0.5) * T_SIZE;
}

bool	parsing(char *file, t_data *data)
{
	if (!file_validity(file))
		return_error("Invalid file extension", data);
	if (!open_file(file, data->parse))
		return_error("Can't open file", data);
	if (!stock_description(data->parse))
		return_error("Failed to stock description due to invalid format.", data);
	if (!validity_description(data->parse))
		return_error("Invalid description", data);
	if (!load_texture(data))
		return_error("Can't load texture", data);
	if (!valid_color(data->parse, data))
		return_error("Invalid color", data);
	printf("Floor color: 0x%08X\n", data->floor_color);
	printf("Ceiling color: 0x%08X\n", data->ceiling_color);
	if (!stock_map(data))
		return_error("No map", data);
	if (!validity_map(data))
		return_error("Invalid map", data);
	if (!transform_map(data))
		return_error("Invalid map", data);
	if (!validity_map_wall(data))
		return_error("Invalid map", data);
	set_player_starting_direction(data);
	return (true);
}
