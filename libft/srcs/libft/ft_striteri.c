/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:13:16 by cgorin            #+#    #+#             */
/*   Updated: 2025/01/01 18:29:07 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Apply a function to each character of a string
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	if (s && f)
	{
		i = 0;
		while (s[i])
		{
			(*f)(i, s + i);
			i++;
		}
	}
}

/* Paramètres
s: La chaîne de caractères sur laquelle itérer.
f: La fonction à appliquer à chaque caractère.
Fonctions ex- ternes autorisées
Aucune
Description
Applique la fonction ’f’ à chaque caractère de la
chaîne de caractères transmise comme argument,
et en passant son index comme premier argument.
Chaque caractère est transmis par adresse à ’f’
afin d’être modifié si nécessaire. */