/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:47:15 by jsoulet           #+#    #+#             */
/*   Updated: 2023/02/20 16:47:18 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*strf;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		strf = malloc((ft_strlen(s + start) + 1) * sizeof(char));
	else
		strf = malloc ((len + 1) * sizeof(char));
	if (!strf)
		return (0);
	i = 0;
	while (s[start] && i < len)
		strf[i++] = s[start++];
	strf[i] = 0;
	return (strf);
}
	/*si len est > que du start a la fin de s on reserve
	 la memoire strictement necessaire*/
		/*sinon on reserve la memoire de la taille de len + 1 pour \0*/
	/* on inscrit notre sous chaine dans la chaine final*/