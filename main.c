/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:12:14 by wperu             #+#    #+#             */
/*   Updated: 2021/01/22 16:47:07 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <errno.h>

static bool is_built_in(char *cmd)
{
    const char  *built_in[]= {"cd", "pwd", "env", NULL};
    int         i;

    i = 0;

    while(built_in[i])
    {
        if(!strcmp(built_in[i], cmd))
            return (true);
    }
    return (false);
}

static void exec_built_in(char **built_in)
{
    if (!strcmp(built_in[0], "pwd"))
        built_in_pwd();
    else if (!strcmp(built_in[0], "cd"))
        built_in_cd(built_in[1]);
    else if (!strcmp(built_in[2],))
}


int main(int argc, char **argv, char **envp)
{
    char *buffer = NULL;
    size_t buf_size = 2048;
    char **cmd = NULL;
    char *path = NULL;

    ft_dup_env(envp);
    (void)argc;
    (void)argv;
    if (!(buffer = (char *)ft_calloc(sizeof(char), buf_size)))
    {
        strerror(errno);
        return (EXIT_FAILURE);
    }
    write(1,"minishell> ",11);
    while (get_next_line(0, &buffer) > 0)
    {
        cmd = ft_split(buffer, ' ');
        if (cmd[0] == NULL)
            ft_printf("Command not found\n");
        else if (is_built_in(cmd[0]) == true)
        {
            
            path = getcwd(buffer,buf_size);
            ft_exec_cmd(cmd);
        }
        else
            exec_built_in(cmd);
        write(1,"minishell> ",11);
        free(cmd);
    }
    free(buffer);
}