/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:05:23 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/01 18:25:23 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Apply a function to the content of a list
// Returns a new list
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	new = ft_lstnew((*f)(lst->content));
	if (!new)
		return (NULL);
	tmp = new;
	lst = lst->next;
	while (lst)
	{
		new->next = ft_lstnew((*f)(lst->content));
		if (!new->next)
		{
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (tmp);
}
