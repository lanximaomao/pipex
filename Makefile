# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 10:03:20 by lsun              #+#    #+#              #
#    Updated: 2023/02/16 14:30:44 by lsun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

SRCS = main.c pipex.c pipex_utils.c get_path.c

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C libft all
	make -C libft bonus
	cc $(FLAGS) $(SRCS) libft/libft.a -o $(NAME)

clean:
	make -C libft clean

fclean:clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean clean all

.PHONY: all bonus clean fclean re
