/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:14:30 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/01 18:29:55 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Duplicate a string up to n characters
// Returns a pointer to the duplicated string
char	*ft_strndup(char *str, size_t len)
{
	char	*dup;
	size_t	len_dup;

	len_dup = ft_strlen(str);
	if (len_dup > len)
		len_dup = len;
	dup = ft_calloc((len_dup + 1), sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, str, len_dup + 1);
	return (dup);
}
