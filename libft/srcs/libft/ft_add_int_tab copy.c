/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_int_tab copy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:12:27 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/22 14:52:23 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Transform a string to a int array
// Returns the new int array
int	*ft_add_int_tab(const char *str)
{
	int		i;
	int		*new_tab;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]) && )
			return (NULL);
		i++;
	}
	new_tab = malloc((i + 1) * sizeof(int));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
			new_tab[i] = str[i] - '0';
		else
			new_tab[i] = -1;
		i++;
	}
	new_tab[i] = -2;
	return (new_tab);
}