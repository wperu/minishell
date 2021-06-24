/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 12:16:31 by wperu             #+#    #+#             */
/*   Updated: 2021/06/24 16:00:10 by emenella         ###   ########.fr       */
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
		dup2(g_ms->pfd[0], g_ms->st_in);
		ft_excute(g_ms, cmd_right);
		close(g_ms->pfd[0]);
		printf("child finish: %s\n", cmd_right->name);
		exit(0);
	}
	else
	{
		close(g_ms->pfd[0]);
		dup2(g_ms->pfd[1], g_ms->st_out);
		ft_excute(g_ms, cmd_left);
		close(g_ms->pfd[1]);
		printf("parent finish\n");
		wait(NULL);
	}
}
