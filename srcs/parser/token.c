/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:39:52 by wperu             #+#    #+#             */
/*   Updated: 2021/07/03 02:25:42 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_token(char *cmd, int i, int j)
{
	t_token	*tok;
	t_token	*new;

	if (cmd == NULL)
		return ;
	tok = g_ms->tok;
	new = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!new)
		return ;
	new->token = ft_nstrndup(cmd, i, j);
	new->redir = NULL;
	new->next = NULL;
	if (tok == NULL)
		g_ms->tok = new;
	else
	{
		while (tok->next != NULL)
			tok = tok->next;
		tok->next = new;
	}
}

int	ft_one_nospace(char *buffer)
{
	int	i;

	i = 0;
	while (buffer && buffer[i])
	{
		if (buffer[i] > 13 && buffer[i] != ' ' && buffer[i] != '\0' )
			return (1);
		i++;
	}
	return (0);
}

int	ft_redir2(t_token *tok)
{
	int		i;
	int		cpt;
	char	*tmp;

	i = 0;
	while (tok)
	{
		cpt = 0;
		i = 0;
		while (tok->token[i])
		{
			if (ft_check_redir(tok->token, i, 0))
			{
				cpt = cpt + ft_check_redir(tok->token, i, 0);
				if (tok->redir == NULL)
					tok->redir = ft_strndup(tok->token + i,
							ft_check_redir(tok->token, i, 0));
				else
					tok->redir = ft_strjoin(ft_strjoin(tok->redir, " "),
							ft_strndup(tok->token + i,
								ft_check_redir(tok->token, i, 0)));
				 i = i + ft_check_redir(tok->token, i, 0);
			}
			if (tok->token[i] && (ft_check_redir(tok->token, i, 0) == 0))
				i++;
		}
		if (cpt != 0)
		{
			tmp = ft_trim_redir(tok->token, i - cpt);
			tok->token = tmp;
		}
		tok = tok->next;
	}
	return (1);
}

int	ft_check_redir(char *str, int index, int i)
{
	char	*tmp;

	tmp = str + index;
	if ((ft_strncmp(tmp, "<<", 2) == 0 || ft_strncmp(tmp, ">>", 2) == 0)
		&& ft_check_cote(str, index))
	{
		i = 2;
		while (tmp[i] == ' ' && ft_check_cote(str, i + index) && tmp[i])
			i++;
		while ((tmp[i] != ' ' && ft_fin_redir(tmp, i) != 1 && tmp[i])
			|| (!ft_check_cote(str, i + index) && tmp[i]))
			i++;
	}
	else if ((ft_strncmp(tmp, "<", 1) == 0 || ft_strncmp(tmp, ">", 1) == 0)
		&& ft_check_cote(str, index))
	{
		i = 1;
		while (tmp[i] == ' ' && ft_check_cote(str, i + index) && tmp[i])
			i++;
		while ((tmp[i] != ' ' && ft_fin_redir(tmp, i) != 1 && tmp[i])
			|| (!ft_check_cote(str, i + index) && tmp[i]))
			i++;
	}
	return (i);
}

int	ft_fin_redir(char *str, int idx)
{
	if (ft_strncmp(str + idx, "<<", 2) == 0
		|| ft_strncmp(str + idx, ">>", 2) == 0)
		return (1);
	else if (ft_strncmp(str + idx, "<", 1) == 0
		|| ft_strncmp(str + idx, ">", 1) == 0)
		return (1);
	else
		return (0);
}
