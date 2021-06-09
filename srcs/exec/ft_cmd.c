/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:24:34 by wperu             #+#    #+#             */
/*   Updated: 2021/06/09 16:37:12 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_split_cmd(t_token *tok)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = 0;
	while (tok->next)
	{
		while (tok->token[i] != ' ')
			i++;
		g_ms->cmds->name = ft_strndup(tok->token, i);
		g_ms->cmds->arg = ft_split(tok->token + i + 1, ' ');
		tok = tok->next;	
		}	
	}
}
