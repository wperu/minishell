/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 01:36:22 by wperu             #+#    #+#             */
/*   Updated: 2021/07/03 02:19:58 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_redir_out(int i, char **arg)
{
	if (ft_strcmp(arg[i], ">") == 0)
		return (1);
	else if (ft_strcmp(arg[i], ">>") == 0)
		return (1);
	return (0);
}

void	ft_redir_out(int i, char **arg)
{
	if (ft_strcmp(arg[i], ">") == 0)
	{
		g_ms->st_out = open(arg[i + 1], O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	else if (ft_strcmp(arg[i], ">>") == 0)
	{
		g_ms->st_out = open(arg[i + 1], O_CREAT | O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
}
