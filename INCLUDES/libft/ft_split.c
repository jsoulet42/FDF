/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:37:54 by rrodor            #+#    #+#             */
/*   Updated: 2023/06/16 17:18:12 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwrd(const char *s, char c)
{
	int	l;
	int	i;

	l = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			l++;
		while (s[i] != c && s[i])
			i++;
	}
	return (l);
}

static int	ft_init(char const *s, char c, int *i, int *j)
{
	int	l;

	l = ft_countwrd(s, c);
	*i = 0;
	*j = 0;
	return (l);
}

char	**ft_split(char const *s, char c)
{
	char	**wrd;
	int		l;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (0);
	l = ft_init(s, c, &i, &j);
	wrd = ft_calloc(l + 1, sizeof(char *));
	if (!wrd)
		return (0);
	while (j++ < l)
	{
		k = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i + k] != c && s[i + k])
			k++;
		wrd[j - 1] = ft_substr(s, i, k);
		if (!wrd[j - 1])
			return (0);
		i += k;
	}
	return (wrd);
}
