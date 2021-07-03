# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/08 14:26:55 by amonteli          #+#    #+#              #
#    Updated: 2021/07/03 01:37:10 by wperu            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME			=		minishell

INC_DIR			=		includes

HEADERS			=		includes/minishell.h

CC				=		@gcc

CFLAGS 			= 		-Wall -Wextra -Werror #-fsanitize=address -g3

SRCS			=		\
						main.c \
						$(addprefix reader/, reader.c) \
						$(addprefix utils/, global_utils.c tools.c ft_strcmp.c ft_redir.c ft_signal.c ft_pipe.c ft_split_cote.c ft_space.c ft_redir_out.c) \
						$(addprefix built_in/, built_in.c export.c export_utils.c export_utils2.c unset.c ft_built_exit.c) \
						$(addprefix envs/, init_env.c) \
						$(addprefix exec/, ft_exec2.c ft_cmd.c) \
						$(addprefix parser/, parser.c token.c) 

OBJS			= 		$(addprefix srcs/, $(SRCS:.c=.o))

LIB 			= 		libft/libft.a $(LDFLAGS) -lreadline

all				: 		$(NAME)

$(NAME)		: $(OBJS)
		@make -C libft
		$(CC) $(CFLAGS) $(OBJS) -I $(HEADERS) $(LIB) -o $(NAME)
		@printf "%b" "\033[0;32m $(NAME) is done !$(NO_COLOR)\n"

%.o: %.c $(HEADERS)
		$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

bonus		:		$(NAME)

clean		:
		@/bin/rm -f $(OBJS)
		@make clean -C libft

fclean		:		clean
		@/bin/rm -f $(NAME)
		@make fclean -C libft

re			:		fclean all
