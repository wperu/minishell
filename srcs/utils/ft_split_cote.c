/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 21:51:22 by emenella          #+#    #+#             */
/*   Updated: 2021/06/22 18:49:11 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	numstring(char *s1, char c)
{
	int	comp;
	int	cles;
	int	i;
	int	index_head;

	comp = 0;
	cles = 0;
	i = -1;
	index_head = 0;
	while (s1[++i] != '\0')
	{
		if (s1[i] == c && ft_check_cote(&s1[index_head], i - index_head))
			cles = 0;
		else if (cles == 0)
		{
			cles = 1;
			index_head = i;
			comp++;
		}
	}
	return (comp);
}

static int	numchar(char *s, char c, int i)
{
	int	lenght;

	lenght = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && ft_check_cote(s, i))
			break ;
		lenght++;
		i++;
	}
	return (lenght);
}

static char	**freee(char **dst, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)dst[j]);
	}
	free(dst);
	return (NULL);
}

static char	**fillup(char *s, char **dst, char c, int l)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < l)
	{
		k = 0;
		while (s[i] == c)
			i++;
		dst[j] = (char *)malloc(sizeof(char) * numchar(s, c, i) + 1);
		printf("len string : %d\n", numchar(s, c, i));
		if (dst[j] == NULL)
			return (freee(dst, j));
		while (s[i] != '\0' && !(s[i] == c && ft_check_cote(s, i)))
			dst[j][k++] = s[i++];
		dst[j][k] = '\0';
		j++;
	}
	dst[j] = 0;
	return (dst);
}

char	**ft_split_cote(char *s, char c)
{
	char	**result;
	int		len;

	if (s == NULL)
		return (NULL);
	len = numstring((char *)s, c);
	result = malloc(sizeof(char *) * (len + 1));
	if (result == NULL)
		return (NULL);
	return (fillup(s, result, c, len));
}
