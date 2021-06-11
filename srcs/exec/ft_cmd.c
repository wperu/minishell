/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:24:34 by wperu             #+#    #+#             */
/*   Updated: 2021/06/11 17:53:12 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_split_cmd(t_token *tok)
{
	int	i;

	i = 0;
	while (tok->next)
	{
		while (tok->token[i] != ' ' && tok->token[i])
			i++;
		ft_add_cmd(tok, i);
		g_ms->cmds->name = ft_strndup(tok->token, i);
		g_ms->cmds->arg = ft_split(tok->token + i + 1, ' ');
		tok = tok->next;
	}
}

void	t_add_cmd(t_token *tok, int i)
{
	t_cmd	*ctmp;
	t_cmd	*new;

	if (tok == NULL)
		return ;
	ctmp = g_ms->cmds;
	new = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return ;
	new->name = ft_strndup(tok->token, i);
	new->arg = ft_split_arg(tok->token, i);
	new->sep = ft_redir_cmd(new->arg, &new->end);
	if (ctmp == NULL)
		g_ms->cmds = new;
	else
	{
		while (ctmp->next != NULL)
			ctmp = ctmp->next;
		ctmp->next = new;
	}
}

int	ft_redir_cmd(char **arg, int *end)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_strcmp(arg[i], ">") == 0)
		{
			g_ms->st_out = open(arg[i + 1], O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			end = i;
		}
		else if (ft_strcmp(arg[i], ">>") == 0)
			g_ms->st_out = open(arg[i + 1], O_CREAT | O_WRONLY | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		i++;
	}
	if (end == 0)
		return (0);
	else
		return (1);
}
