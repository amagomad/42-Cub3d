/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 16:07:53 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	stock_map(t_data *data)
{
	char	*line;

	data->map_width = 0;
	data->map_height = 0;
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
		if (data->map_width < (int)ft_strlen(line))
			data->map_width = ft_strlen(line);
		data->parse->map = ft_add_str_tab(data->parse->map, line);
		if (!data->parse->map)
			return_error("Invalid map : malloc error", data, true);
		data->map_height++;
	}
	if (data->parse->map == NULL)
		return_error("Invalid map : no map", data, true);
}

void	validity_map_wall(t_data *data)
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
				if ((i > 0 && data->map[i - 1][j] == 4)
					|| (i < data->map_height - 1 && data->map[i + 1][j] == 4)
					|| (j > 0 && data->map[i][j - 1] == 4)
					|| (j < data->map_width - 1 && data->map[i][j + 1] == 4))
					return_error("Invalid: not surrounded by wall", data, true);
			}
			if (data->map[i][j] == -2)
				return_error("Invalid: invalid character", data, true);
		}
	}
}

int	type_map(int i, int j, t_data *data)
{
	if (j >= (int)ft_strlen(data->parse->map[i])
		|| ft_isspace(data->parse->map[i][j]))
		return (4);
	else if (data->parse->map[i][j] == '1')
		return (1);
	else if (data->parse->map[i][j] == '0')
		return (0);
	else if (ft_strchr("NSWE", data->parse->map[i][j]))
	{
		data->player_x = j;
		data->player_y = i;
		data->player_dir = data->parse->map[i][j];
		return (0);
	}
	else if (data->parse->map[i][j] == 'D')
		return (2);
	return (-2);
}

void	transform_map(t_data *data)
{
	int	i;
	int	j;

	data->map = malloc(sizeof(int *) * data->map_height);
	if (!data->map)
		return_error("Invalid map : malloc error", data, true);
	i = -1;
	while (++i < data->map_height)
	{
		data->map[i] = malloc(sizeof(int) * (data->map_width + 1));
		j = -1;
		while (++j < data->map_width)
			data->map[i][j] = type_map(i, j, data);
		data->map[i][j] = -1;
	}
}

void	validity_map(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = -1;
	start = 0;
	while (data->parse->map[++i])
	{
		if (data->parse->map[i][0] == '\0')
			return_error("Invalid map : empty line", data, true);
		j = -1;
		while (data->parse->map[i][++j] && data->parse->map[i][j] != '\n')
		{
			while (ft_isspace(data->parse->map[i][j]))
				j++;
			if (ft_strrchr("NSEW", data->parse->map[i][j]))
				start++;
		}
	}
	if (start == 0)
		return_error("Invalid map : no player", data, true);
	else if (start > 1)
		return_error("Invalid map : too many players", data, true);
}
