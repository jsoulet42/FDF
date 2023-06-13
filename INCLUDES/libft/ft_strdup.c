/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:42:59 by jsoulet           #+#    #+#             */
/*   Updated: 2023/02/20 16:43:09 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*array;
	int		i;

	i = ft_strlen(s);
	array = malloc((i + 1) * sizeof(char));
	i = -1;
	if (array)
	{
		while (s[++i])
			array[i] = s[i];
		array[i] = 0;
	}
	return (array);
}
