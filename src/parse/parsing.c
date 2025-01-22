/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:30:06 by amagomad          #+#    #+#             */
/*   Updated: 2025/01/22 17:50:31 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	stock_map(t_parsing *parse)
{
	char	*line;
	int		max_width;
	int		height;

	height = 0;
	max_width = 0;
	while (1)
	{
		line = get_next_line(parse->file_fd);
		if (!line)
			break ;
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
        	line[ft_strlen(line) - 1] = '\0';
		if (max_width < (int)ft_strlen(line))
			max_width = ft_strlen(line);
		if (ft_strlen(line) < max_width)
			continue ;
		parse->map = ft_add_str_tab(parse->map, line);
		if (!parse->map)
			return (false);
		height++;
	}
	parse->map_width = max_width;
	parse->map_height = height;
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

	data->icon = mlx_load_png("src/img/icon.png");
	if (!(texture[0] = mlx_load_png(parse->no_texture)) || 
		!(texture[1] = mlx_load_png(parse->so_texture)) ||
		!(texture[2] = mlx_load_png(parse->ea_texture)) ||
		!(texture[3] = mlx_load_png(parse->we_texture)))
		return (false);
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

bool	transform_map(t_data *data)
{
	int		i;
	int		j;

	data->map = ft_calloc(sizeof(int), data->parse->map_height * data->parse->map_width);
	if (!data->map)
		return (false);
	i = -1;
	while (++i < data->parse->map_height)
	{
		j = -1;
		while (++j < data->parse->map_width)
		{
			if (data->parse->map[i][j] == '1')
				data->map[i * data->parse->map_width + j] = 1;
			else if (data->parse->map[i][j] == ' ')
				data->map[i * data->parse->map_width + j] = 2;
			else if (data->parse->map[i][j] == '0')
				data->map[i * data->parse->map_width + j] = 0;
			else if (ft_strchr("NSWE", data->parse->map[i][j]))
				data->map[i * data->parse->map_width + j] = 0;
			printf("parse -> %c ", data->parse->map[i][j]);
			printf("map -> %d\n", data->map[i * data->parse->map_width + j]);
		}
	}
	return (true);
}

void	print_map_str(t_data *data)
{
	int	i;

	i = 0;
	printf("map_width = %d\n", data->parse->map_width);
	printf("map_height = %d\n", data->parse->map_height);
	while (i < data->parse->map_height)
	{
		printf("%s\n", data->parse->map[i]);
		i++;
	}
	printf("\n");
}

void print_map(t_data *data)
{
    int row, col;

    printf("map\n");
    printf("map_width = %d\n", data->parse->map_width);
    printf("map_height = %d\n", data->parse->map_height);

    for (row = 0; row < data->parse->map_height; row++)
    {
        for (col = 0; col < data->parse->map_width; col++)
        {
            int idx = row * data->parse->map_width + col;
            printf("%d", data->map[idx]);
        }
        printf("\n");
    }
}


bool	parsing(char *file, t_data *data)
{
	if (!file_validity(file))
		return_error("Invalid file");
	if (!open_file(file, data->parse))
		return_error("Can't open file");
	if (!stock_description(data->parse))
		return_error("Invalid description");
	if (!validity_description(data->parse))
		return_error("Invalid description");
	//if (!load_texture(data, parse))
	//	exit(1);
	if (!stock_map(data->parse))
		return_error("Invalid map");
	if (!validity_map(data->parse->map))
		return_error("Invalid map");
	if (!transform_map(data))
		return_error("Invalid map");
	print_map_str(data);
	print_map(data);
	return (true);
}