/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:39:57 by wperu             #+#    #+#             */
/*   Updated: 2021/06/14 16:46:07 by wperu            ###   ########lyon.fr   */
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
	g_ms->ret = 0;
	g_ms->p = 0;
	g_ms->ext = 0;
	i = 0;
	g_ms->path = NULL;
}

int	ft_parse_redir_v2(char **cmd, t_mshell *ms)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], ">") == 0)
			ms->st_out = open(cmd[i + 1], O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (ft_strcmp(cmd[i], ">>") == 0)
			ms->st_out = open(cmd[i + 1], O_CREAT | O_WRONLY | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (ft_strcmp(cmd[i], "|"))
			ms->p = 1;
		/* else if (ft_strcmp(cmd[i],"<\0") == 0)
            if ((ms->st_in = open(cmd[i + 1],O_RDONLY)) < 0)
            {
                ft_printf("minishell: %s: No such file or directory\n", cmd[i +1]);
                return(-1);
            }*/
		i++;
	}
	return (1);
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
	g_ms->ret = 0;
	g_ms->p = 0;
	g_ms->ext = 0;
	free(g_ms->path);
	g_ms->path = NULL;
}
