/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:34:54 by wperu             #+#    #+#             */
/*   Updated: 2021/06/22 17:21:27 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in_export(t_cmd *cmd)
{
	int	i;

	if ((cmd->arg[0] == NULL && (ft_strcmp(cmd->name, "export") == 0)))
		ft_display_export();
	i = 0;
	while (cmd->arg[i])
	{
		if (ft_check_correct_var(cmd->arg[i]) == 0)
		{
			ft_putstr_fd("minishell: export: `", STDERR);
			ft_putstr_fd(cmd->arg[i], STDERR);
			ft_putstr_fd("': not a valid identifier\n", STDERR);
		}
		else if (cmd->arg[i] && cmd->arg[i][0] != '=')
			ft_add_env_export(cmd->arg[i]);
		i++;
	}
}

void	ft_print_export(char *var, t_mshell *ms)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (var[i])
	{
		write(ms->st_out, &var[i], 1);
		if (var[i] == '=' && k == 0)
		{
			ft_putstr_fd("\"", g_ms->st_out);
			k = 1;
		}
		if (var[i + 1] == '\0' && k == 1)
			ft_putstr_fd("\"\n", g_ms->st_out);
		if (var[i + 1] == '\0' && k == 0)
			ft_putstr_fd("\n", g_ms->st_out);
		i++;
	}
}

void	ft_display_export(void)
{
	t_env	*tmp;

	tmp = g_ms->env;
	while (tmp)
	{
		write(g_ms->st_out, "declare -x ", 11);
		ft_print_export(tmp->var, g_ms);
		tmp = tmp->next;
	}
}
