/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:12:27 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/22 14:50:38 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Add a int tab to a 2 dim int array
// Returns the new int array
int	**ft_add_int_tab2(int **table, int *tab)
{
	int		i;
	int		**new_table;

	i = 0;
	if (table)
		while (table[i] != NULL)
			i++;
	new_table = malloc((i + 2) * sizeof(int *));
	new_table[i] = tab;
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