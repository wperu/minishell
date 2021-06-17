# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/08 14:26:55 by amonteli          #+#    #+#              #
#    Updated: 2021/06/17 19:53:21 by emenella         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		minishell

INC_DIR			=		includes

HEADERS			=		includes/minishell.h

CC				=		gcc

CFLAGS 			= 		-Wall -Wextra #-Werror -g3 -fsanitize=address 

SRCS			=		\
						main.c \
						$(addprefix reader/, reader.c) \
						$(addprefix utils/, global_utils.c tools.c ft_strcmp.c ft_redir.c ft_signal.c) \
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

%.o: %.c $(HEADERS)
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

bonus		:		$(NAME)

clean		:
		@/bin/rm -f $(OBJS)
		@make clean -C libft

fclean		:		clean
		@/bin/rm -f $(NAME)
		@make fclean -C libft

re			:		fclean all
