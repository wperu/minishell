/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 11:41:11 by amonteli          #+#    #+#             */
/*   Updated: 2020/07/17 00:42:15 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void			pf_convert_dbonus(t_pfinfo *p)
{
	if (p->flags & PF_L || p->flags & PF_LL)
		return (pf_convert_decimal(p, p->flags & PF_LL
		? va_arg(p->va, long long) : va_arg(p->va, long)));
	else if (p->flags & PF_H || p->flags & PF_HH)
		return (pf_convert_decimal(p, p->flags & PF_HH
		? (char)va_arg(p->va, int) : (short)va_arg(p->va, int)));
	else
		pf_convert_decimal(p, va_arg(p->va, int));
}

void			pf_convert_ubonus(t_pfinfo *p)
{
	if (p->flags & PF_L || p->flags & PF_LL)
		return (pf_convert_unsigned(p, p->flags & PF_LL
			? va_arg(p->va, long long) : va_arg(p->va, long)));
	else if (p->flags & PF_H || p->flags & PF_HH)
		return (pf_convert_unsigned(p, p->flags & PF_HH
	? (u_int8_t)va_arg(p->va, u_int32_t) :
	(u_int16_t)va_arg(p->va, u_int32_t)));
	else
		return (pf_convert_unsigned(p, va_arg(p->va, unsigned int)));
}

void			pf_convert_bonus(t_pfinfo *p)
{
	if (p->type == 'x' || p->type == 'X')
	{
		if (p->flags & PF_L || p->flags & PF_LL)
			return (pf_convert_hexa(p, p->type == 'x'
			? LOW_HEXA : UP_HEXA, p->flags & PF_LL
			? va_arg(p->va, long long) : va_arg(p->va, long)));
		else if (p->flags & PF_H || p->flags & PF_HH)
			return (pf_convert_hexa(p, p->type == 'x'
				? LOW_HEXA : UP_HEXA, p->flags & PF_HH
	? (u_int8_t)va_arg(p->va, u_int32_t) :
	(u_int16_t)va_arg(p->va, u_int32_t)));
		else
			return (pf_convert_hexa(p, p->type == 'x'
			? LOW_HEXA : UP_HEXA, va_arg(p->va, unsigned int)));
	}
	else if (p->type == 'u')
		pf_convert_ubonus(p);
}

void			pf_bind_ptr(t_pfinfo *p)
{
	t_pfcontent	*content;
	int			size;
	int			*ptr;

	if (!(ptr = va_arg(p->va, void *)))
		return ;
	content = p->content;
	size = 0;
	while (content)
	{
		size += content->size;
		content = content->next;
	}
	*ptr = size;
}
