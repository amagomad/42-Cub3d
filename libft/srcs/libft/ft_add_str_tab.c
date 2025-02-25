/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:12:27 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/18 18:56:56 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Add a string to a string array
// Returns the new string array
char	**ft_add_str_tab(char **table, const char *str)
{
	int		i;
	char	**new_table;

	i = 0;
	if (table)
		while (table[i] != NULL)
			i++;
	new_table = malloc((i + 2) * sizeof(char *));
	new_table[i] = ft_strdup(str);
	if (!new_table[i])
	{
		free(new_table);
		return (NULL);
	}
	new_table[i + 1] = NULL;
	while (--i >= 0)
		new_table[i] = table[i];
	if (table)
		free(table);
	return (new_table);
}
