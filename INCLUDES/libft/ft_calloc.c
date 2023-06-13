/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:07:15 by jsoulet           #+#    #+#             */
/*   Updated: 2023/02/20 15:07:23 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	tmp;
	void	*array;

	tmp = nmemb * size;
	if (!nmemb || !size)
		return (malloc(1));
	if (tmp / size != nmemb)
		return (0);
	array = malloc(tmp);
	if (array)
		ft_bzero(array, tmp);
	return (array);
}
/* se if est pour si la multiplication depasse le max int.
 quand on divise par size cela ne retombe pas sur nmemb.
 on se retrouverai donc avec un malloc de petite taille et donc mauvais.*/