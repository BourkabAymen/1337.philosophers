# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abourkab <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 20:38:08 by abourkab          #+#    #+#              #
#    Updated: 2023/02/20 20:38:13 by abourkab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

OBJ_DIR	=	obj

CC = gcc -pthread

CFLAGS = -g -fsanitize=thread

RM		= rm -rf

SRCS 	= main.c ft_ato_long.c validation.c init.c error.c time.c \
			output.c garbage_collector.c mutex.c \
			routine_finish.c routine_dining.c

OBJS	= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@$(RM) obj

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: $(NAME)
