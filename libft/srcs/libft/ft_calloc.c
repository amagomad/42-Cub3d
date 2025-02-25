/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:13:42 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/01 18:23:30 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Allocate memory and set it to zero
// Returns a pointer to the allocated memory
void	*ft_calloc(size_t count, size_t size)
{
	void	*buffer;

	if ((count >= 65535 && size >= 65535) || count * size >= 65535)
		return (NULL);
	buffer = (void *) malloc(size * count);
	if (buffer == NULL)
		return (NULL);
	ft_bzero(buffer, (count * size));
	return (buffer);
}
