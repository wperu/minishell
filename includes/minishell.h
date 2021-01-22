/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:31:02 by amonteli          #+#    #+#             */
/*   Updated: 2021/01/22 13:25:43 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/types.h>
# include "../libft/includes/libft.h"


typedef struct		s_env
{
		char				*var;
		struct s_env		*next;
}					t_env;

t_env *first = NULL;


int		main(int argc, char **argv, char **env);

void	ft_exec_cmd(char **cmd);
void    ft_dup_env(char **envp);
void	ft_add_env_var(char *var);
void	ft_get_env_var(char *var);
// built-in

void	built_in_cd(char *path);
void	built_in_pwd(void);

void	shell_loop();
#endif
