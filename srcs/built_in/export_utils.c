/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:11:20 by wperu             #+#    #+#             */
/*   Updated: 2021/06/16 19:15:57 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_env(char *var, t_env *tmp)
{
	int	len;

	len = ft_chr(var, '=');
	if (var[len - 1] == '+')
		len--;
	while (tmp)
	{
		if (ft_strncmp(var, tmp->var, len) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_change_var(char *var, t_env *tmp)
{
	int	len;

	len = ft_chr(var, '=');
	while (tmp)
	{
		if (ft_strncmp(var, tmp->var, len) == 0)
		{
			free(tmp->var);
			tmp->var = ft_strdup(var);
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_add_env_export(char *var)
{
	t_env	*tmp;
	t_env	*last;

	tmp = g_ms->env;
	last = NULL;
	if (ft_check_env(var, tmp))
		ft_manage_add_env(var, tmp);
	else
	{
		tmp = g_ms->env;
		last = malloc(sizeof(t_env));
		if (!last)
			return ;
		last->var = ft_strdup(var);
		last->next = NULL;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = last;
	}
}

void	ft_manage_add_env(char *var, t_env *tmp)
{
	if (var[ft_chr(var, '=') - 1] == '+')
		ft_joinvar(var, tmp);
	else if (var[ft_chr(var, '=') - 1] != '+'
		&& ft_chr(var, '+') < ft_chr(var, '='))
		printf("minishell: export: `%s': not a valid identifier\n", var);
	else
		ft_change_var(var, tmp);
}
