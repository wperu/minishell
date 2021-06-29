/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:24:34 by wperu             #+#    #+#             */
/*   Updated: 2021/06/29 22:54:45 by emenella         ###   ########.fr       */
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
	//new->redir = ft_split_redir(tok->redir);
	ft_redir_cmd(new->arg, &new->end, &new->sep);
		//exit(0);
	//new->sep = ft_redir_cmd(new->arg, &new->end, &new->sep);
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
	printf("tok = %s\n",tok->token);
	while (tok)
	{
		i = 0;
		while (tok->token[i] == ' ' && ft_check_cote(tok->token, i) && tok->token[i])
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

int	ft_redir_cmd(char **arg, int *end, int *sep)
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
			if (*sep == 0)
			{
				*sep = 1;
				*end = i;
			}
		}
		else if (ft_strcmp(arg[i], ">>") == 0)
		{
			g_ms->st_out = open(arg[i + 1], O_CREAT | O_WRONLY | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (*sep == 0)
			{
				*sep = 1;
				*end = i;
			}
		}
		else if (ft_strcmp(arg[i], "<") == 0)
		{
			printf("in redirection <\n");
			printf("%s\n", arg[i + 1]);
			printf("%d\n", g_ms->st_in = open(arg[i + 1], O_RDONLY));
			if (g_ms->st_in < 0)
			{
				printf("minishell: %s: No such file or directory\n", arg[i + 1]);
				return (-1);
			}
			if (*sep == 0)
			{
				*sep = 2;
				*end = i;
			}	
		}
		i++;
	}
	if (g_ms->st_out == STDOUT)
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
}
/*
char **ft_split_redir(char *redir)
{
	char	**tmp;
	int		len;

	if(redir == NULL)
		return(NULL);
	len = numstring
}
*/