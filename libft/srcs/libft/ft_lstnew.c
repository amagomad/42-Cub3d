/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:51:46 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/01 18:25:29 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Create a new list element
t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = NULL;
	lst = malloc (sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst -> content = content;
	lst -> next = NULL;
	return (lst);
}
