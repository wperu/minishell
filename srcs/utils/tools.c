/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:19:56 by wperu             #+#    #+#             */
/*   Updated: 2021/06/08 16:20:20 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_nstrndup(char *str, int n, int start)
{
	int		i;
	int		j;
	char	*dst;

	i = start;
	j = 0;
	dst = (char *)malloc(sizeof(*dst) * (n - start) + 1);
	if (!dst)
		return (NULL);
	while (str[i] == ' ')
		i++;
	while (i < n)
	{
		dst[j] = str[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*dst;

	i = 0;
	dst = (char *)malloc(sizeof(*dst) * n + 1);
	if (!dst)
		return (NULL);
	while (i < n)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}


