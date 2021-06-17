/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 15:30:04 by wperu             #+#    #+#             */
/*   Updated: 2021/06/16 19:15:56 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>

bool	is_built_in(char *cmd)
{
	char	**built_in;
	int		i;

	i = 0;
	built_in = ft_split("cd pwd env echo export unset exit", ' ');
	while (built_in[i])
	{
		if (!strcmp(built_in[i], cmd))
		{
			free(built_in);
			return (true);
		}
		i++;
	}
	free(built_in);
	return (false);
}

int	minishell(char **envp)
{
	char		*buffer;
	size_t		buf_size;
	char		**cmd;

	cmd = NULL;
	buffer = NULL;
	buf_size = 2048;
	ft_init_mshell();
	ft_dup_env(envp);
	buffer = (char *)ft_calloc(sizeof(char), buf_size);
	if (!buffer)
	{
		strerror(errno);
		return (EXIT_FAILURE);
	}
	signal(SIGINT, &ft_signal_c);
	signal(SIGQUIT, &ft_silence);
	ft_gnl_minishell(g_ms, cmd, buffer);
	free_lst();
	printf("Bye \n");
	free(buffer);
	return (g_ms->ret);
}

void	ft_gnl_minishell(t_mshell *ms, char **cmd, char *buffer)
{
	int	i;

	while (buffer != NULL && ms->ext != 1)
	{
		buffer = readline("minishell> ");
		if (buffer != NULL && ft_strlen(buffer) != 0)
		{
			add_history(buffer);
			ft_parse(buffer);
			cmd = ft_split(buffer, ' ');
			i = 0;
			ft_split_cmd(g_ms->tok);
			ft_display_cmd(g_ms->cmds);
			if (ft_parse_redir_v2(cmd, ms) == 1)
				ft_excute(ms, g_ms->cmds);
			if (ms->ext == 1)
				break ;
			free_array(cmd);
			ft_reset_mshell();
		}
	}
	if (ms->ext != 1)
		printf("exit\n");
	free(buffer);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc == 1)
		return (minishell(envp));
	else
		return (0);
}
