/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:01:44 by lsun              #+#    #+#             */
/*   Updated: 2023/02/16 14:56:11 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**env;
	char	*cmd1;
	char	*cmd2;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1_args;
	char	**cmd2_args;
	int		fd[2];
}			t_pipex;

char		**get_env(char **env);
int			get_path(t_pipex *pipex);
int			get_path_cmd1(char **path_env, t_pipex *pipex);
int			get_path_cmd2(char **path_env, t_pipex *pipex);
void		free_char(char **str);
void		free_all(t_pipex *pipex);
int			close_all(t_pipex *pipex, int fd1, int fd2);

int			pipex_init(t_pipex *pipex, char **argv);
void		pipe_cmd1(t_pipex *pipex, int fd0, int fd1);
void		pipe_cmd2(t_pipex *pipex, int fd0, int fd1);
int			get_pipe(t_pipex *pipex);

#endif
