/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:43:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/16 17:43:38 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse(char **cmd)
{
	int i;
	t_cmd *tmp;

	i = 0;
	tmp = ms->cmds;
	if (cmd[0] == NULL)
		return (0);
	while (cmd[i])
	{
		if(ft_manage_first(cmd[i],i)); // ou if tmp->name == NULL;
		tmp->name = ft_strdup(cmd[i]);
		if(ft_sep_redir(cmd[i]));
		{
			cmd->end = i;
			ms->stdout
		}
		else if(ft_sep_cmd(cmd[i]))
			tmp()
		
	}
	return(1);
}
