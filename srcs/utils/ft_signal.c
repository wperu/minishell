/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:16:06 by wperu             #+#    #+#             */
/*   Updated: 2021/06/22 18:02:20 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_signal_c(int sign)
{
	sign = 0;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal_slash(int i)
{
	printf("Quit: 3\n");
	signal(i, SIG_IGN);
}

void	ft_nl(int i)
{
	printf("\n");
	signal(i, SIG_IGN);
}

void	ft_silence(int i)
{
	signal(i, SIG_IGN);
}

void	ft_manage_signal(int key)
{
	if (key == 0)
	{
		signal(SIGINT, &ft_signal_c);
		signal(SIGQUIT, &ft_silence);
	}
	if (key == 1)
	{
		signal(SIGINT, &ft_nl);
		signal(SIGQUIT, &ft_signal_slash);
	}
	else
	{
		signal(SIGINT, &ft_silence);
		signal(SIGQUIT, &ft_silence);
	}
}
