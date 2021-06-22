/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:04:34 by wperu             #+#    #+#             */
/*   Updated: 2021/06/22 19:16:28 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_correct_var(char *var)
{
	int	len;
	int	i;

	i = 0;
	len = ft_chr(var, '=');
	if (len != 0)
	{
		if (var[len - 1] == '+')
			len--;
	}
	while (i < len)
	{
		if ((var[i] >= '0' && var[i] <= '9') || var[i] == '_'
			|| (var[i] >= 'a' && var[i] <= 'z')
			|| (var[i] >= 'A' && var[i] <= 'Z'))
			i++;
		else
			return (0);
	}
	return (1);
}

char	*ft_trim(char *str)
{
	int		i;
	int		cpt;
	char	*dst;

	i = 0;
	cpt = 0;
	while (str[i] != '\0')
	{
		ft_cpt_cote(str, &i, &cpt);
		i++;
	}
	dst = (char *)malloc(sizeof(char) * i - cpt + 1);
	if (!dst)
		return (NULL);
	return (ft_trimcpy(dst, str));
}

char	*ft_trimcpy(char *dst, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ft_tcote(str, dst, &i, &j);
		else if (str[i] == '\"')
			ft_tdcote(str, dst, &i, &j);
		else
		{
			dst[j] = str[i];
			i++;
			j++;
		}
	}
	dst[j] = '\0';
	return (dst);
}

int	ft_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

void	ft_joinvar(char *var, t_env *tmp)
{
	int	i;

	i = ft_chr(var, '=');
	i--;
	while (tmp)
	{
		if (ft_strncmp(var, tmp->var, i) == 0)
		{
			if (ft_chr(tmp->var, '=') == (int)ft_strlen(tmp->var))
				tmp->var = ft_strjoin(tmp->var, "=");
			tmp->var = ft_strjoin(tmp->var, var + i + 2);
			break ;
		}		
		tmp = tmp->next;
	}
}
