/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:43:50 by jsoulet           #+#    #+#             */
/*   Updated: 2023/02/20 16:51:37 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char	const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[j] && i < len)
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] && i < len)
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}
