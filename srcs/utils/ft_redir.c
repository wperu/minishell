/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:39:57 by wperu             #+#    #+#             */
/*   Updated: 2021/07/03 02:19:58 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_mshell(void)
{
	int	i;

	g_ms = NULL;
	g_ms = malloc(sizeof(t_mshell));
	if (!g_ms)
	{
		printf("ERROR MALLOC");
		free(g_ms);
		g_ms = NULL;
	}
	g_ms->env = NULL;
	g_ms->cmds = NULL;
	g_ms->tok = NULL;
	g_ms->st_in = STDIN;
	g_ms->st_out = STDOUT;
	g_ms->st_err = STDERR;
	g_ms->ret = -1;
	g_ms->p = 0;
	g_ms->ext = 0;
	i = 0;
	g_ms->path = NULL;
}

void	ft_reset_mshell(void)
{
	free(g_ms->cmds);
	free(g_ms->tok);
	g_ms->tok = NULL;
	g_ms->cmds = NULL;
	g_ms->st_in = STDIN;
	g_ms->st_out = STDOUT;
	g_ms->st_err = STDERR;
	g_ms->ret = -1;
	g_ms->p = 0;
	g_ms->ext = 0;
	free(g_ms->path);
	g_ms->path = NULL;
}

char	*ft_trim_redir(char *str, int cpt)
{
	int		i;
	int		j;
	char	*trimeur;

	trimeur = (char *)malloc(sizeof(char) * cpt + 1);
	if (!trimeur)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_check_redir(str, i, 0))
			i = i + ft_check_redir(str, i, 0);
		else if ((str[i] && ft_fin_redir(str, i) != 1 )
			 || (!ft_check_cote(str, i) && str[i]))
		{
			trimeur[j] = str[i];
			i++;
			j++;
		}
	}
	trimeur[j] = '\0';
	return (trimeur);
}

void	ft_rereplace(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->arg)
			ft_replace(cmd->arg);
		if (cmd->redir)
			ft_replace(cmd->redir);
		cmd = cmd->next;
	}
}

int	ft_cote(char *cmd, int i)
{
	int	j;
	int	cote;

	j = 0;
	cote = -1;
	while (j < i && cmd[j])
	{
		if (cmd[j] == 39)
			cote = cote * -1;
		j++;
	}
	if (cote == -1)
		return (1);
	else
		return (0);
}
