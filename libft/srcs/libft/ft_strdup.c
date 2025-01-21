/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:14:13 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/01 18:28:55 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Duplicate a string
// Returns a pointer to the duplicated string
char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;

	dest = 0;
	dest = (char *) malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* The strdup() function allocates sufficient memory for a copy of the
     string s1, does the copy, and returns a pointer to it.  The pointer may
     subsequently be used as an argument to the function free(3).

     If insufficient memory is available, NULL is returned and errno is set to
     ENOMEM.

 */