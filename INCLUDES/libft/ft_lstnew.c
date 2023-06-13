/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:18:53 by jsoulet           #+#    #+#             */
/*   Updated: 2023/06/12 10:23:50 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tlist	*ft_lstnew(void *content)
{
	t_tlist	*lst;

	lst = malloc(sizeof(t_tlist));
	if (!lst)
		return (0);
	lst->content = content;
	lst->next = 0;
	return (lst);
}
