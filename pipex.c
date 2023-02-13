/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:06:27 by linlinsun         #+#    #+#             */
/*   Updated: 2023/02/13 23:19:38 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
** allowed function: open, close, read, write, malloc, free, perror, strerror, access,
** dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
*/

/*
** ./pipex infile "ls -l" "wc -l" outfile
*/

/*
** ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
** ./pipex infile "ls -l" "cat pipex.c" "grep 3 " outfile
*/

// /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki

//inplement the perror, stdrr;
//inplement > and <

#include "pipex.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_pipex
{
	char* cmd1;
	char* cmd2;
	char** cmd1_args;
	char** cmd2_args;
	char* infile;
	char* outfile;
} t_pipex;



void find_my_path ()
{
	return;
}

//void get_cmd(char ** cmd_wth_arg)
//{
//	char *cmd_path;
//	int fd;

//	cmd_path = ft_strjoin("/bin/", cmd_wth_arg[0]);
//	fd = open("infile", O_RDWR);
//	dup2(fd, 1);
//	execve(cmd_path, cmd_wth_arg, NULL);
//	close(fd);
//}

void ft_ls()
{
	char cmd[] = "/bin/ls";
	char *argVec[] = {"ls", "-l", NULL};
	char *envVec[] = {NULL};
	if (execve(cmd, argVec, envVec) == -1)
	{
		perror("execve");
		exit(errno);
	}
}


void free_char(char** str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
	}
	free(str);
}

int get_pipe (t_pipex *pipex)
{
	int fd[2];
	int pid1;
	int pid2;
	char *cmd_path;

	if (pipe(fd) == -1)
	{
		ft_printf("cannot open a pipe.\n");
		return (1);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		ft_printf("cannot fork.\n");
		return (1);
	}
	else if (pid1 == 0) //children process for cmd1
	{
		cmd_path = ft_strjoin("/bin/", pipex->cmd1);
		if (!cmd_path)
		{
			ft_printf("cannot join this string.\n");
			return (1);
		}
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		if (execve(cmd_path, pipex->cmd1_args, NULL) == -1)
		{
			perror("execve cmd1");
			exit(errno);
		}
	}
	pid2 = fork();
	if (pid2 == -1)
		return(1);
	else if (pid2 == 0) //children process for cmd2
	{
		cmd_path = ft_strjoin("/usr/bin/", pipex->cmd2);
		if (!cmd_path)
			return(1);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		if (execve(cmd_path, pipex->cmd2_args, NULL) == -1)
		{
			perror("execve cmd2");
			exit(errno);
		}
	}
	wait(NULL);
	close(fd[0]);
	close(fd[1]);
	return(0);
}

int pipex_init(t_pipex *pipex, char** argv)
{
	pipex->infile = argv[1];
	pipex->outfile = argv[4];
	pipex->cmd1_args = ft_split(argv[2], ' ');
	if (!pipex->cmd1_args)
		exit(1);
	pipex->cmd1 = pipex->cmd1_args[0];
	pipex->cmd2_args = ft_split(argv[3], ' ');
	if (!pipex->cmd2_args)
		exit(1);
	pipex->cmd2 = pipex->cmd2_args[0];
	//ft_printf("cmd1 is: %s\n", pipex->cmd1);
	//ft_printf("cmd1 arg is: %s\n", pipex->cmd1_args[1]);
	//ft_printf("cmd2 is: %s\n", pipex->cmd2);
	//ft_printf("cmd2 arg is: %s\n", pipex->cmd2_args[1]);
	return(0);
}

void free_all(t_pipex *pipex)
{
	free_char(pipex->cmd1_args);
	free_char(pipex->cmd2_args);
	free(pipex);
}

int main(int argc, char** argv)
{
	t_pipex *pipex;

	if (argc != 5)
		exit(1);
	pipex = malloc(sizeof(t_pipex));
	if (pipex_init(pipex, argv) == 1)
		exit(1);
	if (get_pipe(pipex) == 1)
		exit(1);
	//free_all(pipex);
	return (0);
}

