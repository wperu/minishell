/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:24:34 by wperu             #+#    #+#             */
/*   Updated: 2021/06/16 15:20:08 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_cmd(t_token *tok, int i)
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
	//printf("name = %s\n", new->name);
	new->arg = ft_split(tok->token + i, ' ');//ft_split_arg(tok->token, i);
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

void	ft_split_cmd(t_token *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		i = 0;
		while (tok->token[i] != '\0')
		{
			if (tok->token[i] == ' ' && ft_check_cote(tok->token, i))
				break ;
			i++;
		}
		ft_add_cmd(tok, i);
		//g_ms->cmds->name = ft_strndup(tok->token, i);
		//g_ms->cmds->arg = ft_split(tok->token, ' ');//ft_split(tok->token + i + 1, ' ');
		tok = tok->next;
	}
}

int	ft_redir_cmd(char **arg, int *end)
{
	int	i;

	i = 0;
	*end = 0;
	while (arg[i])
	{
		if (ft_strcmp(arg[i], ">") == 0)
		{
			g_ms->st_out = open(arg[i + 1], O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (*end == 0)
				*end = i;
		}
		else if (ft_strcmp(arg[i], ">>") == 0)
		{
			g_ms->st_out = open(arg[i + 1], O_CREAT | O_WRONLY | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (*end == 0)
				*end = i;
		}
		i++;
	}
	if (*end == 0)
	{
		*end = i;
		return (0);
	}
	return (1);
}

void	ft_display_cmd(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmds;
	while (tmp)
	{
		printf("name = %s\n", tmp->name);
		i = 0;
		while (tmp->arg[i])
		{
			printf("arg = %s\n", tmp->arg[i]);
			i++;
		}
		printf("sep = %d , end = %d\n", tmp->sep, tmp->end);
		tmp = tmp->next;
	}
}
