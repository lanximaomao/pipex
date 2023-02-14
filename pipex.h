/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:01:44 by lsun              #+#    #+#             */
/*   Updated: 2023/02/14 17:24:26 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"

#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

# include <stdio.h>
# include <stdlib.h>

typedef struct s_pipex
{
	char* cmd1;
	char* cmd2;
	char* cmd1_path;
	char* cmd2_path;
	char** cmd1_args;
	char** cmd2_args;
	int fd[2];
} t_pipex;

#endif
