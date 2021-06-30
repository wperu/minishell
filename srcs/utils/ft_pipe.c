/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 12:16:31 by wperu             #+#    #+#             */
/*   Updated: 2021/06/30 23:03:42 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
# include <errno.h>

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
	char	**env;
	t_pipe	p;

	p = (t_pipe){
		.fd[STDIN_FILENO] = STDIN_FILENO,
		.fd[STDOUT_FILENO] = STDOUT_FILENO,
		.in = false,
		.out = false};
	cmd = g_ms->cmds;
	env = ft_lst_to_array();
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
		ft_pipe_exec(&p, cmd, env);
		cmd = cmd->next;
	}
}

int	ft_pipe_exec(t_pipe *s, t_cmd *cmd, char *env[])
{
	pid_t		pid;
	int			wstatus;
	int			ret;
	char		**cd;
	const int	prec_fd = s->fd[STDIN_FILENO];

	dprintf(2, "START: fd in : %d, fd out : %d\n", s->fd[0], s->fd[1]);

	cd = ft_dup_cmd(cmd->name, cmd->arg, cmd->end);
	ret = 0;
	if (s->out)
		if (pipe(s->fd) < 0)
			return (-1);
	pid = fork();
	if (pid == 0)
	{
		if (s->in)
		{
			if (dup2(prec_fd, STDIN_FILENO) < 0 || close(prec_fd) < 0)
			{
				dprintf(2, "Error: %d\n", errno);
				exit(1);
			}
		}
		if (s->out)
		{
			if (dup2(s->fd[1], STDOUT_FILENO) < 0 || close(s->fd[1]) < 0)
			{
				dprintf(2, "Error: %d\n", errno);
				exit(1);
			}
		}
		dprintf(2, "@@@@@@ name: %s, args: %s, env %p\nin: %d out: %d\nfd in : %d, fd out %d\n@@@\n", cmd->name, cd[1], env, s->in, s->out, s->fd[0], s->fd[1]);
		ret = execve(cmd->name, cd, env);
		exit(ret);
	}
	else if (pid > 0)
	{
		while (waitpid(pid, &wstatus, 0) >= 0)
			;
		if (WIFEXITED(wstatus))
			ret = WEXITSTATUS(wstatus);
		if (s->out)
			close(s->fd[1]);
		if (s->in)
			close(prec_fd);
		return (ret);
	}
	else
		return (-1);
}
