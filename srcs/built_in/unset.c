/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 13:36:00 by wperu             #+#    #+#             */
/*   Updated: 2021/06/16 15:05:45 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in_unset(t_cmd *cd)
{
	t_env	*tmp;
	t_env	*previous;
	t_env	*to_remove;
	int		i;

	i = 0;
	while (cd->arg[i])
	{	
		tmp = g_ms->env;
		previous = NULL;
		to_remove = NULL;
		while (tmp)
		{
			if (ft_strncmp(cd->arg[i], tmp->var, ft_chr(cd->arg[i], '=')) == 0)
			{
				to_remove = tmp;
				previous->next = tmp->next;
				free(to_remove);
				to_remove = NULL;
				break ;
			}
			previous = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}
