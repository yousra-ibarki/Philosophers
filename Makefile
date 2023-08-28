# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoibarki <yoibarki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 12:10:29 by yoibarki          #+#    #+#              #
#    Updated: 2023/08/28 10:52:13 by yoibarki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = 	main.c \
		ft_atoi.c \
		ft_time.c \
		ft_check.c \
		ft_mutex.c

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME):$(OBJS) philosopher.h
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	@rm -f $(OBJS)

fclean:clean
	@rm -f $(NAME)

re: fclean all

.phony: re clean fclean all