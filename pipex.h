/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:01:44 by lsun              #+#    #+#             */
/*   Updated: 2023/02/14 17:33:27 by lsun             ###   ########.fr       */
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

char** get_env (char** env);
void get_path(char **env, t_pipex *pipex);
void free_char(char** str);
void free_all(t_pipex *pipex);
int close_all(t_pipex *pipex, int fd1, int fd2);

int pipex_init(t_pipex *pipex, char** argv);
int pipe_child(t_pipex *pipex, int fd0, int fd1);
int pipe_parent(t_pipex *pipex, int fd0, int fd1);
int get_pipe (t_pipex *pipex);

#endif
