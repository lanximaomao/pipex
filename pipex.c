/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:06:27 by linlinsun         #+#    #+#             */
/*   Updated: 2023/02/16 18:17:17 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* double check with norm */
/* error catching */

#include "pipex.h"

int	pipex_init(t_pipex *pipex, char **argv)
{
	pipex->cmd1_args = ft_split(argv[2], ' ');
	if (!pipex->cmd1_args)
		exit(1);
	pipex->cmd1 = ft_strjoin("/", pipex->cmd1_args[0]);
	if (!pipex->cmd1)
		exit(1);
	pipex->cmd2_args = ft_split(argv[3], ' ');
	if (!pipex->cmd2_args)
		exit(1);
	pipex->cmd2 = ft_strjoin("/", pipex->cmd2_args[0]);
	if (!pipex->cmd2)
		exit(1);
	pipex->fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	pipex->fd[0] = open(argv[1], O_RDONLY);
	if (pipex->fd[1] == -1)
	{
		perror("Fail to create or open outfile");
		exit(1);
	}
	if (pipex->fd[0] == -1)
	{
		perror("Fail to open infile");
		exit(1);
	}
	return (0);
}

void	pipe_cmd1(t_pipex *pipex, int fd0, int fd1)
{
	dup2(pipex->fd[0], 0);
	dup2(fd1, 1);
	close_all(pipex, fd0, fd1);
	if (execve(pipex->cmd1_path, pipex->cmd1_args, pipex->env) == -1)
	{
		perror("Cannot execute the first command");
		exit (1);
	}
}

void	pipe_cmd2(t_pipex *pipex, int fd0, int fd1)
{
	dup2(fd0, 0);
	dup2(pipex->fd[1], 1);
	close_all(pipex, fd0, fd1);
	if (execve(pipex->cmd2_path, pipex->cmd2_args, pipex->env) == -1)
	{
		perror("Cannot execute the second command");
		exit(1);
	}
}

int	get_pipe(t_pipex *pipex)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid1 == 0)
		pipe_cmd1(pipex, fd[0], fd[1]);
	pid2 = fork();
	if (pid2 == -1)
		return (1);
	else if (pid2 == 0)
		pipe_cmd2(pipex, fd[0], fd[1]);
	wait(NULL);
	close_all(pipex, fd[0], fd[1]);
	return (0);
}
