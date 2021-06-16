/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 08:31:19 by wperu             #+#    #+#             */
/*   Updated: 2021/06/16 15:03:10 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in_exit(t_cmd *cmd, t_mshell *msh)
{
	ft_putstr_fd("exit\n", STDERR);
	if (cmd->arg[0])
		msh->ret = ft_atoi(cmd->arg[0]);
	else
		msh->ret = 0;
}
