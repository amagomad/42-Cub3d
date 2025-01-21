/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:12:27 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/01 18:23:44 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Convert a string to an integer
// Returns the integer
int	ft_atoi(const char *str)
{
	unsigned int	res;
	int				sign;

	res = 0;
	sign = 1;
	while (*str != '\0' && (ft_isspace((unsigned int)(*str))))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res * sign);
}
