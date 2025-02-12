/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:50:21 by cgorin            #+#    #+#             */
/*   Updated: 2025/02/12 22:36:24 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	return_error(char *str)
{
	ft_fprintf(2, "Error: %s\n", str);
	exit(1);
}

float	degrees_to_radians(float degrees)
{
	return (degrees * (PI / 180.0));
}
