/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:19:33 by jsoulet           #+#    #+#             */
/*   Updated: 2023/02/20 15:19:37 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int	i;

	i = 0;
	while (n --)
	{
		if (((unsigned char *)s)[i++] == ((unsigned char)c))
			return (((unsigned char *)s) + --i);
	}
	return (NULL);
}
/* --i pour retirer l'incrementation supplementaire*/