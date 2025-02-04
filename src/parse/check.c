/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:57:58 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/04 18:16:08 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	validity_description(t_parsing *parse)
{
	int	i;
	int	j;

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

bool	ft_isdigit_str(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

void	ft_free_str_tab(char **tab_str)
{
	int	i;

	i = -1;
	while (tab_str[++i])
		free(tab_str[i]);
	free(tab_str);
}

bool	validate_color(const char *color)
{
	char	**components;
	int		count_sep;
	int		r;
	int		g;
	int		b;
	int		i;

	count_sep = 0;
	while (ft_isspace(*color))
		color++;
	i = -1;
	while (color[++i])
	{
		if (color[i] == ',')
			count_sep++;
	}
	if (count_sep != 2)
		return (false);		
	components = ft_split(color, ',');
	if (!components)
		return (false);
	if (!components[0] || !components[1] || !components[2] || components[3])
	{
		ft_free_str_tab(components);
		return (false);
	}
	i = -1;
	while (++i < 3)
	{
		if (components[i][0] == '\0' || !ft_isdigit_str(components[i]))
		{
			ft_free_str_tab(components);
			return (false);
		}
	}
	r = ft_atoi(components[0]);
	g = ft_atoi(components[1]);
	b = ft_atoi(components[2]);
	ft_free_str_tab(components);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error: Color values out of range. R=%d, G=%d, B=%d\n", r, g, b);
		return (false);
	}
	return (true);
}

bool	valid_color(t_parsing *parsing)
{
	if (parsing->floor_color == NULL || parsing->ceiling_color == NULL)
		return (false);
	if (!validate_color(parsing->floor_color))
		return_error("Invalid floor color format (must be F R,G,B with values between 0 and 255)");
	if (!validate_color(parsing->ceiling_color))
		return_error("Invalid ceiling color format (must be C R,G,B with values between 0 and 255)");
	return (true);
}
