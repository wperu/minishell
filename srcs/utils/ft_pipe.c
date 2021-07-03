/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 12:16:31 by wperu             #+#    #+#             */
/*   Updated: 2021/07/03 02:20:02 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_toksize(t_token *tok)
{
	int		i;
	t_token	*lst;

	i = 0;
	lst = tok;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_pipe(void)
{
	t_cmd	*cmd;
	t_pipe	p;
	size_t	i;
	int		wstatus;

	p = (t_pipe){
		.fd[STDIN_FILENO] = STDIN_FILENO,
		.fd[STDOUT_FILENO] = STDOUT_FILENO,
		.in = false,
		.out = false,
		.pids = {0},
		.pids_index = 0};
	cmd = g_ms->cmds;
	while (cmd != NULL)
	{
		if (p.out)
		{
			p.in = true;
			p.out = false;
			p.fd[STDOUT_FILENO] = STDOUT_FILENO;
		}
		if (cmd->next != NULL)
			p.out = true;
		ft_replace(cmd->arg);
		ft_cmd_trim(cmd);
		if (cmd->redir)
			ft_replace(cmd->redir);
		ft_redir_cmd(cmd->redir);
		g_ms->ret = ft_pipe_exec(&p, cmd);
		cmd = cmd->next;
	}
	cmd = g_ms->cmds;
	i = -1;
	while (++i < p.pids_index)
	{
		while (waitpid(p.pids[i], &wstatus, 0) >= 0)
			;
		if (WIFEXITED(wstatus))
			p.ret = (char)WEXITSTATUS(wstatus);
		p.pids[i] = 0;
	}
	p.pids_index = 0;
}

int	ft_pipe_exec(t_pipe *s, t_cmd *cmd)
{
	pid_t		pid;
	int			ret;
	char		**cd;
	const int	prec_fd = s->fd[g_ms->st_in];

	cd = ft_dup_cmd(cmd->name, cmd->arg);
	ret = 0;
	if (s->out)
		if (pipe(s->fd) < 0)
			return (-1);
	pid = fork();
	if (pid == 0)
	{
		if (s->in)
		{
			if (dup2(prec_fd, g_ms->st_in) < 0 || close(prec_fd) < 0)
			{
				dprintf(2, "Error: %d\n", errno);
				exit(1);
			}
		}
		if (s->out)
		{
			if (dup2(s->fd[STDOUT], g_ms->st_out) < 0
				|| close(s->fd[STDOUT]) < 0)
			{
				dprintf(2, "Error: %d\n", errno);
				exit(1);
			}
		}
		return (g_ms->ret = ft_excute(g_ms, cmd));
	}
	else if (pid > 0)
	{
		s->pids[s->pids_index++] = pid;
		if (s->out)
			close(s->fd[1]);
		if (s->in)
			close(prec_fd);
		return (ret);
	}
	else
		return (-1);
}
