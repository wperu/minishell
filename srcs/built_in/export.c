/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:34:54 by wperu             #+#    #+#             */
/*   Updated: 2021/06/03 15:59:56 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in_export(char **cmd)
{
	int	i;

	if ((cmd[1] == NULL && (ft_strcmp(cmd[0], "export") == 0)))
		ft_display_export();
	i = 1;
	while (cmd[i])
	{
		if (ft_check_correct_var(ft_trim(cmd[i], 34)) == 0)
		{
			ft_putstr_fd("minishell: export: `", STDERR);
			ft_putstr_fd(cmd[i], STDERR);
			ft_putstr_fd("': not a valid identifier\n", STDERR);
		}
		else if (cmd[i] && cmd[i][0] != '=')
			ft_add_env_export(ft_trim(cmd[i], 34));
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
			ft_putstr_fd("\"", ms->st_out);
			k = 1;
		}
		if (var[i + 1] == '\0' && k == 1)
			ft_putstr_fd("\"\n", ms->st_out);
		if (var[i + 1] == '\0' && k == 0)
			ft_putstr_fd("\n", ms->st_out);
		i++;
	}
}

void	ft_display_export(void)
{
	t_env	*tmp;

	tmp = g_ms->env;
	while (tmp)
	{
		write(g_ms->st_in, "declare -x ", 11);
		ft_print_export(tmp->var, g_ms);
		tmp = tmp->next;
	}
}
