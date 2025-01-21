/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:47:26 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/01 18:28:49 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

// Copy a string
// Returns a pointer to the destination string
char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src [i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest [i] = src[i];
	return (dest);
}
