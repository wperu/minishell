/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:58:57 by wperu             #+#    #+#             */
/*   Updated: 2021/06/08 16:17:48 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_replace_var(char *cmd, int index)
{
	int		i;
	char	*venv;
	char	*begin;
	char	*end;

	i = index + 1;
	while (ft_isalnum(cmd[i]) || cmd[i] == '_')
		i++;
	begin = ft_strndup(cmd, index);
	end = ft_strdup(cmd + i);
	venv = ft_strndup(cmd + index + 1, i - index - 1);
	venv = getenv(venv);
	cmd = ft_strjoin(begin, ft_strjoin(venv, end));
	free(end);
	free(begin);
	//free(venv);
	return (cmd);
}

char	*ft_replace(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
			cmd = ft_replace_var(cmd, i);
		printf("cmd = %s\n", cmd);
		if (cmd[i])
			i++;
		puts("ok");
	}
	//ft_backslash(cmd);
	//ft_cote();
	return (cmd);
}

/*
char	**ft_parser(char *buf)
{
	char	**cmd;
	int		i;
	int		backslash;
	int		cote;
	int		dcote;

	i = 0;
	backslash = 0;
	cote = 0;
	while ((cmd[i] != ';' || cmd[i] != '|') && cmd[i])
	{
		if (cmd[i] == 39 || cmd[i] == 34)
		{
			if (!cote)
				cote = 1;
			else
				cote = 0;
		}
	}
	if (cmd[i] == '\'')
	{
		if (backslash == 0)
			backslash = 1;
		else
			backslash = 0;
	}
}
*/
int	ft_isseparator(char *cmd, int i)
{
	if ((cmd[i] == ';' || cmd[i] == '|'))
	{
		//if (ft_check_cote(cmd, i) && ft_backslash(cmd, i))
		return (1);
		/*else
			return (0);*/
	}
	else
		return (0);
}

void	ft_parse(char *buf)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buf[i])
	{
		if (ft_isseparator(buf, i))
		{
			 ft_add_token(buf, i, j);
			 j = i + 1;
		}
		i++;
	}
	ft_add_token(buf, i, j);
}

int	ft_check_cote(char *cmd, int i)
{
	int	j;
	int	cote;
	int	dcote;

	j = 0;
	cote = -1;
	dcote = -1;
	while (j < i && cmd[j])
	{
		if (cmd[j] == 39 && ft_backslash(cmd, j) == 0)
			cote = cote * -1;
		if (cmd[j] == 34 && ft_backslash(cmd, j) == 0)
			dcote = dcote * -1;
		j++;
	}
	if (cote == -1 && dcote == -1)
		return (1);
	else
		return (0);
}

int ft_backslash(char *cmd, int index)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (i < index)
	{
		if (cmd[i] == 47)
			cpt++;
		i++;
	}
	if (cpt % 2 != 0 && cmd[i] == 47)
		return (1);
	else
		return (0);
}
