/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:14:33 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/01 18:30:09 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	search_needle(const char *haystack, const char *needle)
{
	size_t	i;

	i = 0;
	while (needle[i])
	{
		if (needle[i] != haystack[i])
			return (0);
		i++;
	}
	return (1);
}

// Locate a substring in a string
// Returns a pointer to the first occurrence of the substring in the string
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (!needle[i])
		return ((char *)(haystack));
	while (*haystack && i < len)
	{
		if (*haystack == needle[0] && ft_strlen(needle) <= len - i)
			if (search_needle(haystack, needle))
				return ((char *)(haystack));
		haystack++;
		i++;
	}
	return (NULL);
}
