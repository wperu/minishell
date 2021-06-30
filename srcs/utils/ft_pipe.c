/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 12:16:31 by wperu             #+#    #+#             */
/*   Updated: 2021/06/30 05:14:18 by emenella         ###   ########.fr       */
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
	char	**env;

	cmd = g_ms->cmds;
	env = ft_lst_to_array();
	while (cmd != NULL)
	{
		if (cmd == g_ms->cmds)
		{
			p.in = 0;
			p.out = 1;
		}
		else if (cmd->next == NULL)
		{
			p.in = 1;
			p.out = 0;
		}
		else
		{
			p.in = 1;
			p.out = 1;
		}
		printf("in: %d, out: %d\n", p.in, p.out);
		ft_pipe_exec(&p, cmd, env);
		cmd = cmd->next;
	}
}

int	ft_pipe_exec(t_pipe *s, t_cmd *cmd, char *env[])
{
	static int	prec_fd = -1;
	pid_t		pid;
	int			wstatus;
	int			ret;
	char		**cd;

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
			dup2(prec_fd, 1);
			close(0);
		}
		if (s->out)
		{
			dup2(s->fd[1], 1);
			close(1);
		}
		ret = execve(cmd->name, cd, env);
		exit(ret);
	}
	else if (pid > 0)
	{
		while (waitpid(pid, &wstatus, 0) <= 0);
		if (WIFEXITED(wstatus))
			ret = WEXITSTATUS(wstatus);
		if (s->out)
			close(s->fd[1]);
		if (s->in)
			close(prec_fd);
		prec_fd = s->fd[0];
		return (ret);
	}
	else
		return (-1);
}
