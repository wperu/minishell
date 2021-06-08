/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 13:15:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/06/08 14:42:18 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

void	free_lst(void)
{
	t_env	*index;
	t_env	*tmp;

	index = g_ms->env;
	tmp = index;
	while (index != NULL)
	{
		tmp = index;
		index = index->next;
		free(tmp->var);
		tmp->var = NULL;
		free(tmp);
		tmp = NULL;
	}
}

char	**ft_lst_to_array(void)
{
	char	**array;
	t_env	*tmp;
	int		i;

	array = NULL;
	tmp = g_ms->env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	array = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!array)
		exit(-1);
	tmp = g_ms->env;
	i = 0;
	while (tmp)
	{
		array[i] = tmp->var;
		tmp = tmp->next;
		i++;
	}
	return (array);
}
/*
char	*ft_strndup(char *str, int n)
{
	char	*tab;
	int		i;

//printf("str = %s indice = %i\n",str,n);
	tab = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < n)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	printf("tab = %s\n", tab);
	return (tab);
}*/
