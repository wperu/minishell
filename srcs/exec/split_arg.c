/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 15:32:23 by wperu             #+#    #+#             */
/*   Updated: 2021/06/12 16:57:24 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
static	int		ft_count_word(char const *s, char c)
{
	int	cword;
	int	i;

	i = 0;
	cword = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			cword++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (cword);
}

static	int		ft_size_word(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[size + i])
		size++;
	return (size);
}

static	void	ft_freeall(char **split, int index)
{
	int i;

	i = 0;
	while (i <= index)
	{
		free(split[i]);
		i++;
	}
}

static	char	**ft_s_split(char **split, char const *s, char c, int i)
{
	int	index;
	int	j;

	index = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			j = ft_size_word(s, c, i);
			if (!(split[index] = malloc(sizeof(char) * (j + 1))))
			{
				ft_freeall(split, index);
				return (NULL);
			}
			j = 0;
			while (s[i] && s[i] != c)
				split[index][j++] = s[i++];
			split[index++][j] = '\0';
		}
	}
	split[index] = NULL;
	return (split);
}

char	**ft_split_arg(char *token)
{
	char	**arg;

	if (!token)
		return (NULL);
	arg = malloc(sizeof(char *) * ft_cword(token) + 1);
	if (!arg)
		return (NULL);
	arg = ft_perfect_split(arg, token);
	if (!arg)
	{
		free(arg);
		return (NULL);
	}
	return (arg);
}
*/