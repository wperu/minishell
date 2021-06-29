/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:39:52 by wperu             #+#    #+#             */
/*   Updated: 2021/06/28 18:04:27 by wperu            ###   ########lyon.fr   */
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
	printf("token = %s\n", new->token);
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
				if (g_ms->tok->redir == NULL)
					g_ms->tok->redir = ft_strndup(tok->token + i, ft_check_redir(tok->token, i, 0));
				else
					g_ms->tok->redir = ft_strjoin(ft_strjoin(g_ms->tok->redir," "), ft_strndup(tok->token + i, ft_check_redir(tok->token, i, 0)));
				 i = i + ft_check_redir(tok->token, i, 0);
				printf("redir= %s\n", g_ms->tok->redir);
			}
			if (tok->token[i] && ft_fin_redir(tok->token, i) != 1)
				i++;
		}
		if (cpt != 0)
		{
			tmp = ft_trim_redir(tok->token, i - cpt);
			tok->token = tmp;
		}
		tok = tok->next;
	}
	/*if (tok->token == NULL)
		return (0);
	else*/
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
	//g_ms->tok->redir = ft_strjoin(g_ms->tok->redir, ft_strndup(str + index, i));
	//printf("redir= %s\n", g_ms->tok->token);
	return (i);
}

int	ft_fin_redir(char *str, int idx)
{
	if (ft_strncmp(str + idx, "<<", 2) == 0 || ft_strncmp(str + idx, ">>", 2) == 0)
		return (1);
	else if (ft_strncmp(str + idx, "<", 1) == 0 || ft_strncmp(str + idx, ">", 1) == 0)
		return (1);
	else
		return (0);
}
/*
char	*ft_get_redir(char *str)
{

}*/

char	*ft_trim_redir(char *str, int cpt)
{
	int		i;
	int		j;
	char	*trimeur;

	trimeur = (char *)malloc(sizeof(char) * cpt + 1);
	if (!trimeur)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_check_redir(str, i, 0))
			i = i + ft_check_redir(str, i, 0);
		else if (str[i] && ft_fin_redir(str, i) != 1)
		{
			printf("i = %d ,j= %d\n", i, j);
			trimeur[j] = str[i];
			i++;
			j++;
		}
	}
	trimeur[j] = '\0';
	printf("trim = %s\n", trimeur);
	return (trimeur);
}
