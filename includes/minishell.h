/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:31:02 by amonteli          #+#    #+#             */
/*   Updated: 2021/06/28 17:28:46 by wperu            ###   ########lyon.fr   */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft/libft.h"

# define	STDIN 0
# define	STDOUT 1
# define	STDERR 2

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}							t_env;

typedef struct s_cmd
{
	char			*name;
	char			**arg;
	char			**redir;
	int				sep;
	int				end;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_tok
{
	char			*token;
	char			*redir;
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

int		main(int argc, char **argv, char **env);

void	ft_exec_cmd(char **cmd, char **env, t_mshell *ms);
void	free_array(char **array);
void	free_lst(void);
void	ft_dup_env(char **envp);
void	ft_add_env_var(char *var);
char	*ft_get_env_var(char *var);
char	**ft_lst_to_array(void);
bool	get_abs_path(char **cmd, char **envp);
void	ft_excute(t_mshell *ms, t_cmd *cmd);

// built-in

void	ft_replace_env(char *var, char *name);
void	ft_joinvar(char *var, t_env *tmp);
void	ft_print_export(char *var, t_mshell *ms);
void	built_in_export(t_cmd *cmd);
void	built_in_unset(t_cmd *cmd);
void	built_in_cd(char *path);
void	ft_change_path(char *oldpwd, char *pwd, char *pwd_ptr);
void	built_in_exit(t_cmd *cmd, t_mshell *msh);
char	*built_in_pwd(char *cmd);
void	built_in_env(t_mshell *ms);
int		exec_built_in(t_cmd *cmd, t_mshell *ms);
bool	is_built_in(char *cmd);
void	built_in_echo(t_cmd *cmd, t_mshell *ms);
void	ft_display_export(void);
void	ft_add_env_export(char *var);
void	ft_manage_add_env(char *var, t_env *tmp);
int		ft_env_size(t_env *env);
int		ft_chr(char *str, char c);
int		ft_check_env(char *var, t_env *tmp);
char	*ft_trim(char *str);
char	*ft_trimcpy(char *dst, char *str);
int		ft_check_correct_var(char *var);

//libft
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strncat(char *dest, const char *src, size_t n);
char	*ft_strndup(char *str, int n);
//redir

void	ft_init_mshell(void);
void	ft_reset_mshell(void);
int		ft_parse_redir_v2(char **cmd, t_mshell *ms);
//int		ft_redir(char **cmd, t_mshell *ms);
void	ft_pipe(t_mshell *ms, char **cmd);
void	shell_loop(void);

//signal

void	ft_signal_c(int sign);
void	ft_signal_slash(int i);
void	ft_silence(int i);
void	ft_nl(int i);
void	ft_manage_signal(int key);

//exec
int		ft_exec_cmd2(t_cmd *cmd, char**env, t_mshell *ms);
int		ft_usepath(t_cmd *cmd, char**env, t_mshell *ms, int i);

void	ft_gnl_minishell(t_mshell *ms, char **cmd, char *buffer);

// parsing
void	ft_parse(char *cmd);
char	*ft_replace_var(char *cmd, int index);
char	*ft_nstrndup(char *str, int n, int start);
int		ft_isseparator(char *cmd, int i);
int		ft_check_cote(char *cmd, int i);
int		ft_cote(char *cmd, int i);
int		ft_backslash(char *cmd, int index);

//token
void	ft_add_token(char *cmd, int i, int j);
int		ft_one_nospace(char *buffer);
//cmd

void	ft_split_cmd(t_token *tok);
void	ft_display_cmd(t_cmd *cmds);
int		ft_redir_cmd(char **arg, int *end, int *sep);
void	ft_add_cmd(t_token *tok, int i);
t_list	*read_input_from(char *key);
char	**ft_dup_cmd(char *name, char **arg, int end);
char	**ft_replace(char **cmd);

char	**ft_split_cote(char *s, char c);

char	*ft_trim(char *str);
char	*ft_trimcpy(char *dst, char *str);
void	ft_cmd_trim(t_cmd *cmd);
void	ft_tdcote(char *src, char *dst, int *i, int *j);
void	ft_tcote(char *src, char *dst, int *i, int *j);
void	ft_cpt_cote(char *str, int *i, int *cpt);
int		ft_redir2(t_token *tok);
int		ft_check_redir(char *str, int index, int i);
int		ft_fin_redir(char *str, int idx);
char	*ft_trim_redir(char *str, int cpt);
#endif
