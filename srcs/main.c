/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 15:30:04 by wperu             #+#    #+#             */
/*   Updated: 2021/07/02 19:33:30 by wperu            ###   ########lyon.fr   */
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
	free(buffer);
	return (g_ms->ret);
}

void	ft_gnl_minishell(t_mshell *ms, char **cmd, char *buffer)
{
	while (buffer != NULL && ms->ext != 1)
	{
		buffer = readline("minishell>");
		if (ft_one_nospace(buffer) == 1)
		{
			add_history(buffer);
			ft_parse(buffer);
			cmd = ft_split(buffer, ' ');
			ft_redir2(g_ms->tok);
			ft_space(g_ms->tok);// wtf
			ft_split_cmd(g_ms->tok);
			//ft_display_cmd(g_ms->cmds);
			ft_replace(g_ms->cmds->arg);
			ft_cmd_trim(g_ms->cmds);
			ft_redir_cmd(g_ms->cmds->redir);
			//ft_dup2();
			ft_excute(ms, g_ms->cmds);
			if (ms->ext == 1)
				break ;
			free_array(cmd);
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

void	ft_space(t_token *tok)
{
	char	*tmp;
	int		cpt;
	int		i;

	while (tok && tok->redir)
	{
		cpt = 0;
		i = 0;
		while (tok->redir[i])
		{
			if (ft_fin_redir(tok->redir, i) && ft_check_cote(tok->redir, i))
				cpt++;
			i++;
		}
	//	printf("cpt = %d\n", cpt);
		if (cpt != 0)
		{
			tmp = ft_add_space(tok->redir, i + cpt);
			tok->redir = tmp;
		}
		tok = tok->next;
	}
}

char	*ft_add_space(char *str, int idx)
{
	char	*redir;
	int		i;
	int		j;

	redir = (char *)malloc(sizeof(char) * idx + 1);
	if (!redir)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '<' && str[i + 1] && ft_check_cote(str, i))
		{
			redir[j] = str[i];
			j++;
			i++;
			redir[j] = ' ';
			j++;
		}
		else if (str[i] == '>' && str[i + 1] != '>' && str[i + 1] && ft_check_cote(str, i))
		{
			redir[j] = str[i];
			j++;
			i++;
			redir[j] = ' ';
			j++;
		}
		else
		{
			redir[j] = str[i];
			j++;
			i++;
		}
	}
	redir[j] = '\0';
//	printf("redir = %s\n", redir);
	return (redir);
}
