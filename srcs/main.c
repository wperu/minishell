/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 15:30:04 by wperu             #+#    #+#             */
/*   Updated: 2021/06/23 14:58:51 by emenella         ###   ########.fr       */
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
	ft_gnl_minishell(g_ms, buffer);
	free_lst();
	printf("Bye \n");
	free(buffer);
	return (g_ms->ret);
}

void	ft_gnl_minishell(t_mshell *ms, char *buffer)
{
	while (buffer != NULL && ms->ext != 1)
	{
		buffer = readline("minishell> ");
		if (ft_one_nospace(buffer) == 1)
		{
			add_history(buffer);
			ft_parse(buffer);
			ft_split_cmd(g_ms->tok);
			ft_display_cmd(g_ms->cmds);
			if (ft_lstsize((t_list *)g_ms->tok) > 1)
				ft_pipe(g_ms->cmds, g_ms->cmds->next);
			else
				ft_excute(ms, g_ms->cmds);
			if (ms->ext == 1)
				break ;
			//ft_reset_mshell();
		}
		ft_reset_mshell();
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
