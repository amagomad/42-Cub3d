/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:50:21 by cgorin            #+#    #+#             */
/*   Updated: 2025/03/13 17:56:32 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	return_error(char *str, t_data *data, bool free_parse)
{
	ft_fprintf(2, "Error: %s\n", str);
	if (free_parse)
		free_parsing(data);
	if (!free_parse)
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

void	handle_sprites(t_data *data)
{
	t_sprite	*sprite;
	int			i;
	int			j;

	i = 0;
	while (i < data->num_sprites)
	{
		sprite = &data->sprites[i];
		j = 0;
		while (j < sprite->total_frames)
		{
			mlx_delete_texture(sprite->frames[j]);
			j = j + 1;
		}
		free(sprite->frames);
		i = i + 1;
	}
	free(data->sprites);
	free(data->z_buffer);
}
