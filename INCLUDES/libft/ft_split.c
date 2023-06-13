/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:42:10 by jsoulet           #+#    #+#             */
/*   Updated: 2023/02/20 16:42:16 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*strdupm(char const *s, int start, int end)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(((end - start) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (start < end)
	{
		dest[i++] = s[start++];
	}
	dest[i] = 0;
	return (dest);
}

static int	count_word(const char *s, char c)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			k++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (k);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		start;
	int		i;
	int		j;

	tab = (char **) malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
				i++;
		start = i;
		while (s[i] != c && s[i])
				i++;
		if (start != i)
			tab[j++] = strdupm(s, start, i);
	}
	tab[j] = 0;
	return (tab);
}
