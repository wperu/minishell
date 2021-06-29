/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:45:10 by amonteli          #+#    #+#             */
/*   Updated: 2021/06/29 22:50:25 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*read_input_from(char *key)
{
	t_list	*lst;
	char	*buffer;
	int		end;

	lst = NULL;
	buffer = NULL;
	end = 1;
	while (end)
	{
		ft_manage_signal(0);
		buffer = readline("> ");
		if (buffer != NULL && ft_strcmp(key, buffer) != 0)
			ft_lstadd_front(&lst, ft_lstnew(buffer));
		else
		{
			end = 0;
			free(buffer);
		}
	}
	return (lst);
}
