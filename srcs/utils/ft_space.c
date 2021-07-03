/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 23:23:17 by wperu             #+#    #+#             */
/*   Updated: 2021/07/03 02:19:57 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (cpt != 0)
		{
			tmp = ft_add_space(tok->redir, i + cpt, 0, 0);
			tok->redir = tmp;
		}
		tok = tok->next;
	}
}

char	*ft_add_space(char *str, int idx, int i, int j)
{
	char	*redir;

	redir = (char *)malloc(sizeof(char) * idx + 1);
	if (!redir)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '<'
			&& str[i + 1] && ft_check_cote(str, i))
		{
			redir[j++] = str[i++];
			redir[j++] = ' ';
		}
		else if (str[i] == '>' && str[i + 1] != '>'
			&& str[i + 1] && ft_check_cote(str, i))
		{
			redir[j++] = str[i++];
			redir[j++] = ' ';
		}
		else
			redir[j++] = str[i++];
	}
	redir[j] = '\0';
	return (redir);
}

void	ft_dup2(void)
{
	if (g_ms->st_out != STDOUT)
	{
		dup2(g_ms->st_out, 1);
		close(g_ms->st_out);
	}
	else if (g_ms->st_in != STDIN)
	{
		dup2(g_ms->st_in, 0);
		close(g_ms->st_in);
	}
}

void	ft_sous_exec(char **env, char **cd, t_cmd *cmd)
{
	ft_dup2();
	if (execve(cmd->name, cd, env) < 0
		&& printf("%s not an executable\n", cmd->name))
		exit(EXIT_SUCCESS);
}
