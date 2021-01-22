/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 04:01:50 by amonteli          #+#    #+#             */
/*   Updated: 2020/07/17 00:23:31 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_lltoa_base(long long n, char *base)
{
	int		size;
	int		neg;
	char	*tab;

	size = ft_numlen(n);
	neg = 0;
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	if (!(tab = (char *)malloc(sizeof(char) * (size + 1 + neg))))
		return (NULL);
	if (neg)
		tab[0] = '-';
	tab[size + neg] = '\0';
	while (size)
	{
		tab[size - (neg ? 0 : 1)] = base[n % ft_strlen(base)];
		n = n / ft_strlen(base);
		size--;
	}
	return (tab);
}
