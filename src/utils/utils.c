/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:50:21 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/23 18:01:05 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	return_error(char *str, t_data *data, bool free_parse)
{
	ft_fprintf(2, "Error: %s\n", str);
	if (free_parse)
		free_parsing(data);
	free_all(data);
	exit(EXIT_FAILURE);
}

void	ft_free_str_tab(char **tab_str)
{
	int	i;

	i = -1;
	while (tab_str[++i])
		free(tab_str[i]);
	free(tab_str);
}
