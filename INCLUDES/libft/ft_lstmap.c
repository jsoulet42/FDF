/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:18:35 by jsoulet           #+#    #+#             */
/*   Updated: 2023/06/27 10:56:28 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tlist	*ft_lstmap(t_tlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_tlist	*new;
	t_tlist	*lstf;

	if (!lst)
		return (0);
	new = ft_lstnew((*f)(lst->content));
	if (!new)
		return (NULL);
	lstf = new;
	lst = lst->next;
	while (lst)
	{
		new->next = ft_lstnew((*f)(lst->content));
		if (!new->content)
		{
			ft_lstclear(&lstf, (*del));
			return (0);
		}
		new = new->next;
		lst = lst->next;
	}
	return (lstf);
}
