/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:13:26 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/01 18:30:41 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Create a substring from a string
// Returns the new string
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (len > len_s - start)
		len = len_s - start;
	if (start > len_s)
	{
		res = (char *)malloc(sizeof(char) * (1));
		res[0] = 0;
		return (res);
	}
	else
		res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}
