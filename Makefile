# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 10:03:20 by lsun              #+#    #+#              #
#    Updated: 2023/02/23 11:22:41 by lsun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

SRCS = main.c pipex.c pipex_utils.c get_path.c
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft all
	make -C libft bonus
	cc $(FLAGS) $(OBJS) libft/libft.a -o $(NAME)

$(OBJS):
	cc -c $(FLAGS) $(SRCS)

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean:clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean clean all

.PHONY: all bonus clean fclean re
