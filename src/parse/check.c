/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:57:58 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/22 17:01:44 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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
