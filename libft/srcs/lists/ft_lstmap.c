/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 18:31:39 by amonteli          #+#    #+#             */
/*   Updated: 2020/07/16 03:39:51 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mynewlist;
	t_list	*first;

	if (!lst)
		return (NULL);
	if (!(mynewlist = ft_lstnew(f(lst->content))))
		return (NULL);
	first = mynewlist;
	while (lst)
	{
		if (lst->next)
		{
			if (!(mynewlist->next = ft_lstnew(f(lst->next->content))))
			{
				ft_lstclear(&first, del);
				return (0);
			}
			mynewlist = mynewlist->next;
		}
		lst = lst->next;
	}
	mynewlist->next = NULL;
	return (first);
}
