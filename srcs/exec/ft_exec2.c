/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:59:31 by wperu             #+#    #+#             */
/*   Updated: 2021/07/03 02:00:01 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_usepath(t_cmd *cmd, char**env, t_mshell *ms, int i)
{
	struct stat		buf;
	char			*tmp;
	char			**cd;

	cd = ft_dup_cmd(cmd->name, cmd->arg);
	while (cmd->name && ms->path && ms->path[i++])
	{
		tmp = ft_strjoin(ft_strjoin(ms->path[i], "/"), cmd->name);
		if (lstat(tmp, &buf) == 0)
		{
			if (fork() == 0)
			{
				ft_dup2();
				if (execve(tmp, cd, env) < 0
					&& printf("minishell: %s: command not found\n", cmd->name))
					exit(EXIT_SUCCESS);
			}
			ft_manage_signal(1);
			wait(&ms->status);
			free(tmp);
			return (1);
		}
		free(tmp);
	}
	return (0);
}

int	ft_exec_cmd2(t_cmd *cmd, char **env, t_mshell *ms)
{
	int		fd;
	char	**cd;

	cd = ft_dup_cmd(cmd->name, cmd->arg);
	fd = open(cmd->name, 0);
	if (ft_chr(cmd->name, '/') < (int)ft_strlen(cmd->name))
	{
		if (fd > 0 && !close(fd))
		{
			if (g_ms->st_out != STDOUT)
				ft_sous_exec(env, cd, cmd);
			else if (fork() == 0 && execve(cmd->name, cd, env) < 0
				&& printf("minishell: %s: Command not found\n", cmd->name))
				exit(EXIT_SUCCESS);
			ft_manage_signal(2);
			wait(&ms->status);
			ms->status = WEXITSTATUS(ms->status);
			free(cd);
			return (1);
		}
	}
	else
		return (ft_usepath(cmd, env, ms, 0));
	return (0);
}

int	ft_excute(t_mshell *ms, t_cmd *cmd)
{
	char	**env;

	env = NULL;
	if (cmd->name == NULL)
		printf("");
	else if (is_built_in(cmd->name) == true)
		return (g_ms->ext = exec_built_in(cmd, ms));
	else
	{
		env = ft_lst_to_array();
		if (ft_get_env_var("PATH="))
		{
			g_ms->path = ft_split(ft_get_env_var("PATH=") + 5, ':');
			if (!ft_exec_cmd2(cmd, env, ms))
				printf("minishell: %s: Command not found\n", cmd->name);
		}
		else
			printf("minishell: %s: Command not found\n", cmd->name);
		free(env);
		env = NULL;
	}
	signal(SIGINT, &ft_signal_c);
	signal(SIGQUIT, SIG_IGN);
	return (-1);
}

int	exec_built_in(t_cmd *cmd, t_mshell *ms)
{
	char	*pwd;

	if (!strcmp(cmd->name, "pwd"))
	{
		pwd = built_in_pwd(cmd->name);
		ft_putstr_fd(pwd, ms->st_out);
		ft_putstr_fd("\n", ms->st_out);
	}
	else if (!strcmp(cmd->name, "cd"))
		built_in_cd(cmd->arg[0]);
	else if (!strcmp(cmd->name, "env"))
		built_in_env(ms);
	else if (!strcmp(cmd->name, "echo"))
		built_in_echo(cmd, ms);
	else if (!strcmp(cmd->name, "export"))
		built_in_export(cmd);
	else if (!strcmp(cmd->name, "unset"))
		built_in_unset(cmd);
	else if (!strcmp(cmd->name, "exit"))
	{
		built_in_exit(cmd, ms);
		g_ms->ext = 1;
		return (1);
	}
	return (-1);
}

char	**ft_dup_cmd(char *name, char **arg)
{
	char	**tab;
	int		i;
	int		len;

	tab = NULL;
	len = 0;
	if (arg)
		while (arg[len])
			len++;
	tab = malloc(sizeof(char *) * (1 + len + 1));
	i = 0;
	tab[0] = ft_strdup(name);
	if (arg)
	{
		while (arg[i])
		{
			tab[i + 1] = ft_strdup(arg[i]);
			i++;
		}
	}
	i++;
	tab[i] = NULL;
	return (tab);
}
