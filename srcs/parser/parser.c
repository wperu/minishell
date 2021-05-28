/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:58:57 by wperu             #+#    #+#             */
/*   Updated: 2021/05/28 16:51:57 by wperu            ###   ########lyon.fr   */
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

int	ft_isseprator(char *cmd, int i)
{
	if ((cmd[i] == ';' || cmd[i] != '|') && i > 0)
	{
		if (ft_check_cote(cmd, i) && cmd[i - 1] != '\'')
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

void	ft_parser_2(char *buf, t_mshell *ms)
{
	char	**cmd;
	int		i;

	i = 0;
	while (buf[i])
	{
		if (ft_isseparator(buf, i)
		{
			ft_add_token(buf,i,ms->tok)
		}
		i++;
	}
	ft_add_token();
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

