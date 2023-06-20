/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:46:57 by romaurel          #+#    #+#             */
/*   Updated: 2023/06/20 08:53:30 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen2(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_strchr2(char *s, char c)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s && s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}

char	*ft_strndup(char *s, int len)
{
	int		i;
	char	*cp;

	if (!s || !len)
		return (NULL);
	cp = (char *) malloc((len + 1) * sizeof(char));
	if (!cp)
		return (NULL);
	i = -1;
	while (++i < len)
		cp[i] = s[i];
	cp[i] = 0;
	return (cp);
}
