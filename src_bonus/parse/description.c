/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   description.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:28:34 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 21:15:12 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	assign_element(t_parsing *parse, char *line)
{
	int	j;

	j = 0;
	if (ft_strrchr("NSEW", line[0]) == NULL)
		j = 2;
	if (ft_strrchr("FC", line[0]) == NULL)
		j = 3;
	while (ft_isspace(line[j]))
		j++;
	if (ft_strncmp(line, "NO", 2) == 0)
		parse->no_texture = ft_strdup(line + j);
	else if (ft_strncmp(line, "SO", 2) == 0)
		parse->so_texture = ft_strdup(line + j);
	else if (ft_strncmp(line, "WE", 2) == 0)
		parse->we_texture = ft_strdup(line + j);
	else if (ft_strncmp(line, "EA", 2) == 0)
		parse->ea_texture = ft_strdup(line + j);
	else if (ft_strncmp(line, "F", 1) == 0)
		parse->floor_color = ft_strdup(line + j);
	else if (ft_strncmp(line, "C", 1) == 0)
		parse->ceiling_color = ft_strdup(line + j);
	else
		return (false);
	return (true);
}

bool	validity_desc(t_parsing *parse)
{
	int	i;

	i = -1;
	while (parse->desc[++i])
	{
		if (parse->desc[i][0] == '\0')
			return (false);
		if (!assign_element(parse, parse->desc[i]))
			return (false);
	}
	if (parse->no_texture == NULL || parse->so_texture == NULL
		|| parse->we_texture == NULL || parse->ea_texture == NULL
		|| parse->floor_color == NULL || parse->ceiling_color == NULL)
		return (false);
	return (true);
}

bool	is_valid_desc(char *line)
{
	return (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0);
}

bool	stock_desc(t_parsing *parse)
{
	int		count;

	count = 0;
	parse->line = ft_strdup(" ");
	while (count < 6 && parse->line)
	{
		free(parse->line);
		parse->line = get_next_line(parse->file_fd);
		if (!parse->line)
			return (false);
		parse->line[ft_strlen(parse->line) - 1] = '\0';
		while (ft_isspace(*parse->line))
			parse->line++;
		if (is_valid_desc(parse->line))
		{
			parse->desc = ft_add_str_tab(parse->desc, parse->line);
			if (!parse->desc)
				return (false);
			count++;
		}
		else if (ft_isalnum(*parse->line))
			return (false);
	}
	return (true);
}
