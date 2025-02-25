/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:57:58 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 17:11:28 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

char	**sep_color(const char *color)
{
	char	**components;
	int		count_sep;
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
		return (NULL);
	components = ft_split(color, ',');
	if (!components)
		return (NULL);
	if (!components[0] || !components[1] || !components[2] || components[3])
	{
		ft_free_str_tab(components);
		return (NULL);
	}
	return (components);
}

bool	validate_color(char **components, uint32_t *f_color)
{
	int	i;
	int	r;
	int	g;
	int	b;

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
	if (r < 0 || r > 255 || g < 0
		|| g > 255 || b < 0 || b > 255)
		return (false);
	*f_color = (0xFF << 24) | ((uint32_t)b << 16) | \
		((uint32_t)g << 8) | (uint32_t)r;
	return (true);
}

void	valid_color(t_parsing *parsing, t_data *data)
{
	char	**components;

	if (parsing->floor_color == NULL || parsing->ceiling_color == NULL)
		return_error("Invalid color format", data, true);
	components = sep_color(parsing->floor_color);
	if (!components || !validate_color(components, &data->floor_color))
		return_error("Invalid floor color format \
			(must be F R,G,B with values between 0 and 255)", data, true);
	components = sep_color(parsing->ceiling_color);
	if (!components || !validate_color(components, &data->ceiling_color))
		return_error("Invalid ceiling color format \
			(must be C R,G,B with values between 0 and 255)", data, true);
}
