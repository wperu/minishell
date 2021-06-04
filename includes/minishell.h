/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:31:02 by amonteli          #+#    #+#             */
/*   Updated: 2021/06/04 15:20:07 by wperu            ###   ########lyon.fr   */
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
# include <sys/stat.h>
# include "../libft/includes/libft.h"

# define	STDIN 0
# define	STDOUT 1
# define	STDERR 2

typedef struct s_redir
{
	int				fd;
	struct s_redir	*next;
}							t_redir;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}							t_env;

typedef struct s_cmd
{
	char			*name;
	char			**arg;
	int				sep;
	int				end;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_tok
{
	char			*token;
	struct s_tok	*next;
}				t_token;

typedef struct s_mshell
{
	int		pfd[2];
	int		p;
	char	**path;
	int		status;
	int		st_in;
	int		st_out;
	int		st_err;
	int		ret;
	int		ext;
	t_cmd	*cmds;
	t_env	*env;
	t_token	*tok;
}							t_mshell;

t_mshell	*g_ms;
//t_env		*first;

int		main(int argc, char **argv, char **env);

void	ft_exec_cmd(char **cmd, char **env, t_mshell *ms);
void	free_array(char **array);
void	free_lst(void);
void	ft_dup_env(char **envp);
void	ft_add_env_var(char *var);
char	*ft_get_env_var(char *var);
char	**ft_lst_to_array(void);
bool	get_abs_path(char **cmd, char **envp);
void	ft_excute(t_mshell *ms, char **cmd);

// built-in

void	ft_replace_env(char *var, char *name);
void	ft_joinvar(char *var, t_env *tmp);
void	ft_print_export(char *var, t_mshell *ms);
void	built_in_export(char **cmd);
void	built_in_unset(char **cmd);
void	built_in_cd(char *path);
void	ft_change_path(char *oldpwd, char *pwd, char *pwd_ptr);
void	built_in_exit(char **cmd, t_mshell *msh);
char	*built_in_pwd(char *cmd);
void	built_in_env(t_mshell *ms);
int		exec_built_in(char **built_in, t_mshell *ms);
bool	is_built_in(char *cmd);
void	built_in_echo(char **cmd, t_mshell *ms);
void	ft_display_export(void);
void	ft_add_env_export(char *var);
void	ft_manage_add_env(char *var, t_env *tmp);
int		ft_env_size(t_env *env);
int		ft_chr(char *str, char c);
int		ft_check_env(char *var, t_env *tmp);
char	*ft_trim(char *str, char c);
char	*ft_trimcpy(char *dst, char *str, char c);
int		ft_check_correct_var(char *var);

//libft
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strncat(char *dest, const char *src, size_t n);

//redir

void	ft_init_mshell(void);
void	ft_reset_mshell(void);
int		ft_parse_redir_v2(char **cmd, t_mshell *ms);
int		ft_redir(char **cmd, t_mshell *ms);
void	ft_pipe(t_mshell *ms, char **cmd);
void	shell_loop(void);

//signal

void	ft_signal_c(int sign);
void	ft_signal_slash(int i);
void	ft_silence(int i);
void	ft_nl(int i);
void	ft_manage_signal(int key);

//exec
int		ft_exec_cmd2(char **cmd, char**env, t_mshell *ms);
int		ft_usepath(char **cmd, char**env, t_mshell *ms, int i);

void	ft_gnl_minishell(t_mshell *ms, char **cmd, char *buffer);

// parsing
char	*ft_parse(char *cmd);
char	*ft_replace_var(char *cmd, int index);
char	*ft_strndup(char *str, int n);
char	ft_isseparator(char *cmd, int i);

#endif
