/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:44:49 by jsoulet           #+#    #+#             */
/*   Updated: 2023/02/20 16:44:54 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*sdest;
	size_t	i;

	i = ft_strlen(s);
	sdest = malloc((i + 1) * sizeof(char));
	if (!sdest)
		return (0);
	i = -1;
	while (s[++i])
		sdest[i] = (*f)((unsigned int) i, s[i]);
	sdest[i] = 0;
	return (sdest);
}
