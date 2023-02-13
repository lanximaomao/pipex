# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 10:03:20 by lsun              #+#    #+#              #
#    Updated: 2023/02/13 13:55:54 by lsun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

SRCS = pipex.c

CFLAGS = -c -Wall -Wextra -Werror

all: $(NAME)
	make -C libft all
	make -C libft bonus
	cc $(FLAGS) $(SRCS) libft/libft.a -o $(NAME)

clean:
	make -C libft clean

fclean:
	rm -f $(NAME)

re: fclean clean all

.PHONY: all bonus clean fclean re