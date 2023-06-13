/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:42:30 by jsoulet           #+#    #+#             */
/*   Updated: 2023/02/20 16:42:39 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	if (!c)
		return (((char *)s) + ft_strlen(s));
	while (((char *)s)[++i])
		if (((char *)s)[i] == (char) c)
			return (((char *)s) + i);
	return (NULL);
}
	/*si c
	 = NULL alors renvoyer un pointeur sur '\0'*/