/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 12:16:31 by wperu             #+#    #+#             */
/*   Updated: 2021/06/22 19:34:07 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pipe(t_cmd *cmd_left, t_cmd *cmd_right)
{
	pid_t	pid;

	pipe(g_ms->pfd);
	pid = fork();
	if (pid == 0)
	{
		close(g_ms->pfd[1]);
		dup2(g_ms->pfd[0], 0);
		close(g_ms->pfd[0]);
		ft_excute(g_ms, cmd_right);
	}
	else
	{
		close(g_ms->pfd[0]);
		dup2(g_ms->pfd[1], 1);
		close(g_ms->pfd[1]);
		ft_excute(g_ms, cmd_left);
		wait(&g_ms->status);
	}
}
