/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:46:04 by jsoulet           #+#    #+#             */
/*   Updated: 2023/02/20 16:46:10 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	is_set(char s1, const char *set)
{
	size_t	i;

	i = -1;
	while (set[++i])
		if (set[i] == s1)
			return (1);
	return (0);
}

static size_t	cpt_set(char const *s1, const char *set)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (is_set(s1[++i], set) && s1[i])
		j++;
	i = ft_strlen(s1);
	if (j != i)
		while (is_set(s1[--i], set) && i > 0)
			j++;
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strf;
	size_t	i;
	size_t	j;

	if (!set)
		return ((char *)s1);
	if (cpt_set(s1, set) == ft_strlen(s1) || !s1)
		return (ft_strdup(""));
	i = 0;
	j = 0;
	strf = malloc(((ft_strlen(s1) - cpt_set(s1, set)) + 1) * sizeof(char));
	if (!strf)
		return (NULL);
	while (is_set(s1[i], set) && s1[i])
		i++;
	while (j < ft_strlen(s1) - cpt_set(s1, set) && s1[i])
		strf[j++] = s1[i++];
	strf[j] = 0;
	return (strf);
}
	/* on definie si le charactere s1 est eggal
	 à l'un des separateurs dans set.*/
	/* on compte le nommbre de separateur dans s1.*/
	/*nombre de separateurs au debut de s1.*/
/*nombre de separateurs a la fin de s1.*/
	/*si les chaines sont remplit de set ou qu'elles sont vide
		on strdup pour que renvoyer une chaine avec un \0*/
	/* on reserve un emplacement memoire de la taille de s1 - les separateurs.*/
	/*on fait avancer i tant que ce sont des separateurs.*/
	/* on inscrit s1 dans strf a partir de i 
	et tant que j est < a taille de s1 moins les separateurs.*/