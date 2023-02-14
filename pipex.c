/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:06:27 by linlinsun         #+#    #+#             */
/*   Updated: 2023/02/14 17:08:05 by lsun             ###   ########.fr       */
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
** ./pipex infile "ls -l" "wc -l" outfile
*/

// /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki

//inplement the perror, stdrr;
//inplement > and <

#include "pipex.h"


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
		i++;
	}
	free(str);
}

int close_all(t_pipex *pipex, int fd1, int fd2)
{
	if (fd1 > 0)
		close(fd1);
	if (fd2 > 0)
		close(fd2);
	if (pipex->fd[0] > 0)
		close(pipex->fd[0]);
	if (pipex->fd[1] > 0)
		close(pipex->fd[1]);
	return(0);
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
		dup2(pipex->fd[0], 0);//read from infile
		dup2(fd[1], 1);
		close_all(pipex, fd[0], fd[1]);
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
		dup2(pipex->fd[1],1);
		close_all(pipex, fd[0], fd[1]);
		if (execve(cmd_path, pipex->cmd2_args, NULL) == -1)
		{
			perror("execve cmd2");
			exit(errno);
		}
	}
	wait(NULL);
	close_all(pipex, fd[0], fd[1]);
	return(0);
}

int pipex_init(t_pipex *pipex, char** argv)
{
	pipex->cmd1_args = ft_split(argv[2], ' '); //free
	if (!pipex->cmd1_args)
		exit(1);
	pipex->cmd1 = ft_strjoin("/", pipex->cmd1_args[0]);//if join fail and free
	if (!pipex->cmd1)
		exit(1);
	pipex->cmd2_args = ft_split(argv[3], ' ');
	if (!pipex->cmd2_args)
		exit(1);
	pipex->cmd2 = ft_strjoin("/", pipex->cmd2_args[0]); //if join fail and free
	if (!pipex->cmd2)
		exit(1);
	pipex->fd[0] = open(argv[1], O_RDONLY, S_IRWXU); // S_IRWXU gives user access right to the created file
	pipex->fd[1] = open(argv[4], O_WRONLY | O_CREAT, S_IRWXU);
	if (pipex->fd[0] == -1 || pipex->fd[1] == -1)
		exit(1);
	return(0);
}

void free_all(t_pipex *pipex)
{
	free_char(pipex->cmd1_args);
	free_char(pipex->cmd2_args);
	free(pipex);
}

char** get_env (char** env)
{
	int i;
	char *path;
	char** path_env;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H')
			break;
		else
			i++;
	}
	path = ft_substr(env[i], 4, ft_strlen(env[i]));//free?
	path_env = ft_split(path, ':'); // free_char?
	return(path_env);
}

void get_path(char **env, t_pipex *pipex)
{
	int i;
	char **path_env;

	i = 0;
	path_env = get_env(env);
	while (path_env[i])
	{
		pipex->cmd1_path = ft_strjoin(path_env[i], pipex->cmd1); // free
		if (access(pipex->cmd1_path, X_OK) == 0)
			break;
		i++;
	}
	i = 0;
	while (path_env[i])
	{
		pipex->cmd2_path = ft_strjoin(path_env[i], pipex->cmd2); // free
		if (access(pipex->cmd2_path, X_OK) == 0)
			break;
		i++;
	}
	ft_printf("my cmd1 path is %s\n", pipex->cmd1_path);
	ft_printf("my cmd2 path is %s\n", pipex->cmd2_path);

}

int main(int argc, char** argv, char** env)
{
	t_pipex *pipex;

	if (argc != 5)
		exit(1);
	pipex = malloc(sizeof(t_pipex));
	if (pipex_init(pipex, argv) == 1)
		exit(1);
	get_path(env, pipex);
	if (get_pipe(pipex) == 1)
		exit(1);
	free_all(pipex);
	return (0);
}

