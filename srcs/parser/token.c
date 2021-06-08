/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:39:52 by wperu             #+#    #+#             */
/*   Updated: 2021/06/08 16:12:59 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_token(char *cmd, int i, int j)
{
	t_token	*tok;
	t_token	*new;

	if (cmd == NULL)
		return ;
	tok = g_ms->tok;
	new = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!new)
		return ;
	new->token = ft_nstrndup(cmd, i, j);
	new->next = NULL;
	printf("token = %s\n", new->token);
	if (tok == NULL)
		g_ms->tok = new;
	else
	{
		while (tok->next != NULL)
			tok = tok->next;
		tok->next = new;
	}
}
