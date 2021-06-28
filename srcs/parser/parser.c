/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:58:57 by wperu             #+#    #+#             */
/*   Updated: 2021/06/28 16:32:45 by wperu            ###   ########lyon.fr   */
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

char	**ft_replace(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[j])
	{
		 i = 0;
		while (cmd[j][i])
		{
			if (cmd[j][i] == '$' && ft_cote(cmd[j], i))
				cmd[j] = ft_replace_var(cmd[j], i);
			if (cmd[j][i])
				i++;
			//puts("ok");
		}
		j++;
	}
	return (cmd);
}

int	ft_isseparator(char *cmd, int i)
{
	if ((cmd[i] == '|') && ft_check_cote(cmd, i))
		return (1);
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
		if (cmd[j] == 39)
			cote = cote * -1;
		if (cmd[j] == 34)
			dcote = dcote * -1;
		j++;
	}
	if (cote == -1 && dcote == -1)
		return (1);
	else
		return (0);
}

int ft_cote(char *cmd, int i)
{
	int	j;
	int	cote;

	j = 0;
	cote = -1;
	while (j < i && cmd[j])
	{
		if (cmd[j] == 39)
			cote = cote * -1;
		j++;
	}
	if (cote == -1)
		return (1);
	else
		return (0);
}
