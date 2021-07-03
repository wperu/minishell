/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:24:34 by wperu             #+#    #+#             */
/*   Updated: 2021/07/03 01:35:59 by wperu            ###   ########lyon.fr   */
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
	new->name = ft_strtrim(ft_strndup(tok->token, i), " ");
	new->arg = ft_split_cote(tok->token + i, ' ');
	new->redir = ft_split_cote(tok->redir, ' ');
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
		while (tok->token[i] == ' '
			&& ft_check_cote(tok->token, i) && tok->token[i])
			i++;
		while (tok->token[i] != '\0')
		{
			if (tok->token[i] == ' ' && ft_check_cote(tok->token, i))
				break ;
			i++;
		}
		ft_add_cmd(tok, i);
		tok = tok->next;
	}
}

int	ft_redir_cmd(char **arg)
{
	int	i;

	i = 0;
	if (arg)
	{
		while (arg[i])
		{
			if (ft_check_redir_out(i, arg))
				ft_redir_out(i, arg);
			else if (ft_strcmp(arg[i], "<") == 0)
			{
				g_ms->st_in = open(arg[i + 1], O_RDONLY);
				if (g_ms->st_in < 0)
				{
					printf("minishell: %s: No such file or directory\n",
						arg[i + 1]);
					return (-1);
				}
			}
			else if (ft_strcmp(arg[i], "<<") == 0 && arg[i + 1])
				read_input_from(arg[i + 1]);
			i++;
		}
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
		i = 0;
		if (tmp->redir)
		{
			while (tmp->redir[i])
			{
				printf("redir = %s\n", tmp->redir[i]);
				i++;
			}
		}
		tmp = tmp->next;
	}
}

void	ft_cmd_trim(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->name = ft_trim(cmd->name);
	while (cmd->arg[i])
	{
		cmd->arg[i] = ft_trim(cmd->arg[i]);
		i++;
	}
	if (cmd->redir)
	{
		while (cmd->redir[i])
		{
			cmd->redir[i] = ft_trim(cmd->redir[i]);
			i++;
		}
	}
}
