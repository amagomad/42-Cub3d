/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:50:21 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/18 21:36:53 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	return_error(char *str, t_data *data)
{
	ft_fprintf(2, "Error: %s\n", str);
	free_all(data);
	free(data);
	exit(EXIT_FAILURE);
	//mlx_terminate(data->mlx);
}

float	degrees_to_radians(float degrees)
{
	return (degrees * (PI / 180.0));
}
