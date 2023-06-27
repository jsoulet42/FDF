/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:37:54 by rrodor            #+#    #+#             */
/*   Updated: 2023/06/24 17:42:55 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

typedef struct s_split
{
	char	**wrd;
	int		l;
	int		i;
	int		j;
	int		k;

}			t_split;

int	verif_ft_split(const char *str, int j)
{
	int	i;

	i = j;
	if (!str[i])
		return (0);
	if (!str[i + 1])
		return (0);
	if (!str[i + 2])
		return (0);
	if (!str[i + 3])
		return (0);
	return (1);
}

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
	if (s[i - 2] == ' ')
		l--;
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

t_split	ft_init_split(char const *s, char c)
{
	t_split	split;

	split.i = 0;
	split.j = 0;
	split.l = ft_countwrd(s, c);
	split.wrd = ft_calloc(split.l + 1, sizeof(char *));
	return (split);
}

char	**ft_split(char const *s, char c)
{
	t_split	p;

	if (!s)
		return (0);
	p = ft_init_split(s, c);
	if (!p.wrd)
		return (0);
	while (p.j++ < p.l)
	{
		p.k = 0;
		while (s[p.i] == c && s[p.i])
			p.i++;
		while (s[p.i + p.k] != c && s[p.i + p.k])
			p.k++;
		p.wrd[p.j - 1] = ft_substr(s, p.i, p.k);
		if (!p.wrd[p.j - 1])
			return (0);
		p.i += p.k;
		if (verif_ft_split(s, p.i) == 1)
		{
			if (s[p.i + 2] == '\n' && s[p.i + 1] == ' ' && s[p.i + 3] == '\0')
				break ;
		}
	}
	return (p.wrd);
}
