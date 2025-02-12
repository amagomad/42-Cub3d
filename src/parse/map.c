/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/12 23:01:23 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	stock_map(t_data *data)
{
	char	*line;
	int		max_width;
	int		height;

	height = 0;
	max_width = 0;
	line = ft_strdup("");
	while (line)
	{
		free(line);
		line = get_next_line(data->parse->file_fd);
		if (!line)
			break ;
		if (data->parse->map == NULL && line[0] == '\n')
			continue ;
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (max_width < (int)ft_strlen(line))
			max_width = ft_strlen(line);
		data->parse->map = ft_add_str_tab(data->parse->map, line);
		if (!data->parse->map)
			return (false);
		height++;
	}
	if (data->parse->map == NULL)
		return (false);
	data->map_width = max_width;
	data->map_height = height;
	return (true);
}

bool	validity_map_wall(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map_height)
	{
		j = -1;
		while (++j < data->map_width)
		{
			if (data->map[i][j] == 0 || data->map[i][j] == 2)
			{
				if (i > 0 && data->map[i - 1][j] == 4)
					return_error("Invalid map: `0` in contact with `4` first line");
				else if (i < data->map_height - 1 && data->map[i + 1][j] == 4)
					return_error("Invalid map: `0` in contact with `4` last line");
				else if (j > 0 && data->map[i][j - 1] == 4)
					return_error("Invalid map: `0` in contact with `4`");
				else if (j < data->map_width - 1 && data->map[i][j + 1] == 4)
					return_error("Invalid map: `0` in contact with `4`");
			}
		}
	}
	printf("Map is valid\n");
	return (true);
}

bool	transform_map(t_data *data)
{
	int	i;
	int	j;

	data->map = malloc(sizeof(int *) * data->map_height);
	if (!data->map)
		return (false);
	i = -1;
	while (++i < data->map_height)
	{
		data->map[i] = malloc(sizeof(int) * (data->map_width + 1));
		j = -1;
		while (++j < data->map_width)
		{
			if (j >= (int)ft_strlen(data->parse->map[i]) || ft_isspace(data->parse->map[i][j]))
			{
				data->map[i][j] = 4;
			}
			else if (data->parse->map[i][j] == '1')
				data->map[i][j] = 1;
			else if (data->parse->map[i][j] == '0')
				data->map[i][j] = 0;
			else if (ft_strchr("NSWE", data->parse->map[i][j]))
			{
				data->map[i][j] = 0;
				data->player_x = j;
				data->player_y = i;
				data->player_dir = data->parse->map[i][j];
			}
			else if (data->parse->map[i][j] == 'D') // 'D' pour les portes
				data->map[i][j] = 2;
			else if (data->parse->map[i][j] == 'O') // 'O' pour une porte ouverte
				data->map[i][j] = 0;
		}
		data->map[i][j] = -1;
	}
	return (true);
}

bool	validity_map(char **map)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = -1;
	start = 0;
	while (map[++i])
	{
		if (map[i][0] == '\0')
			return_error("Invalid map : empty line");
		j = -1;
		while (map[i][++j] && map[i][j] != '\n')
		{
			while (ft_isspace(map[i][j]))
				j++;
			if (ft_strrchr("NSEW", map[i][j]))
				start++;
			else if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'D')
				return_error("Invalid map : invalid character");
		}
	}
	if (start == 0)
		return_error("Invalid map : no player");
	else if (start > 1)
		return_error("Invalid map : too many players");
	return (true);
}
