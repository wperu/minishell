/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:36:27 by amonteli          #+#    #+#             */
/*   Updated: 2021/01/22 16:37:09 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(int args_count, char **args, char **env)
{

}

char *ft_get_env_var(char *var)
{
	t_env *tmp;
	size_t len;

	*tmp = first
	len = ft_strlen(var);
	while (tmp)
	{
		if(!ft_strncmp(var,tmp->var, len))
			return (tmp->var);
	
		tmp = tmp->next;
	}
	return(NULL);
}

void	ft_add_env_var(char *var)
{
	t_env *env1;
	t_env new;

	if(var == NULL)
		return;
	*env1 = first;
	if(!( new = (t_env *)ft_calloc(sizeof(t_env), 1)))
		return;
	new->var = var;
	new->next = NULL;
	if(env1 == NULL)
		first = new;
	else
	{
		while(env1-> next != NULL)
			env1 = env1->next;
		env1->next= new;
	}
}

void ft_dup_env(char **envp)
{
	int i;
	

	while(envp[i])
	{
		ft_add_env_var(ft_strdup(envp[i])) ;
		i++;
	}

}


/*
void ft_dup_env(char **envp)
{
    char *var_lst[];//= {"PATH", "HOME", "OLDPWD", "PWD", "SHLVL", NULL};
    size_t nb_elem;
    int i;

    i = 0;
    *var_lst[]= {"PATH", "HOME", "OLDPWD", "PWD", "SHLVL", NULL};
    nb_elem = 5;
    while (envp[i])
    {
        ft_add_tail(strdup(envp[i])));
        if (!ft_strncmp(envp[i], "PATH", 4)) 
            var_lst[0] = NULL;
        else if (!ft_strncmp(envp[i], "HOME", 4)) 
            var_lst[1] = NULL;
        else if (!ft_strncmp(envp[i], "OLDPWD", 6)) 
            var_lst[2] = NULL;
        else if (!ft_strncmp(envp[i], "PWD", 3))
             var_lst[3] = NULL;
        else if (!ft_strncmp(envp[i], "SHLVL", 5))
             var_lst[4] = NULL;
    }

	i = 0;
	while(i < nb_elem)
	{
		if(var_lst[i] != NULL)
			add_env_var(var_lst[i]);
		i++;
	}
}
*/