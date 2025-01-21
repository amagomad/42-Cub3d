/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:57:58 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/21 00:35:20 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	validity_description(t_parsing *parse)
{
	int i;
	int j;

	if (parse->description == NULL)
		return (false);
	i = -1;
	while (parse->description[++i])
	{
		if (parse->description[i][0] == '\0')
			return (false);
		j = 0;
		if (ft_strrchr("NSEW", parse->description[i][j]) == NULL)
			j = 3;
		if (ft_strrchr("FC", parse->description[i][j]) == NULL)
			j = 2;
		while (ft_isspace(parse->description[i][j]))
			j++;
		if (ft_strncmp(parse->description[i], "NO", 2) == 0)
			parse->no_texture = ft_strdup(parse->description[i] + j);
		else if (ft_strncmp(parse->description[i], "SO", 2) == 0)
			parse->so_texture = ft_strdup(parse->description[i] + j);
		else if (ft_strncmp(parse->description[i], "WE", 2) == 0)
			parse->we_texture = ft_strdup(parse->description[i] + j);
		else if (ft_strncmp(parse->description[i], "EA", 2) == 0)
			parse->ea_texture = ft_strdup(parse->description[i] + j);
		else if (ft_strncmp(parse->description[i], "F", 1) == 0)
			parse->floor_color = ft_strdup(parse->description[i] + j);
		else if (ft_strncmp(parse->description[i], "C", 1) == 0)
			parse->ceiling_color = ft_strdup(parse->description[i] + j);
		else
			return (false);
	}
	if (parse->no_texture == NULL || parse->so_texture == NULL
		|| parse->we_texture == NULL || parse->ea_texture == NULL
		|| parse->floor_color == NULL || parse->ceiling_color == NULL)
		return (false);
	return (true);
}

bool validity_map(char **map)
{
	size_t i;
	size_t j;
	size_t start;

	if (map == NULL)
		return_error("No map");
	i = -1;
	start = 0;
	while (map[++i])
	{
		if (map[i][0] == '\0')
			return_error("Invalid map : empty line");
		j = -1;
		while (map[i][++j] && map[i][j] != '\n')
		{
			if (ft_strrchr("NSEW", map[i][j]))
				start++;
			else if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ')
				return_error("Invalid map : invalid character");
			while (ft_isspace(map[i][j]))
				j++;
			if (map[i][j] == '0' && (i == 0 || ft_isspace(map[i][j - 1])
				|| ft_isspace(map[i][j + 1]) || j == 0 || j == ft_strlen(map[i]) - 1))
				return_error("Invalid map : invalid wall");
		}
	}
	if (start == 0)
		return_error("Invalid map : no player");
	else if (start > 1)
		return_error("Invalid map : too many players");
	return (true);
}

bool	open_file(char *file, t_parsing *parse)
{
	parse->file_fd = open(file, O_RDONLY);
	if (parse->file_fd < 0)
		return (false);
	return (true);
}

bool	file_validity(char *file)
{
	size_t	file_name_len;

	file_name_len = ft_strlen(file);
	if (file_name_len <= 4 || ft_strcmp(&file[file_name_len - 4], ".cub"))
		return (false);
	return (true);
}
