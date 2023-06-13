/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:45:22 by jsoulet           #+#    #+#             */
/*   Updated: 2023/02/20 16:45:27 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	k;

	if ((!big || !little) && !len)
		return (NULL);
	if (!*little)
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		k = 0;
		while (little[k] == big[i + k] && i + k < len)
			if (!little[k++ +1])
				return ((char *)big + i);
		i++;
	}
	return (0);
}
/*Si little est vide return le début de big.*/
/* i + k pour ne pas changer i de position 
	donc même position dans big*/
/*test si le prochain charactere de little est \0 
	c'est que trouvé donc return sinon k++*/